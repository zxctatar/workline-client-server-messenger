#ifndef ADDUSERINCHATCONTROLLER_H
#define ADDUSERINCHATCONTROLLER_H

#include <QObject>
#include <qqml.h>

class AddUserInChatController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AddUserInChatController(QObject* parent = nullptr);
    ~AddUserInChatController();

private:

};

#endif // ADDUSERINCHATCONTROLLER_H
