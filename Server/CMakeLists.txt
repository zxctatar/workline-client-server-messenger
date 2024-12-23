cmake_minimum_required(VERSION 3.16)

project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Boost 1.83.0 COMPONENTS system REQUIRED)

set(PQXX_INCLUDE_DIR /usr/local/include)
set(PQXX_LIB_DIR /usr/lib/x86_64-linux-gnu/libpqxx.so)

add_executable(Server src/main.cpp
    include/ThreadPool.h
    src/utils/ThreadPool.cpp


)

if(NOT EXISTS ${PQXX_INCLUDE_DIR})
    message(FATAL_ERROR "PQXX_INCLUDE_DIR not found.")
else()
    include_directories(${PQXX_INCLUDE_DIR})
endif()

if(NOT EXISTS ${PQXX_LIB_DIR})
    message(FATAL_ERROR "PQXX_LIB_DIR not found.")
else()
    link_directories(${PQXX_LIB_DIR})
endif()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost library not found.")
endif()

target_link_libraries(Server ${Boost_LIBRARIES} pqxx pq)

include(GNUInstallDirs)
install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
