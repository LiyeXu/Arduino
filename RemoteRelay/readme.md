## Remote Relay ##

This is a very basic prototype project shows how you can turn on/off your AC, lamp or air cleaner via Internet. (so called IoT or LoL? Whatever...)

The essential components are:

- a piece of bread-board based hardware to handle the IR signals and electric relay;
- some code sketches in C (for [Arduino](http://www.arduino.cc/)) and Lua (for [ESP8266](http://espressif.com/en/products/esp8266/) w/ [NodeMCU](http://www.nodemcu.com/index_en.html) ROM) to drive the hardware;
- a [TCP client](https://play.google.com/store/apps/details?id=com.sollae.eztcpclient) to setup the WIFI connection;
- a Linux server w/ a public IP running [MQTT server](https://github.com/emqtt/emqttd);
- a [MQTT client](http://mqttfx.org/) to send the operation commands;

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB02.jpg)
 
![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB01.jpg)