#ifndef MAINTENANCELOGUT_H
#define MAINTENANCELOGUT_H

#include <QObject>
#include "vehicle.h"

class MaintenanceLog;   // Forward decls...

class MaintenanceLogUT : public QObject
{
    Q_OBJECT
public:
    MaintenanceLogUT();

    // Test helper functions...
    static bool checkIfClosed(const MaintenanceLog& ml);
    static bool addVehiclesToLog(MaintenanceLog& ml,
                            const Vehicle& v1, const Vehicle& v2,
                            const Vehicle& v3, const Vehicle& v4);
    static bool addEventsToLog(MaintenanceLog& ml, const Vehicle& v1, const Vehicle& v2);

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // File API tests...
    void testCtor();
    void testCreateNewLog();
    void testOpenExistingLog();
    void testDeleteLog();
    void testClose();
    void testSave();
    void testClear();

    // Vehicle API tests...
    void testAddVehicle();
    void testGetVehicle();
    void testUpdateVehicle();
    void testRemoveVehicle();
    void testHasVehicle();
    void testIsVehicleUsed();
    void testGetVehicles();

    // Event API tests...
    void testAddEvent();
    void testGetEvent();
    void testUpdateEvent();
    void testRemoveEvent();
    void testRemoveAllEventsByVehicle();
    void testHasEvent();
    void testGetEvents();
    void testListAllEvents();

private:
    std::string myLogFileName;
    Vehicle v1, v2, v3, v4;
};

#endif // MAINTENANCELOGUT_H
