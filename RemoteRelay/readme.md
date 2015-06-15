## Remote Relay ##

### 0. Overview ###
This is a very basic prototype project shows how you can **build** a thing to turn on/off your AC or air cleaner via Internet. 

(So called IoT? Ok.)

The essential components are:

- a piece of bread-board based hardware to handle the IR signals and electric relay;
- some code sketches in C (for [Arduino](http://www.arduino.cc/)) and Lua (for [ESP8266](http://espressif.com/en/products/esp8266/) w/ [NodeMCU](http://www.nodemcu.com/index_en.html)) to drive the hardware;
- a [TCP client](https://play.google.com/store/apps/details?id=com.sollae.eztcpclient) to setup the WIFI connection;
- a Linux server w/ a public IP running [MQTT server](https://github.com/emqtt/emqttd);
- a [MQTT client](http://mqttfx.org/) to send the operation commands;

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB02.jpg)
 
![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB01.jpg)

### 1. Hardware ###
Well, first of all, find and wire up all these things below:

- Bread board x1.
- 6V1A power adapter x1.
- 5v/3v BB power board x1.
- Arduino Nano board x1.
- ESP8266-01 x1.
- 1K ohm potentiometer x1.
- DS3231 x1.
- IR sender x1.
- IR receiver x1.
- Electric relay x1.
- Buzzer x1.

### 2. Software ###

- The latest NodeMCU firmwares can be found at [here](https://github.com/nodemcu/nodemcu-firmware);
- Yes, you will need a piece of FTDI232 adapter to burn this firmware into ESP8266
- Then use the [NodeMCU Studio](http://bbs.nodemcu.com/t/nodemcu-studio-ban-ben-geng-xin-wei-build20150111-update-to-version-build20150111/64) to upload all [LUA scripts](https://github.com/LiyeXu/Arduino/tree/master/RemoteRelay/ESP8266);
- [Arduino sketches](https://github.com/LiyeXu/Arduino/tree/master/RemoteRelay/LCU) should be complied and uploaded to the Nano board. Depedency Libs can be found at here.