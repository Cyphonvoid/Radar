#include <Radar.h>

                                                 /*  ***[𝐁𝐔𝐆 𝐑𝐄𝐏𝐎𝐑𝐓]***                    
     [𝐁𝐔𝐆 𝐅𝐎𝐔𝐍𝐃 - DATED : May 17, 2022(𝐒𝐎𝐋𝐕𝐄𝐃❗)] : Process() doesn't return values properly.
     [𝐒𝐎𝐋𝐔𝐓𝐈𝐎𝐍  : Dated May 18, 2022] : Process(Exp) could return value to the variable (Exp) however for some reason Same variable Exp's value couldn't be updated when returned. 
                  Statement : Exp = Process(Exp); had to be changed to Exp1 = Process(Exp); Same issue had been noted inside Process function aswell and same SOL has been applied there.*/

      
void INSTRUCTIONS(){
   /*Instructions*/
   Serial.println(F("                              𝐈𝐍𝐒𝐓𝐑𝐔𝐂𝐓𝐈𝐎𝐍𝐒"));
   Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

   Serial.println(F("To Exit Application press 'e'or 'E'"));
   Serial.println(F("Back button - 'e' or 'E'"));
   for(byte i = 0; i < 3; i++){Serial.println();}

   
   Serial.println(F("Press any key to exit"));
   FILTER();
   WAIT();
}

void RADAR(){
  Serial.println("Radar Surviliance System is now active...");
}


void CALCULATOR(){

  /*To store Mathematical expression*/
   String Exp;
   String Exp1 = "";
   String Exp2; 
   bool EXIT = false;
   byte Count = 0; 
   
   Serial.println(F("                            __________________________ "));
   Serial.println(F("                           /🔱 𝐀𝐫𝐢𝐭𝐡𝐦𝐞𝐭𝐢𝐜 𝐂𝐚𝐥𝐜𝐮𝐥𝐚𝐭𝐨𝐫. 🔱/ "));
   Serial.println(F(" ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));   
   Serial.println(F(" 𝐄𝐧𝐭𝐞𝐫 𝐚𝐧𝐲 𝐚𝐫𝐢𝐭𝐡𝐦𝐞𝐭𝐢𝐜 𝐦𝐚𝐭𝐡𝐞𝐦𝐚𝐭𝐢𝐜𝐚𝐥 𝐞𝐱𝐩𝐫𝐞𝐬𝐬𝐢𝐨𝐧 𝐭𝐨 𝐞𝐯𝐚𝐥𝐮𝐚𝐭𝐞. 𝐏𝐫𝐞𝐬𝐬 (𝐏) 𝐭𝐨 𝐞𝐯𝐚𝐥𝐮𝐚𝐭𝐞 𝐞𝐱𝐩𝐫𝐞𝐬𝐬𝐢𝐨𝐧 "));
   for(byte i = 0; i < 4; i++){Serial.println();}

   while(true){
    
     while(true){
       FILTER();
       WAIT();
       
       Exp = System.Data.Recieve();
  
       if((Exp == "E") or (Exp == "e")){
          EXIT = true;
          break;
       }

       else if((Exp == "P") or (Exp == "p")){
         Serial.println(Exp1);
         break;
       }
       Exp2 = Process(Exp);
       /*Process the expression as String to convert it into Usable form*/
       Exp1 = (Exp1 == "") ? Exp2 : Exp1  +  Exp2;
       if(Count == 0){
        Serial.print(F("𝐄𝐐𝐔𝐀𝐓𝐈𝐎𝐍 :- "));
       }
       
       Serial.print(((Count == 0) ? "" : "             "));
       Serial.println(Exp2);
       
       Count++;
     }

   Count = 0; 
   EVALUATE(Exp1);
     
   if(EXIT == true){
      EXIT = false;
      break;
   }
  }
}


String Process(String Word){
  /*Process the equation which is string to filter out unwanted elements*/
  //NOTE[!] :- This system is not completely filtering out unwanted elements
  String STR;
  char Grbg = '\f';
  
  
  /*Filter and reset unwanted values to a common value*/
   for(byte i = 0; Word[i] != '\0'; i++){
     if(((Word[i] >= 'A') and (Word[i] <= 'z')) and (Word[i] != 't')){
        Word[i] = Grbg;
     }
   }
   delay(10);
   /*Remove all the unwanted values*/
   STR = System.Data.Remove(Word, Grbg);

 return STR;  
}



byte EVALUATE(String Exp){   

    //[1] Concept converting a string into an actual expression
    //[2]Using a algorithm to process string to make calculator
}
