#include "UserObject.h"

/* Serial.println(Arr[0]);SSES/Obj] */

class SCAN {
  /*Variables*/
 
 public: 
   byte Isize = 0;
  /*Contains scanning/Inspections Functions*/

  
  /*[1]*/
  byte Verify(ACCOUNT *Obj, String Info){
    /*Put &ACCOUNT[0] in first parameter that is Obj*/
    int VSSID = Info.toInt();
    for(byte i = 0; i < Isize; i++){
      
      if(Obj->Name == Info){
        return true;
      }

      else if(Obj->Pass == Info){
        return true; 
      }

      else if(Obj->Key == Info){
        return true;
      }

      if(VSSID != 0){
       if(Obj->SSID == VSSID){
        return true;
       }
      }
      Obj++;
    }

    return false;
  }


  String Verify(ACCOUNT *Obj, String Info1, String Info2){

      int VSSID1 = Info1.toInt();
      int VSSID2 = Info2.toInt();

      byte Name = false;
      byte Pass = false;

      byte N = false;
      byte P = false;
      if((VSSID1 == 0) or (VSSID2 == 0)){
        /*Set Both equal to zero because when evaluating in if statements below to find user it can give false reading since if no integers are given in argument it will 
         * interpret characters in string in arguments as zero. 
         */
        VSSID1 = 2;
        VSSID2 = 2;
      }

      /*ITERATE THROUGH OBJECTS TO FIND A MATCH FOR BOTH INFO*/
    
      for(byte i = 0; i < Isize; i++){

         if(Info1 != Info2){
           Name = (((Obj->Name == Info1) or (Obj->Pass == Info1) or (Obj->Key == Info1) or (Obj->SSID == VSSID1)) == true) ? true : false;
           Pass = (((Obj->Name == Info2) or (Obj->Pass == Info2) or (Obj->Key == Info2) or (Obj->SSID == VSSID2)) == true) ? true : false;
           
           if(Name == true){N = 1;}
           if(Pass == true){P = 1;}
           
           
           if((Name == true) and (Pass == true)){
             return "true";
           }
         }
         
         Obj++;
      }


      if((N == false) and (P == true)){
        return "N";
      }

      else if((N == true) and (P == false)){
        return "P";
      }

      else if(((P == true) and (N == true)) or ((Name == false) and (Pass == false))){
        return "false";
      }
      
      //[UD BEHAVIOUR]!!! Here we have three different if statements returning three different types of data. If function is called to return something and it absolutely sure
      // to return and the function doesn't return anything then it creates a UD behaviour where Control of program bounces around and return back. If one of three if statments was same 
      // as some other one, then it would leave a possibility to return a value, and due to lack of returning a missing possible value and function is called it generated UD.
  }


  /*[2]*/
  byte StringLen(String string){
    /*This function will return the length of string*/
    byte len = 0;
    char *ptr = &string[0];
    
    for(byte i = 0; string[i] != '\0'; i++){
        /*Count only when there is no space character in between*/
        if(*ptr != ' '){
         
         len++;
        }

      ptr++;
    }
    
   return len; 
  }


  /*[3]*/

  byte Search(String Data, char Char){
    /*This function searches if specific letter is present or not*/
    char *Ptr = &Data[0];

    for(byte i = 0; Data[i] != '\0'; i++){
      
      if(*Ptr == Char){
        return i;
      }
      Ptr++;
     }

      if(Ptr != &Data[0]){
       return false;
      }
   }


   byte CapitalLetter(String Word){
     /*Detects Capital letters in a string*/
    for(byte i = 0; Word[i] != '\0'; i++){
     if((Word[i] >= 'A') and (Word[i] <= 'Z')){
      return true;
     }
     
    }
      
   
      return false;   
   }

};


/*[CLASS DATA] for various operatoins on Software Operation*/

class DATA{
 
 public: 
  /*Variables*/
  byte Isize = 0;
  byte ACLen = 0; /*Refers to Contacts Array Length, it is necessary for some functions*/


