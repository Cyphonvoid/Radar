/* [ACCOUNT OBJECT] */

class ACCOUNT {
  
  struct Contacts {
    
    /*Sub Attributes*/
    String Name = " ";
    String SendMsg = " ";
    String GetMsg = " ";
    String tempGetMsg = " ";
    long int SSID = 0;
    
  } ACC0, ACC1, ACC2, ACC3, ACC4, ACC5, ACC6;

  /*[MAIN Attributes]*/
 public:
  
  static const byte Index = 5;
  String Name = " ";
  String Pass = " ";
  String Key = " ";
  long int SSID = 0; 
  byte Notify;
  String Notify2; 
  struct Contacts Contacts[Index] = {ACC0, ACC1, ACC2, ACC3, ACC4};

  /*This is friend request*/
  String InviteReq[Index];

  String Initval = " ";
  /*Local Attributes Inaccesible by any other Function*/

  ACCOUNT(){
    for(byte i = 0; i < Index; i++){
      InviteReq[i] = Initval;
    }
  }

  byte FindContact(ACCOUNT *H){

    /*This functions checks an individual Object of anyone has already been registered in Contacts of current user, if yes then return true else false*/
    for(byte i = 0; i < Index; i++){

      if(Contacts[i].Name == H->Name){
        return true; 
      }
    }

    return false; 
  }

  byte FindFriendReq(ACCOUNT *H){

    /*This function finds if the Friend Req exists in current user's list*/

    for(byte i = 0; i < Index; i++){
      if(InviteReq[i] == H->Name){
        return true;
      }
    }

    return false;
  }
  
  byte ContactAvailable(){
    /*Returns true if the User has any contacts available otherwise false*/

    for(byte i = 0; i < Index; i++){
      if(Contacts[i].Name != " "){
        return true;
      }
    }

    return false;
  }


  byte AddContact(ACCOUNT *G){
    /*This function adds a contact to current user's contact list*/
   byte Check = false; 

   
     

     if(Name != G->Name){/*This if statement makes sure that current user doesn't exists in it's own contact list*/
       for(byte i = 0; i < Index; i++){
          if(Contacts[i].Name == Initval){
            Contacts[i].Name = G->Name;
            Contacts[i].SSID = G->SSID;
          return true;
         }
      }

     }
     
     return false;
  }

  byte DeleteContact(ACCOUNT *H){
    /*Deletes a given contact, if succesfully deleted returns true otherwise false*/
    for(byte i = 0; i < Index; i++){
      if((Contacts[i].Name == H->Name) or (Contacts[i].SSID == H->SSID)){
        Contacts[i].Name = " ";
        Contacts[i].SSID = 0;
        Contacts[i].GetMsg = " ";
        Contacts[i].SendMsg = " ";
        return true; 
      }
    }

    return false; 
  }


  byte SendRequestTo(ACCOUNT *G){

    if(Name != G->Name){
     for(byte i = 0; i < Index; i++){
      if(G->InviteReq[i] == Initval){
        G->InviteReq[i] = Name;
        return true;
      }
     }
    }
    return false; 
   }


  byte AcceptReq(ACCOUNT *G){

    for(byte i = 0; i < Index; i++){
      if(InviteReq[i] == G->Name){
        InviteReq[i] = Initval;

        /*Recheck if it actually removed User name from the InviteReq[]*/
        if(InviteReq[i] == Initval){
          return true;
        }
      }
    }

    return false;  
  }


   byte AvailableReq(){
    byte Num = 0; 
    for(byte i = 0; i < Index; i++){
      if(InviteReq[i] != " "){
        Num++;
      }
    }

    return Num;
   }


  byte FriendListSize(){
    return Index; 
  }

  String Notifications(){
    /*Only checks if there are friend requests if yes then return true*/
    for(byte i = 0; i < Index; i++){
     if(InviteReq[i] != Initval){
      Notify2 =  "❗";
      return Notify2;
     }
    }
    Notify2 = "";
    return Notify2; 
  }

 String GetData(char G){
   /*Returns any attribute of the Object*/

   if(G == 'N'){
    return Name;
   }

   else if(G == 'P'){
    return Pass;
   }

   else if(G == 'S'){
    return (String)SSID;
   }

   else if(G == 'K'){
    return Key;
   }
 }


 byte SetAttribute(char H, String Data){
   /*Sets any attribute of object to any value*/
    long int tmpSSID = Data.toInt();
    if(H == 'N'){
      Name = Data;
      return true;
    }

    else if(H == 'S'){
      SSID = tmpSSID;
      return true; 
    }

    else if(H == 'P'){
      Pass = Data;
      return true; 
    }

    else if(H == 'K'){
      Key = Data;
      return true; 
    }

    return false; 
 }


 byte DeleteFriendReq(ACCOUNT *User){
      /*To delete the User you can  Pass  Username of the Object, since the argument is a pointer you would need pass address of the variable*/

      for(byte i = 0; i < Index; i++){
        if(InviteReq[i] == User->Name){

           /*Deletion of the Object from List*/
           InviteReq[i] = Initval;

           /*Confirm deletion before sending true or false*/
           if(InviteReq[i] == Initval){
            return true;
           }

           else{
            return false;
           }
           
        }
      }

      return false;
 }
};
