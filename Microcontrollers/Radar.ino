#include <Servo.h>


//create servo object to control a servo
Servo myservo; 

//variable to store the servo position
int pos = 0;  
const int trigPin = 7;
const int echoPin = 8;

void setup() {
  // attaches the servo on pin 9 to the servo object
  myservo.attach(9);  
  Serial.begin(115200);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // goes from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) { 
    //tell servo to go to position in variable 'pos'
    myservo.write(pos);              
    delay(7);             
  }
    
// goes from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) { 
    // tell servo to go to position in variable 'pos'
    myservo.write(pos);              
    delay(7);     
  }
}
