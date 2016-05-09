//Reciever Code

//Libraries
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Initialize Variables and Transciever Code
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int allClearLED = 6;
int landLED = 5;
int emergLED = 3;
int motorPin = 7;
int count = 0;

//Setup Void Code
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(allClearLED, OUTPUT);
  pinMode(landLED, OUTPUT);
  pinMode(emergLED, OUTPUT);
}

//Void Loop Code
void loop(void){

//Checks for radio connection
 if (radio.available()){
   bool terminate = false;  
   
   //Always check for a command to be given from the transmitter
   while (!terminate){
     
     //Read the transmission being given from the transmiter
     terminate = radio.read(msg, 1);      
     
     //If the "emergency protocols" button has been pressed
     if (msg[0] == 33 ){
       Serial.println("WARNING! TERMINATION PROTOCOLS ACTIVATED! COMMENCING EMERGENCY SHUTDOWN!");
       digitalWrite(allClearLED, LOW);
       digitalWrite(landLED, LOW);
       digitalWrite(emergLED,HIGH);
       digitalWrite(motorPin, LOW); 
       delay(100);
       digitalWrite(emergLED,LOW);
       terminate = true;   
       delay(100);
     }
     
     //If the "landing" command has been given
     else if(msg[0] == 66){
       Serial.println("Landing protocols activated. Now landing the quadcopter");
       digitalWrite(motorPin, HIGH);
       digitalWrite(allClearLED, LOW);
       digitalWrite(landLED, HIGH);
       digitalWrite(emergLED,LOW);
       delay(1);
       digitalWrite(motorPin, LOW);
       delay(199);
     }
     
     //If the "all clear" command has been given
     else if(msg[0] == 99){
       Serial.println("All systems normal");
       digitalWrite(allClearLED, HIGH);
       digitalWrite(landLED, LOW);
       digitalWrite(emergLED,LOW);
       digitalWrite(motorPin, HIGH);
       delay(200);
     }
     }
   }
 //If there is no detection of the transmitter, the reciever will shut down the motor
 else{
   Serial.println("WARNING! LOST CONNECTION WITH TRANSMITTER! COMMENCING EMERGENCY SHUTDOWN!");
   digitalWrite(allClearLED, HIGH);
   digitalWrite(landLED, HIGH);
   digitalWrite(emergLED, HIGH);
   digitalWrite(motorPin, LOW);
   delay(200);
 }
}


