#ifndef STRAVAACTIVITIESUT_H
#define STRAVAACTIVITIESUT_H

#include <QObject>
#include <QJsonDocument>

class StravaActivitiesUT : public QObject
{
    Q_OBJECT
public:
    StravaActivitiesUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testGetDefault();
    void testGetAll();
    void testGetYTD();
    void testSummarizeDateRange();
    void testSummarizeWeeks();
    void testSummarizeMonths();
    void testKMsOnNewBike();
    void testSort();

private:
    QString         myAccessToken;
    QString         myClientSecret;
    QString         myId;
};

#endif // STRAVAACTIVITIESUT_H
