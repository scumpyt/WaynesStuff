#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // ******************************************************************************
    // Add the import path to my plugins...
    QStringList importPathList = engine.importPathList();
    importPathList.append("C:/Users/wayne_000/Documents/QtProjects/WaynesPlugins");
    engine.setImportPathList(importPathList);
    qDebug() << "Path List: " << engine.importPathList();
    // ******************************************************************************

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
