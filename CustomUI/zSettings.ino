

byte SETTINGS(){
  char Read;
  byte Loop = 0;
  bool Trigg = false;
  /*Show all settings option*/
 while(true){
 
 Serial.println(F("                                      ________________"));
 Serial.println(F("𝐁𝐚𝐜𝐤 (𝐄)                             /𝐒𝐘𝐒𝐓𝐄𝐌 𝐒𝐄𝐓𝐓𝐈𝐍𝐆𝐒/"));
 Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
 Serial.println(F("  𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫 𝐀𝐜𝐜𝐞𝐬𝐬(𝐀)   /     𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐒𝐞𝐭𝐭𝐢𝐧𝐠𝐬(𝐓)                                                                                  "));
 Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
 for(byte i = 0; i < 4; i++){Serial.println();}
 
 while(true){
   /*Wait until the user chooses an option*/
   FILTER();
   WAIT();
   
   Read = Serial.read();

   if((Read == 'e') or (Read == 'E')){
    /*Exit the settings if user presses Exit*/
    Trigg = true;
    break;
   }

   Loop = SettingsControl(Read);

   if(Loop == 9){
    continue; 
   }
   
   break;
  }
 
  
 if(Trigg == true){
   Trigg = false;
   break;
  }
 
 }
}


byte SettingsControl(char Read){

  if((Read == 'A') or (Read == 'a')){

   AdminCheck();
   return true;
  }

  else if((Read == 'T') or (Read == 't')){
   AccountSettings();
   return true;
  }


  else{
    /* If user presses any other option accidently don't proceed and just keep the control flow on hold*/
    return 9;
  } 
}

byte AdminCheck(){
  static String Admin = "";
  static byte Count = 0; 
  int SSID = System.SSID;
  int SSID2 = 0; 
  String Name;
  String Pass;
  
  /*If it is first time then display this*/
while(true){

   /*Give access if either it's user's first time or user is actually admin who hasn't logged out*/
 if((Admin != "") or (Count == 0)){
  if((GSSID > 9999) or (Count == 0)){
     Admin = AdminAccess();
     
     if(Admin != ""){
       Count = 2;
     }
     
    
  }
 }
  else if((Admin == "") and (Count != 0)){
    while(true){
     /*Ask for password and username*/
     Serial.println(F("                         ____________________ "));
     Serial.println(F("                        |🔓|𝐄𝐧𝐭𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐈𝐃 |"));
     Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔▔▔ "));

     FILTER();
     WAIT();

     Name = System.Data.Recieve();
     if((Name == "E") or (Name == "e")){
      break;
     }
     Serial.println("     𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞         " + Name);

     Serial.println(F("                         _________________ "));
     Serial.println(F("                        |🔑|𝐄𝐧𝐭𝐞𝐫 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝 |"));
     Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔ "));

     FILTER();
     WAIT();

     Pass = System.Data.Recieve();
     
     if((Pass == "E") or (Pass == "e")){
      break;
     }
     
     Serial.println("     𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝         " + Pass);

     bool Y =  System.Scan.Verify(&ACCOUNT[0], Name, Pass);

     if((Y == true) and (Count == 0)){
       Admin = AdminAccess();
       Count = 2;
     }

     if((Y == true) and (Count > 0)){
       User = System.Data.RetrieveUSER(&ACCOUNT[0], Pass);
       String SSID = User->GetData('S');

       if(SSID.toInt() > 9999){
         Admin = AdminAccess();
         Count = 2;
       }

      else{
      Serial.println(F("       𝐘𝐨𝐮 𝐝𝐨𝐧❜𝐭 𝐡𝐚𝐯𝐞 𝐚𝐮𝐭𝐡𝐨𝐫𝐢𝐳𝐞𝐝 𝐚𝐜𝐜𝐞𝐬𝐬 𝐭𝐨 𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫 𝐜𝐨𝐧𝐭𝐫𝐨𝐥𝐬"));
      FILTER();
      WAIT();
     }
     }

     else{
      Serial.println(F("       𝐘𝐨𝐮 𝐝𝐨𝐧❜𝐭 𝐡𝐚𝐯𝐞 𝐚𝐮𝐭𝐡𝐨𝐫𝐢𝐳𝐞𝐝 𝐚𝐜𝐜𝐞𝐬𝐬 𝐭𝐨 𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫 𝐜𝐨𝐧𝐭𝐫𝐨𝐥𝐬"));
      FILTER();
      WAIT();
     }
    break;
   }
  }

 

  break;
 }
}


