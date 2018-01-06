#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include "stravaactivitiesut.h"
#include "stravaactivities.h"
#include "stravaaccess.h"
#include "stravarangesummary.h"

StravaActivitiesUT::StravaActivitiesUT()
{
    myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    myId           = "10883156";
}

void StravaActivitiesUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void StravaActivitiesUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void StravaActivitiesUT::init()
{
    // Runs before each test...
}

void StravaActivitiesUT::cleanup()
{
    // Runs at the end of each test...
}

void StravaActivitiesUT::testGetDefault()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint;
    endPoint = "activities";

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    StravaActivities sAct(args.at(1).toJsonDocument());

    qDebug() << "NUM RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() <= 30);
}

void StravaActivitiesUT::testGetAll()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

//    ////////////////////////// AFTER /////////////////////////////////
//    // Create a date for start of year...
//    QDateTime janFirst (QDate(2016, 1, 1));
//    qint64 secondsSinceEpoch = janFirst.toMSecsSinceEpoch() / 1000;

//    QString endPoint;
//    endPoint = QString("athlete/activities?after=%1").arg(secondsSinceEpoch);
//    ///////////////////////////////////////////////////////////

//    ////////////////////////// AFTER (ALL TIME) /////////////////////////////////
//    // Create a date for start of year...
//    QDateTime theEpoch (QDate(1970, 1, 1));
//    qint64 secondsSinceEpoch = theEpoch.toMSecsSinceEpoch() / 1000;

//    QString endPoint;
//    endPoint = QString("athlete/activities?after=%1&per_page=200").arg(secondsSinceEpoch);
//    ///////////////////////////////////////////////////////////

//    ////////////////////////////// BEFORE /////////////////////////////
//    // Create a date for tomorrow...
//    QDateTime janFirst (QDate(2016, 1, 1));
//    qint64 secondsSinceEpoch = janFirst.toMSecsSinceEpoch() / 1000;

//    QString endPoint;
//    endPoint = QString("athlete/activities?before=%1").arg(secondsSinceEpoch);
//    ///////////////////////////////////////////////////////////

//    ///////////////////////////// PER_PAGE ////////////////////////////////
//    // This works, but only seems to retrieve the current years stuff???
//    QString endPoint;
//    endPoint = QString("athlete/activities?per_page=200");
//    /////////////////////////////////////////////////////////////

    QString endPoint = StravaActivities::getEndPointForAllTime();

    qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    StravaActivities sAct(args.at(1).toJsonDocument());

    qDebug() << "NUM RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 30);
}

void StravaActivitiesUT::testGetYTD()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    ////////////////////////// AFTER /////////////////////////////////
    // Create a date for start of year...
    QDateTime janFirst (QDate(2016, 1, 1));
    qint64 secondsSinceEpoch = janFirst.toMSecsSinceEpoch() / 1000;

    QString endPoint;
    endPoint = QString("athlete/activities?after=%1&per_page=200").arg(secondsSinceEpoch);
    ///////////////////////////////////////////////////////////

    qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    StravaActivities sAct(args.at(1).toJsonDocument());

    qDebug() << "NUM RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 30);
}

void StravaActivitiesUT::testSummarizeDateRange()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    // Create StravaActivities with ALL rides...
    StravaActivities sAct(args.at(1).toJsonDocument());

    //qDebug() << "NUM TOTAL RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 40);

    // Now get summary for month of July, 2016...
    QDateTime startRange (QDate(2016,7,1),QTime(0,0));
    QDateTime endRange   (QDate(2016,8,1),QTime(0,0));

    StravaRangeSummary theSummary = sAct.summarizeDateRange(startRange, endRange);

    qDebug() << "JULY - # rides = " << theSummary.totalRides();
    qDebug() << "JULY - # dist  = " << theSummary.totalDist();
    qDebug() << "JULY - # mTime = " << theSummary.totalMovingTime();
    qDebug() << "JULY - # eTime = " << theSummary.totalElapsedTime();

    //qDebug() << theSummary;

    QVERIFY(theSummary.totalRides() == 10);
}

