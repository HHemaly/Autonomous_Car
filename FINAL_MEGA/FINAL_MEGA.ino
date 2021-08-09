#include <Arduino_FreeRTOS.h>
//mp3
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define Slave answer size
#define ANSWERSIZE 1

////////////////////////////////////////////////////////////////////////////
//defining tasks
void headlights(void *pvParameters);
void gear(void *pvParameters);
void parkingg(void *pvParameters);
void mp3 (void *pvParameters);
/////////////////////////////////////////////////////////////////////////////

//Adaptive headlights
int led = 5;           // the PWM pin the LED is attached to
int brightness = 0; 
//////////////////////////////////////////////////////////////////////////
//gear
int seg_a = 45; // declare the variables
int seg_b = 42;
int seg_c = 41;
int seg_d = 39;
int seg_e = 49;
int seg_f = 44;
int seg_g = 47;
int d1=46;
#define joyX A0
#define joyY A1
int  xValue;
int  yValue;
///////////////////////////////////////////////////////////////////////////////////
//parking
const int wh11 = 31;
const int wh12 = 30;
const int wh21 = 6;
const int wh22 = 7;
const int ena = 12;
const int enb = 8;
 int checkp=0;
 int first=0;
 int parking=0;
 int checkdis=1;
 int buzzer=3;
const int triggerRight = 37;
const int echoRight = 36;
long durationRight;
int distanceRight;

const int triggerFront = 33;
const int echoFront = 32;
long durationFront;
int distanceFront;
////////////////////////////////////////////////////////////////////////////////////////////////
//mp3
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
String response = "";
int check=1;
int next=1;
int previous=1;

