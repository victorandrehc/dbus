//
// Created by vaco on 19.04.24.
//

#pragma once
#include <dbus/dbus.h>
#include <string>

namespace dbus {
    class common {
    public:
        static const inline std::string INTERFACE_NAME = "in.dbus.example.interface";
        static const inline std::string SERVER_BUS_NAME = "in.dbus.example.server";
        static const inline std::string CLIENT_BUS_NAME = "in.dbus.example.client";
        static const inline std::string SERVER_OBJECT_PATH_NAME = "/in/dbus_example/server";
        static const inline std::string CLIENT_OBJECT_PATH_NAME = "/in/dbus_example/client";
        static const inline std::string METHOD_NAME = "add_numbers";

        explicit common(const std::string &bus_name): bus_name(bus_name) {};
        bool init();
        virtual bool requestName() = 0;
    protected:



        DBusConnection *conn;
        DBusError dbus_error;
        const std::string& bus_name;
    };

}; // dbus

