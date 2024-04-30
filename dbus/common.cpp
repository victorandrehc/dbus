//
// Created by vaco on 19.04.24.
//

#include "common.h"

namespace dbus {


    bool common::init() {
        dbus_error_init(&dbus_error);
        conn = dbus_bus_get(DBUS_BUS_SESSION, &dbus_error);
        return !dbus_error_is_set(&dbus_error) && conn;
    }


} // dbus