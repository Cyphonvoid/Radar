byte LOGIN(){
  byte Break = 0;
  String Name;
  String Pass;
  String SSID;
  
  Serial.println(F("𝐁𝐚𝐜𝐤 (𝐄)                        ____________________"));
  Serial.println(F("                               /𝐋𝐎𝐆𝐈𝐍 𝐈𝐍𝐓𝐎 𝐀𝐂𝐂𝐎𝐔𝐍𝐓/"));
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

 while(true){
   /*USERNAME LOGIN SECTION*/
   Serial.println(F("                         ____________________ "));
   Serial.println(F("                        |🔓|𝐄𝐧𝐭𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐈𝐃 |"));
   Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔▔▔ "));

  while(true){
    FILTER();
    WAIT();

    Name = System.Data.Recieve();

    if((Name == "e") or (Name == "E")){Break++; break;/*BACK BUTTON*/}
    Serial.println("                     ➜   " + Name);
    break;
  }
  
   if(Break != 0){break;}
   
  /*PASSWORD LOGIN SECTION*/
  Serial.println(F("                         _________________ "));
  Serial.println(F("                        |🔑|𝐄𝐧𝐭𝐞𝐫 𝐩𝐚𝐬𝐬𝐰𝐨𝐫𝐝 |"));
  Serial.println(F("                         ▔▔▔▔▔▔▔▔▔▔▔ "));

  while(true){
    FILTER();
    WAIT();

    Pass = System.Data.Recieve();

    if((Pass == "e") or (Pass == "E")){Break++;break;/*BACK BUTTON*/}
    Serial.println("                     ➜   " + Pass);
   
   break; 
  }

  if(Break != 0){break;}
  /*LOGIN INFO PROCESSING*/


  //[BUG(NOT SOLVED)] : -  Since we're verifying name and passs seperately it dismisses possibility that both info could be legit but yet not belong to same User
  // Thus Anyone can log into the system with anyone's password as long as they're registered in the system.
  
  String VName = System.Scan.Verify(&ACCOUNT[0], Name, Pass);
  
  
     if((VName == "false") or (VName == "N") or (VName == "P")){
      byte Loop = 0;
      
      if(VName == "false"){
        Serial.println(F("                                  ❌ 𝐄𝐢𝐭𝐡𝐞𝐫 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐨𝐫 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐢𝐬𝐧❜𝐭 𝐜𝐨𝐫𝐫𝐞𝐜𝐭, 𝐏𝐥𝐞𝐚𝐬𝐞 𝐦𝐚𝐤𝐞 𝐬𝐮𝐫𝐞 𝐲𝐨𝐮 𝐞𝐧𝐭𝐞𝐫 𝐜𝐨𝐫𝐫𝐞𝐜𝐭 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧 ❗"));
      }

      if(VName == "N"){
        Serial.println(F("                                  ❌ 𝐔𝐬𝐞𝐫𝐧𝐚𝐦𝐞 𝐢𝐬𝐧❜𝐭 𝐜𝐨𝐫𝐫𝐞𝐜𝐭, 𝐏𝐥𝐞𝐚𝐬𝐞 𝐦𝐚𝐤𝐞 𝐬𝐮𝐫𝐞 𝐲𝐨𝐮 𝐞𝐧𝐭𝐞𝐫 𝐜𝐨𝐫𝐫𝐞𝐜𝐭 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧 ❗"));
      }

      if(VName == "P"){
        Serial.println(F("                                  ❌ 𝐏𝐚𝐬𝐬𝐰𝐨𝐫𝐝 𝐢𝐬𝐧❜𝐭 𝐜𝐨𝐫𝐫𝐞𝐜𝐭, 𝐏𝐥𝐞𝐚𝐬𝐞 𝐦𝐚𝐤𝐞 𝐬𝐮𝐫𝐞 𝐲𝐨𝐮 𝐞𝐧𝐭𝐞𝐫 𝐜𝐨𝐫𝐫𝐞𝐜𝐭 𝐢𝐧𝐟𝐨𝐫𝐦𝐚𝐭𝐢𝐨𝐧 ❗"));
      }

      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println(F("              𝐑𝐞-𝐄𝐧𝐭𝐞𝐫(𝐑)                  𝐄𝐱𝐢𝐭 𝐨𝐫 𝐁𝐚𝐜𝐤 (𝐄) "));

      while(true){
       FILTER();
       WAIT();

       char Read = Serial.read();

       if((Read == 'r') or (Read == 'R')){
          /*If user wants to Renter all information*/
          Loop = 2;
       }

       else if((Read == 'e') or (Read == 'E')){
          /*If user wants to quit*/
         Loop = 4;
       }
       
       break; 
      }

    if(Loop == 2){
      continue;/*Go back on Top to Re enter all details*/
    }

    else if(Loop == 4){
      Serial.println(F("                     ...[𝐄𝐱𝐢𝐭𝐞𝐝]... "));
      break;
    }

   break;
  }  
   
      
     SSID = System.Data.Retrieve(Name, System.Data.RetrieveUser(ACCOUNT, Name), System.S);
    // SSID = System.Data.RETRIEVE(Pass, 'S', ACCOUNT);
    
    System.SSID = Atoi(SSID);
    System.Log_DataIn(Name, Pass, SSID.toInt());
    
    //[BUG FOUND!] : - toInt() member of string class can't return long data type integers. NOT SOLVEDD YET!
    /*Show When Login is correct and complete*/
    Serial.println(F("                             _____________________________________________"));
    Serial.println("                         ✔ /𝐀𝐜𝐜𝐨𝐮𝐧𝐭 𝐬𝐮𝐜𝐜𝐞𝐬𝐬𝐟𝐮𝐥𝐥𝐲 𝐯𝐞𝐫𝐢𝐟𝐢𝐞𝐝 // 𝐒𝐒𝐈𝐃 𝐧𝐨 :-  " + (String)System.SSID + "/");
    Serial.println(F("                           ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ "));
    Serial.println(F("                                      𝐏𝐫𝐞𝐬𝐬 𝐚𝐧𝐲 𝐤𝐞𝐲 𝐭𝐨 𝐄𝐗𝐈𝐓 "));

 
    FILTER();
    WAIT();
    
  break;
 }

}
