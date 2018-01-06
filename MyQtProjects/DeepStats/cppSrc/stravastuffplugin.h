#ifndef STRAVASTUFFPLUGIN_H
#define STRAVASTUFFPLUGIN_H

#include <QtQml>
#include <QQmlExtensionPlugin>
#include "stravaportal.h"
#include "stravaactivitiesmodel.h"

class StravaStuffPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("ca.scumpyware.stravastuff"));
        qmlRegisterType<StravaPortal>(uri, 1, 0, "StravaPortal");
        qmlRegisterUncreatableType<StravaActivitiesModel>(uri, 1, 0, "StravaActivitiesModel",
                                                     "StravaActivitiesModel is uncreatable");
    }
};
#endif // STRAVASTUFFPLUGIN_H
