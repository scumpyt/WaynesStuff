#include "stravarangesummary.h"
#include <QVector>
#include <QLoggingCategory>
#include <algorithm>

#include <QDebug>

static QLoggingCategory loggingCategory("Strava.RangeSummary");

class StravaRangeSummaryPrivate
    : public QSharedData
{
public:
    StravaRangeSummaryPrivate(const QDateTime& startDate,const QDateTime& endDate)
        : myStartDate(startDate)
        , myEndDate(endDate)
    {}
public:
    QDateTime               myStartDate;
    QDateTime               myEndDate;
    QVector<StravaActivity> myRides;
};

StravaRangeSummary::StravaRangeSummary(const QDateTime& startDate,
                                       const QDateTime& endDate,
                                       QObject *parent)
    : QObject(parent)
    , d_ptr(new StravaRangeSummaryPrivate(startDate, endDate))
{

}

StravaRangeSummary::StravaRangeSummary(const StravaRangeSummary &rhs)
    : d_ptr(rhs.d_ptr)
{

}

StravaRangeSummary &StravaRangeSummary::operator=(const StravaRangeSummary &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

StravaRangeSummary::~StravaRangeSummary()
{

}

void StravaRangeSummary::addRide(const StravaActivity &ride)
{
    // Add logic to ensure date IS within range...
    d_ptr->myRides.append(ride);
}

QDateTime StravaRangeSummary::startDate() const
{
    return d_ptr->myStartDate;
}

QDateTime StravaRangeSummary::endDate() const
{
    return d_ptr->myEndDate;
}

int StravaRangeSummary::totalRides() const
{
    return d_ptr->myRides.count();
}

double StravaRangeSummary::totalDist() const
{
    double tot = 0.0;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        tot += sa.getDistance();
    }
    return tot;
}

double StravaRangeSummary::avgDist() const
{
    double totDist = totalDist();
    int    nRides  = totalRides();

    if (nRides > 0)
    {
        return totDist / nRides;
    }
    return 0.0;
}

double StravaRangeSummary::medianDist() const
{
    if (d_ptr->myRides.count() <= 0) return 0.0;

    // Populate vector with all dists...
    QVector<double> vect;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        vect.append(sa.getDistance());
    }

    // Sort vector...
    std::sort(vect.begin(), vect.end());

    // Return 'mid' value...
    double median = vect.size()%2
            ? vect[vect.size() / 2]
            : ((double)vect[vect.size() / 2 - 1] + vect[vect.size() / 2]) * .5;

    return median;
}

int StravaRangeSummary::totalMovingTime() const
{
    int tot = 0;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        tot += sa.getMovingTime();

    }
    return tot;
}

int StravaRangeSummary::avgMovingTime() const
{
    int totMTime = totalMovingTime();
    int nRides   = totalRides();
    if (nRides > 0)
    {
        return totMTime / nRides;
    }
    return 0;
}

int StravaRangeSummary::medianMovingTime() const
{
    if (d_ptr->myRides.count() <= 0) return 0;

    // Populate vector with all dists...
    QVector<int> vect;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        vect.append(sa.getMovingTime());
    }

    // Sort vector...
    std::sort(vect.begin(), vect.end());

    // Return 'mid' value...
    int median = vect.size()%2
            ? vect[vect.size() / 2]
            : ((double)vect[vect.size() / 2 - 1] + vect[vect.size() / 2]) * .5;

    return median;
}

QString StravaRangeSummary::totalMovingTimeHMS() const
{
    int tot = totalMovingTime();
    return myConvertToHMS(tot);
}

QString StravaRangeSummary::avgMovingTimeHMS() const
{
    int tot = avgMovingTime();
    return myConvertToHMS(tot);
}

QString StravaRangeSummary::medianMovingTimeHMS() const
{
    int tot = medianMovingTime();
    return myConvertToHMS(tot);
}

QString StravaRangeSummary::myConvertToHMS(int mTime) const
{
    if (mTime <= 0 || mTime < 86400)    // 86400 is # of seconds in a day..
    {
        QTime tm = QTime(0,0,0).addSecs(mTime);
        return (tm.toString("HH:mm:ss"));
    }
    else
    {
        int hh = mTime / 60 / 60;
        int mm = (mTime - (hh*60*60)) / 60;
        int ss = mTime - ((hh*60*60) + (mm * 60));
        return QString("%1:%2:%3").arg(hh,2,10,QLatin1Char('0'))
                                  .arg(mm,2,10,QLatin1Char('0'))
                                  .arg(ss,2,10,QLatin1Char('0'));
    }
}

int StravaRangeSummary::totalElapsedTime() const
{
    int tot = 0;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        tot += sa.getElapsedTime();
    }
    return tot;
}

double StravaRangeSummary::avgSpeedKMsPerHour() const
{
    double tot = 0.0;
    foreach(StravaActivity sa, d_ptr->myRides)
    {
        //tot += sa.getAverageSpeed();
        tot += sa.getAverageSpeedKMsPerHr();
    }

    if (d_ptr->myRides.count() > 0)
    {
        tot = tot / d_ptr->myRides.count();
    }

    return tot;
}

//StravaActivity StravaRangeSummary::longestRide() const
//{
//    StravaActivity longest;

//    foreach(StravaActivity sa, d_ptr->myRides)
//    {
//        if (sa.getDistance() > longest.getDistance())
//        {
//            longest = sa;
//        }
//    }

//    return longest;
//}

double StravaRangeSummary::longestRideDist() const
{
    StravaActivity longest;

    foreach(StravaActivity sa, d_ptr->myRides)
    {
        if (sa.getDistance() > longest.getDistance())
        {
            longest = sa;
        }
    }

    //return longest.getDistInKms();
    return longest.getDistance();
}

QString StravaRangeSummary::longestRideTimeHMS() const
{
    StravaActivity longest;

    foreach(StravaActivity sa, d_ptr->myRides)
    {
        if (sa.getDistance() > longest.getDistance())
        {
            longest = sa;
        }
    }


    int tot = longest.getMovingTime();
    QTime tm = QTime(0,0,0).addSecs(tot);
    return (tm.toString("HH:mm:ss"));
}

//QDebug operator<<(QDebug os, const StravaRangeSummary& theSummary)
//{
//    os << "\n------------------------------------------" << "\n"
//       << "Num Rides    = " << theSummary.totalRides()  << "\n"
//       << "Total Dist   = " << theSummary.totalDist()  << "\n"
//       << "Total MTime  = " << theSummary.totalMovingTime()  << "\n"
//       << "Total ETime  = " << theSummary.totalElapsedTime()  << "\n"
//       << "AvgSpd       = " << theSummary.avgSpeed()  << "\n"
//       << "Longest Ride = " << theSummary.longestRide().getDistance() << "\n"
//       << "------------------------------------------" << "\n";

//    return os;
//}
