#include "../include/TopBarController.h"

TopBarController::TopBarController(QObject* parent)
    : QObject(parent)
{
}

TopBarController::~TopBarController()
{
}

void TopBarController::getUserRole() const
{
    emit needUserRoleSignal();
}

void TopBarController::getUserData() const
{
    emit needUserDataSignal();
}

void TopBarController::slotSetUserRole(const QString& userRole_) const
{
    emit setUserRoleSignal(userRole_);
}

void TopBarController::slotSetUserData(const QString& userFirstName_, const QString& userLastName_, const QString& userMiddleName_, const QString& userEmail_, const QString& userPhoneNumber_) const
{
    emit setUserDataSignal(userFirstName_, userLastName_, userMiddleName_, userEmail_, userPhoneNumber_);
}
