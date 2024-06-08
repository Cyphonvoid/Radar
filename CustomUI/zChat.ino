
byte CHAT(int tempSSID){
  /*This function is the main page of the Chat system, chat and other requests will be processed by seperate functions*/
 char Read;
 byte LOOP = true;
 byte BREAK = false;
 String FrndReqs; 
 String ShowMsg = "";

 /*Display Friend requests of the user*/
 
 

 while(true){
  User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)System.SSID);
  byte TMP = User->AvailableReq();
  FrndReqs = (TMP == 0) ? "" : (String)TMP; 

  /*Main Title Display*/
  
  Serial.println(F("                                                                     ___________________                                               "));
  Serial.println(F("                                                                    /𝐂𝐨𝐧𝐭𝐚𝐜𝐭𝐬 & 𝐌𝐞𝐬𝐬𝐚𝐠𝐞𝐬/                                               "));
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
  Serial.println((" 𝐁𝐚𝐜𝐤 (𝐄)               //               𝐀𝐝𝐝 𝐬𝐨𝐦𝐞𝐨𝐧𝐞(𝐀)             //               " + FrndReqs + " 𝐅𝐫𝐢𝐞𝐧𝐝 𝐑𝐞𝐪𝐮𝐞𝐬𝐭𝐬(𝑭)           //           𝐌𝐞𝐬𝐬𝐚𝐠𝐞𝐬(𝐌)"));        
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
  /*White space*/
  for(byte i = 0; i < 4; i++){Serial.println();}


  /*Display Contacts of the User*/
  
  User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)tempSSID);
  bool FoundContacts = User->ContactAvailable();

  if(FoundContacts == true){
    /*If any contact is found, display it here*/
      for(byte i = 0; i < ACCOUNT[0].Index; i++){

         /*Displays a symbol if there are any new messages*/
         ShowMsg = (User->Contacts[i].tempGetMsg == User->Initval) ? "" :  " [❗]";
         Serial.println("     " + ((String)(i+1)) + ")     " + User->Contacts[i].Name + ShowMsg);
      }
  }

  else{
    /*If no contact is found then display this message*/
    Serial.println(F("𝐘𝐨𝐮 𝐝𝐨𝐧❜𝐭 𝐡𝐚𝐯𝐞 𝐚𝐧𝐲 𝐜𝐨𝐧𝐭𝐚𝐜𝐭𝐬 𝐲𝐞𝐭, 𝐛𝐮𝐭 𝐲𝐨𝐮 𝐜𝐚𝐧 𝐬𝐞𝐚𝐫𝐜𝐡 𝐨𝐫 𝐚𝐝𝐝 𝐬𝐨𝐦𝐞"));
  }


   while(true){
    FILTER();
    WAIT();

    Read = Serial.read();

    if((Read == 'e') or (Read == 'E')){
      BREAK = true;
      break;
    }

    LOOP = ChatControl(Read);

    if(LOOP == false){
      continue;
    }

    break;
   }



  if(BREAK == true){
    BREAK = false;
    break;
  }
  
 }
  
}


byte ChatControl(char Read){

  if((Read == 'a') or (Read == 'A')){
    CHAT_INVITE();
    return true;
  }

  if((Read == 'f') or (Read == 'F')){
    FRIEND_REQ();
    return true;
  }

  if((Read == 'm') or (Read == 'M')){
    OPEN_CHAT();
    return true;
  }

  else{
    return false;
  }
}



