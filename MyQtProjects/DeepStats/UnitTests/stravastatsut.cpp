#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include "stravastatsut.h"
#include "stravastats.h"
#include "stravaaccess.h"

StravaStatsUT::StravaStatsUT()
{
    myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    myId           = "10883156";
}
void StravaStatsUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint;
    endPoint = "athletes/" + myId + "/stats";

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));

    myJsonBlob = args.at(1).toJsonDocument();
}

void StravaStatsUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void StravaStatsUT::init()
{
    // Runs before each test...
}

void StravaStatsUT::cleanup()
{
    // Runs at the end of each test...
}

void StravaStatsUT::testGetBiggestRideDistance()
{
    StravaStats sa (myJsonBlob);

    double dist = sa.getBiggestRideDistance();
    qDebug() << "BIG DIST = " << dist / 1000.0;
    QVERIFY(dist > 54000.0);
}

void StravaStatsUT::testGetStat()
{
    StravaStats sa (myJsonBlob);

    int recCount = sa.getStat("count", StravaStats::RECENT).toInt();
    int ytdCount = sa.getStat("count", StravaStats::YTD).toInt();
    int allCount = sa.getStat("count", StravaStats::ALLTIME).toInt();

    qDebug() << "REC COUNT = " << recCount;
    qDebug() << "YTD COUNT = " << ytdCount;
    qDebug() << "ALL COUNT = " << allCount;

    QVERIFY(recCount <= ytdCount);
    QVERIFY(allCount >= 41);

    double recDist = sa.getStat("distance", StravaStats::RECENT).toDouble();
    double ytdDist = sa.getStat("distance", StravaStats::YTD).toDouble();
    double allDist = sa.getStat("distance", StravaStats::ALLTIME).toDouble();

    qDebug() << "REC DIST = " << recDist / 1000.0;
    qDebug() << "YTD DIST = " << ytdDist / 1000.0;
    qDebug() << "ALL DIST = " << allDist / 1000.0;

    double recMTime = sa.getStat("moving_time", StravaStats::RECENT).toDouble();
    double ytdMTime = sa.getStat("moving_time", StravaStats::YTD).toDouble();
    double allMTime = sa.getStat("moving_time", StravaStats::ALLTIME).toDouble();

    qDebug() << "REC MTime = " << recMTime;
    qDebug() << "YTD MTime = " << ytdMTime;
    qDebug() << "ALL MTime = " << allMTime;
}
