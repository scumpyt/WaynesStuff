#ifndef STRAVAACTIVITY_H
#define STRAVAACTIVITY_H

#include <QObject>
#include <QSharedDataPointer>
#include <QDateTime>

class StravaActivityPrivate;

class StravaActivity : public QObject
{
    Q_OBJECT
public:
    explicit StravaActivity(int atheletId = -1,
                            const QDateTime& startDate = QDateTime(),
                            double dist = 0.0, int movingTime = 0,
                            int elapsedTime = 0, double avgSpeed = 0.0,
                            QObject *parent = 0);
    StravaActivity(const StravaActivity &);
    StravaActivity &operator=(const StravaActivity &);
    ~StravaActivity();

    int         getAtheleteId() const;
    QDateTime   getStartDate() const;
    QDateTime   getStartDateLocal() const;
    double      getDistance() const;
    double      getDistInKms() const;
    int         getMovingTime() const;
    int         getElapsedTime() const;
    double      getAverageSpeed() const;    // Meters/second
    double      getAverageSpeedKMsPerHr() const;

    friend QDebug operator<<(QDebug os, const StravaActivity& sa);

private:
    QSharedDataPointer<StravaActivityPrivate> d_ptr;
};

#endif // STRAVAACTIVITY_H
