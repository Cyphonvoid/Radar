
/*This is a terminal window which will let programmer or anyone choose which program to execute and exit out. Seperate Programs outside the application can also be implemented*/

byte TERMINAL(){
  /*Variable*/
  String READCODE = "";
  bool Loop;
  
  while(true){ 
   /*Terminal Display*/
   delay(100);
   for(byte i = 0; i < 3; i++){Serial.println();}
   Serial.println(F("    (𝐂) 𝐀𝐫𝐝𝐮𝐢𝐧𝐨 𝐓𝐞𝐫𝐦𝐢𝐧𝐚𝐥  [𝐕𝐞𝐫𝐬𝐢𝐨𝐧 𝟏𝟎.𝟎.𝟏𝟗𝟎𝟒𝟐.𝟏𝟓𝟖𝟔]  "));
   Serial.println(F("     ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
   Serial.println();
   Serial.println();
   Serial.println(F(" >/ 𝗔𝗽𝗽𝗹𝗶𝗰𝗮𝘁𝗶𝗼𝗻 (𝗢)"));
   Serial.println(F(" >/ 𝗚𝗲𝗻𝗲𝗿𝗮𝘁𝗲 𝗔𝗰𝗰𝗼𝘂𝗻𝘁𝘀 (𝗙)"));
   Serial.println(F(" >/ 𝗜𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗶𝗼𝗻𝘀 (𝗜)"));
   //Serial.println(F(" >/ 𝐂𝐚𝐥𝐜𝐮𝐥𝐚𝐭𝐨𝐫 (𝐂)"));

   for(byte i = 0; i < 3; i++){Serial.println();}
   
   while(true){
    FILTER();
    WAIT();

    READCODE = System.Data.Recieve();
    
    Loop = TerminalControls(READCODE);

    if(Loop == false){
      continue;
    }
    
    break;
   }
  
  }

}


byte TerminalControls(String Read){

  /*Open Application*/
  if((Read == "o") or (Read == "O")){
     APPLICATION();

     return true;
  }

  else if((Read == "f") or (Read == "F")){
     GENERATEACCOUNTS();

     return true;
  }

  else if((Read == "i") or (Read == "I")){
     INSTRUCTIONS();

     return true;
  }

  /*else if((Read == "c") or (Read == "C")){
     CALCULATOR();
     
     return true;
  }*/

  else if((Read == "R") || (Read == "r")){
    
  }

  else if((Read == "d")){
    Serial.println(System.Log_Name());
    Serial.println(System.Log_Pass());
    Serial.println(System.Log_SSID());
  }
  
  else{
    return false;
  }
  
}
