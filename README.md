# README 
This is a basic dbus example. By compilling this example two targets will be generated, main_server and main_client, containing respectivelly the server and the client application. On this Exapmple Client sends a "Hello World" message by which the server answers with another "Hello World" message via a dbus method message. 

# Compilling 
```
mkdir build
cd build
cmake ..
ninja all
```