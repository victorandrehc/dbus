//
// Created by vaco on 19.04.24.
//

#pragma once

#include "common.h"

namespace dbus {

    class server : public common {
    public:
        server(const std::string &bus_name) : common(bus_name) {};
        static void run(server *self);
    private:
        virtual bool requestName() override;
        bool popMessage();
        DBusMessage *message;
        const char *reply_str = "Hello from server";

    };

} // dbus