String AdminAccess(){
  /*Administrator Access where it displays all the options which Admin can access*/
  char Read; 
  byte Loop = false;
  byte Exit = false; 
  String AdminName = "";

  
     
  /*Administrator option Menu*/
  
  while(true){
    if(GSSID > 9999){
      User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)GSSID);
      AdminName = User->Name; 
      }
    for(byte i = 0; i < 4; i++){
      Serial.println();
    }
    Serial.println((" 𝐋𝐎𝐆𝐎𝐔𝐓 𝐀𝐃𝐌𝐈𝐍 𝐔𝐈(𝐔)                                           𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫:- " + AdminName));                                        
    Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
    Serial.println(F(" 𝐃𝐢𝐬𝐩𝐥𝐚𝐲 𝐔𝐬𝐞𝐫 𝐃𝐚𝐭𝐚𝐛𝐚𝐬𝐞(𝐃)      /      𝐃𝐞𝐥𝐞𝐭𝐞 𝐀𝐜𝐜𝐨𝐮𝐧𝐭(𝐋)       /        𝐍𝐞𝐰 𝐀𝐝𝐦𝐢𝐧(𝐍)"));
    Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
    for(byte i = 0; i < 4; i++){Serial.println();}/*Margin to make UI better looking*/

    while(true){
        FILTER();
        WAIT();
    
        Read = Serial.read();
   
        if((Read == 'e') or (Read == 'E') or (Read == 'u') or (Read == 'U')){
           Exit = true;
           break;
        }

        /*Run the option which user chooses*/
        Loop = AdminPanel(Read);

        /*If user presses any wrong key then continue the loop*/
        if(Loop == false){
          continue;
        }
      break;
     }

     if(Exit == true){
      /*It exits and return Name*/
     
       /*Check if user has just checked out options or has actually become a new administrator so that we don't loose that first chance for anyone to become admin*/

      if((Read == 'u') or (Read == 'U')){
         return "";
      }
      if(GSSID > 9999){
          User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)System.SSID);
          String Name = User->GetData('N');
          return Name;
      }
     

       return ""; 
     }
   }
}

byte AdminPanel(char Read){

   if((Read == 'd') or (Read == 'D')){

      System.Display.Database(ACCOUNT);
      return true;
   }

   if((Read == 'n') or (Read == 'N')){
      NewAdmin();
      return true;
   }

   if((Read == 'l') or (Read == 'L')){
      DeleteAccount();
      return true;
   }

  else{
    return false; 
  }
}

byte NewAdmin(){

  /*It registers any user as a new administrator*/
 while(true){
  Serial.println(F("                         ____________________ "));
  Serial.println(F("                        |🔓|𝐄𝐧𝐭𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐈𝐃 |"));
  Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔▔▔ "));

  FILTER();
  WAIT();

  String Name = System.Data.Recieve();
  Name = System.Data.Remove(Name, ' ');
  if((Name == "E") or (Name == "e")){
    break;
  }
  Serial.println("          𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞         " + Name);

  

  Serial.println(F("                         _________________ "));
  Serial.println(F("                        |🔑|𝐄𝐧𝐭𝐞𝐫 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝 |"));
  Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔ "));

  FILTER();
  WAIT();

  String Pass = System.Data.Recieve();
  Pass = System.Data.Remove(Pass, ' ');
  
  if((Pass == "E") or (Pass == "e")){
    break;
  }
  
  Serial.println("          𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝         " + Pass);
  String Y = System.Scan.Verify(&ACCOUNT[0], Name, Pass);

  if(Y == "true"){
    User = System.Data.RetrieveUSER(&ACCOUNT[0], Pass);

    /*Create new USSID*/
    long int USSID = System.Generate.USSID();
   
    /*Set the USSID to SSID attribute in the object*/
    User->SetAttribute('S', (String)USSID);
    
    /*Reset System.SSID to new USSID*/
    String SSID = User->GetData('S');
    GSSID = Atoi(SSID);
    
    Serial.println();
    Serial.println(F("𝐘𝐨𝐮❜𝐯𝐞 𝐛𝐞𝐞𝐧 𝐬𝐮𝐜𝐜𝐞𝐬𝐬𝐟𝐮𝐥𝐥𝐲 𝐫𝐞𝐠𝐢𝐬𝐭𝐞𝐫𝐞𝐝 𝐚𝐬 𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫, 𝐲𝐨𝐮 𝐜𝐚𝐧 𝐚𝐜𝐜𝐞𝐬𝐬 𝐚𝐥𝐥 𝐭𝐡𝐞 𝐨𝐩𝐭𝐢𝐨𝐧𝐬."));
    Serial.println(F("𝐘𝐨𝐮𝐫 𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐋𝐢𝐧𝐤𝐞𝐝 𝐭𝐨 𝐚 𝐦𝐨𝐝𝐢𝐟𝐢𝐞𝐝 𝐒𝐒𝐈𝐃 𝐧𝐮𝐦𝐛𝐞𝐫 𝐜𝐚𝐥𝐥𝐞𝐝 𝐔𝐧𝐢𝐪𝐮𝐞 𝐒𝐒𝐈𝐃 𝐧𝐨(𝐔𝐒𝐒𝐈𝐃), 𝐅𝐨𝐫 𝐞𝐠 :- ❜𝟑𝟒𝟓𝟔𝟑❜."));
    Serial.println("𝐘𝐎𝐔𝐑 [𝐔𝐒𝐒𝐈𝐃 𝐍𝐎] :- " + User->GetData('S'));

    
    //[BUG SOLVED] Date : May 8, 2022. UD behaviour due to using toInt() member of String class on SSID object. Atoi has been used instead to eliminate bug. 
  }
    
  else{
    Serial.println(F("𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐝𝐨𝐞𝐬𝐧❜𝐭 𝐞𝐱𝐢𝐬𝐭𝐬"));
  }
  
  FILTER();
  WAIT();
 
 break;
 }
}


