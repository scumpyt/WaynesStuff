#include "stravaactivity.h"

#include <QDebug>

class StravaActivityPrivate : public QSharedData
{
public:
    StravaActivityPrivate(int atheleteId, const QDateTime& startDate,
                          double dist, int movingTime,
                          int elapsedTime, double avgSpeed)
        : myAthleteId(atheleteId)
        , myStartDate(startDate)
        , myDistance(dist)
        , myMovingTime(movingTime)
        , myElapsedTime(elapsedTime)
        , myAvgSpeed(avgSpeed)
    {}

public:
    int         myAthleteId;
    QDateTime   myStartDate;    // UTC
    double      myDistance;     // in meters
    int         myMovingTime;   // in Seconds
    int         myElapsedTime;  // in seconds
    double      myAvgSpeed;     // in meters per second
};

StravaActivity::StravaActivity(int atheleteId, const QDateTime& startDate,
                               double dist, int movingTime,
                               int elapsedTime, double avgSpeed,
                               QObject *parent)
    : QObject(parent)
    , d_ptr(new StravaActivityPrivate(atheleteId, startDate,
                                      dist, movingTime,
                                      elapsedTime, avgSpeed))
{

}

StravaActivity::StravaActivity(const StravaActivity &rhs) : d_ptr(rhs.d_ptr)
{

}

StravaActivity &StravaActivity::operator=(const StravaActivity &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

StravaActivity::~StravaActivity()
{

}

int StravaActivity::getAtheleteId() const
{
    return d_ptr->myAthleteId;
}

QDateTime StravaActivity::getStartDate() const
{
    return d_ptr->myStartDate;
}

QDateTime StravaActivity::getStartDateLocal() const
{
    return d_ptr->myStartDate.toLocalTime();
}

double StravaActivity::getDistance() const
{
    return d_ptr->myDistance;
}

double StravaActivity::getDistInKms() const
{
    return d_ptr->myDistance / 1000.0;
}

int StravaActivity::getMovingTime() const
{
    return d_ptr->myMovingTime;
}

int StravaActivity::getElapsedTime() const
{
    return d_ptr->myElapsedTime;
}

double StravaActivity::getAverageSpeed() const
{
    return d_ptr->myAvgSpeed;
}

double StravaActivity::getAverageSpeedKMsPerHr() const
{
    return getAverageSpeed() * 3.6;
}

QDebug operator<<(QDebug os, const StravaActivity& sa)
{
    os << "\n------------------------------------------" << "\n"
       << "ID           = " << sa.getAtheleteId()  << "\n"
       << "Date(UTC)    = " << sa.getStartDate().toString(Qt::ISODate) << "\n"
       << "Dist(Kms)    = " << sa.getDistInKms() << "\n"
       << "mTime(secs)  = " << sa.getMovingTime() << "\n"
       << "eTime(secs)  = " << sa.getElapsedTime() << "\n"
       << "avgSpd(m/sec)= " << sa.getAverageSpeed() << "\n"
       << "------------------------------------------" << "\n";

    return os;
}
