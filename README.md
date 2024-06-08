
# Radar Project
Radar project is an active online A.I surveillance system designed for in house motion detection equiped with HC SR04 40Khz high frequency ultrasonic sensor, MG 90S 9g Micro Servo motor and NodeMCU ESP8266 2.4ghz WiFi microcontroller. System self hosts Webserver using NodeMCU to provide RESTful Api calls to provide real-time data. System is fully integrated with real-time AI assistant support for efficient data interpretation and processing providing real-time insights into situations within houses.

# Parts Used

1) Arduino Mega ATMEGA 2560 
2) Arduino Uno
3) NodeMCU WiFi microcontroller
4) HC SR04 40khz Ultrasonic sensor
5) 5v MG 90S 9g Servo Motor
6) Regular 1.5v led
7) 12v X-10 Connectivity hobby On/Off switches.


# How does entire project work?
After booting up the radar harware system it self hosts a webserver accessible over pubic internet. A python client running on local network on some device such as PC constantly invoke RESTful API calls to Radar nodeMCU webserver. After getting required data, python client will directly transport data to llama3's long term memory aka MongoDB collections using OpenVisualAI api. Once the data is stored we can use frontend chrome extension in order to directly interact with A.I assistant for real-time insights and feedbacks.

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
This component allows the radar motion detection data to be directly sent to python client running within local network. Python Client then forwards the data using OpenVisualAI Api which injects data directly into long term memory of the llama3 AI model. In order to access A.I assistant navigate to the Frontend folder which will 

# RADAR CUSTOM UI
Radar project can also be integrated with an UI interface as well complete with offline account signup. In order to use CustomUI in arduino
first combine both folders together in arduino (Microcontroller & CustomUI) then navigate to the 1_Terminal.ino file and Simply Add your entry point of your program for invokation directly controlled by UI. Custom UI provides a wrapper to include in projects and use it. 

# RADAR Frontend
Frontend component contains custom UI to interact with llama3 AI assistant which is written in react.js primarily. This component is just simply a chrome extension with configurations specified in manifest.json within Frontend folder. 

1) STEP: Get your frontend ready and compiled to be used. 
To get started do `npm install` this will install all the necessary dependiencies in root directory. Then enter command `npm build` in order to compile the react.js app to be used in chrome extension. You can tweak manifest.json file to fit individual needs. Finally enter `npm start` to start the development server to use it or you can also enter `npm run` to directly run it in your browser.  

2) STEP: Start locally installed A.I model.
If you don't have ollama already installed install ollama using pip, then enter command `ollama run` to run ollama server to interact with llama3. Now run the ai_server.py file as well which is acts as middleware between A.I running locally and Frontend to faciliate conversation by invoking vector database, implementing RAG architecture and much more. 

3) STEP: Run the Radar hardware. 
Now, after following the schematic diagram and assembling all the parts do the following
    - Upload NodeMCUWebServer.ino to nodemcu microcontroller
    - upload RadarHead.ino to ArduinoMega 2560
    - upload Radar.ino to Arduino Uno

Also you can integrate your program with CustomUI as well in order to make things more appealing.
    - Now, connect the hardware to a 7v supply by making there's enough current for every component. 7volts 4000mili amperes charger will work great as well. The servo will start sweeping as soon as hardware system is all connnected and turned on along with nodemcu webserver.

navigate to `http://webserver/` to verify the webserver is running smoothly. It should redirect to '/$update.htm' automatically. You can also check `http//:webserver/radarStatus` to see what it displays, this is route that is being used internally within python client. 


Also make sure you have a way to mount the radar head which has sonar sensor on top on servo motor which will do sweep motion. 
Now you can see, everytime radar detects motion it will light up red led at pin 13, register motion detection through 180 degree sweeping motion with sonar. Now you can ask your A.I assistant about real-time insights into situations. Place this radar setup anywhere in your room wherever you think it needs to be monitored. 

