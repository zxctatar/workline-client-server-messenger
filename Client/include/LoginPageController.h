#ifndef LOGINPAGECONTROLLER_H
#define LOGINPAGECONTROLLER_H

#include <QObject>
#include "qqml.h"
#include "ServerConnector.h"

class LoginPageController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit LoginPageController(ServerConnector& serverConnector_, QObject* parent = nullptr);
    ~LoginPageController();

private:
    ServerConnector& serverConnector_;
};

#endif // LOGINPAGECONTROLLER_H
