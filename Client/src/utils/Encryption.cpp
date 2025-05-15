#include "../include/Encryption.h"

Encryption::Encryption()
    : key_("HsmgFSasfWwNGFNam")
{
}

Encryption::~Encryption()
{
}

QString Encryption::encrypt(const QString& message_)
{
    QString result_;
    int keyLength_ = key_.length();
    int keyIndex_ = 0;

    for(int i = 0; i < message_.length(); ++i)
    {
        QChar textChar_ = message_[i];

        if(textChar_.isLetter())
        {
            QChar keyChar_ = key_[keyIndex_ % keyLength_];
            keyIndex_++;

            QChar base_;
            int alphabetSize_;

            if(textChar_.script() == QChar::Script_Cyrillic)
            {
                base_ = textChar_.isUpper() ? QChar(0x0410) : QChar(0x0430);
                alphabetSize_ = 33;
            }
            else
            {
                base_ = textChar_.isUpper() ? 'A' : 'a';
                alphabetSize_ = 26;
            }

            QChar lowerKey_ = keyChar_.toLower();
            int keyShift_ = lowerKey_.unicode() - 'a';

            int shiftedPos_ = (textChar_.unicode() - base_.unicode() + keyShift_) % alphabetSize_;
            QChar encryptedChar_ = QChar(base_.unicode() + shiftedPos_);
            result_.append(encryptedChar_);
        }
        else
        {
            result_.append(textChar_);
        }
    }
    return result_;
}

QString Encryption::decrypt(const QString& message_)
{
    QString result_;
    int keyLength_ = key_.length();
    int keyIndex_ = 0;

    for(int i = 0; i < message_.length(); ++i)
    {
        QChar textChar_ = message_[i];

        if(textChar_.isLetter())
        {
            QChar keyChar_ = key_[keyIndex_ % keyLength_];
            keyIndex_++;

            QChar base_;
            int alphabetSize_;

            if(textChar_.script() == QChar::Script_Cyrillic)
            {
                base_ = textChar_.isUpper() ? QChar(0x0410) : QChar(0x0430);
                alphabetSize_ = 33;
            }
            else
            {
                base_ = textChar_.isUpper() ? 'A' : 'a';
                alphabetSize_ = 26;
            }

            QChar lowerKey_ = keyChar_.toLower();
            int keyShift_ = lowerKey_.unicode() - 'a';

            int shiftedPos_ = (textChar_.unicode() - base_.unicode() - keyShift_) % alphabetSize_;

            if(shiftedPos_ < 0)
            {
                shiftedPos_ += alphabetSize_;
            }

            QChar decryptedChar_ = QChar(base_.unicode() + shiftedPos_);
            result_.append(decryptedChar_);
        }
        else
        {
            result_.append(textChar_);
        }
    }
    return result_;
}
