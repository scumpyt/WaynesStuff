#ifndef STRAVASTATSUT_H
#define STRAVASTATSUT_H

#include <QObject>
#include <QJsonDocument>

class StravaStatsUT : public QObject
{
    Q_OBJECT
public:
    StravaStatsUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testGetBiggestRideDistance();
    void testGetStat();

private:
    QString         myAccessToken;
    QString         myClientSecret;
    QString         myId;
    QJsonDocument   myJsonBlob;
};

#endif // STRAVASTATSUT_H
