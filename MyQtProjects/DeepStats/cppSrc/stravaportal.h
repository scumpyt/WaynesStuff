#ifndef STRAVAPORTAL_H
#define STRAVAPORTAL_H

#include <QObject>

//#include "portalactivitiesmodel.h"
#include "portalactivitiesmodel.h"
#include "stravaaccess.h"
#include "deepstats_global.h"

class DEEPSTATS_EXPORT StravaPortal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PortalActivitiesModel* portalActivitiesModel READ portalActivitiesModel CONSTANT)
public:
    explicit StravaPortal(QObject *parent = 0);
   ~StravaPortal();

    PortalActivitiesModel* portalActivitiesModel() const;

    // fetch features
    Q_INVOKABLE void fetchActivities();

    Q_INVOKABLE void summarize(const QString& startDateStr, const QString& endDateStr);
    Q_INVOKABLE void sort(const QString& sortFieldStr);

public slots:
    void onJsonReceived(const QUrl& requestUrl, const QJsonDocument& json);
    QVariantMap getSummaryVMap() const;

signals:
    void activitiesModelUpdated();
    void newSummaryAvailable();

private:
    QString myAccessToken;
    QString myClientSecret;
    QString myId;

    QString myGetEverythingEndPoint;

    StravaAccess*           myStravaAccess;         // Make all these smart pointers!!!
    StravaActivities*       myStravaActivities;
    PortalActivitiesModel*  myActivitiesModel;
    StravaRangeSummary      mySummary;

    Q_DISABLE_COPY(StravaPortal) // replace with C++11 'delete'
};

#endif // STRAVAPORTAL_H