void setup() {

Serial.begin(9600);
///////////////////////////////////////////////////////////////////////////
//headlights
pinMode(led, OUTPUT);
xTaskCreate(headlights,"headlights",128,NULL,1,NULL);
//////////////////////////////////////////////////////////////////////////
//gear
 pinMode(seg_a,OUTPUT); // configure all pins used to outputs
  pinMode(seg_b,OUTPUT);
  pinMode(seg_c,OUTPUT);
  pinMode(seg_d,OUTPUT);
  pinMode(seg_e,OUTPUT);
  pinMode(seg_f,OUTPUT);
  pinMode(seg_g,OUTPUT);
  pinMode(d1,OUTPUT);
  xTaskCreate(gear,"gear",128,NULL,1,NULL);
  /////////////////////////////////////////////////////////////////////////////
   //parking
     pinMode(triggerRight,OUTPUT);
     pinMode(buzzer,OUTPUT);
  pinMode(echoRight,INPUT);
     pinMode(triggerFront,OUTPUT);
  pinMode(echoFront,INPUT);
  // put your setup code here, to run once:
  pinMode(wh11,OUTPUT);
  pinMode(wh12,OUTPUT);
  pinMode(wh21,OUTPUT);
  pinMode(wh22,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
    xTaskCreate(parkingg,"parkingg",128,NULL,1,NULL);
  ///////////////////////////////////////////////////////////////////////////////
   Wire.begin();
  mySoftwareSerial.begin(9600);


  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
 // myDFPlayer.play(1);  //Play the first mp3

   if (response.equals("b")) {
   
    myDFPlayer.pause();  //Play next mp3 every 3 second.
  }
 xTaskCreate(mp3,"mp3",128,NULL,1,NULL);
}
void loop() {
  // put your main code here, to run repeatedly:

}
void headlights(void *pvParameters){
 while(1){
  
unsigned int AnalogValue;

AnalogValue = analogRead(A2);

Serial.println(AnalogValue);


if(AnalogValue>=0 && AnalogValue<150){
  brightness=50;
  Serial.println(brightness);

}
if(AnalogValue>=150 && AnalogValue<300){
  brightness=125;
    Serial.println(brightness);

}
if(AnalogValue>=300 && AnalogValue<500){
  brightness=255;
    Serial.println(brightness);

}
  analogWrite(led, brightness);
 delay(1000);

 }
}
void gear(void *pvParameters){
 while(1){
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
 
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);
  delay(1000);
 
 digitalWrite(d1,HIGH); // set common anode HIGH (5V) 

   if(xValue <= 550 && yValue >= 495 &&  yValue  <= 525 )  // send ldown to display if stick is in lower left quadrant
  {
  
    //default
  digitalWrite(seg_a,HIGH);
  digitalWrite(seg_b,HIGH);
  digitalWrite(seg_c,HIGH);
  digitalWrite(seg_d,HIGH);
  digitalWrite(seg_e,HIGH);
  digitalWrite(seg_f,HIGH);
  digitalWrite(seg_g,HIGH);
  }

 

  if(xValue >= 505 &&  xValue  < 560 && yValue==1023 )  // send ldown to display if stick is in lower left quadrant
  {
  
    //right

     //p
  digitalWrite(seg_a,LOW);
  digitalWrite(seg_b,LOW);
  digitalWrite(seg_c,HIGH);
  digitalWrite(seg_d,HIGH);
  digitalWrite(seg_e,LOW);
  digitalWrite(seg_f,LOW);
  digitalWrite(seg_g,LOW);
  }
    
  if(xValue >= 1 &&  xValue  < 600 && yValue<100)  // send ldown to display if stick is in upper left quadrant
  {
   
   //left
  //n
  digitalWrite(seg_a,LOW);
  digitalWrite(seg_b,LOW);
  digitalWrite(seg_c,LOW);
  digitalWrite(seg_d,HIGH);
  digitalWrite(seg_e,LOW);
  digitalWrite(seg_f,LOW);
  digitalWrite(seg_g,HIGH);
    
    
  }
  if(yValue <= 550 && yValue >400 && xValue<=1023&&xValue>1000 )  // send ldown to display if stick is in lower right quadrant
  {
   //up

    //d
  digitalWrite(seg_a,HIGH);
  digitalWrite(seg_b,LOW);
  digitalWrite(seg_c,LOW);
  digitalWrite(seg_d,LOW);
  digitalWrite(seg_e,LOW);
  digitalWrite(seg_f,HIGH);
  digitalWrite(seg_g,LOW);


   
   
  }
  if(yValue <= 590 && xValue>=0 && xValue<100)  // send ldown to display if stick is in upper right quadrant
  {
    
    //down
 //r
  digitalWrite(seg_a,LOW);
  digitalWrite(seg_b,HIGH);
  digitalWrite(seg_c,HIGH);
  digitalWrite(seg_d,HIGH);
  digitalWrite(seg_e,LOW);
  digitalWrite(seg_f,LOW);
  digitalWrite(seg_g,HIGH);
  
    
  }      
 }
 }
 ////////////////
  ////////////////
 void parkingg(void *pvParameters){
  Serial.print(parking);
  noTone(buzzer);
   if(parking==0){
    while(first==0){
if(checkp==0){
  moveForward();
}
digitalWrite(triggerRight, LOW);
delayMicroseconds(2);
//// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(triggerRight, HIGH);
delayMicroseconds(10);
digitalWrite(triggerRight, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durationRight = pulseIn(echoRight, HIGH);
// Calculating the distance
distanceRight= (durationRight*0.034/2);
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distanceRight);

//sound and parking
    // Sounds the buzzer at the frequency relative to the note D in Hz   
     if(distanceRight<=10 && distanceRight>5){
    tone(buzzer,200);    
    // Waits some time to turn off
    delay(200);
    //Turns the buzzer off
    noTone(buzzer); }
    // Sounds the buzzer at the frequency relative to the note D in Hz   
    if(distanceRight<=5){
    tone(buzzer,300);             
    delay(50);    
    noTone(buzzer); 
    checkp=1;
    stop(); 
    
    delay(1000); 
   
       first=1;
   break;}
    // Sounds the buzzer at the frequency relative to the note E in Hz}
    }
park();
stop();

while(checkdis==1){

    moveForward();


  digitalWrite(triggerFront, LOW);
delayMicroseconds(2);
//// Sets the trigPin on HIGH state for 10 micro seconds

digitalWrite(triggerFront, HIGH);
delayMicroseconds(10);
digitalWrite(triggerFront, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
durationFront = pulseIn(echoFront, HIGH);
// Calculating the distance
distanceFront= (durationFront*0.034/2);
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distanceFront);

//sound and parking

//while(checkdis==1){
 if(distanceFront<=20 && distanceFront>15){
    tone(buzzer,200);    
    // Waits some time to turn off
    delay(200);
    //Turns the buzzer off
    noTone(buzzer); }
    // Sounds the buzzer at the frequency relative to the note D in Hz   
    if(distanceFront<=15){
    tone(buzzer,300);             
    delay(50);    
    noTone(buzzer); 
    checkp=1;
    stop(); 
    delay(10000); 
 checkdis=0;
 break;
 }
 
 noTone(buzzer);   
parking=1;

   }
   stop();

}
delay(1000000000000);
 }