byte CHAT_INVITE(){
  /*This function will Add any account to the user's contact list*/
  String Name; 
  String SSID = (String)System.SSID;
  String SSID2;
  byte Verify; 
  Serial.println(F("             𝐁𝐚𝐜𝐤 (𝐄)"));
  Serial.println(F(" _________________________________"));
  Serial.println(F("|𝐄𝐧𝐭𝐞𝐫 𝐭𝐡𝐞 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐨𝐟 𝐚𝐧𝐲 𝐀𝐜𝐜𝐨𝐮𝐧𝐭.|"));
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

  while(true){
    FILTER();
    WAIT();

    Name = System.Data.Recieve();
    
    if((Name == "E") or (Name == "e")){
      break;
    }
    Verify = System.Scan.Verify(&ACCOUNT[0], Name);
   

      if(Verify == true){

        /*Retrieve the other Account from the name provided by user*/
        User = System.Data.RetrieveUSER(&ACCOUNT[0], Name);

        /*Retrieve current User with SSID stored in System.SSID*/
        User1 = System.Data.RetrieveUSER(&ACCOUNT[0], SSID);

        /*Finally send request to the other account*/
        bool Y = User1->SendRequestTo(User);

        if(Y == true){
          for(byte i = 0; i < 3; i++){Serial.println();}
              Serial.print("𝐅𝐫𝐢𝐞𝐧𝐝 𝐫𝐞𝐪𝐮𝐞𝐬𝐭 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐬𝐞𝐧𝐭 𝐭𝐨 ");
              Serial.println(User->Name);
        }

        else{
          Serial.println(F("[𝐄𝐑𝐑𝐎𝐑]:- 𝐘𝐨𝐮 𝐜𝐚𝐧❜𝐭 𝐬𝐞𝐧𝐝 𝐟𝐫𝐢𝐞𝐧𝐝 𝐫𝐞𝐪𝐮𝐞𝐬𝐭 𝐭𝐨 𝐲𝐨𝐮𝐫𝐬𝐞𝐥𝐟"));
        }
       }

     
    else{
      for(byte i = 0; i < 3; i++){Serial.println();}
      Serial.println(F("𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐜𝐨𝐮𝐥𝐝 𝐧𝐨𝐭 𝐛𝐞 𝐟𝐨𝐮𝐧𝐝, 𝐦𝐚𝐤𝐞 𝐬𝐮𝐫𝐞 𝐬𝐩𝐞𝐥𝐥𝐢𝐧𝐠 𝐢𝐬 𝐜𝐨𝐫𝐫𝐞𝐜𝐭"));
     
    }
   
    
  }
  
}


