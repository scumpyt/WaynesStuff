#include <QCoreApplication>
#include <QtTest/QtTest>

#include "vehicleut.h"
#include "oilchangeut.h"
#include "tirerotationut.h"
#include "scheduledmaintut.h"
#include "misceventut.h"
#include "maintenancelogut.h"
#include "persistenceenginefactoryut.h"
#include "persistenceenginecsvut.h"
#include "persistenceengineut.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int retVal = 0;

    // If any app-specific initialization needed, do it here...
    bool initOK = true;

    //////////////////////////////////////////////////////////////////////////

    // All tests go inside this if...
    if ( initOK )
    {
        VehicleUT vehicleUT;
        retVal += QTest::qExec( &vehicleUT, argc, argv );

        OilChangeUT oilChangeUT;
        retVal += QTest::qExec( &oilChangeUT, argc, argv );

        TireRotationUT tireRotationUT;
        retVal += QTest::qExec( &tireRotationUT, argc, argv );

        ScheduledMaintUT scheduledMaintUT;
        retVal += QTest::qExec( &scheduledMaintUT, argc, argv );

        MiscEventUT miscEventUT;
        retVal += QTest::qExec( &miscEventUT, argc, argv );

        MaintenanceLogUT maintenanceLogUT;
        retVal += QTest::qExec( &maintenanceLogUT, argc, argv );

        PersistenceEngineFactoryUT persistenceEngineFactoryUT;
        retVal += QTest::qExec( &persistenceEngineFactoryUT, argc, argv );

        PersistenceEngineCSVUT persistenceEngineCSVUT;
        retVal += QTest::qExec( &persistenceEngineCSVUT, argc, argv );

        PersistenceEngineUT persistenceEngineUT;
        retVal += QTest::qExec( &persistenceEngineUT, argc, argv );
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

