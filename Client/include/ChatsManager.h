#ifndef CHATSMANAGER_H
#define CHATSMANAGER_H

#include <QObject>
#include <QMap>

class ChatsManager : public QObject
{
    Q_OBJECT

public:
    static ChatsManager& instance();

    void addAvatar(const int userId_, const QString& avatarPath_);
    QString getAvatar(const int userId_);
    void clearAvatars();

private:
    explicit ChatsManager(QObject* parent = nullptr);
    ~ChatsManager();

    QMap<int, QString> avatars_;
};

#endif // CHATSMANAGER_H
