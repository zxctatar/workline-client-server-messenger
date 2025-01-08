cmake_minimum_required(VERSION 3.16)

project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Boost 1.83.0 COMPONENTS system log log_setup REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_executable(Server src/main.cpp


    src/db/Database.cpp
    include/Database.h

    src/db/DBConnection.cpp
    include/DBConnection.h


)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost library not found.")
endif()

target_link_libraries(Server ${Boost_LIBRARIES} PkgConfig::PQXX PostgreSQL::PostgreSQL)

include(GNUInstallDirs)
install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
