#ifndef STRAVAACTIVITIES_H
#define STRAVAACTIVITIES_H

#include <QObject>
#include <QSharedDataPointer>
#include <QJsonDocument>
#include "stravarangesummary.h"

#include "deepstats_global.h"

class StravaActivitiesPrivate;

class DEEPSTATS_EXPORT StravaActivities : public QObject
{
    Q_OBJECT
public:
    enum class SortField
    {
        rideNumber,
        startDate,
        distance,
        movingTime,
        elapsedTime,
        averageSpeed
    };

    explicit StravaActivities(const QJsonDocument& jsonBlob = QJsonDocument(), QObject *parent = 0);
    ~StravaActivities();

    StravaActivities(const StravaActivities &);
    StravaActivities &operator=(const StravaActivities &);

    int numActivities() const;
    StravaActivity getActivityAtIndex(int index) const;

    StravaRangeSummary summarizeDateRange(const QDateTime& startRange, const QDateTime& endRange);

    void sortBy(SortField sortField = SortField::rideNumber, bool dump=false);

    // Use this endPoint to populate this object with ALL rides,
    // all the time, and then do date-range manipulation using
    // the in-memory objects...
    static QString getEndPointForAllTime();

protected:
    void myParseJsonBlob();

private:
    QSharedDataPointer<StravaActivitiesPrivate> d_ptr;
};

#endif // STRAVAACTIVITIES_H
