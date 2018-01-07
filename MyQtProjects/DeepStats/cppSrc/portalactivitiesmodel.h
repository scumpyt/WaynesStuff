#ifndef PORTALACTIVITIESMODEL_H
#define PORTALACTIVITIESMODEL_H

#include <QObject>
#include <QAbstractItemModel>

#include "stravaactivities.h"
#include "deepstats_global.h"

class DEEPSTATS_EXPORT PortalActivitiesModel : public QAbstractItemModel
{
    Q_OBJECT
    //Q_PROPERTY(bool isComplete READ isComplete)
    //Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum PortalActivitiesModelItemRoles
    {
        athleteId    =   Qt::UserRole + 1,
        rideNumber,
        startDate,
        distance,
        distInKms,
        movingTime,
        elapsedTime,
        averageSpeed,
        avgSpdKMsPerHr
    };
    Q_ENUM(PortalActivitiesModelItemRoles)

    PortalActivitiesModel();
   ~PortalActivitiesModel();

    // Model functions...
    QHash<int, QByteArray>  roleNames() const override;

    virtual int             columnCount(const QModelIndex &parent) const override;
    virtual bool            canFetchMore(const QModelIndex &parent) const override;
    virtual void            fetchMore(const QModelIndex &parent) override;
    virtual QModelIndex     index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex     parent(const QModelIndex &child) const override;

    virtual int             rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant        data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    //int count() const;
    //bool isComplete() const;

    QString                 myConvertToHMS(int mTime) const;

public slots:
    void                    reload(const StravaActivities& theActivities);
    QVariantMap             getActivityAtIndex(int index) const;

    void                    sortBy(StravaActivities::SortField sortField = StravaActivities::SortField::rideNumber);

signals:
    //void countChanged();
    void                    activitiesLoaded();

private:    // Move all of this data to d_ptr...
    StravaActivities        myActivities;
};

#endif // PORTALACTIVITIESMODEL_H
