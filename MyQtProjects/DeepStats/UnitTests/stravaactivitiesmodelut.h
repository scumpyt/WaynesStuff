#ifndef STRAVAACTIVITIESMODELUT_H
#define STRAVAACTIVITIESMODELUT_H

#include <QObject>

class StravaActivitiesModelUT : public QObject
{
    Q_OBJECT
public:
    StravaActivitiesModelUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testBasics();

private:
    QString myAccessToken;
    QString myClientSecret;
    QString myId;
};

#endif // STRAVAACTIVITIESMODELUT_H
