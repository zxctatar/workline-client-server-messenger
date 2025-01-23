#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "include/ServerConnector.h"
#include "include/MainController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ServerConnector server("localhost", 8001);

    MainController mainController(server);

    qmlRegisterSingletonInstance<MainController>("com.example.mainController", 1, 1, "MainController", &mainController);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
