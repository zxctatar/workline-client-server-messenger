#include "../../include/JsonWorker.h"

JsonWorker::JsonWorker()
{
}

JsonWorker::~JsonWorker()
{
}

QJsonObject JsonWorker::JsonProcessing(const QString& jsonStr_)
{
    QJsonDocument jsonDoc_ = QJsonDocument::fromJson(jsonStr_.toUtf8());

    if(!jsonDoc_.isObject() || jsonDoc_.isNull())
    {
        qWarning() << "Invalid JSON";
        return QJsonObject();
    }

    return jsonDoc_.object();
}

QString JsonWorker::createJsonGET_ID(const QString& info_)
{
    QJsonObject jsonObject_;
    jsonObject_.insert("Info", QJsonValue::fromVariant(info_));
    QJsonDocument json_(jsonObject_);
    QString jsonString_ = json_.toJson(QJsonDocument::Indented);
    return jsonString_;
}
