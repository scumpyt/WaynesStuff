#include "stravaactivities.h"
#include "stravaactivity.h"
#include <QLoggingCategory>

#include <vector>
#include <algorithm>

#include <QJsonObject>
#include <QJsonArray>

static QLoggingCategory loggingCategory("Strava.Activities");

class StravaActivitiesPrivate : public QSharedData
{
//public:
//    StravaActivitiesPrivate() {}

public:
    QJsonDocument           myJsonBlob;
    //QVector<StravaActivity> myActivities;
    std::vector<StravaActivity> myActivities;
};

StravaActivities::StravaActivities(const QJsonDocument& jsonBlob, QObject *parent)
    : QObject(parent)
    , d_ptr(new StravaActivitiesPrivate)
{
    d_ptr->myJsonBlob = jsonBlob;
    if (!d_ptr->myJsonBlob.isEmpty() && !d_ptr->myJsonBlob.isNull())
    {
        myParseJsonBlob();
    }
}

void StravaActivities::myParseJsonBlob()
{
    // Should be an array...
    if (d_ptr->myJsonBlob.isArray())
    {
        qCDebug(loggingCategory) << "Activities: It's an ARRAY";

        QJsonArray jsonArray = d_ptr->myJsonBlob.array();
        QVariantList vList = jsonArray.toVariantList();

        qCDebug(loggingCategory) << "TOTAL Activities found = " << vList.size();

        foreach(QVariant v, vList)
        {
            if (v.canConvert<QVariantMap>())
            {
                QVariantMap map = v.toMap();

//                // Diag. dump only...
//                for(int i = 0; i < map.keys().size(); i++)
//                {
//                    QString key = map.keys().at(i);
//                    qCDebug(loggingCategory) << key << map[key];
//                }

//                int workoutType = map["workout_type"].toInt();
//                if (workoutType < 10 || workoutType > 12) continue;     // Skip non-rides...

                if (map["type"].toString() != "Ride") continue;     // Skip non-rides...

//                if (map.contains("type"))
//                {
//                    qCDebug(loggingCategory) << "TYPE FOUND = " << map["type"];
//                    if (map["type"].toString() != "Ride") continue;     // Skip non-rides...
//                }
//                else
//                {
//                    qCDebug(loggingCategory) << "TYPE NOT FOUND";
//                }

                int curId = 10883156;   // Figure this one out later...

                // Example: 2016-08-17T21:07:54Z     it's UTC...
                QString tStr = map["start_date"].toString();
                //qCDebug(loggingCategory) << "TSTR = " << tStr;
                QDateTime curDate = QDateTime::fromString(tStr, Qt::ISODate);

                double dist     = map["distance"].toDouble();
                int movingTime  = map["moving_time"].toInt();
                int elapsedTime = map["elapsed_time"].toInt();
                double avgSpeed = map["average_speed"].toDouble();

                StravaActivity curActivity(curId, curDate, dist,
                                           movingTime, elapsedTime, avgSpeed);

                //qCDebug(loggingCategory) << curActivity;

                //d_ptr->myActivities.append(curActivity);      // QVector vesion...
                d_ptr->myActivities.push_back(curActivity);     // std::vector version...
            }
        }

        qCDebug(loggingCategory) << "TOTAL Rides found = " << d_ptr->myActivities.size();
    }
    else if (d_ptr->myJsonBlob.isObject())
    {
        qCDebug(loggingCategory) << "Activities: It's an OBJECT";
    }
    else
    {
        qCDebug(loggingCategory) << "Activities: It's NEITHER";
    }
}

StravaActivities::StravaActivities(const StravaActivities &rhs)
    : d_ptr(rhs.d_ptr)
{

}

StravaActivities &StravaActivities::operator=(const StravaActivities &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

StravaActivities::~StravaActivities()
{

}

int StravaActivities::numActivities() const
{
    return (int)d_ptr->myActivities.size();
}

StravaRangeSummary StravaActivities::summarizeDateRange(const QDateTime &startRange, const QDateTime &endRange)
{
    // Ignore the TIME's for this, and just use the DATE's...

    StravaRangeSummary summ;
    //qCDebug(loggingCategory) << "++++++++++++++++++++++++ SUMMARIZE +++++++++++++++++++++++++++++++++";
    foreach(StravaActivity sa, d_ptr->myActivities)
    {
        if (sa.getStartDateLocal().date() >= startRange.date() &&
            sa.getStartDateLocal().date() <= endRange.date())
        {
            //qCDebug(loggingCategory) << sa.getStartDateLocal().date();
            summ.addRide(sa);
        }
    }
    //qCDebug(loggingCategory) << "++++++++++++++++++++++++ DONE SUMMARIZE +++++++++++++++++++++++++++++";
    return summ;
}

QString StravaActivities::getEndPointForAllTime()
{
    QDateTime theEpoch (QDate(1970, 1, 1));
    qint64 secondsSinceEpoch = theEpoch.toMSecsSinceEpoch() / 1000;

    qCDebug(loggingCategory) << "Secs since epoch = " << secondsSinceEpoch;

    QString endPoint = QString("athlete/activities?after=%1&per_page=200").arg(secondsSinceEpoch);
    return endPoint;
}

StravaActivity StravaActivities::getActivityAtIndex(int index) const
{
    if (index < 0 || index >= d_ptr->myActivities.size())
    {
        return StravaActivity();
    }
    return d_ptr->myActivities.at(index);
}

void StravaActivities::sortBy(SortField sortField, bool dump)
{
    switch (sortField)
    {
    case SortField::startDate:
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getStartDate() < b.getStartDate(); }
                  );
        break;

    case SortField::distance:
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getDistance() < b.getDistance(); }
                  );
        break;

    case SortField::movingTime:
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getMovingTime() < b.getMovingTime(); }
                  );
        break;

    case SortField::elapsedTime:
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getElapsedTime() < b.getElapsedTime(); }
                  );
        break;

    case SortField::averageSpeed:
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getAverageSpeed() < b.getAverageSpeed(); }
                  );
        break;

    default:
    case SortField::rideNumber:     // THIS NEEDS WORK!!!
        std::sort (d_ptr->myActivities.begin(), d_ptr->myActivities.end(),
                   [](StravaActivity a, StravaActivity b)
                        { return a.getStartDate() < b.getStartDate(); }
                  );
        break;
    }

    if (dump)
    {
        for (auto a: d_ptr->myActivities)
        {
            qCDebug(loggingCategory) << a;
        }
    }
}
