#ifndef SELECTEDSERVERMANAGER_H
#define SELECTEDSERVERMANAGER_H

#include <QObject>
#include <qqml.h>

class SelectedServerManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    static SelectedServerManager& instance();

    void setServerData(const int receivedServerId_, const QString& receivedServerName_, const QString& receivedServerDescription_);
    bool getServerSelected();
    int getServerId();

private:
    explicit SelectedServerManager(QObject* parent = nullptr);
    ~SelectedServerManager();

    int serverId_;
    QString serverName_;
    QString serverDescription_;
};

#endif // SELECTEDSERVERMANAGER_H
