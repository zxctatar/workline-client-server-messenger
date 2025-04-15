#ifndef SELECTEDCHATMANAGER_H
#define SELECTEDCHATMANAGER_H

#include <QObject>

class SelectedChatManager : public QObject
{
    Q_OBJECT

public:
    static SelectedChatManager& instance();

    void setChatId(const int chatId_);
    int getChatId();

signals:
    void setNewChatIdSignal(const int chatId_);

private:
    explicit SelectedChatManager(QObject* parent = nullptr);
    ~SelectedChatManager();

    int chatId_;
};

#endif // SELECTEDCHATMANAGER_H
