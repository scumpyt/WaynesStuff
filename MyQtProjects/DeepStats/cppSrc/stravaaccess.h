#ifndef STRAVAACCESS_H
#define STRAVAACCESS_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

#include "deepstats_global.h"

class DEEPSTATS_EXPORT StravaAccess : public QObject
{
    Q_OBJECT
public:
    explicit StravaAccess(QObject *parent = 0);
    ~StravaAccess();

    QString getBaseUrl() const;


signals:
    void DataReceived(QVariant results);
    void ErrorReceived(QString message);

    void jsonReceived (const QUrl& requestUrl, const QJsonDocument& json);

public slots:
    bool APICall(QString &endpoint, QString &accessToken /***, bool compress = false ***/ );
    void receivedAPIResults(QNetworkReply *reply);

private:
    QNetworkAccessManager *myManager;
    QString myBaseUrl;
    QTime myT1;
};

#endif // STRAVAACCESS_H
