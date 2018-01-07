#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include "stravaactivitiesmodelut.h"
#include "portalactivitiesmodel.h"
#include "stravaaccess.h"

StravaActivitiesModelUT::StravaActivitiesModelUT()
{
    myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    myId           = "10883156";
}

void StravaActivitiesModelUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void StravaActivitiesModelUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void StravaActivitiesModelUT::init()
{
    // Runs before each test...
}

void StravaActivitiesModelUT::cleanup()
{
    // Runs at the end of each test...
}

void StravaActivitiesModelUT::testBasics()
{
    StravaAccess sa;

    QSignalSpy jsonSpy (&sa, SIGNAL(jsonReceived(const QUrl&, const QJsonDocument&)));
    QSignalSpy errSpy  (&sa, SIGNAL(ErrorReceived(QString)));

    QString endPoint = StravaActivities::getEndPointForAllTime();

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

    PortalActivitiesModel mdl;
    QVERIFY(mdl.rowCount() == 0);

    mdl.reload(sAct);
    QVERIFY(mdl.rowCount() > 44);

    for (int i=0; i<mdl.rowCount(); ++i)
    {
        QVariantMap vMap = mdl.getActivityAtIndex(i);

        qDebug() << i << ": " << vMap["startDate"].toDate().toString("yyyy:MM:dd") << " "
                              << vMap["distInKms"].toDouble() << " "
                              << vMap["movingTime"].toInt();
    }
}
