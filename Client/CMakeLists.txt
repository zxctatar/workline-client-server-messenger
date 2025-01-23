cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

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

    QML_FILES src/view/widgets/ErrorText.qml
    QML_FILES src/view/widgets/WindowText.qml
    QML_FILES src/view/widgets/InputField.qml
    QML_FILES src/view/widgets/MyButton.qml
    QML_FILES src/view/widgets/BackButton.qml
    QML_FILES src/view/widgets/Tooltip.qml
    RESOURCES src/view/widgets/qmldir

    QML_FILES src/view/loginpage/LoginPage.qml
    RESOURCES src/view/loginpage/qmldir

    QML_FILES src/view/registrationpage/RegistrationPage.qml
    RESOURCES src/view/registrationpage/qmldir

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
    SOURCES src/controller/registrationpagecontroller/RegistrationPageController.cpp
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
)

include(GNUInstallDirs)
install(TARGETS appClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