byte FRIEND_REQ(){
  /*Displays all the recent sent and Recieved Friend requests*/
  String SSID = (String)System.SSID;
  byte Len = ACCOUNT[0].FriendListSize();
  byte Req = false; 
  
  Serial.println(F(" ___________________________________"));
  Serial.println(F("|𝘼𝙘𝙘𝙚𝙥𝙩 𝙍𝙚𝙦𝙪𝙚𝙨𝙩 (𝘼)   //   𝘿𝙚𝙡𝙚𝙩𝙚 (𝘿)|"));
  Serial.println(F(" ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ "));


  
  /*Extract original object of Current User and store it's adress and use it as pointer*/

  User = System.Data.RetrieveUSER(&ACCOUNT[0], SSID);


  /*After finding user,  display all the recieved requests*/
  for(byte i = 0; i < Len; i++){
    
    if(User->InviteReq[i] != " "){
     Serial.println("     𝐘𝐨𝐮 𝐫𝐞𝐜𝐞𝐢𝐯𝐞𝐝 𝐟𝐫𝐢𝐞𝐧𝐝 𝐫𝐞𝐪𝐮𝐞𝐬𝐭 𝐛𝐲 " + User->InviteReq[i]);
     Req = true; 
    }
  }


  while(true){
    FILTER();
    WAIT();

    char Read = Serial.read();

    if((Read == 'e') or (Read == 'E')){      
       break;
    }

   if(Req == true){
    if((Read == 'a') or (Read == 'A')){
      /*If User wants to Accept the Request then proceed to ask user which one, user would like to acceot*/
      for(byte i = 0; i < 2; i++){Serial.println();}
      Serial.println(F("     [*]𝙀𝙣𝙩𝙚𝙧 𝙐𝙨𝙚𝙧𝙣𝙖𝙢𝙚 𝙤𝙛 𝙐𝙨𝙚𝙧, 𝙮𝙤𝙪 𝙬𝙖𝙣𝙩 𝙩𝙤 𝙖𝙘𝙘𝙚𝙥𝙩 𝙧𝙚𝙦𝙪𝙚𝙨𝙩 𝙤𝙛."));

      /*Add the following user in Current User's contact list*/
      while(true){
        FILTER();
        WAIT();

        String Name = System.Data.Recieve();

        if((Name == "E") or (Name == "e")){
          
          break;
        }
        User1 = System.Data.RetrieveUSER(&ACCOUNT[0], Name);

        /*Check if the user already exists or not*/
        bool Y = System.Scan.Verify(&ACCOUNT[0], Name);
        
        /*Check if the user already exists in Current User's lists, if it does then don't add another time*/
        bool H = false; 
        bool T = User->FindContact(User1);

       if(Y == true){
        if(T == false){
           bool J =  User->AddContact(User1);
            User1->AddContact(User);
            H = User->AcceptReq(User1);

            if(H == true){
                Serial.println("     ✔ 𝐂𝐨𝐧𝐭𝐚𝐜𝐭 𝐀𝐝𝐝𝐞𝐝 " + User1->Name);
              }

            /*Check if the user is trying to add himself, which is illegal*/
            if(J == false){
               Serial.println(F(" [𝐄𝐑𝐑𝐎𝐑]:- 𝐘𝐨𝐮 𝐜𝐚𝐧❜𝐭 𝐚𝐝𝐝 𝐲𝐨𝐮𝐫𝐬𝐞𝐥𝐟 𝐢𝐧 𝐲𝐨𝐮𝐫 𝐜𝐨𝐧𝐭𝐚𝐜𝐭𝐬"));
            }
        }
       }

       else{
         Serial.println(F("     ❌ 𝐂𝐚𝐧 𝐧𝐨𝐭 𝐚𝐝𝐝 𝐭𝐡𝐞 𝐠𝐢𝐯𝐞𝐧 𝐜𝐨𝐧𝐭𝐚𝐜𝐭. 𝐄𝐢𝐭𝐡𝐞𝐫 𝐭𝐡𝐞 𝐞𝐧𝐭𝐞𝐫𝐞𝐝 𝐔𝐬𝐞𝐫 𝐈𝐃 𝐝𝐨𝐞𝐬𝐧❜𝐭 𝐞𝐱𝐢𝐬𝐭 𝐨𝐫 𝐢𝐬 𝐚𝐥𝐫𝐞𝐚𝐝𝐲 𝐢𝐧 𝐲𝐨𝐮𝐫 𝐌𝐞𝐬𝐬𝐚𝐠𝐞 𝐥𝐢𝐬𝐭. "));
       }
        
       
       FILTER();
       WAIT();
       break;
      }
     }

      /*If User chooses to delete a friend a request*/
     if((Read == 'd') or (Read == 'D')){
         String Name;
         byte Y;
         
        /*Ask which one does the user wants to delte*/
        for(byte i = 0 ; i < 2; i++) Serial.println();
        Serial.println(F("     [*]𝙏𝙮𝙥𝙚 𝙩𝙝𝙚 𝙐𝙨𝙚𝙧𝙣𝙖𝙢𝙚 𝙤𝙛 𝙩𝙝𝙚 𝙐𝙨𝙚𝙧 𝙩𝙤 𝙙𝙚𝙡𝙚𝙩𝙚 𝙛𝙧𝙞𝙚𝙣𝙙 𝙧𝙚𝙦𝙪𝙚𝙨𝙩 𝙤𝙛"));

        while(true){
          FILTER();
          WAIT();

          Name = System.Data.Recieve();

          if((Name == "E") or (Name == "e")){
            break;
          }

          User1 = System.Data.RetrieveUSER(&ACCOUNT[0], Name);

          bool T =  User->DeleteFriendReq(User1);

          /*Confirm if the account has actually been deleted*/
          bool FindReq = User->FindFriendReq(User1);

          if((FindReq == true) or (User1 == NULL) or (T == false)){
              Serial.println(F("𝐒𝐨𝐦𝐞𝐭𝐡𝐢𝐧𝐠 𝐰𝐞𝐧𝐭 𝐰𝐫𝐨𝐧𝐠❗ 𝐂𝐨𝐮𝐥𝐝𝐧❜𝐭 𝐝𝐞𝐥𝐞𝐭𝐞 𝐭𝐡𝐞 𝐫𝐞𝐪𝐮𝐞𝐬𝐭")); 
          }

          else if((FindReq == false)){
            Serial.println(F("𝐅𝐫𝐢𝐞𝐧𝐝 𝐫𝐞𝐪𝐮𝐞𝐬𝐭 𝐡𝐚𝐬 𝐛𝐞𝐞𝐧 𝐝𝐞𝐥𝐞𝐭𝐞𝐝"));
          }

          break;
        }
        
     }

     
    }

   else{
    continue;
   }
  
   break;
  }  
}


