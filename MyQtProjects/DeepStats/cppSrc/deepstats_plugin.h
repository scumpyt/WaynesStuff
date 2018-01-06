#ifndef DEEPSTATS_PLUGIN_H
#define DEEPSTATS_PLUGIN_H

#include <QtQml>
#include <QQmlExtensionPlugin>
#include "stravaportal.h"
#include "portalactivitiesmodel.h"

class DeepStats_Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("ca.scumpyware.deepstats"));
        qmlRegisterType<StravaPortal>(uri, 1, 0, "StravaPortal");
        qmlRegisterUncreatableType<PortalActivitiesModel>(uri, 1, 0, "PortalActivitiesModel",
                                                     "PortalActivitiesModel is uncreatable");
    }
};

#endif // DEEPSTATS_PLUGIN_H
