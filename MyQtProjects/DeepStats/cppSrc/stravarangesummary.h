#ifndef STRAVARANGESUMMARY_H
#define STRAVARANGESUMMARY_H

#include <QObject>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QDebug>

#include "stravaactivity.h"

#include "deepstats_global.h"

class StravaRangeSummaryPrivate;

class DEEPSTATS_EXPORT StravaRangeSummary : public QObject
{
    Q_OBJECT
public:
    explicit StravaRangeSummary(const QDateTime& startDate = QDateTime(),
                                const QDateTime& endDate = QDateTime(),
                                QObject *parent = 0);
    StravaRangeSummary(const StravaRangeSummary &);
    StravaRangeSummary &operator=(const StravaRangeSummary &);
    ~StravaRangeSummary();

    void            addRide(const StravaActivity& ride);

    QDateTime       startDate() const;
    QDateTime       endDate() const;

    int             totalRides() const;
    double          totalDist() const;
    double          avgDist() const;
    double          medianDist() const;
    int             totalMovingTime() const;
    int             avgMovingTime() const;
    int             medianMovingTime() const;
    QString         totalMovingTimeHMS() const;
    QString         avgMovingTimeHMS() const;
    QString         medianMovingTimeHMS() const;
    int             totalElapsedTime() const;
    double          avgSpeedKMsPerHour() const;
    double          longestRideDist() const;
    QString         longestRideTimeHMS() const;

    //friend QDebug operator<<(QDebug os, const StravaRangeSummary& theSummary);

protected:
    QString         myConvertToHMS(int mTime) const;

private:
    QSharedDataPointer<StravaRangeSummaryPrivate> d_ptr;
};

#endif // STRAVARANGESUMMARY_H
