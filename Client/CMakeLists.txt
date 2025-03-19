cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Widgets)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup(REQUIRES 6.5)

qt_policy(SET QTP0004 NEW)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

qt_add_executable(appClient
    src/main.cpp
    src/resources.qrc
)

qt_add_qml_module(appClient
    URI Client
    VERSION 1.0

    QML_FILES src/main.qml
    RESOURCES src/qmldir

    QML_FILES src/resources/Sizes.qml
    QML_FILES src/resources/Colors.qml
    QML_FILES src/resources/Fonts.qml
    QML_FILES src/resources/Shadows.qml
    RESOURCES src/resources/qmldir

    QML_FILES src/view/customwidgets/compositewidgets/TopBar.qml
    QML_FILES src/view/customwidgets/compositewidgets/ServerTable.qml
    RESOURCES src/view/customwidgets/compositewidgets/qmldir

    QML_FILES src/view/customwidgets/widgets/ErrorText.qml
    QML_FILES src/view/customwidgets/widgets/WindowText.qml
    QML_FILES src/view/customwidgets/widgets/InputField.qml
    QML_FILES src/view/customwidgets/widgets/MyButton.qml
    QML_FILES src/view/customwidgets/widgets/BackButton.qml
    QML_FILES src/view/customwidgets/widgets/Tooltip.qml
    QML_FILES src/view/customwidgets/widgets/ShowPasswordButton.qml
    QML_FILES src/view/customwidgets/widgets/MyPopup.qml
    QML_FILES src/view/customwidgets/widgets/NotificationManager.qml
    QML_FILES src/view/customwidgets/widgets/ServerObject.qml
    QML_FILES src/view/customwidgets/widgets/AddServerButton.qml
    QML_FILES src/view/customwidgets/widgets/MenuButton.qml
    QML_FILES src/view/customwidgets/widgets/MenuWidget.qml
    QML_FILES src/view/customwidgets/widgets/Separator.qml
    QML_FILES src/view/customwidgets/widgets/MenuPageInputField.qml
    QML_FILES src/view/customwidgets/widgets/MenuText.qml
    QML_FILES src/view/customwidgets/widgets/MenuPageLabel.qml
    QML_FILES src/view/customwidgets/widgets/ApplicationObject.qml
    QML_FILES src/view/customwidgets/widgets/ApproveButton.qml
    QML_FILES src/view/customwidgets/widgets/RejectButton.qml
    RESOURCES src/view/customwidgets/widgets/qmldir

    QML_FILES src/view/windowpages/menuprofilepage/MenuProfilePage.qml
    RESOURCES src/view/windowpages/menuprofilepage/qmldir

    QML_FILES src/view/windowpages/menumainpage/MenuMainPage.qml
    RESOURCES src/view/windowpages/menumainpage/qmldir

    QML_FILES src/view/windowpages/menuapplicationpage/MenuApplicationPage.qml
    RESOURCES src/view/windowpages/menuapplicationpage/qmldir

    QML_FILES src/view/windows/AddServerWindow.qml
    QML_FILES src/view/windows/MenuWindow.qml
    RESOURCES src/view/windows/qmldir

    QML_FILES src/view/apppages/loginpage/LoginPage.qml
    RESOURCES src/view/apppages/loginpage/qmldir

    QML_FILES src/view/apppages/registrationpage/RegistrationPage.qml
    RESOURCES src/view/apppages/registrationpage/qmldir

    QML_FILES src/view/apppages/mainpage/MainPage.qml
    RESOURCES src/view/apppages/mainpage/qmldir

    SOURCES src/connection/ServerConnector.cpp
    SOURCES include/ServerConnector.h

    SOURCES src/utils/JsonWorker.cpp
    SOURCES include/JsonWorker.h

    SOURCES src/controller/maincontroller/MainController.cpp
    SOURCES include/MainController.h

    SOURCES src/controller/loginpagecontroller/LoginPageController.cpp
    SOURCES include/LoginPageController.h

    SOURCES src/controller/registrationpagecontroller/RegistrationPageController.cpp
    SOURCES include/RegistrationPageController.h

    SOURCES src/model/usermodel/UserModel.cpp
    SOURCES include/UserModel.h

    SOURCES src/controller/servertablecontroller/ServerTableController.cpp
    SOURCES include/ServerTableController.h

    SOURCES src/model/servermodel/ServerModel.cpp
    SOURCES include/ServerModel.h

    SOURCES src/controller/useraccountcontroller/UserAccountController.cpp
    SOURCES include/UserAccountController.h

    SOURCES src/controller/topbarcontroller/TopBarController.cpp
    SOURCES include/TopBarController.h

    SOURCES src/controller/applicationpagecontroller/ApplicationPageController.cpp
    SOURCES include/ApplicationPageController.h
    SOURCES src/model/unverifiedusermodel/UnverifiedUserModel.cpp
    SOURCES include/UnverifiedUserModel.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appClient
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