  String Recieve(){
    delay(40);  // [IMPORTANT], It is important to use delay() just before recieving any data. Otherwise it will cause UD behavious. 

    /*Compile String into a word and then return this string*/
    String Word;
    char Char;
    
    byte LEN = Serial.available();
    char *Ptr = &Char;

    for(byte i = 0; i < LEN; i++){
      Char = Serial.read();

      Word = (i == 0) ? *Ptr : Word + *Ptr;
    }

    return Word;
  }

  String Retrieve(String DataIn, ACCOUNT G, char DataOut){
    /*Retrieve any information about any user*/
     SCAN Scan;
     String *Arr[4];
     long int SSID;
     byte *Nt; 
     byte BL = false;
     if((G.Name == DataIn) or (G.Pass == DataIn) or (G.Key == DataIn) or (G.SSID == DataIn.toInt())){
      BL = true;
     }

     if(BL == true){        //   ASCII
         Arr[0] = &G.Name;  //N   78
         Arr[1] = &G.Pass;  //O   79
         Arr[2] = &G.Key;   //P   80
                            //Q   81
         Nt = &G.Notify;    //R   82
        
         SSID = G.SSID;

         if(DataOut == 'Q'){
          
          String Send = (String)SSID;
          return Send;
         }

         if(DataOut =='R'){
          String Send = (String)*Nt;
          return Send;      /*!![Undefined behaviour]!! Fixed & Found, there was absense of statement return Send; which led to a undefined behaviour*/
         }

         else{
          
          return *Arr[(DataOut-78)];
         }
     }

     else{
      return "false";
     }  
  }


  String RETRIEVE(String DataIn, char DataOut, ACCOUNT ACCOUNT []){

    for(byte i = 0; i < Isize; i++){

       if(DataOut == 'N'){
         if((ACCOUNT[i].Name == DataIn) or (ACCOUNT[i].Pass == DataIn) or (ACCOUNT[i].Key == DataIn) or (ACCOUNT[i].SSID == DataIn.toInt())){
          return ACCOUNT[i].Name;
         }
       }


       if(DataOut == 'P'){
         if((ACCOUNT[i].Name == DataIn) or (ACCOUNT[i].Pass == DataIn) or (ACCOUNT[i].Key == DataIn) or (ACCOUNT[i].SSID == DataIn.toInt())){
          return ACCOUNT[i].Pass;
         }
       }


       if(DataOut == 'K'){
         if((ACCOUNT[i].Name == DataIn) or (ACCOUNT[i].Pass == DataIn) or (ACCOUNT[i].Key == DataIn) or (ACCOUNT[i].SSID == DataIn.toInt())){
          return ACCOUNT[i].Key;
         }
       }

       if(DataOut == 'S'){
          if((ACCOUNT[i].Name == DataIn) or (ACCOUNT[i].Pass == DataIn) or (ACCOUNT[i].Key == DataIn) or (ACCOUNT[i].SSID == DataIn.toInt())){
          return (String)ACCOUNT[i].SSID;
         }
       }
    }
  }


 byte Register(ACCOUNT *A, String Name, String Pass, String Key, int SSID){
   /*Registers the Information to an object registered for that User*/
   if(A == NULL){return false; }
   A->Name = Name;
   A->Pass = Pass;
   A->Key = Key;
   A->SSID = SSID;

   if((A->Name == Name) and (A->Pass == Pass) and (A->Key == Key) and (A->SSID == SSID)){
      return true;
   }

   else{
    return false;
   }
   
 }

 String Remove(String Word, char C){
  /*Removes a character from the String word*/

  char *Ptr = &Word[0];

  /*Scan through the string to search the C*/
  for(byte i = 0; Word[i] != '\0'; i++){
    
   /*Match with C*/
   if(*Ptr == C){

     while(true){

  
     /*Shift all the elements*/
       for(byte G = i; Word[G] != '\0'; G++){
        Word[G] = Word[G+1];
       }

       if(*Ptr == C){
        /*When there's multiple values packed together, the program shifts the rest of the other values, which causes improper filteration
         * This If statement makes sure that there are no leftovers
         */
        continue;
       }
      break; 
      }
   }

 
  Ptr++; 
  delay(4);
  }

 return Word;
 }


