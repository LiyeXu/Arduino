## Remote Relay ##

### -1. Warning ###
**Use this instruction at your own risk!**

### 0. Overview ###
This is a very basic prototype project shows how you can **build** a thing to turn on/off your AC or air cleaner via Internet. 

(So called IoT? Fine...)

The essential components are:

- a piece of bread-board based hardware to handle the IR signals and electric relay;
- some code sketches in C (to drive [Arduino](http://www.arduino.cc/)) and Lua (for [ESP8266](http://espressif.com/en/products/esp8266/) w/ [NodeMCU](http://www.nodemcu.com/index_en.html) firmware);
- a [TCP client](https://play.google.com/store/apps/details?id=com.sollae.eztcpclient) to setup the WIFI connection;
- a Linux server w/ a public IP running [MQTT server](https://github.com/emqtt/emqttd);
- a [MQTT client](http://mqttfx.org/) to send the operation commands.

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/Sketch.png)

### 1. Hardware ###

Well, first of all, find and wire up all these things below:

![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB02.jpg)
 
![](https://raw.githubusercontent.com/LiyeXu/Arduino/master/RemoteRelay/BB01.jpg)

- Bread board x1;
- 6V1A power adapter x1;
- 5v/3v BB power board x1;
- Arduino Nano board x1;
- ESP8266-01 x1;
- 1K ohm potentiometer x1;
- DS3231 x1;
- IR sender x1;
- IR receiver x1;
- Electric relay x1;
- Buzzer x1.

### 2. MQTT Broker ###
To make the operation commands reach to your device, a public accessible MQTT broker server must be setup first.

- Setup a Linux VM in [Azure](http://azure.microsoft.com/en-us/services/virtual-machines/) or [AWS](https://docs.aws.amazon.com/zh_cn/AWSEC2/latest/UserGuide/EC2_GetStarted.html)
- Install Erlang;
- Install [emqttd](https://github.com/emqtt/emqttd);
- Setup ACL configuration file to enable MQTT topics: smartrelay/1, smartrelay/1/sensors;
- Start up emqttd service.

### 3. Software ###
Then we need to burn some code snippets into the device, so that this thing can response to our commands.

- The latest NodeMCU firmwares can be found at [here](https://github.com/nodemcu/nodemcu-firmware);
- And yes, you will need a piece of FTDI232 adapter to burn this firmware into ESP8266
- Replace [YOUR_MQTT_BROKER_DOMAIN_NAME] with the VM domain name you setup in step 2
- Then use the [NodeMCU Studio](http://bbs.nodemcu.com/t/nodemcu-studio-ban-ben-geng-xin-wei-build20150111-update-to-version-build20150111/64) to upload all [LUA scripts](https://github.com/LiyeXu/Arduino/tree/master/RemoteRelay/ESP8266);
- [Arduino sketches](https://github.com/LiyeXu/Arduino/tree/master/RemoteRelay/LCU) should be complied and uploaded to the Nano board. Depedency Libs can be found at [here](https://github.com/LiyeXu/Arduino/tree/master/RemoteRelay/Arduino%20Libs).



### 4. Setup WIFI ###
If everything went well... we should be able to light up the broad and connect to its AP (**CyberRelay_1**) from a PC or a mobile device. Now with any TCP client you can send your Internet available WiFi credentials in the format of **[SSID]@pwd@[Password]** to **192.168.4.1:80**. There will be a double beep confirmation once the internet connection is setup.

### 5. MQTT Client ###
Now with any MQTT client, you can connect to the VM 

