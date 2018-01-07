#include <QCoreApplication>
#include <QtTest/QtTest>

#include "stravaaccessut.h"
#include "stravastatsut.h"
#include "stravaactivitiesut.h"
#include "stravaactivitiesmodelut.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
\
    int retVal = 0;

    // If any app-specific initialization needed, do it here...
    bool initOK = true;

    //////////////////////////////////////////////////////////////////////////

    // All tests go inside this if...
    if ( initOK )
    {
        StravaAccessUT stravaAccessUT;
        retVal += QTest::qExec( &stravaAccessUT, argc, argv );

        StravaStatsUT stravaStatsUT;
        retVal += QTest::qExec( &stravaStatsUT, argc, argv );

        StravaActivitiesUT stravaActivitiesUT;
        retVal += QTest::qExec( &stravaActivitiesUT, argc, argv );

        StravaActivitiesModelUT stravaActivitiesModelUT;
        retVal += QTest::qExec( &stravaActivitiesModelUT, argc, argv );
    }

    qDebug() << "=====================================================================";

    if ( retVal == 0 )
    {
        qDebug() << "============================= ALL OK! ===============================";
    }
    else
    {
        qDebug() << "===================== " << retVal << " Test(s) FAILED in total =====================";
    }

    qDebug() << "=====================================================================";

    return retVal;
}
