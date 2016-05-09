  //Transmitter Code
  
  //Libraries
  #include  <SPI.h>
  #include "nRF24L01.h"
  #include "RF24.h"
  
  //Initialize variables and Transciever Code
  int msg[1];
  RF24 radio(9,10);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  int allClearSwitch = 6;
  int landSwitch = 7;
  int killSwitch = 8; 
  boolean killStatus = false;
  boolean clearStatus = true;
  boolean landStatus = false;
  
  //Setup Void Code
  void setup(void){
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(pipe);
  }
  
  //Loop Void Code
  void loop(void){
    
   //If the termination switch is pushed down
   if (digitalRead(killSwitch) == HIGH){
     
     //Continuously transmit the "emergency protocol" command
     clearStatus = false;
     landStatus = false;
     killStatus = true;
     delay(100);
   }
   
   //If the landing switch is pushed down
   else if (digitalRead(landSwitch) == HIGH){
     
     //Continuously transmit the "landing" command
     clearStatus = false;
     landStatus = true;
     killStatus = false;
     delay(100);
   }
   
   //If the landing switch is pushed down
   else if (digitalRead(allClearSwitch) == HIGH){
     
     //Continuously transmit the "all clear" command
     clearStatus = true;
     landStatus = false;
     killStatus = false;
     delay(100);
   }
   
   
   //Determinne the kind of signal to transmit
   
   //-If the "emergency protocol" command has been given
   if(killStatus == true){
     msg[0] = 33;
   }
   
   //-If the "landing" command has been given
   else if(landStatus == true){
     msg[0]=66;
   }
   
   //-If the "all clear" command has been given
   else if(clearStatus == true){
     msg[0]=99;
   }
   
   //Transmit the coommand to the receiver
   radio.write(msg, 1);
 }

