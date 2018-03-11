# BoardCaptain

This project is a side project for my master thesis where I have to build a FPGA carrier board. This carrier board needs several power supplies and temeprature control. To reuse this work in future projects I decided to focus a bit more on this smart PSU. The control unit is a Atmega32u4 with Arduino bootloader. To simplify programming effort I am using the Arduino language. This accelerates development process and makes it easy to adapt by other people. I am using several open source libraries from third parties and and this software is open to :)

## Third party libraries

Since this project is based on third party libraries I'd like to think that you are familiar with the topic of arduino library management. The folowing libraries are used in this project:

 - Linduino for SM-BUS communication (http://www.linear.com/solutions/linduino)
 - Serial interpreter (CLI) (https://github.com/scogswell/ArduinoSerialCommand)
