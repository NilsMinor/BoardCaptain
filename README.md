# BoardCaptain

This project is a side project for my master thesis where I have to build a FPGA carrier board. This carrier board needs several power supplies and temeprature control. To reuse this work in future projects I decided to focus a bit more on this smart PSU. The control unit is a Atmega32u4 with Arduino bootloader. To simplify programming effort I am using the Arduino language. This accelerates development process and makes it easy to adapt by other people. I am using several open source libraries from third parties and and this software is open to :)

The BoardCaptain PCB is 48mm x 48mm with castleated vias on the left and right side.
![alt-text-1](img/3d_no_components.png?raw=true "") ![alt-text-2](img/3d_components.png?raw=true "")

## Third party libraries

Since this project is based on third party libraries I'd like to think that you are familiar with the topic of arduino library management. The folowing libraries are used in this project:

 - Linduino for SM-BUS communication (http://www.linear.com/solutions/linduino)
 - 


 ## Tasklist

Short overview of things to be implemented in the future

 ### Power
 - [ ] Implement ZL2102 drivers for PMBus communication
 ### Communication
 - [ ] Implement CLI communication to get and set the following data
 #### Function
 - [ ] Set output voltages of the ZL2102 dcdc converters
 - [ ] Read output current of the ZL2102 dcdc converters
 - [ ] Read input voltage of the ZL2102 dcdc converters
 - [ ] Implement FAN Controller functionallity





