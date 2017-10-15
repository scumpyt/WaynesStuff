#ifndef PERSISTENCEENGINECSVUT_H
#define PERSISTENCEENGINECSVUT_H

#include <QObject>

class PersistenceEngineCSVUT : public QObject
{
    Q_OBJECT
public:
    PersistenceEngineCSVUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCreateNewLog();
    void testOpenExistingLog();
    void testDeleteLog();
    void testLogExists();
    void testWriteVehicles();
    void testWriteEvents();
    void testReadVehicles();
    void testReadEvents();
//    void testCloseLog();  // @TODO - Add, although probably tested sufficiently elsewhere

private:
    std::string myLogFileName;
};

#endif // PERSISTENCEENGINECSVUT_H
