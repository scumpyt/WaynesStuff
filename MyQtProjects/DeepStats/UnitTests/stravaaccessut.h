#ifndef STRAVAACCESSUT_H
#define STRAVAACCESSUT_H

#include <QObject>

class StravaAccessUT : public QObject
{
    Q_OBJECT
public:
    StravaAccessUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testBlankAccessToken();
    void testInvalidAccessToken();
    void testValidAccessToken();
    void testGetStats();
    void testGetActivities();
    void testGetActivitiesByDates();

private:
    QString myAccessToken;
    QString myClientSecret;
    QString myId;
};

#endif // STRAVAACCESSUT_H
