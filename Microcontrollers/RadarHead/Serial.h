#include <HardwareSerial.h>


class SerialPort0{
  protected:
   
  public:
    SerialPort0(){
     
    }
    void ClearBuffer(){
      int length = Serial.available();
      if(length > 0){
        for(int i = 0; i < length; i++){
          char c = Serial.read();
        }
      }
    }

    String input(){
      //Clear the buffer first
      ClearBuffer();

      //Check if there's anything in the buffer if not then just wait
      while(Serial.available() == 0){}

      //If buffer is not empty then wait a little bit again because few bytes may still be incoming to complete the string sent
      delay(40);

      //Now since 40 mili seconds should be enough time for all the bits to arrive we can now see the length;
      byte length = Serial.available();

      //Read everything from the Serial buffer
      String word = "";
      for(int i = 0; i < length; i++){
        char c = Serial.read();
        word+=c; 
      }
      return word;
    }

    HardwareSerial port(){
      return Serial;
    }
};

class SerialPort1{
  protected:
   
  public:
    SerialPort1(){
     
    }
    void ClearBuffer(){
      byte length = Serial1.available();
      if(length > 0){
        for(int i = 0; i < length; i++){
          char c = Serial1.read();
        }
      }
    }

    String input(){
      //Clear the buffer first
      ClearBuffer();

      //Check if there's anything in the buffer if not then just wait
      while(Serial1.available() == 0){}

      //If buffer is not empty then wait a little bit again because few bytes may still be incoming to complete the string sent
      delay(40);

      //Now since 40 mili seconds should be enough time for all the bits to arrive we can now see the length;
      byte length = Serial1.available();

      //Read everything from the Serial buffer
      String word = "";
      for(int i = 0; i < length; i++){
        char c = Serial1.read();
        word+=c; 
      }
      return word;
    }

    HardwareSerial port(){
      return Serial1;
    }
};

class SerialPort2{
  protected:
   
  public:
    SerialPort2(){
     
    }
    void ClearBuffer(){
      byte length = Serial2.available();
      if(length > 0){
        for(int i = 0; i < length; i++){
          char c = Serial2.read();
        }
      }
    }

    String input(){
      //Clear the buffer first
      ClearBuffer();

      //Check if there's anything in the buffer if not then just wait
      while(Serial2.available() == 0){}

      //If buffer is not empty then wait a little bit again because few bytes may still be incoming to complete the string sent
      delay(40);

      //Now since 40 mili seconds should be enough time for all the bits to arrive we can now see the length;
      byte length = Serial2.available();

      //Read everything from the Serial buffer
      String word = "";
      for(int i = 0; i < length; i++){
        char c = Serial2.read();
        word+=c; 
      }
      return word;
    }

    HardwareSerial port(){
      return Serial2;
    }
};


class SerialPort3{
  protected:
   
  public:
    SerialPort3(){
     
    }
    void ClearBuffer(){
      byte length = Serial3.available();
      if(length > 0){
        for(int i = 0; i < length; i++){
          char c = Serial.read();
        }
      }
    }

    String input(){
      //Clear the buffer first
      ClearBuffer();

      //Check if there's anything in the buffer if not then just wait
      while(Serial3.available() == 0){}

      //If buffer is not empty then wait a little bit again because few bytes may still be incoming to complete the string sent
      delay(40);

      //Now since 40 mili seconds should be enough time for all the bits to arrive we can now see the length;
      byte length = Serial3.available();

      //Read everything from the Serial buffer
      String word = "";
      for(int i = 0; i < length; i++){
        char c = Serial3.read();
        word+=c; 
      }
      return word;
    }

    HardwareSerial port(){
      return Serial3;
    }
};


class SerialChannel{
  protected:
  SerialPort0 port0;
  SerialPort1 port1;
  SerialPort2 port2;
  SerialPort3 port3;

  int current_port = 0;

  public:
  SerialChannel(){

  }

  void Select(int num){
    current_port = num;
  }

  SerialPort0 channel0(){
    return port0;
  }

  SerialPort1 channel1(){
    return port1;
  }

};
