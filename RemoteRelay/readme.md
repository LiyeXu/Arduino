## Remote Relay ##

This is a very basic prototype project shows how you can turn on/off your AC, lamp or air cleaner via Internet.

The essential components are:

- a piece of bread-board based hardware to handle the IR signals and electric relay;
- some code sketches in C (for Arduino) and Lua (for ESP8266 NodeMCU) to drive the hardware;
- a modile device w/ a TCP/IP client App installed to setup the WIFI connection;
- a Linux server w/ a public IP running MQTT server;
- a MQTT client to send the operation command;

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB02.jpg)

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB01.jpg)