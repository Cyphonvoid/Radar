#include "System.h"
#include "zxCalculator.h"
/*
 *  [INTRODUCTION]
 *  System.h file has the class "System" this basically provides utility functions to create Custom Pages like Login(), Register and more. 
 *  this class also handles and supports ACCOUNT class (Inside UserObject.h) to basically Manipulate objects, Object Data and much more. 
 *  
 *  SubSystem.h is a file which includes sub-classes for System class. Sub classes actually package related functions together in one class.
 *  
 *  I have also added terminal which runs in void loop. The purpose is to use terminal to access application instead of directly accessing application so we can customize and manipulate
 *  Pages and programs. Terminal acts as place holder for any extra program that will run and be accessed seperately from terminal. Currently Terminal has three functions included. 
 *  
 */

Calculator Calculator; 

const byte Isize = 3;
ACCOUNT *User, *User1;  /*Pointer required in AccountSetting, this is used in many functions for various purposes like in zChat probably*/
ACCOUNT ACCOUNT[Isize]; /*Array of objects has been declared in which actual Users are contained, these are blank and empty objects and when Account is created 
                          attributes of a random Object is filled with that information and it finally represents a actual user*/
                          
SYSTEM System(Isize, ACCOUNT[0].Index);  


/*These Variables are used for HomePage function to display lot of things*/
String Login = "𝐋𝐨𝐠𝐈𝐧[𝐋]";
String SignUP = "𝐒𝐢𝐠𝐧𝐔𝐩(U)";
String Logout = "𝐋𝐨𝐠𝐨𝐮𝐭(U)";
String Chats = "𝐂𝐡𝐚𝐭𝐬(𝐂)"; 
String LogIn = Login;        
String Notify = "";
String SignUp = SignUP;
String CHATS = "  /   🎮 " + Notify + Chats;

long int GSSID = 0; 

void setup(){
  /* Pre-UI To guide user to use Application*/
  Serial.begin(115200);
  delay(50);
  
}


void loop(){

 /* Application Call, This function is used to call the actual Application and A generate account feature.
    The reason it is not included inside the application is because you would generate account before accessing the application
    */
    TERMINAL();
}


void APPLICATION(){
     /*This is the actual Application Inside this function it calls the home Page of the application*/
     HomePage();
}


/***********************Functions*********/
int FILTER(){
  byte T = 0; 
  /* Filters out the Serial buffer to make space for new values*/
  for(byte i = 1; Serial.available() >= i; T++){
    Serial.read();   
  }
 
/*Return the number of times loop has run, no of loop isn't necessary to return and niether it has been used in code anywhere. But just in case if I need. */
return T;
}

void WAIT(int I = 5){
  

  /*HANGS the control wherever the function is called, this will put the main control of program to hold at a specific line(Where you call it)*/
  while(Serial.available() == 0){
    
  } 
  
  
  //creatng animations using mathemathic functions and msrgin functoin
}

long int Atoi(String str){
 long int res = 0; // Initialize result

 // Iterate through all characters of input string and
 // update result
 for (int i = 0; str[i] != '\0'; ++i) {
     if (str[i]> '9' || str[i]<'0'){
         return -1; 
     }
     res = res*10 + str[i] - '0';
     
 }

 return res;
}

int Function(){

  
}
