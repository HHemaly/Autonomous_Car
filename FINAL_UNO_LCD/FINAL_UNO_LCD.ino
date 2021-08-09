#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <URTouch.h>
#include <Wire.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 9
 
// Define Slave answer size
#define ANSWERSIZE 1
#include <stdint.h>
#include "TouchScreen.h"
#define YP A2  
#define XM A3 
#define YM 8   
#define XP 9   
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
//Serial.begin(9600);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//int songNo;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
int x, y;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
String answer ;
void setup(){
 Serial.begin(9600);
   Wire.begin(SLAVE_ADDR);
  
  // Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
//  myTouch.InitTouch();
//  myTouch.setPrecision(PREC_MEDIUM);
  uint16_t identifier = tft.readID();
   tft.begin(identifier);
 tft.fillRect(0, 0, 120, 120, WHITE);
  tft.fillRect(120, 0, 120, 120,BLACK);
    tft.setTextColor(BLACK);
  tft.setCursor(10, 50);
   tft.setTextSize(3.5);
  tft.println("Play");
 tft.setTextColor(WHITE);
  tft.setCursor(130, 50);
   tft.setTextSize(3.5);
  tft.println("Pause");
 tft.fillRect(0, 120, 120, 120, BLACK);
  tft.fillRect(120, 120, 120, 120,WHITE);
    tft.setTextColor(WHITE);
  tft.setCursor(10, 170);
   tft.setTextSize(3.5);
  tft.println("Prev.");
 tft.setTextColor(BLACK);
  tft.setCursor(130, 170);
   tft.setTextSize(3.5);
  tft.println("Next");
   tft.fillRect(0, 240,240, 80,YELLOW);
  
   mySoftwareSerial.begin(9600);
  Serial.begin(9600);



 delay(200);
  
}
 
void receiveEvent() {
 
  // Read while data received
  while (0 < Wire.available()) {
    byte x = Wire.read();
  }
  
  // Print to Serial Monitor
  Serial.println("Receive event");
}
 
void requestEvent() {
 
  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  Serial.println(answer);
  // Print to Serial Monitor
  Serial.println("Request event");
}
void loop(){
  
 TSPoint p = ts.getPoint();
   static unsigned long timer = millis();
 if (p.z > ts.pressureThreshhold) {
    if(p.x>=145 && p.x<=425 && p.y>=110&& p.y<=500){
      Serial.println(F("play "));
      answer="a";
    
    }
    if(p.x>=146 && p.x<=400 && p.y>=580&& p.y<=907){
      Serial.println(F("pause"));
    answer="b";
    }
     if(p.x>=468 && p.x<=730 && p.y>=139&& p.y<=506){
      Serial.println(F("prev."));
      answer="d";
    }
     if(p.x>=480 && p.x<=730 && p.y>=566&& p.y<=904){
      Serial.println(F("Next"));
     answer="c";
    }
 }
 delay(400);
      }
