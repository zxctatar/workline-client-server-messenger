#include "../../include/ImageWorker.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QUuid>
#include <QStandardPaths>

ImageWorker::ImageWorker()
{
}

ImageWorker::~ImageWorker()
{
}

QString ImageWorker::encodeImage(const QString& base64Image_)
{
    QByteArray decodedPath_ = QByteArray::fromBase64(base64Image_.toUtf8());
    QString imagePath_ = QString::fromUtf8(decodedPath_);

    QFile file_(imagePath_.remove("file://"));
    if(!file_.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open file" << imagePath_;
    }

    QByteArray imageData_ = file_.readAll();
    file_.close();

    return QString::fromUtf8(imageData_.toBase64());
}

QImage ImageWorker::decodeImage(const QString& base64Image_)
{
    QByteArray imageData_ = QByteArray::fromBase64(base64Image_.toUtf8());
    QImage image_;
    if(image_.loadFromData(imageData_))
    {
        return image_;
    }
    return QImage();
}

QString ImageWorker::saveImageToTempFile(const QImage& image_)
{
    if(!image_.isNull())
    {
        QString filePath_ = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
        + "/" + QUuid::createUuid().toString() + ".png";
        image_.save(filePath_);
        return "file:///" + QDir::toNativeSeparators(filePath_);
    }
    else
    {
        return "";
    }
}

void ImageWorker::cleanupTempFiles()
{
    QString tempDir_ = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QDir dir_(tempDir_);

    QStringList filters_;
    filters_ << "*.png";
    dir_.setNameFilters(filters_);

    for(const QString& dirFile_ : dir_.entryList(filters_))
    {
        dir_.remove(dirFile_);
    }
}
