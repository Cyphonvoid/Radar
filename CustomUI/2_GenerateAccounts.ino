
 byte GENERATEACCOUNTS(){

  /*Local Variables*/
  String Read;
  byte T = true;
  byte FreeSpace = 0;
  bool BREAK = false;
 
  FreeSpace = System.Data.FreeSpace(&ACCOUNT[0]);
  
  /*Display Text*/
  Serial.println(F("                                                                     𝐀𝐂𝐂𝐎𝐔𝐍𝐓 𝐆𝐄𝐍𝐄𝐑𝐀𝐓𝐈𝐎𝐍"));
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
  /*Information Display Panel*/
  Serial.println(" 𝐅𝐫𝐞𝐞 𝐬𝐩𝐚𝐜𝐞:- " + (String)FreeSpace +  "  / 𝐓𝐨𝐭𝐚𝐥 𝐋𝐢𝐦𝐢𝐭:- " + (String)Isize); 
  Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));

 while(true){
  Serial.println();
  Serial.println();
  Serial.print(F(" 𝐄𝐧𝐭𝐞𝐫 𝐭𝐡𝐞 𝐧𝐮𝐦𝐛𝐞𝐫 𝐨𝐟 𝐀𝐜𝐜𝐨𝐮𝐧𝐭𝐬 𝐭𝐨 𝐛𝐞 𝐠𝐞𝐧𝐞𝐫𝐚𝐭𝐞𝐝:- "));


  while(true){
    FILTER();
    WAIT();

    /*Take in the Input*/
    Read = System.Data.Recieve();

    /*Display the Number User entered*/
    Serial.println(Read.toInt());
    
    if((Read == "E") or (Read == "e")){
      Serial.println();
      Serial.println(F("[𝐄𝐱𝐢𝐭𝐞𝐝]"));
      BREAK = true;
      break;
    }

     T = GENProcess(Read.toInt());

      if(T == true){
        
         /*Animation*/
         Serial.println();
         Serial.print(F(" 𝐆𝐞𝐧𝐞𝐫𝐚𝐭𝐢𝐧𝐠..."));
         delay(random(50, 400));
         Serial.print(F("."));
         delay(random(50, 400));
         Serial.print(F("..."));
         delay(random(50, 400));
         Serial.print(F(".."));
         delay(random(50, 400));
         Serial.println();
         Serial.println();
         
         System.Display.Database(ACCOUNT);
      }

     else{
         Serial.println(F(" 𝐂𝐨𝐮𝐥𝐝𝐧❜𝐭 𝐆𝐞𝐧𝐞𝐫𝐚𝐭𝐞 𝐀𝐧𝐲 𝐀𝐜𝐜𝐨𝐮𝐧𝐭𝐬"));
     }
   break;
  }

  if(BREAK == true){
    BREAK = false;
    break;
  }
  
 }
    
 }



 byte GENProcess(int Lim){

  /*Local Variables*/
  String Name;
  String Pass;
  String Key;
  int SSID;
  byte B = false;

  /*Actual Generation Process*/
  for(byte i = 0; i < Lim; i++){

     /*Check if any User object is empty for storing accounts*/
     User = System.Data.EntryAvailable(&ACCOUNT[0]);

     if(User != NULL){
      
        /*Generate Name, Pass, Key and SSID for the Account*/
        Name = System.Generate.Username(&ACCOUNT[0]);
        Pass = System.Generate.Password();
        Key  = System.Generate.Key();
        SSID = (i == 0) ? System.Generate.USSID() : System.Generate.SSID();

        B = System.Data.Register(User, Name, Pass, Key, SSID);
        
     }
      
    
  }
  if(B == false){
    return false;
  }

  else{
    return true;
  }
 }



 
