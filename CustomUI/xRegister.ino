

/*Registration*/

byte REGISTER(){
  bool Y = false;
  byte Break = 0;
  String Name;
  String Pass;
  String Key;
  int SSID;
 /*Display Inittial Text*/
 for(byte i = 0; i < 6; i++){}
 Serial.println(F("𝐁𝐚𝐜𝐤(𝐄)                         _____________________"));
 Serial.println(F("                               /𝐂𝐑𝐄𝐀𝐓𝐄 𝐍𝐄𝐖 𝐀𝐂𝐂𝐎𝐔𝐍𝐓/"));
 Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));


 
 Serial.println(F("                         __________________"));
 Serial.println(F("                        |𝐄𝐧𝐭𝐞𝐫 𝐧𝐞𝐰 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞|"));
 Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔ "));

 /*  [USERNAME SECTION]
  1) Name can't be any longer than 14 Characters
  2) Username should be unique (Can't have a username that already exists)
  */
while(true){
 while(true){
     FILTER();
     WAIT();
    
    
     /*Store Name*/
     Name = System.Data.Recieve();
   
     /*Process Data*/
     Name = System.Data.Remove(Name, ' ');
     byte Len = System.Scan.StringLen(Name);
     byte Bool = System.Scan.Verify(&ACCOUNT[0], Name);

     if((Name == "E") or (Name == "e")){
      Break++;
      break;
     }
     Serial.println("𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞:-               " + Name);


     if((((Len >= 14) or (Len <= 5)) and (Bool == true)) or ((Len >= 14) or (Len <= 5)) or (Bool == true)){

        if(Len >= 14){
          /*Display when length isn't VALID*/
           
           Serial.println(F("                         ❌ 𝐄𝐑𝐑𝐎𝐑[𝟏]:-  𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐦𝐮𝐬𝐭 𝐧𝐨𝐭 𝐞𝐱𝐜𝐞𝐞𝐝 𝐦𝐨𝐫𝐞 𝐭𝐡𝐚𝐧 𝟏𝟒 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬 ❗ ❗ "));
           for(byte i = 0; i < 1; i++){Serial.println();}
           Y = true;
          continue;
        }

        if(Len <= 5){
         
          Serial.println(F("                         ❌ 𝐄𝐑𝐑𝐎𝐑[𝟐]:- 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐦𝐮𝐬𝐭 𝐛𝐞 𝐚𝐭 𝐥𝐞𝐚𝐬𝐭 𝟔 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬 𝐥𝐨𝐧𝐠 ❗❗"));
          for(byte i = 0; i < 1; i++){Serial.println();}
          Y = true;
          continue;
        }

        if(Bool == true){
          /*Display when the Username isn't VALID*/
          
          Serial.println(F("                         ❌ 𝐄𝐑𝐑𝐎𝐑[𝟑]:- 𝐓𝐡𝐢𝐬 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐡𝐚𝐬 𝐚𝐥𝐫𝐞𝐚𝐝𝐲 𝐛𝐞𝐞𝐧 𝐭𝐚𝐤𝐞𝐧 ❗❗"));
          for(byte i = 0; i < 2; i++){Serial.println();}
          Y = true;
         continue;
        }

        
     }

     
  /*Only display when the User has got atleast one information wrong*/
  if(Y == true){
    Serial.println(F("                        ✔ 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐯𝐞𝐫𝐢𝐟𝐢𝐞𝐝 ❗"));
  }
  break;
 }



 /*   [PASSWORD SECTION]
   1) Store the password
   2) Filter out unwanted characters
   3) Password must not be any longer than 14 characters
   4) Password must not already exists
  
  */
 if(Break != 0){break;}
 Serial.println(F("                         _________________"));
 Serial.println(F("                        |𝐄𝐧𝐭𝐞𝐫 𝐧𝐞𝐰 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝|"));
 Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔"));
 bool Loop = false;
 bool T = false;
  while(true){
    
    FILTER();
    WAIT();

    /*store the password*/
    Pass = System.Data.Recieve();
    
    /*Process the data*/
    Pass = System.Data.Remove(Pass, ' ');
    byte Len = System.Scan.StringLen(Pass);
    bool Letter = System.Scan.CapitalLetter(Pass);
    bool BOOL = System.Scan.Verify(&ACCOUNT[0], Pass);
   
    if((Pass == "E") or (Pass == "e")){
      Break++;
      break;
     }

    Serial.println("𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝:-               " + Pass);
   
    if(Len <= 5){
      Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑[𝟏]:- 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐦𝐮𝐬𝐭 𝐛𝐞 𝐚𝐭 𝐥𝐞𝐚𝐬𝐭 𝟔 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬 𝐥𝐨𝐧𝐠 ❗❗"));
      Serial.println();
      Loop = true;
    }

     if(Len >= 15){
        Serial.println(F("❌ 𝐄𝐑𝐑𝐎𝐑[𝟏]:- 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐦𝐮𝐬𝐭 𝐧𝐨𝐭 𝐞𝐱𝐜𝐞𝐞𝐝 𝐦𝐨𝐫𝐞 𝐭𝐡𝐚𝐧 𝟏𝟓 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬 ❗❗"));
        Serial.println();
        Loop = true;
       }

    if(Letter == false){
      Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑[𝟐]:- 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐦𝐮𝐬𝐭 𝐜𝐨𝐧𝐭𝐚𝐢𝐧 𝐚𝐭 𝐥𝐞𝐚𝐬𝐭 𝐨𝐧𝐞 𝐮𝐩𝐩𝐞𝐫𝐜𝐚𝐬𝐞 𝐥𝐞𝐭𝐭𝐞𝐫 ❗❗"));
      Serial.println();
      Loop = true;
    }

    if(BOOL == true){
      Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑[𝟑]:- 𝐓𝐡𝐢𝐬 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐡𝐚𝐬 𝐚𝐥𝐫𝐞𝐚𝐝𝐲 𝐛𝐞𝐞𝐧 𝐭𝐚𝐤𝐞𝐧 ❗❗ "));
      Serial.println();
      Loop = true;
    }

    if(Loop == true){
      /*If Loop is true then it Loops back again to the starting to store information*/
      T = true;
      Loop = false;
      continue;
    }

    
    if(T == true){
      /*Display after User has typed any info incorrect at least once*/
      Serial.println(F("                        ✔ 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐯𝐞𝐫𝐢𝐟𝐢𝐞𝐝 ❗"));
    }
   
   break;
  }

 /*  [SECURITY KEY SECTION
   1)Security Key can be anything from one letter to any length less than 8
   
  */
 if(Break != 0){break;}
 Serial.println(F("                         ___________________________________"));
 Serial.println(F("                        |𝐂𝐡𝐨𝐨𝐬𝐞 𝐚 𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐫𝐞𝐜𝐨𝐯𝐞𝐫𝐲 𝐬𝐞𝐜𝐮𝐫𝐢𝐭𝐲 𝐤𝐞𝐲|"));
 Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

 byte N = 0;
 while(true){
  FILTER();
  WAIT();

  Key = System.Data.Recieve();

  /*Process Data*/
  Key = System.Data.Remove(Key, ' ');
  byte Len = System.Scan.StringLen(Key);
  if((Key == "E") or (Key == "e")){
      Break++;
      break;
     }
     
  Serial.println("                         " + Key);
  if(Len >= 8){
    Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑:- 𝐊𝐞𝐲 𝐦𝐮𝐬𝐭 𝐧𝐨𝐭 𝐞𝐱𝐜𝐞𝐞𝐝 𝐦𝐨𝐫𝐞 𝐭𝐡𝐚𝐧 𝟖 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫 ❗❗"));
    N++;
    continue;
  }

  if(N != 0){
    Serial.println(F("                       ✔ 𝐊𝐞𝐲 𝐯𝐞𝐫𝐢𝐟𝐢𝐞𝐝 ❗"));
  }

  break;
 }
 
  if(Break != 0){break;}/*Exit the registration function when Uses presses "e" or "E"*/ 
  
 /*FINAL REGISTRATION*/
 SSID = System.Generate.SSID();
 System.SSID = 0;

 User = System.Data.EntryAvailable(&ACCOUNT[0]);
 
 bool REG = System.Data.Register(User, Name, Pass, Key, SSID);
 
 
  if(REG == true){
    Serial.println(F("                                             _________________________________________"));
    Serial.println(F("                                            /🔱𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐬𝐮𝐜𝐜𝐞𝐬𝐬𝐟𝐮𝐥𝐥𝐲 𝐫𝐞𝐠𝐢𝐬𝐭𝐞𝐫𝐞𝐝.🔱/"));
    Serial.println(F("                                            ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  "));
    Serial.println("                            𝐔𝐒𝐄𝐑𝐍𝐀𝐌𝐄: "+Name + "    𝐏𝐀𝐒𝐒𝐖𝐎𝐑𝐃: "+Pass + "    𝐒𝐄𝐂𝐔𝐑𝐈𝐓𝐘 𝐊𝐄𝐘: "+Key + "    𝐒𝐒𝐈𝐃: "+SSID);  
    Serial.println();               
    Serial.println(F("                                                    𝐏𝐫𝐞𝐬𝐬 𝐚𝐧𝐲 𝐤𝐞𝐲 𝐭𝐨 𝐄𝐗𝐈𝐓              "));
    }
  else {
    Serial.println(F("                                     ______________________________________________________________________________  "));
    Serial.println(F("                                    / 𝐒𝐨𝐦𝐞𝐭𝐡𝐢𝐧𝐠 𝐰𝐞𝐧𝐭 𝐰𝐫𝐨𝐧𝐠❗ 𝐘𝐨𝐮𝐫 𝐚𝐜𝐜𝐨𝐮𝐧𝐭 𝐜𝐨𝐮𝐥𝐝𝐧❜𝐭 𝐛𝐞 𝐫𝐞𝐠𝐢𝐬𝐭𝐞𝐫𝐞𝐝❗ 𝐏𝐫𝐞𝐬𝐬 𝐚𝐧𝐲 𝐤𝐞𝐲 𝐭𝐨 𝐄𝐗𝐈𝐓 / " ));
    Serial.println(F("                                    ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ "));
    Serial.println(F("                                    [𝐏𝐑𝐎𝐆𝐑𝐀𝐌 𝐒𝐓𝐀𝐓𝐔𝐒]"));
    Serial.println();
    Serial.println(F("                                   𝐑𝐄𝐆 == 𝐅𝐚𝐥𝐬𝐞     [𝐒𝐲𝐬𝐭𝐞𝐦.𝐃𝐚𝐭𝐚.𝐑𝐞𝐠𝐢𝐬𝐭𝐞𝐫() 𝐫𝐞𝐭𝐮𝐫𝐧𝐬 𝐅𝐚𝐥𝐬𝐞 ]  𝐋𝐢𝐧𝐞 𝟐𝟎𝟕"));
    
    if(User == NULL){
       Serial.println(F("                                   𝐔𝐬𝐞𝐫 == 𝐍𝐔𝐋𝐋  [𝐒𝐲𝐬𝐭𝐞𝐦.𝐃𝐚𝐭𝐚.𝐄𝐧𝐭𝐫𝐲𝐀𝐯𝐚𝐢𝐥𝐚𝐛𝐥𝐞() 𝐫𝐞𝐭𝐮𝐫𝐧𝐬 𝐍𝐔𝐋𝐋]  𝐋𝐢𝐧𝐞 𝟐𝟎𝟗"));
    }

    
  }

  FILTER();
  WAIT();

  break;
 }
}
