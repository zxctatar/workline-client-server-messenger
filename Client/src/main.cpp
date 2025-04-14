#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QIcon>
#include "include/MainController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MainController>("com.mainController", 1, 0, "MainController");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
