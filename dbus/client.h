//
// Created by vaco on 19.04.24.
//

#pragma once

#include <atomic>
#include "common.h"

namespace dbus {

    class client : public common {
    public:
        client(const std::string &bus_name) : common(bus_name){};
        static void run(client *self);
    private:
        virtual bool requestName() override;
        constexpr static uint32_t REQUEST_NAME_TRIES = 100;
        const char *message_str = "Hello World from client";


    };

} // dbus


