#include "SubSystem.h"

/*Container class [SYSTEM.h] for storing sub OBJECTS*/

class SYSTEM {
 /*Variables*/

 private:  /*System Data*/
 
     struct LOG {
       /*Data to keep track of current User's login*/
       long int SSID = 0;
         String Name = "";
         String Pass = "";
       /***************/
     };
     
    /*Contains important info about currently logged in user*/
    struct LOG LOG;

 public:  
     
    byte Index = 0; /*Used for registering the User to increment and store other info for next user*/
    byte Isize = 0;
    
    long int SSID = 0; 

    
    char N = 'N';
    char P = 'O';
    char K = 'P';
    char S = 'Q';
    char Nn = 'R';
 
  /*OBJECTS*/
   SCAN Scan;
   DATA Data;
   DISPLAYS Display;
   CREATE Generate; 
   
   
 /*Constructor*/
 SYSTEM(byte Size, byte ACLen){
  Isize = Size; 

  /*Setup for SCAN Object*/
  Scan.Isize = Size;
  
  
  /*Initial Setup for DATA Object*/
  Data.Isize = Size;
  Data.ACLen = ACLen;

  /*Setup for Display Object*/
  Display.Isize = Size; 

  /*Setup for Generate Object*/
  Generate.Isize = Size;
  //CREATE Generate(Isize); 
  
 }

 /*System LOGOUT*/
 void Logout(){
  SSID = 0;
 }
 
  /*Current System Data Loggings*/
  
 long Log_DataIn(String Name, String Pass, long int SSID){
   /*Sets the each variable to arguments to store currently logged in user's info*/
   LOG.Name = Name;
   LOG.Pass = Pass;
   LOG.SSID = SSID;
 }

 String Log_Name(){
   return LOG.Name;
 }

 String Log_Pass(){
  return LOG.Pass;
 }

 long int Log_SSID(){
  return LOG.SSID;
 }

 
 
};
