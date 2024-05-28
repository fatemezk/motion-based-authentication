#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sensordatahandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SensorDataHandler sensorHandler;
    engine.rootContext()->setContextProperty("sensorHandler", &sensorHandler);

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
