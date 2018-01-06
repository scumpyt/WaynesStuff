#include "stravaaccess.h"
#include <QLoggingCategory>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

//#include "qcompressor.h"

static QLoggingCategory loggingCategory("Strava.Access");

StravaAccess::StravaAccess(QObject *parent)
    : QObject(parent)
    , myBaseUrl("https://www.strava.com/api/v3/")
{
    myManager = new QNetworkAccessManager();

    // TODO: Figure out what needs to be changed here.
    connect(myManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(receivedAPIResults(QNetworkReply*)));

    // Secret credentials...
    //myAccessToken  = "659e3f2d0715de508392fa1a6cd2711a46cdf673";
    //myClientSecret = "c7ce2869b57fd5da98aa733b5a019ceb6825c34a";
    //myClientId     = "13022";
    //myId           = "10883156";
}

StravaAccess::~StravaAccess()
{
    delete myManager;
}

QString StravaAccess::getBaseUrl() const
{
    return myBaseUrl;
}

bool StravaAccess::APICall(QString &endpoint, QString &accessToken  /***, bool compress ***/ )
{
    if(endpoint.isEmpty() || accessToken.isEmpty()) {
        qCWarning(loggingCategory) << "endpoint or accessToken is empty.";
        return false;
    }

    QUrl base = QUrl(myBaseUrl);
    QUrl absoluteEndPoint = base.resolved(QUrl(endpoint));

    QNetworkRequest request(absoluteEndPoint);

    // Set headers
    request.setRawHeader("User-Agent", "ScumpyWare");
    QString bearerTokenString = "Bearer %1";
    bearerTokenString = bearerTokenString.arg(accessToken);
    request.setRawHeader("Authorization", bearerTokenString.toUtf8());
    request.setRawHeader("Accept", "application/json");

//    if(compress) {
//        qDebug() << "Requesting gzip compression.";
//        request.setRawHeader("Accept-Encoding", "gzip");
//    }

    myT1.start();
    myManager->get(request);

    return true;
}

void StravaAccess::receivedAPIResults(QNetworkReply *reply)
{
    qCDebug(loggingCategory) << "Time to get Strava API Reply: " << myT1.elapsed();
    if(!reply) {
        qCDebug(loggingCategory) << "Error: The reply object is empty.";
        emit ErrorReceived("Error: The reply object is empty.");
        return;
    }

    if(reply->error() != QNetworkReply::NoError) {
        qCDebug(loggingCategory) << "Error: " << reply->errorString();
        emit ErrorReceived(reply->errorString());
        return;
    }

    QByteArray inputText = reply->readAll();
    //qDebug() << inputText;
    QByteArray decompressed;

//    if(reply->request().rawHeader("Accept-Encoding") == "gzip") {
//        QCompressor::gzipDecompress(inputText, decompressed);
//        inputText = decompressed;
//    }

    QUrl requestUrl = reply->url();
    qCDebug(loggingCategory) << "URL = " << requestUrl;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(inputText);
    if (!jsonDoc.isArray() && !jsonDoc.isObject())
    {
        QString errStr ("Response is not a JSON object or array.");
        qCWarning(loggingCategory) << errStr;
        emit ErrorReceived(errStr);
        return;
    }

    if(jsonDoc.isObject())
    {
        //qCDebug(loggingCategory) << "Returned DATA is an OBJECT";
        QJsonObject jsonObj;
        jsonObj = jsonDoc.object();

        if(jsonObj.contains("errors"))
        {
            qCWarning(loggingCategory) << jsonObj["message"].toString();
            emit ErrorReceived(jsonObj["message"].toString());
            return;
        }
    }

    emit jsonReceived(requestUrl, jsonDoc);

    reply->deleteLater();
}
