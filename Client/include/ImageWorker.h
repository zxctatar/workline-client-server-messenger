#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <QByteArray>
#include <QImage>
#include <QHash>

class ImageWorker
{
public:
    explicit ImageWorker();
    ~ImageWorker();

    QString encodeImage(const QString& base64Image_) const;
    QImage decodeImage(const QString& base64Image_) const;
    QString saveImageToTempFile(const QImage& image_) const;
    void cleanupTempFiles();

private:
    mutable QHash<QString, QString> imageCache_;
};

#endif // IMAGEWORKER_H
