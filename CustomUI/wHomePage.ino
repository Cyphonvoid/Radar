byte HomePage(){
  char Read;
  byte Input = 0;
  //
  bool APP_EXIT = false;
/*Shows and redirects the user to any desired pages*/


while(true){
    if(System.SSID == 0){
      CHATS = "";
      Notify = "";
      LogIn = Login;
      SignUp = SignUP;
    }
    else{
      User = System.Data.RetrieveUSER(&ACCOUNT[0], (String)System.SSID);
      Notify = User->Notifications();
      CHATS = "  /   🎮 " + Notify + Chats;
      
    }

    
    for(byte i = 0; i < 4; i++){Serial.println();}
    Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
    Serial.println(" Ｅｔｈｅｒｅｕｍ                                                                                                          🔒 " + LogIn + "  /    📋 " + SignUp +  "" + CHATS + "  /  ⚙ 𝐒𝐞𝐭𝐭𝐢𝐧𝐠𝐬(𝐒)");
    Serial.println();
    Serial.println(F("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔"));
    
                                                        
    Serial.println(F("                                                                                                                                                          s/                             "));
    Serial.println(F("                                                                                                                                                          md                             "));
    Serial.println(F("                                                                                                                                                         .MM.                            "));
    Serial.println(F("                                                                                                                                                         oMMo                            "));
    Serial.println(F("                                                                                                                                                        `mMMm`                           "));
    Serial.println(F("                                                                                                                                                        /MMMM:                           "));
    Serial.println(F("                                                                                                                                                        dMMMMy                           "));
    Serial.println(F("                                                                                                                                                       -MMMMMN`                          "));
    Serial.println(F("                                                                                                                                                    ``.hMMMMMMs..`                       "));
    Serial.println(F("                                                                                                                                                `./oo+yMMMMMMMMo+oo/.`                   "));
    Serial.println(F("                                                                                                                                              `/s+-` `dMMMMMMMMy  `-+s+.                 "));
    Serial.println(F("                                                                                                                                            `os:     oMMMMMMMMMM/     -ss.               "));
    Serial.println(F("                                                                                                                                           :h:      -MMMMMMMMMMMN.      .y+              "));
    Serial.println(F("                                                                                                                                          os`      `mMMMMMMMMMMMMd        +y             "));
    Serial.println(F("                                                                                                                                         ss        /MMMMMMMMMMMMMM-        +y            "));
    Serial.println(F("                                                                                                                                        :d`         oMMMMMMMMMMMM+          y+           "));
    Serial.println(F("                                                                                                                                        d/           /NMMMMMMMMN/           .m`          "));
    Serial.println(F("                                                                                                                                       `N`     /d+    :mMMMMMMm:    sh-      m:          "));
    Serial.println(F("                                                                                                                                       `N    :hMMMs`   .dMMMMd.   `yMMNs.    d/          "));
    Serial.println(F("                                                                                                                                        m.`/hNMMMMMh`   `yMMh`   .hMMMMMmo.  m-          "));
    Serial.println(F("                                                                                                                                        mhmMMMMMMMMMd.   `os`   -mMMMMMMMMmyom`          "));
    Serial.println(F("                                                                                                                                       oMMMMMMMMMMMMMm:        :NMMMMMMMMMMMMMho:-.`     "));
    Serial.println(F("                                                                                                                                     `yMMMMMMMMMMMMMMMN/      +NMMMMMMMMMMMMMMMMMNmdhyo- "));
    Serial.println(F("                                                                                                                                    `dMMMMMMMMMNmmhys++:     `+sydmmNNMMMMMMMMMMMMMNmy:` "));
    Serial.println(F("                                                                                                                                    yMMMMMMNmm+-.                 `.-:/ommhhdddhys+-`    "));    
    Serial.println(F("                                                                                                                                   `MMMMNh/.`/s+.                    `/y+`               "));             
    Serial.println(F("                                                                                                                                   .MMNs.      -os/.`            `.:os/`                 "));                 
    Serial.println(F("                                                                                                                                    mh.           -+ooo+//:://+ooo+:`                    "));                    
    Serial.println(F("                                                                                                                                    .                  `.----.`                          "));
    for(byte i = 0; i < 5; i++){Serial.println();}



    /*CONTROL UNIT*/
    while(true){
     FILTER();
     WAIT();

     Read = Serial.read();
     
     /*Application EXIT*/
     if((Read == 'e') or (Read == 'E')){
      APP_EXIT = true;
      break;
     }
     
     /*Read the Input from InputCtrl to see which option User clicked then load that page*/
     Input = InputControl(Read);

     if(Input == false){
      /*InputCtrl will return false when User has entered a wrong option to prevent it from execution*/
      continue;
     }
  
     break;
    }

   /*Final Application Exit*/
   if(APP_EXIT == true){
     APP_EXIT == false;
     break;
   }
  }
}


byte InputControl(char Read){

       /*LOGIN*/
   if((Read == 'l') or (Read == 'L')){
  
    LOGIN();
     if(System.SSID != 0){
        /*Store information of User in these variables to display it on homepage*/
         LogIn =  System.Data.Retrieve((String)System.SSID, System.Data.RetrieveUser(ACCOUNT, (String)System.SSID), System.N);
         SignUp = Logout;
         
        
      }
      
      
      else{
        /*Reset everything back to original */
         LogIn = Login;
         SignUp = SignUP;
         Notify = "";
            
        }
    return true;
   }

      /*REGISTER*/
   else if((Read == 'u') or (Read == 'U')){
    
    if(System.SSID != 0){
       /*When User is logged and presses this button then log user out*/
       System.Logout();
       LogIn = Login;
       SignUp = SignUP;
       Notify = "";
       return true;
    }
    
    else{
    REGISTER();
    }
    return true;
   }
      
      /*CHAT*/
   else if((Read == 'c') or (Read == 'C')){

    if(System.SSID == 0){
      /*Deactivate this button when User isn't logged in*/
      
      return false;
    }
    else{
      /*Activate this when user is logged in, this means System.SSID has a valid SSID stored*/
      CHAT(System.SSID);
      return true;
    }
   
    
   }
     /*SETTINGS*/
   else if((Read == 's') or (Read == 'S')){
    SETTINGS();
    return true;
   }


   else{
    return false;
   }
}
