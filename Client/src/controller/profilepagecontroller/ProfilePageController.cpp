#include "../../../include/ProfilePageController.h"

ProfilePageController::ProfilePageController(QObject* parent)
    : QObject(parent)
{
}

ProfilePageController::~ProfilePageController()
{
}

void ProfilePageController::getUserData() const
{
    QString userAvatarPath_ = UserAccountManager::instance().getUserAvatarPath();
    QDate userBirthDate_ = QDate::fromString(UserAccountManager::instance().getUserBirthDate(), "yyyy-MM-dd");
    QString userBirthDateString_ = userBirthDate_.toString("dd-MM-yyyy");
    QString userFirstName_ = UserAccountManager::instance().getUserFirstName();
    QString userLastName_ = UserAccountManager::instance().getUserLastName();
    QString userMiddleName_ = UserAccountManager::instance().getUserMiddleName();
    QString userEmail_ = UserAccountManager::instance().getUserEmail();
    QString userPhoneNumber_ = UserAccountManager::instance().getUserPhoneNumber();

    emit setUserDataSignal(userAvatarPath_, userBirthDateString_, userFirstName_, userLastName_, userMiddleName_, userEmail_, userPhoneNumber_);
}
