cmake_minimum_required(VERSION 3.20)
project(dbus_example)

set(CMAKE_CXX_STANDARD 20)
#find_package(DBus REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)
include_directories(${DBUS_INCLUDE_DIRS}
dbus)


add_executable(main_server main_server.cpp
        dbus/server.cpp
        dbus/client.cpp
        dbus/common.cpp)
target_link_libraries(main_server ${DBUS_LIBRARIES})

add_executable(main_client main_client.cpp
        dbus/server.cpp
        dbus/client.cpp
        dbus/common.cpp)
target_link_libraries(main_client ${DBUS_LIBRARIES})