void StravaActivitiesUT::testSummarizeWeeks()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    // Create StravaActivities with ALL rides...
    StravaActivities sAct(args.at(1).toJsonDocument());

    //qDebug() << "NUM TOTAL RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 40);

    QDateTime today = QDateTime::currentDateTime();

    QDateTime startRange (QDate(2016,3,14),QTime(0,0));     // Weeks are Mon-Sun

    while (startRange < today)
    {
        QDateTime endRange = startRange.addDays(7);

        StravaRangeSummary summ = sAct.summarizeDateRange(startRange, endRange);

        qDebug() << startRange.date().toString() << " to "
                 << endRange.date().toString()   << " "
                 << summ.totalRides() << " "
                 << summ.totalDist() / 1000.0 << " "
                 << summ.avgDist() / 1000.0 << " "
                 << summ.longestRideDist();
                 //<< summ.longestRide().getDistInKms();

//        qDebug() << startRange.date().toString() << " to "
//                 << endRange.date().toString();

        startRange = endRange;
    }
}

void StravaActivitiesUT::testSummarizeMonths()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    // Create StravaActivities with ALL rides...
    StravaActivities sAct(args.at(1).toJsonDocument());

    //qDebug() << "NUM TOTAL RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 40);

    QDateTime today = QDateTime::currentDateTime();

    QDateTime startRange (QDate(2016,1,1),QTime(0,0));
    QDateTime yearEnd = startRange.addYears(1);

    while (startRange < yearEnd)
    {
        QDateTime endRange = startRange.addMonths(1);

        StravaRangeSummary summ = sAct.summarizeDateRange(startRange, endRange);

        qDebug() << startRange.date().toString() << " to "
                 << endRange.date().toString()   << " "
                 << summ.totalRides() << " "
                 << summ.totalDist() / 1000.0 << " "
                 << summ.avgDist() / 1000.0 << " "
                 << summ.totalMovingTimeHMS() << " "
                 << summ.longestRideDist() << " "
                 << summ.longestRideTimeHMS();

        startRange = endRange;
    }
}

void StravaActivitiesUT::testKMsOnNewBike()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    // Create StravaActivities with ALL rides...
    StravaActivities sAct(args.at(1).toJsonDocument());

    //qDebug() << "NUM TOTAL RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 40);

    QDateTime startRange (QDate(2016,6,23),QTime(0,0));    // Date of bike purchase...
    QDateTime endRange = QDateTime::currentDateTime();

    StravaRangeSummary summ = sAct.summarizeDateRange(startRange, endRange);

    qDebug() << startRange.date().toString() << " to "
             << endRange.date().toString();
    qDebug() << "NUM RIDES    : " << summ.totalRides();
    qDebug() << "TOT DIST     : " << summ.totalDist() / 1000.0;
    qDebug() << "AVG DIST     : " << summ.avgDist() / 1000.0;
    qDebug() << "MED DIST     : " << summ.medianDist() / 1000.0;
    qDebug() << "TOT MTIME    : " << summ.totalMovingTimeHMS();
    qDebug() << "AVG MTIME    : " << summ.avgMovingTimeHMS();
    qDebug() << "MED MTIME    : " << summ.medianMovingTimeHMS();
    qDebug() << "AVG SPEED    : " << summ.avgSpeedKMsPerHour();
    qDebug() << "LONGEST RIDE : " << summ.longestRideDist();
    qDebug() << "LONGEST MTIME: " << summ.longestRideTimeHMS();
}

void StravaActivitiesUT::testSort()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    // Create StravaActivities with ALL rides...
    StravaActivities sAct(args.at(1).toJsonDocument());

    //qDebug() << "NUM TOTAL RIDES = " << sAct.numActivities();
    QVERIFY(sAct.numActivities() > 40);

    // Now sort by distance...
    sAct.sortBy(StravaActivities::SortField::distance, true);

}
