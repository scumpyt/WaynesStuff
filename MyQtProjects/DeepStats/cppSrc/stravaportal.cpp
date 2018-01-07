#include "stravaportal.h"

#include <QLoggingCategory>

static QLoggingCategory loggingCategory("Strava.Portal");

StravaPortal::StravaPortal(QObject *parent)
    : QObject(parent)
    , myStravaActivities(nullptr)
{
    // Move to config file???
    myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    myId           = "10883156";

    myGetEverythingEndPoint = StravaActivities::getEndPointForAllTime();

    myStravaAccess = new StravaAccess();
    connect(myStravaAccess, SIGNAL(jsonReceived  (const QUrl&, const QJsonDocument&)),
            this,           SLOT  (onJsonReceived(const QUrl&, const QJsonDocument&)));

    myActivitiesModel = new PortalActivitiesModel();
    connect(myActivitiesModel,  SIGNAL(activitiesLoaded()),
            this,               SIGNAL(activitiesModelUpdated()));
}

StravaPortal::~StravaPortal()
{
    if (myStravaAccess)     delete myStravaAccess;
    if (myActivitiesModel)  delete myActivitiesModel;
    if (myStravaActivities) delete myStravaActivities;
}

PortalActivitiesModel* StravaPortal::portalActivitiesModel() const
{
    // This is questionable... breaks encapsulation...
    return myActivitiesModel;
}

void StravaPortal::fetchActivities()
{
    if (!myStravaAccess->APICall(myGetEverythingEndPoint, myAccessToken))
    {
        qCWarning(loggingCategory) << "API CALL FAILED!!!";
        return;
    }
}

void StravaPortal::onJsonReceived(const QUrl& requestUrl, const QJsonDocument& json)
{
    qCDebug(loggingCategory) << "onJsonReceived: " << requestUrl;
    if (requestUrl.toString().endsWith(myGetEverythingEndPoint))
    {
        // then expect ALL activities...
        if (myStravaActivities) delete myStravaActivities;

        myStravaActivities = new StravaActivities(json);
        myActivitiesModel->reload(*myStravaActivities);
    }
}

void StravaPortal::summarize(const QString& startDateStr, const QString& endDateStr)
{
    qCDebug(loggingCategory) << "summarize: FROM " << startDateStr << " TO " << endDateStr;

    if (!myStravaActivities)
    {
        qCWarning(loggingCategory) << "No activities set yet!!!";
        return;
    }

    QDateTime sDate (QDate::fromString(startDateStr, "yyyy-MMM-dd"));
    QDateTime eDate (QDate::fromString(endDateStr, "yyyy-MMM-dd"));

    if (sDate.isValid() && eDate.isValid())
    {
        mySummary = myStravaActivities->summarizeDateRange(sDate, eDate);
        newSummaryAvailable();
    }
    else
    {
        qCWarning(loggingCategory) << "Dates invalid!!!";
    }
}

QVariantMap StravaPortal::getSummaryVMap() const
{
    // get the current summary and return it in a form usable in QML
    QVariantMap map;

    //QString totDistStr = QString("%1").arg((mySummary.totalDist()/1000.0),0,'f',2);

    map.insert("totalRides",            mySummary.totalRides());
    map.insert("totalDist",             QString("%1").arg((mySummary.totalDist()/1000.0),0,'f',2));
    map.insert("avgDist",               QString("%1").arg((mySummary.avgDist()/1000.0),0,'f',2));
    map.insert("medianDist",            QString("%1").arg((mySummary.medianDist()/1000.0),0,'f',2));
    map.insert("totalMovingTime",       mySummary.totalMovingTime());
    map.insert("avgMovingTime",         mySummary.avgMovingTime());
    map.insert("medianMovingTime",      mySummary.medianMovingTime());
    map.insert("totalMovingTimeHMS",    mySummary.totalMovingTimeHMS());
    map.insert("avgMovingTimeHMS",      mySummary.avgMovingTimeHMS());
    map.insert("medianMovingTimeHMS",   mySummary.medianMovingTimeHMS());
    map.insert("totalElapsedTime",      mySummary.totalElapsedTime());
    map.insert("avgSpeedKMsPerHour",    mySummary.avgSpeedKMsPerHour());
    map.insert("longestRideDist",       QString("%1").arg((mySummary.longestRideDist()/1000.0),0,'f',2));
    map.insert("longestRideTimeHMS",    mySummary.longestRideTimeHMS());

    return map;
}

void StravaPortal::sort(const QString& sortFieldStr)
{
    // Figure out how get 'currently selected column'...


    if (sortFieldStr.toUpper() == "DATE")   // MAKE THESE NAMES GLOBAL AND USE THEM FROM BOTH
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::startDate);
    }
    else if (sortFieldStr.toUpper() == "DISTANCE")
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::distance);
    }
    else if (sortFieldStr.toUpper() == "MOVING TIME")
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::movingTime);
    }
    else if (sortFieldStr.toUpper() == "ELAPSED TIME")
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::elapsedTime);
    }
    else if (sortFieldStr.toUpper() == "AVERAGE SPD")
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::averageSpeed);
    }
    else
    {
        myActivitiesModel->sortBy(StravaActivities::SortField::rideNumber);
    }
}
