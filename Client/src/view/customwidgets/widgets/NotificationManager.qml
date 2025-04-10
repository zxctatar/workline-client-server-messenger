import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform

QtObject {
    id: notificationManager
    property ApplicationWindow mainWindow
    property SystemTrayIcon tray
    property MyPopup popup

    function showNotificationManager(message) {
        if (mainWindow.active) {
            // Окно активно, показываем уведомление внутри приложения
            popup.popupText = message
            popup.open()
        } else {
            // Окно неактивно, показываем уведомление через системный трей
            tray.showMessage("WorkLine", message)
        }
    }
}
