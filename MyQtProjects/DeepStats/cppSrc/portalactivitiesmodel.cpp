#include "portalactivitiesmodel.h"
//#include <QQmlEngine>
#include <QLoggingCategory>

static QLoggingCategory loggingCategory("Strava.ActivitiesModel");

PortalActivitiesModel::PortalActivitiesModel()
{
    // Ensure use in QML doesn't take ownership...
    //QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

PortalActivitiesModel::~PortalActivitiesModel()
{

}

QHash<int, QByteArray>  PortalActivitiesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[athleteId]        = "athleteId";
    roles[rideNumber]       = "rideNumber";
    roles[startDate]        = "startDate";
    roles[distance]         = "distance";
    roles[distInKms]        = "distInKms";
    roles[movingTime]       = "movingTime";
    roles[elapsedTime]      = "elapsedTime";
    roles[averageSpeed]     = "averageSpeed";
    roles[avgSpdKMsPerHr]   = "avgSpdKMsPerHr";
    return roles;
}

int PortalActivitiesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

bool PortalActivitiesModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return false;
}

void PortalActivitiesModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
}

QModelIndex PortalActivitiesModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QModelIndex PortalActivitiesModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int PortalActivitiesModel::rowCount(const QModelIndex & parent) const
{
    // Because any valid index will not have children itself, (in the simple List case), any valid parent should return 0...
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return myActivities.numActivities();
    }
}

QVariant PortalActivitiesModel::data(const QModelIndex & index, int role) const
{
    QVariant outData;

    if (index.isValid() &&
        myActivities.numActivities() > 0 &&
        index.row() >= 0 && index.row() < myActivities.numActivities() )
    {
        int indx = index.row();
        if (role == athleteId)
        {
            outData.setValue(myActivities.getActivityAtIndex(indx).getAtheleteId());
        }
        else if (role == rideNumber)
        {
            outData.setValue(indx + 1);
        }
        else if (role == startDate)
        {
//            outData.setValue(myActivities.getActivityAtIndex(indx).getStartDate().date().toString("yyyy.MM.dd"));
            outData.setValue(myActivities.getActivityAtIndex(indx).getStartDateLocal().date().toString("yyyy.MM.dd"));
        }
        else if (role == distance)
        {
            outData.setValue(QString("%1").arg(myActivities.getActivityAtIndex(indx).getDistance(),0,'f',2));
        }
        else if (role == distInKms)
        {
            outData.setValue(QString("%1").arg(myActivities.getActivityAtIndex(indx).getDistInKms(),0,'f',2));
        }
        else if (role == movingTime)
        {
            //outData.setValue(myActivities.getActivityAtIndex(indx).getMovingTime());
            outData.setValue(myConvertToHMS(myActivities.getActivityAtIndex(indx).getMovingTime()));
        }
        else if (role == elapsedTime)
        {
            outData.setValue(myActivities.getActivityAtIndex(indx).getElapsedTime());
        }
        else if (role == averageSpeed)
        {
            outData.setValue(myActivities.getActivityAtIndex(indx).getAverageSpeed());
        }
        else if (role == avgSpdKMsPerHr)
        {
            //outData.setValue(myActivities.getActivityAtIndex(indx).getAverageSpeedKMsPerHr());
            outData.setValue(QString("%1").arg(myActivities.getActivityAtIndex(indx).getAverageSpeedKMsPerHr(),0,'f',2));
        }
    }

    return outData;
}

QString PortalActivitiesModel::myConvertToHMS(int mTime) const
{
    if (mTime <= 0 || mTime < 86400)    // 86400 is # of seconds in a day..
    {
        QTime tm = QTime(0,0,0).addSecs(mTime);
        return (tm.toString("HH:mm:ss"));
    }
    else
    {
        int hh = mTime / 60 / 60;
        int mm = (mTime - (hh*60*60)) / 60;
        int ss = mTime - ((hh*60*60) + (mm * 60));
        return QString("%1:%2:%3").arg(hh,2,10,QLatin1Char('0'))
                                  .arg(mm,2,10,QLatin1Char('0'))
                                  .arg(ss,2,10,QLatin1Char('0'));
    }
}

void PortalActivitiesModel::reload(const StravaActivities& theActivities)
{
    // We could always check if there are any changes or not,
    // but for now just do it blindly...
    beginResetModel();
    myActivities = theActivities;
    endResetModel();

    emit activitiesLoaded();
}

QVariantMap PortalActivitiesModel::getActivityAtIndex(int index) const
{
    // get the Activity at a particular index and return it
    // in a form usable in QML
    QVariantMap map;

    if (index >= 0 && index < myActivities.numActivities())
    {
        StravaActivity curActivity = myActivities.getActivityAtIndex(index);

        map.insert("athleteId",         curActivity.getAtheleteId());
        map.insert("rideNumber",        index+1);
        map.insert("startDate",         curActivity.getStartDateLocal());
        map.insert("distance",          curActivity.getDistance());
        map.insert("distInKms",         curActivity.getDistInKms());
        map.insert("movingTime",        curActivity.getMovingTime());
        map.insert("elapsedTime",       curActivity.getElapsedTime());
        map.insert("averageSpeed",      curActivity.getAverageSpeed());
        map.insert("avgSpdKMsPerHr",    curActivity.getAverageSpeedKMsPerHr());
    }

    return map;
}

void PortalActivitiesModel::sortBy(StravaActivities::SortField sortField)
{
    beginResetModel();
    myActivities.sortBy(sortField);
    endResetModel();

    emit activitiesLoaded();    // Use same signal...
}
