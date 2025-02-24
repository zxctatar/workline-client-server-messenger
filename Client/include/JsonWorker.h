#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <QJsonDocument>
#include <QJsonObject>

class JsonWorker
{
public:
    explicit JsonWorker();
    ~JsonWorker();

    QJsonObject JsonProcessing(const QString& jsonStr_);

    QString createJsonGET_ID(const QString& info_);

private:

};

#endif // JSONWORKER_H
