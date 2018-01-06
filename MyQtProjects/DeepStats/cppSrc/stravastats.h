#ifndef STRAVASTATS_H
#define STRAVASTATS_H

#include <QObject>
#include <QSharedDataPointer>
#include <QVariant>
#include <QJsonDocument>

#include "deepstats_global.h"

class StravaStatsPrivate;
//class StravaStats;
//typedef QExplicitlySharedDataPointer<StravaStats> SharedStravaStats;

class DEEPSTATS_EXPORT StravaStats : public QObject //, public QSharedData
{
    Q_OBJECT
public:
    enum StravaTimePeriod
    {
        UNKNOWN   = 1,
        RECENT,
        YTD,
        ALLTIME
    };
    Q_ENUM(StravaTimePeriod)

    explicit StravaStats(const QJsonDocument& jsonBlob, QObject *parent = 0);
   ~StravaStats();

    StravaStats(const StravaStats &);
    StravaStats &operator=(const StravaStats &);

    double getBiggestRideDistance() const;

    QVariant getStat(const QString& key, StravaTimePeriod epoch);

protected:
    void myParseJsonBlob();

private:
    QSharedDataPointer<StravaStatsPrivate> d_ptr;
};

//Q_DECLARE_METATYPE(SharedStravaStats)
//Q_DECLARE_METATYPE(StravaStats*)

#endif // STRAVASTATS_H
