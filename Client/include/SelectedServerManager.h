#ifndef SELECTEDSERVERMANAGER_H
#define SELECTEDSERVERMANAGER_H

#include <QObject>
#include <qqml.h>

class SelectedServerManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit SelectedServerManager(QObject* parent = nullptr);
    ~SelectedServerManager();

private:
    int serverId_;
    QString serverDescription;
};

#endif // SELECTEDSERVERMANAGER_H
