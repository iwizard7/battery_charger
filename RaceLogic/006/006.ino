#include <Wire.h>
#include <OzOLED.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long period_time = (long)1000;
unsigned long my_timer;

void setup(){
 Serial.begin(115200);
 my_timer = millis();   // "сбросить" таймер
  ss.begin(GPSBaud);

  OzOled.init();  //initialze Oscar OLED display

OzOled.clearDisplay(); 
OzOled.setNormalDisplay();
}

void loop(){

 if (gps.location.isUpdated())
  while (ss.available() > 0)
    gps.encode(ss.read());
   
  else if (gps.date.isUpdated())
  {
    Serial.print(F("DATE       Fix Age="));
    Serial.print(gps.date.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.date.value());
    Serial.print(F(" Year="));
    Serial.print(gps.date.year());
    Serial.print(F(" Month="));
    Serial.print(gps.date.month());
    Serial.print(F(" Day="));
    Serial.println(gps.date.day());
  }

    
  }
   if (millis() - my_timer >= period_time) {

    
   
  


  //  OzOled.clearDisplay(); 

        OzOled.printNumber((long)gps.time.minute() ,2,6);
          OzOled.printNumber((long)gps.time.second() ,8,6);
          Serial.println(gps.time.second());
 my_timer = millis(); 
    //Serial.println();'=/.=]
  }