 ACCOUNT RetrieveUser(ACCOUNT Obj[], String Info){
    /*Functions returns the address of Object which corresponds to the given argument as a member*/
    int VSSID = Info.toInt();


    for(byte i = 0; i < Isize; i++){
      if(Obj[i].Name == Info){
        return Obj[i];
      }

      else if(Obj[i].Pass == Info){
        return Obj[i];
      }

      else if(Obj[i].Key == Info){
        return Obj[i];
      }

      if(VSSID != 0){
       if(Obj[i].SSID == VSSID){
        return Obj[i];
       }
      }
      
    }

  
 }


 ACCOUNT *RetrieveUSER(ACCOUNT *Account, String Info){
     /*Functions returns the address of Object which corresponds to the given argument as a member*/
    long int VSSID = Info.toInt();
    for(byte i = 0; i < Isize; i++){
      
      if(Account->Name == Info){ 
        return Account;
      }
       
      if(Account->Pass == Info){
        return Account;
      }

      if(Account->Key == Info){
        return Account;
      }

     if(VSSID != 0){
      if(Account->SSID == VSSID){
        return Account; 
      }
     }

      Account++;
    }
     /* !![Undefined Behaviour]!! Fixed & Found */
    /*Always put else condition outside, this return statement was put inside for loop which led to UD behaviour*/
    return NULL;
 }



  byte DeleteObject(ACCOUNT *G, long int *SystemSSID){
    /*Deletes any User/Account from the system*/
    String Blank = " ";
    int Index = G->Index;
    
    G->Name = Blank;
    G->Pass = Blank;
    G->SSID = 0;
    G->Key = Blank;

    for(byte i = 0; i < Index; i++){
      G->InviteReq[i] = Blank;
      G->Contacts[i].Name = Blank;
      G->Contacts[i].SendMsg = Blank;
      G->Contacts[i].GetMsg = Blank;
      G->Contacts[i].tempGetMsg = Blank;
      G->Contacts[i].SSID = 0;
    }

   /*Check if the Account has been deleted*/
   if((G->Name == Blank) and (G->Pass == Blank) and (G->SSID == 0)){

     for(byte i = 0; i < Index; i++){
       if((G->InviteReq[i] != Blank) and (G->Contacts[i].Name != Blank) and (G->Contacts[i].SSID != 0)){
          /*Return false if the Contacts haven't been deleted as well*/
          return false;
       }
     }

    *SystemSSID = 0;
    return true;
   }

  return false;
  }



  ACCOUNT *EntryAvailable(ACCOUNT *H){
    /*Checks if there's any available space to register the User in Array of Object*/
    String Blank = " ";

    for(byte i = 0; i < Isize; i++){
      if((H->Name == Blank) and (H->Pass == Blank) and (H->SSID == 0)){
        return H;
      }
     
      H++;
    }

    return NULL;
    
  }
 
 byte FreeSpace(ACCOUNT *H){
   /*This function will return number of empty/Blank objects available in the system*/
   String Blank = " ";
   byte count = 0; 
   for(byte i = 0; i < Isize; i++){

     if((H->Name == Blank) and (H->Pass == Blank) and (H->SSID == 0)){
       count++;
     }

     H++;
   }
   
  return count; 
 }
};


class DISPLAYS {
 /*This class will display animations/stats/Data */
  public:
   byte Isize = 7;

   byte StringLen(String string){
    /*This function will return the length of string*/
    byte len = 0;
    char *ptr = &string[0];
    
    for(byte i = 0; string[i] != '\0'; i++){
        /*Count only when there is no space character in between*/
        if(*ptr != ' '){
         
         len++;
        }

      ptr++;
    }
    
   return len; 
  }

   String Indent(String string, byte Margin){
      /*This function takes in a string value and then adjusts white spaces accordingly, it uses margin value to set a constant value to set a margin*/
      String whitespace = "";
      int Val = 0; 
      
      /*Get the length of the string*/
      int Len =  StringLen(string);
    
      /*Calculate how much white space is needed*/
      Val = (Margin - Len);
    
      for(byte i = 0; i <= Val; i++){
        whitespace = (i == 0) ? " " : whitespace + " ";
      }
      
    
      return whitespace;
      
}


