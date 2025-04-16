#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <QByteArray>
#include <QImage>

class ImageWorker
{
public:
    explicit ImageWorker();
    ~ImageWorker();

    QString encodeImage(const QString& base64Image_);
    QImage decodeImage(const QString& base64Image_);
    QString saveImageToTempFile(const QImage& image_);
    void cleanupTempFiles();
};

#endif // IMAGEWORKER_H
