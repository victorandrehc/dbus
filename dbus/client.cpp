//
// Created by vaco on 19.04.24.
//

#include <iostream>
#include "client.h"

namespace dbus {
    bool client::requestName() {
        for (uint32_t i = 0; i < REQUEST_NAME_TRIES; i++) {
            const int ret = dbus_bus_request_name(conn, bus_name.c_str(), 0, &dbus_error);
            if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
                return true;
            }
            if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE) {
                sleep(1);
                continue;
            }
            if (dbus_error_is_set(&dbus_error)) {
                break;
            }
        }
        return false;
    }

    void client::run(client *self) {
        if (!self->init()) {
            std::cout << "init failed" << std::endl;
            return;
        }
        if (!self->requestName()) {
            std::cout << "requestName failed" << std::endl;
            return;
        }
        std::cout << "Client is running" << std::endl;
        while (true) {
            uint32_t ret;
            DBusMessage *request;
            request = dbus_message_new_method_call(SERVER_BUS_NAME.c_str(), SERVER_OBJECT_PATH_NAME.c_str(),
                                                   INTERFACE_NAME.c_str(), METHOD_NAME.c_str());

            if (request == nullptr) {
                fprintf(stderr, "Error in dbus_message_new_method_call\n");
                exit(1);
            }
            DBusMessageIter iter;
            dbus_message_iter_init_append(request, &iter);
            
            ret = dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &self->message_str);
            if (!ret) {
                std::cout<<"client: Failed to add argument"<<std::endl;
                continue;
            }
            DBusPendingCall *pending_return;
            ret = dbus_connection_send_with_reply(self->conn, request, &pending_return, -1);
            if (!ret) {
                std::cout<<"client: Failed to send request"<<std::endl;
                continue;
            }
            if (pending_return == nullptr)
            {
                std::cout<<"client: Pending return is null"<<std::endl;
                continue;
            }
            dbus_connection_flush(self->conn);
            std::cout<<"client: Sent a message"<<std::endl;


            dbus_message_unref(request);
            dbus_pending_call_block(pending_return);
            DBusMessage *reply;
            if ((reply = dbus_pending_call_steal_reply(pending_return)) == nullptr)
            {
                std::cout<<"Error in dbus_pending_call_steal_reply"<<std::endl;
                exit(-1);
            }
            dbus_pending_call_unref(pending_return);
            char *s;
            if (dbus_message_get_args(reply, &self->dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
            {
                std::cout<<"client: Got a reply: "<<s<<std::endl;
            }
            dbus_message_unref(reply);

            sleep(1);



        }

    }
} // dbus