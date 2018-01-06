#include "stravastats.h"
#include <QJsonObject>

#include <QLoggingCategory>

static QLoggingCategory loggingCategory("Strava.Stats");

class StravaStatsPrivate : public QSharedData
{
public:
    StravaStatsPrivate()
        : myBiggestRideDistance(-1.0)
    {}

public:
    QJsonDocument   myJsonBlob;
    double          myBiggestRideDistance;
    QVariantMap     myRecentRideTotals;
    QVariantMap     myYtdRideTotals;
    QVariantMap     myAllRideTotals;
};

StravaStats::StravaStats(const QJsonDocument& jsonBlob, QObject *parent)
    : QObject(parent)
    , d_ptr(new StravaStatsPrivate)
{
    d_ptr->myJsonBlob = jsonBlob;
    myParseJsonBlob();
}

void StravaStats::myParseJsonBlob()
{
    if (d_ptr->myJsonBlob.isObject())
    {
        qCDebug(loggingCategory) << "It's an OBJECT";

        QJsonObject jsonObj;
        jsonObj = d_ptr->myJsonBlob.object();

        QVariantMap map = jsonObj.toVariantMap();

//        // Diag. dump only...
//        for(int i = 0; i < vals.keys().size(); i++)
//        {
//            QString key = vals.keys().at(i);
//            qCDebug(loggingCategory) << key << vals[key];
//        }

        if (map.contains("biggest_ride_distance"))
        {
            d_ptr->myBiggestRideDistance = map["biggest_ride_distance"].toDouble();
        }

        if (map.contains("recent_ride_totals"))
        {
            d_ptr->myRecentRideTotals = map["recent_ride_totals"].toMap();
        }

        if (map.contains("ytd_ride_totals"))
        {
            d_ptr->myYtdRideTotals = map["ytd_ride_totals"].toMap();
        }

        if (map.contains("all_ride_totals"))
        {
            d_ptr->myAllRideTotals = map["all_ride_totals"].toMap();
        }
    }
    else if (d_ptr->myJsonBlob.isArray())
    {
        qCDebug(loggingCategory) << "It's an ARRAY";
    }
    else
    {
        qCDebug(loggingCategory) << "It's NEITHER";
    }
}

StravaStats::StravaStats(const StravaStats &rhs)
    : d_ptr(rhs.d_ptr)
{

}

StravaStats &StravaStats::operator=(const StravaStats &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

StravaStats::~StravaStats()
{

}

double StravaStats::getBiggestRideDistance() const
{
    return d_ptr->myBiggestRideDistance;
}

QVariant StravaStats::getStat(const QString& key, StravaTimePeriod epoch)
{
    QVariant retVal;

    if (epoch == RECENT)
    {
        retVal = d_ptr->myRecentRideTotals[key];
    }
    else if (epoch == YTD)
    {
        retVal = d_ptr->myYtdRideTotals[key];
    }
    else if (epoch == ALLTIME)
    {
        retVal = d_ptr->myAllRideTotals[key];
    }

    return retVal;
}
