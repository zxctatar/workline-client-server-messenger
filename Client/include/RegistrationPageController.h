#ifndef REGISTRATIONPAGECONTROLLER_H
#define REGISTRATIONPAGECONTROLLER_H

#include <QObject>
#include "qqml.h"
#include "ServerConnector.h"

class RegistrationPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegistrationPageController(ServerConnector& serverConnector_, QObject* parent = nullptr);
    ~RegistrationPageController();

private:
    ServerConnector& serverConnector_;
};

#endif // REGISTRATIONPAGECONTROLLER_H
