#include <QCoreApplication>
#include <QtTest/QtTest>

#include "pathfinderut.h"

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
        PathFinderUT pathFinderUT;
        retVal += QTest::qExec( &pathFinderUT, argc, argv );
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