byte DeleteAccount(){
 /*Deletes account of any user, it resets the original Object to default values again which makes it usable for storing other user*/
 String Name; 

  Serial.println(F("           𝐄𝐧𝐭𝐞𝐫 𝐭𝐡𝐞 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧 𝐨𝐟 𝐭𝐡𝐞 𝐚𝐜𝐜𝐨𝐮𝐧𝐭 𝐰𝐡𝐢𝐜𝐡 𝐧𝐞𝐞𝐝𝐬 𝐭𝐨 𝐛𝐞 𝐝𝐞𝐥𝐞𝐭𝐞𝐝 "));
  Serial.println();
  Serial.println(F("                         ____________________ "));
  Serial.println(F("                        |🔓|𝐄𝐧𝐭𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐈𝐃 |"));
  Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔▔▔ "));
 
 while(true){
  FILTER();
  WAIT();

  Name = System.Data.Recieve();

  if((Name == "E") or (Name == "e")){
    break;
  }

  Serial.println();
  Serial.println();
  Serial.println(F("            𝐀𝐑𝐄 𝐘𝐎𝐔 𝐒𝐔𝐑𝐄 𝐘𝐎𝐔 𝐖𝐀𝐍𝐓 𝐓𝐎 𝐃𝐄𝐋𝐄𝐓𝐄❓ 𝐏𝐫𝐞𝐬𝐬 (𝐘/𝐍)"));
  
  char Read;
  while(true){
   FILTER();
   WAIT();

   Read = Serial.read();

   if((Read == 'y') or (Read == 'Y')){
     /*Retrieve which is user has the exact same name, if there's no match for user function will return NULL pointer*/
     User = System.Data.RetrieveUSER(&ACCOUNT[0], Name);

    /*This function will delete the user*/
     bool Y = System.Data.DeleteObject(User, &System.SSID);

     if(Y == true){
        Serial.println(F("𝐓𝐡𝐢𝐬 𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐝𝐞𝐥𝐞𝐭𝐞𝐝 𝐬𝐮𝐜𝐜𝐞𝐬𝐬𝐟𝐮𝐥𝐥𝐲."));
     }

     else if(Y == false){
         Serial.println(F("                     𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐜𝐨𝐮𝐥𝐝𝐧❜𝐭 𝐛𝐞 𝐝𝐞𝐥𝐞𝐭𝐞𝐝"));
         Serial.println();
         Serial.println(F("     [𝐄𝐑𝐑𝐎𝐑]: 𝐒𝐲𝐬𝐭𝐞𝐦.𝐃𝐚𝐭𝐚.𝐃𝐞𝐥𝐞𝐭𝐞𝐎𝐛𝐣𝐞𝐜𝐭() 𝐝𝐢𝐝𝐧❜𝐭 𝐫𝐞𝐭𝐮𝐫𝐧 ❞𝐭𝐫𝐮𝐞❞."));   
      
     }

     if(User == NULL){
        Serial.println(F("                     𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐜𝐨𝐮𝐥𝐝𝐧❜𝐭 𝐛𝐞 𝐝𝐞𝐥𝐞𝐭𝐞𝐝"));
        Serial.println();
        Serial.println(F("     [𝐄𝐑𝐑𝐎𝐑]:𝐒𝐲𝐬𝐭𝐞𝐦.𝐃𝐚𝐭𝐚.𝐑𝐞𝐭𝐫𝐢𝐞𝐯𝐞𝐔𝐒𝐄𝐑() 𝐫𝐞𝐭𝐮𝐫𝐧𝐬 𝐍𝐔𝐋𝐋"));
     }

      FILTER();
      WAIT();
   }

   if((Read == 'n') or (Read == 'N')){
    break;
   }

   
   break;
  }
  
 
  break;
 }

  
}




