#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>

class Encryption
{
public:
    explicit Encryption();
    ~Encryption();

    QString encrypt(const QString& message_);
    QString decrypt(const QString& message_);

private:
    QString key_;
};

#endif // ENCRYPTION_H
