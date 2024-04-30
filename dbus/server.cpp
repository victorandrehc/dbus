//
// Created by vaco on 19.04.24.
//

#include <atomic>
#include <iostream>
#include "server.h"

namespace dbus {
    bool server::requestName() {
        const int ret = dbus_bus_request_name(conn, bus_name.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE, &dbus_error);
        return !dbus_error_is_set(&dbus_error) && ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER;
    }

    void server::run(server *self) {
        if (!self->init()) {
            std::cout<<"init failed"<<std::endl;
            return;
        }
        if (!self->requestName()) {
            std::cout<<"requestName failed"<<std::endl;
            return;
        }
        std::cout<<"Server is running"<<std::endl;

        while(true)
        {
            bool ret;
            if (!dbus_connection_read_write_dispatch(self->conn, -1))
            {
                fprintf(stderr, "Not connected now.\n");
                exit(1);
            }
            self->message = dbus_connection_pop_message(self->conn);
            ret = self->message!= nullptr;
            char *str;
            DBusMessage *reply;
            if (!ret)
            {
                std::cout<<"Server: Did not get message"<<std::endl;
                sleep(1);
                continue;
            }
            if (!dbus_message_is_method_call(self->message, INTERFACE_NAME.c_str(), METHOD_NAME.c_str()))
            {
                continue;
            }
            std::cout<<"Server: got a message"<<std::endl;

            ret = dbus_message_get_args(self->message, &self->dbus_error, DBUS_TYPE_STRING, &str, DBUS_TYPE_INVALID);
            if(!ret)
            {
                std::cout<<"Server: Failed to get arguments"<<std::endl;
                continue;
            }
            std::cout<<"Server: Got a message with str: "<<str<<std::endl;
            reply = dbus_message_new_method_return(self->message);
            if(reply == nullptr)
            {
                std::cout<<"Server: Failed to create a new method return"<<std::endl;
                continue;
            }

            ret = dbus_message_append_args(reply, DBUS_TYPE_STRING, &self->reply_str, DBUS_TYPE_INVALID);
            if(!ret)
            {
                std::cout<<"Server: Failed to append argument"<<std::endl;
                continue;
            }
            ret = dbus_connection_send(self->conn, reply, nullptr);
            if(!ret)
            {
                std::cout<<"Server: Failed to send reply"<<std::endl;
                continue;
            }
            std::cout<<"Server: Sent a reply"<<std::endl;
            dbus_connection_flush(self->conn);
            dbus_message_unref(reply);

            sleep(1);


        }




    }

    bool server::popMessage() {
        message = dbus_connection_pop_message(conn);
        return message != nullptr;
    }
} // dbus