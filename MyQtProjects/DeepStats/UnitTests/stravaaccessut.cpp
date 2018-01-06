#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>
#include <QDateTime>

#include "stravaaccessut.h"
#include "stravaaccess.h"

StravaAccessUT::StravaAccessUT()
{
    myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    myId           = "10883156";
}

void StravaAccessUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void StravaAccessUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void StravaAccessUT::init()
{
    // Runs before each test...
}

void StravaAccessUT::cleanup()
{
    // Runs at the end of each test...
}

void StravaAccessUT::testBlankAccessToken()
{
    StravaAccess sa;

    QString endPoint ("athlete");
    QString accessToken;    // Leave blank...

    QVERIFY(sa.APICall(endPoint, accessToken) == false);
}

void StravaAccessUT::testInvalidAccessToken()
{
    StravaAccess sa;

    QSignalSpy spy (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint ("athlete");
    QString accessToken("ThisMostCertainlyShouldNOTWork");

    QVERIFY(sa.APICall(endPoint, accessToken) == true);

    spy.wait();
    QVERIFY(spy.count() == 1);
}

void StravaAccessUT::testValidAccessToken()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint ("athlete");

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));
}

void StravaAccessUT::testGetStats()
{
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
}

void StravaAccessUT::testGetActivities()
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
}

void StravaAccessUT::testGetActivitiesByDates()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    // Create a date exactly 4 weeks ago...
    QDateTime now = QDateTime::currentDateTime();
    QDateTime lastMonth = now.addDays(-28);

    QString endPoint;
    endPoint = QString("athlete/activities#after=%1").arg(lastMonth.toMSecsSinceEpoch());

    //qDebug() << "ENDPOINT = " << endPoint;

    QVERIFY(sa.APICall(endPoint, myAccessToken) == true);

    jsonSpy.wait();
    QVERIFY(jsonSpy.count() == 1);
    QVERIFY(errSpy.count() == 0);

    QList<QVariant> args = jsonSpy.takeFirst();                 // take the first signal
    QString requestUrlStr = args.at(0).toString();
    QVERIFY(requestUrlStr.startsWith(sa.getBaseUrl()));
    QVERIFY(requestUrlStr.endsWith(endPoint));
}

