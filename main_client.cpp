#include "client.h"
int main()
{
    dbus::client client(dbus::common::CLIENT_BUS_NAME);
    client.run(&client);
    return 0;
}