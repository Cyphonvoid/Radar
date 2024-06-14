#include "Serial.h"

int echoPin = 8;
int trigPin = 7;
int distance = 0;

int min_range = 2;
int max_range = 15;

int pingPin = 10;
int digPingPin = 13;


SerialChannel serial;
void setup() {
  // put your setup code here, to run once:
  serial.channel0().port().begin(115200);
  serial.channel1().port().begin(115200);
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(digPingPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = calculateDistance();
  Serial.println(distance);
  bool within_range = withinRange(min_range, max_range, distance);

  if(within_range == true){
    distance = trim(distance);
    analogWrite(pingPin, distance);
    digitalWrite(digPingPin, HIGH);
    String result(distance);
    result = "+"+result+"-";
    char *ptr = &result[0];
    serial.channel1().port().write(ptr);
    delay(20);
    //serial.channel0().port().write(1);
  }
  else{
    analogWrite(pingPin, 0);
    digitalWrite(digPingPin, LOW);
    serial.channel1().port().write(0);
    //serial.channel0().port().write(0);
  }
}

bool withinRange(int range1, int range2, int value){
  if(value >= range1 && value <= range2){
    return true;
  }

  else{
    return false;
  }
}

int trim(int value){
  if(value < min_range){
    return 0;
  }
  else if(value > max_range){return 255;}

  return value;
}

int calculateDistance(){ 
  int duration = 0;
  int distance = 0;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}