byte AccountSettings(){
  /*Load the Account Settings option and let the user change his/her Account information*/
  
  
  String INFO; 
  String Name = "𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞";
  String Pass = "𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝";
  String space = "                          ";
  char Read; 

  byte TRIGG = false; 
  while(true){

  Serial.println(F("          [𝐍𝐎𝐓𝐄] :- 𝐖𝐞 𝐰𝐢𝐥𝐥 𝐧𝐞𝐞𝐝 𝐭𝐰𝐨 𝐩𝐢𝐞𝐜𝐞𝐬 𝐨𝐟 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧, 𝐢𝐧 𝐜𝐚𝐬𝐞 𝐲𝐨𝐮 𝐟𝐚𝐢𝐥 𝐭𝐨 𝐫𝐞𝐬𝐞𝐭, 𝐩𝐥𝐞𝐚𝐬𝐞 𝐫𝐞𝐭𝐫𝐲 𝐨𝐫 𝐜𝐨𝐧𝐭𝐚𝐜𝐭 𝐭𝐡𝐞 𝐬𝐲𝐬𝐭𝐞𝐦 𝐀𝐝𝐦𝐢𝐧𝐢𝐬𝐭𝐫𝐚𝐭𝐨𝐫."));             
  Serial.println(F("                           _____________________                                                                          𝐄𝐱𝐢𝐭(𝐄)"));
  Serial.println(F("                          /𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐑𝐞𝐬𝐞𝐭/𝐅𝐨𝐫𝐠𝐨𝐭/ - 𝐏"));
  Serial.println(F("                          ▔▔▔▔▔▔▔▔▔▔▔▔▔"));
  Serial.println(F("                           ______________________"));
  Serial.println(F("                          /𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐑𝐞𝐬𝐞𝐭/𝐅𝐨𝐫𝐠𝐨𝐭 / - 𝐔 "));
  Serial.println(F("                          ▔▔▔▔▔▔▔▔▔▔▔▔▔▔ "));
 
 String Data;
 String Data1; 
  while(true){
    FILTER();
    WAIT();

    Read = Serial.read();

    if(((Read == 'P') or (Read == 'p')) or ((Read == 'u') or (Read == 'U'))){
      /*This section resets the Account Information of User*/
       INFO = ((Read == 'u') or (Read == 'U')) ? Pass : Name;

      /*Ask for Security Key first*/
      Serial.print(space + "𝐄𝐧𝐭𝐞𝐫 𝐒𝐞𝐜𝐮𝐫𝐢𝐭𝐲 𝐤𝐞𝐲 :- ");
      FILTER();
      WAIT();

      Data = System.Data.Recieve();
      
      if((Data == "e") or (Data == "E")){
         /*If user presses this then exit*/
         break;
      }
      
      Serial.println(Data);
      
      /*Ask for the password or the username*/
      for(byte i = 0; i < 3; i++){Serial.println();}
      Serial.print(space + "𝐄𝐧𝐭𝐞𝐫 " + INFO + " :- ");

      FILTER();
      WAIT(); 

      Data1 = System.Data.Recieve();
      
      if((Data == "e") or (Data == "E")){
        break;
      }

      Serial.println(Data1);
      /*Verify both information in order to proceed, otherwise display error and exit*/
      bool D = System.Scan.Verify(&ACCOUNT[0], Data, Data1); 

      
      /*Begin to reset information, only if two Info values Data and Data1 are found to be correc*/
      if(D == true){
        /*Change the INFO value of what it was before to display it on here*/
        
        String SSID = System.Data.Retrieve(Data1, System.Data.RetrieveUser(ACCOUNT, Data1), System.S); 
        INFO = (INFO == Pass) ? "𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞" : "𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝"; /*Changing the INFO to redisplay it inversely this time to save up memory*/
        
        delay(10);  /*Delay helps to prevent any character glitch on display*/
        Serial.println(space + " _____________________");
        Serial.println(space + "|𝐄𝐍𝐓𝐄𝐑 𝐍𝐄𝐖 " + INFO + "|");
        Serial.println(space + " ▔▔▔▔▔▔▔▔▔▔▔▔▔");

       byte Loop = false;
       while(true){
        FILTER();
        WAIT();

        Data = System.Data.Recieve();
        byte Len = System.Scan.StringLen(Data);
        bool Letter = System.Scan.CapitalLetter(Data);
        bool BOOL = System.Scan.Verify(&ACCOUNT[0], Data);

       if((Data == "e") or (Data == "E")){
        break;
       }

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

      if(INFO == Pass){
       if(Letter == false){
          Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑[𝟐]:- 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐦𝐮𝐬𝐭 𝐜𝐨𝐧𝐭𝐚𝐢𝐧 𝐚𝐭 𝐥𝐞𝐚𝐬𝐭 𝐨𝐧𝐞 𝐮𝐩𝐩𝐞𝐫𝐜𝐚𝐬𝐞 𝐥𝐞𝐭𝐭𝐞𝐫 ❗❗"));
          Serial.println();    
          Loop = true;
        }
      }
       if(BOOL == true){
          Serial.println(F("                        ❌ 𝐄𝐑𝐑𝐎𝐑[𝟑]:- 𝐓𝐡𝐢𝐬 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐡𝐚𝐬 𝐚𝐥𝐫𝐞𝐚𝐝𝐲 𝐛𝐞𝐞𝐧 𝐭𝐚𝐤𝐞𝐧 ❗❗ "));
          Serial.println();
          Loop = true;
        }

         if(Loop == true){
          Loop = false;
          continue;
         }

       if((Read == 'p') or (Read == 'U')){
        /*Set pass when User wants to set pass*/
        User = System.Data.RetrieveUSER(&ACCOUNT[0], SSID);
        User->Pass = Data; 
        Serial.println(space + "[❗]𝐘𝐨𝐮𝐫 " + INFO + " 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐮𝐩𝐝𝐚𝐭𝐞𝐝 𝐭𝐨 " + User->Pass);
       }

       else if((Read == 'u') or (Read == 'U')){
        /*Set name when User wants to set name*/
        User = System.Data.RetrieveUSER(&ACCOUNT[0], SSID);
        User->Name = Data;
        Serial.println(space + "[❗]𝐘𝐨𝐮𝐫 " + INFO + " 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐮𝐩𝐝𝐚𝐭𝐞𝐝 𝐭𝐨 " + User->Name);
       }


        Serial.println(space +  "𝐄𝐧𝐭𝐞𝐫 𝐚𝐧𝐲 𝐤𝐞𝐲 𝐭𝐨 𝐞𝐱𝐢𝐭");

        FILTER();
        WAIT();

        

        break;
       }
        
      }

      else if(D == false){
        Serial.println(F("[❗]❌ 𝐓𝐡𝐞 𝐩𝐫𝐨𝐯𝐢𝐝𝐞𝐝 𝐤𝐞𝐲 𝐨𝐫 𝐨𝐭𝐡𝐞𝐫 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧 𝐝𝐨𝐞𝐬𝐧❜𝐭 𝐞𝐱𝐢𝐬𝐭 𝐨𝐫 𝐢𝐬 𝐢𝐧𝐜𝐨𝐫𝐫𝐞𝐜𝐭, 𝐭𝐫𝐲 𝐚𝐠𝐚𝐢𝐧 𝐛𝐲 𝐩𝐫𝐞𝐬𝐬𝐢𝐧𝐠 𝐚𝐧𝐲 𝐤𝐞𝐲 𝐨𝐫 𝐩𝐫𝐞𝐬𝐬 𝐞𝐱𝐢𝐭(𝐄) 𝐭𝐨 𝐞𝐱𝐢𝐭."));
        Serial.println();
        FILTER();
        WAIT();

        char Read = Serial.read();

        if((Read == 'e') or (Read == 'E')){
          break;
        }
        TRIGG = true;
      }

      
    }

  
    
    
    else {
      continue;
    }
    
   break;
  }


  if(TRIGG == true){
      TRIGG = false;
      continue;
    }
  
  break;
  }
  
  
}
