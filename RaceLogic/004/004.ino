
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x78

// Define proper RST_PIN if required.
//#define RST_PIN -1

SSD1306AsciiWire oled;

// Serielle Anschluß
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;     // GPS RX -> Arduino D3 //GPS TX -> Arduino D2
static const uint32_t GPSS = 9600;
SoftwareSerial ss(RXPin, TXPin);

//GPS Library
#include <TinyGPS++.h>
TinyGPSPlus gps;

//Program variables
double Lat;
double Long;

int num_sat, gps_speed;
String heading;

void(*resetFunc)(void) = 0; // Autoreset bei Fehler

void setup() {
ss.begin(GPSS);
 Wire.begin();
  Wire.setClock(400000L);



}

    
void loop() {

  Get_GPS(); //Get GPS data

  //Display info in the OLED
}

void print_speed() {

  oled.setFont(System5x7);
  oled.clear();
    oled.println("normal");
 // oled.print(num_sat , DEC);

}

// Datenzufur zu dem GPS
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

void Get_GPS()
{
  num_sat = gps.satellites.value();

  if (gps.location.isValid() == 1) {

    Lat = gps.location.lat();
    Long = gps.location.lng();

    gps_speed = gps.speed.kmph();

    heading = gps.cardinal(gps.course.value());
}

smartDelay(200);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
   // Serial.println(F("No GPS detected: Please check you wiring."));
  resetFunc();
  delay(1000);
  }
}
