
#include "server.h"
int main()
{
    dbus::server server(dbus::common::SERVER_BUS_NAME);
    server.run(&server);
    return 0;
}