byte OPEN_CHAT(){
   /*Opens up Chat room for each Account to which Current User wants to talk*/
    String Name; 
   /*Initial Setup for the chat*/
   Serial.println();
   Serial.print(F("𝐄𝐧𝐭𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐨𝐟 𝐔𝐬𝐞𝐫, 𝐭𝐨 𝐰𝐡𝐢𝐜𝐡 𝐲𝐨𝐮 𝐰𝐚𝐧𝐭 𝐭𝐨 𝐂𝐡𝐚𝐭:- "));

   while(true){
     FILTER();
     WAIT();

     Name = System.Data.Recieve();

     if((Name == "e") or (Name == "E")){
       break;
     }
     bool T = System.Scan.Verify(&ACCOUNT[0], Name);

     /*Check if The user exists in current user's contact list, if it doesn't then don't start chat*/
     User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)System.SSID);
     User1 = System.Data.RetrieveUSER(&ACCOUNT[0], Name);
     bool Y = User->FindContact(User1);

     if((T == true) and (Y == true)){
      Serial.println(Name);
      CHAT_ROOM(Name);
     }

     else{
      Serial.println();
      Serial.println();
      Serial.println(F("     ❌ [𝐄𝐑𝐑𝐎𝐑]:- 𝐖𝐫𝐨𝐧𝐠 𝐔𝐬𝐞𝐫 𝐈𝐃, 𝐝𝐨𝐞𝐬𝐧❜𝐭 𝐞𝐱𝐢𝐬𝐭𝐬 𝐨𝐫 𝐦𝐢𝐬𝐬𝐩𝐞𝐥𝐥𝐞𝐝."));
     }
   
   }
  
}



byte CHAT_ROOM(String Name){
  /*Here actual Messaging happens*/
  String Message; 
  String SSID = (String)System.SSID;
  byte iLen = 0; 
  byte iLen2 = 0;
  
  for(byte i = 0; i < 3; i++){Serial.println();}
                                                   //[NOTE] Make a function that we can use to have proper indentation when printing anything. 
  Serial.println(F("                               _______________________"));
  Serial.println("                                |" + Name + "   |");
  Serial.println(F("                               ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

  /*Retrieve User object of both Current User and the other one to which the current one wants to chat with*/
  User = System.Data.RetrieveUSER(&ACCOUNT[0], SSID);
  User1 = System.Data.RetrieveUSER(&ACCOUNT[0], Name);
  
  /*Get total size of the actual Contact list*/
  byte Len = User->FriendListSize();

  /*Check at which index does the other User object exists in contact list of Current user*/
  for(byte i = 0; i < Len; i++){
    if(User->Contacts[i].Name == Name){
      iLen2 = i;
      Serial.println("   " + User->Contacts[i].GetMsg);
      break;
    }
  }

  /*Check at which index does the other Current user exists in contact list of Other User object*/
  for(byte i = 0; i < Len; i++){
    if(User1->Contacts[i].Name == User->Name){
      iLen = i; /*Location at which current user exists in contact List of other user*/
      break;
    }
  }
  
  while(true){
    FILTER();
    WAIT();

    Message = System.Data.Recieve();

    if((Message == "E") or (Message == "e")){
      break;
    }

    User1->Contacts[iLen].GetMsg = Message;
    /*This statement here is to show this sign "[!]" when there's a new message.*/
    User1->Contacts[iLen].tempGetMsg = Message;
    User->Contacts[iLen2].SendMsg = Message;

    Serial.println("            " + User->Contacts[iLen2].SendMsg);
  }

  /*After user has checked message the sign will dissapppear*/
  User->Contacts[iLen].tempGetMsg = User->Initval;
}
