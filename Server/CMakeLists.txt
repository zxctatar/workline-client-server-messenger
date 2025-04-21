cmake_minimum_required(VERSION 3.16)

project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Boost 1.83.0 COMPONENTS system log log_setup REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(nlohmann_json REQUIRED)

pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_executable(Server src/main.cpp
    src/db/Database.cpp
    include/Database.h

    src/db/DBConnection.cpp
    include/DBConnection.h

    src/server/Server.cpp
    include/Server.h

    src/session/Session.cpp
    include/Session.h

    src/utils/JsonWorker.cpp
    include/JsonWorker.h

    src/connections/ConnectedUsers.cpp
    include/ConnectedUsers.h

    src/routers/RequestRouter.cpp
    include/RequestRouter.h

    src/db/managers/UserDBManager.cpp
    include/UserDBManager.h

    src/db/DBConnectionPool.cpp
    include/DBConnectionPool.h
    src/db/DatabaseQueries.cpp
    include/DatabaseQueries.h
    src/db/managers/ServerDBManager.cpp
    include/ServerDBManager.h
    include/struct/LoginResult.h
    include/struct/AddResult.h
    include/struct/ServerStruct.h
    include/struct/ReconnectResult.h
    include/struct/ServerDeleteStruct.h
    include/struct/UnverUserStruct.h
    include/struct/CandidateUserStruct.h
    include/struct/PrivateChatStruct.h
    src/db/managers/ChatsDBManager.cpp
    include/ChatsDBManager.h
    include/struct/UsersOnServerStruct.h
    include/struct/ChatHistoryResult.h
    include/struct/SetMessageResult.h
    src/db/managers/MessageDBManager.cpp
    include/MessageDBManager.h
    src/utils/ImageWorker.cpp
    include/ImageWorker.h
    include/struct/ChatDataResult.h

)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost library not found.")
endif()

target_link_libraries(Server ${Boost_LIBRARIES} PkgConfig::PQXX PostgreSQL::PostgreSQL nlohmann_json::nlohmann_json)

include(GNUInstallDirs)
install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