void stop(){
      digitalWrite(wh11, HIGH );
digitalWrite(wh12, HIGH);
digitalWrite(wh21,LOW);
digitalWrite(wh22, LOW);  
analogWrite(ena, 120);  
analogWrite(enb, 120);
}

 void moveBack(){
    digitalWrite(wh11, HIGH );
digitalWrite(wh12, LOW);
digitalWrite(wh21,LOW);
digitalWrite(wh22, HIGH);  
analogWrite(ena, 250);  
analogWrite(enb, 250); 
 }


 void moveLeftbackward(){
    digitalWrite(wh11, HIGH );
digitalWrite(wh12, LOW);
//digitalWrite(wh21,LOW);
//digitalWrite(wh22, HIGH);  
analogWrite(ena, 250);  
analogWrite(enb, 250); 
 }
  void moveRightbackward(){
//    digitalWrite(wh11, LOW );
//digitalWrite(wh12, HIGH);
digitalWrite(wh21,LOW);
digitalWrite(wh22, HIGH);  
analogWrite(ena, 250);  
analogWrite(enb, 250); 
 }
 void moveLeftforward(){
    digitalWrite(wh11, LOW );
digitalWrite(wh12, HIGH);
//digitalWrite(wh21,LOW);
//digitalWrite(wh22, HIGH);  
analogWrite(ena, 250);  
analogWrite(enb, 250); 
 }
  void moveRightforward(){
//    digitalWrite(wh11, LOW );
//digitalWrite(wh12, HIGH);
digitalWrite(wh21,HIGH);
digitalWrite(wh22, LOW);  
analogWrite(ena, 250);  
analogWrite(enb, 250); 
 }
void moveForward(){
digitalWrite(wh11, LOW );
digitalWrite(wh12, HIGH);
digitalWrite(wh21,HIGH);
digitalWrite(wh22, LOW);  
analogWrite(ena, 120);  
analogWrite(enb, 120); 
 }
void park(){
  moveRightbackward();
  delay(500);
  stop();
   delay(1000);
  moveBack();
  delay(500);
  stop();
  delay(100);
  moveRightforward();
  delay(300);
}
////////////////////////////////////////////////////////
//mp3
void mp3(void *pvParameters){
  while(1){
    delay(50);
  Serial.println("Write data to slave");
  
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();
    
  Serial.println("Receive data");
  
  // Read response from Slave
  // Read back 5 characters
  Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
  
  // Add characters to string
   response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  } 
  
  // Print to Serial Monitor
  Serial.println(response);
  static unsigned long timer = millis();

//  if (millis() - timer > 10000) {
//    timer = millis();
//    myDFPlayer.next();  //Play next mp3 every 3 second.
//  }

  if ( response.equals("a") ) {
    timer = millis();
    if(check==1){
    myDFPlayer.start();
     check=0;
     }  //Play next mp3 every 3 second.
  }
 
     if (response.equals("b")) {
   
    myDFPlayer.pause();
    check=1;//Play next mp3 every 3 second.
  }
       if (response.equals("c")&&next==1) {
   
    myDFPlayer.next();
    next=0;
   // check=1;//Play next mp3 every 3 second.
  }
       if (response.equals("d")&&previous==1) {
   
    myDFPlayer.previous();
    previous=0;
   // check=1;//Play next mp3 every 3 second.
  }
  if(response.equals("d")||response.equals("c")||response.equals("b")){
    check=1;
  }
   if(response.equals("a")||response.equals("c")||response.equals("b")){
    previous=1;
  }
    if(response.equals("a")||response.equals("d")||response.equals("b")){
    next=1;
  }
delay(1000);


  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  delay(400);
}

  }
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