   byte Database(ACCOUNT Account[]){
     /*Display all the information of all Users registered*/

     String space;
     byte Margin = 15;
     /*Print titles*/
     Serial.print("𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞" + Indent("username", Margin));
     Serial.print("𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝" + Indent("password", Margin));
     Serial.print("𝐊𝐞𝐲" + Indent("key", Margin));
     Serial.println("𝐒𝐒𝐈𝐃");
     Serial.println();
     for(byte i = 0; i < Isize; i++){
       

       /*Print Data*/
       
       Serial.print(Account[i].Name + Indent(Account[i].Name, Margin));
       Serial.print(Account[i].Pass + Indent(Account[i].Pass, Margin));
       Serial.print(Account[i].Key + Indent(Account[i].Key, Margin));
       Serial.println(Account[i].SSID);
     }
     return true;
   }


};


class CREATE {
  /*Class object for functions that generate some output like SSIDs, And other numbers*/
 
 public:
 int Isize;
 ACCOUNT *User;

 CREATE(){
  
 }
 CREATE(int num){
  Isize = num;
 }
 byte Verify(ACCOUNT *Obj, String Info){
    /*Put &ACCOUNT[0] in first parameter that is Obj*/
    int VSSID = Info.toInt();
    for(byte i = 0; i < Isize; i++){
      if(Obj->Name == Info){
        return true;
      }

      else if(Obj->Pass == Info){
        return true; 
      }

      else if(Obj->Key == Info){
        return true;
      }

      if(VSSID != 0){
       if(Obj->SSID == VSSID){
        return true;
       }
      }
      Obj++;
    }

    return false;
  }
  /*[1]*/
  int SSID(){
     byte Arr[4];
     String Num; 
     byte Len = 4;
     int num;

     /* generating 4 digits for the SSID*/
     Arr[0] = random(0, 9);
     Arr[1] = random(0, 9);
     Arr[2] = random(0, 9);
     Arr[3] = random(0, 9);

     /*Converting int to string to stitch 4 digits together*/
     for(byte i = 0; i < Len; i++){
      Num = (i == 0) ? String(Arr[i]) : Num  + String(Arr[i]);
     }

     /*Re-converting string to int to return generated final number*/
     num = Num.toInt() + 2; //Adding 2 to make a unique number
     return num;
    
  }

  long int USSID(){
  
    
     byte Arr[5];
     String Num; 
     byte Len = 5;
     long int num; /*Always use right data types, because int was used instead of long or long int it couldn't store 5 digit numbers because the actual range is 2 byte
                     for int from -32,786 to 32767
                     */
    bool count = false;
    
    while(true){
     
     /* generating 5 digits for the SSID*/
     Arr[0] = random(2, 9);
     Arr[1] = random(0, 9); 
     Arr[2] = random(0, 9); 
     Arr[3] = random(0, 9); 
     Arr[4] = random(0, 9); 

     /*Converting int to string to stitch 5 digits together*/
     for(byte i = 0; i < Len; i++){
      Num = (i == 0) ? String(Arr[i]) : Num  + String(Arr[i]);
      
     }

     /*Re-converting string to int to return generated final number*/
     break;    
    }
    
   return Num.toInt() + 2;
  }


    String Username(ACCOUNT *User){
      static byte Num = 0; 
      String Name = "Jonathan";

      Name = (Num == 0) ? Name : Name + (String)Num;
      Num++;
      return Name;
    }

    String Password(){
      static byte Num = 10; 
      String Pass = "Jonathan";

      Pass = (Num == 0) ? Pass : Pass + (String)Num;
      Num++;
      return Pass;
    }

    String Key(){
      static byte Num = 5; 
      String Pass = "Jonathan";

      Pass = (Num == 0) ? Pass : Pass + (String)Num;
      Num++;
      return Pass;
      
    }

};
