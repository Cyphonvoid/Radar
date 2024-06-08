
# Radar Project

Radar project is an active online surveillance system designed for in house motion detection equiped with HC SR04 40Khz high frequency ultrasonic sensor, MG 90S 9g Micro Servo motor and NodeMCU ESP8266 2.4ghz WiFi microcontroller. System self hosts Webserver using NodeMCU to provide RESTful Api calls to provide real-time data. System is fully integrated with real-time AI assistant support for efficient data interpretation and processing providing real-time insights into situations within houses.

# Parts Used

1) Arduino Mega ATMEGA 2560 
2) Arduino Uno
3) NodeMCU WiFi microcontroller
4) HC SR04 40khz Ultrasonic sensor
5) 5v MG 90S 9g Servo Motor
6) Regular 1.5v led
7) 12v X-10 Connectivity hobby On/Off switches.


# Code Design & Implementation

# RADAR Microcontrollers
1) NodeMCU WebServer
NodeMCUWebServer.ino file defines and hosts primary webserver used to interaction by hosting RESTful API url routes. Creates it's own access point hosted at http://webserver/radarStatus

2) ArduinoMega 2560
RadarHead.ino files implements code designed to use ultrasonic sensor to detect motion

3) Arduino Uno
Radar.ino files implements the code necessary to drive the servo motor 180 degree in sweep motion to cover wide area.

# Why two separate arduinos for this task?
specific Arduino MEGA 2560 model which has been used in this project doesn't have enough power to provide sufficient current for both Ultrasonic detection and sweeping motion using Servo.


# RADAR GenAI
This component allows the radar motion detection data to be directly sent to python client running within local network. Python Client then forwards the data using OpenVisualAI Api which injects data directly into long term memory of the llama3 AI model. 

# RADAR CUSTOM UI
Radar project can also be integrated with an UI interface as well complete with offline account signup. In order to use CustomUI in arduino
first combine both folders together in arduino (Microcontroller & CustomUI) then navigate to the 1_Terminal.ino file and Simply Add your entry point of your program for invokation directly controlled by UI. Custom UI provides a wrapper to include in projects and use it. 