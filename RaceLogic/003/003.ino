#include "U8glib.h"

//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);                                            // I2C / TWI 1.3
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);   // SCK=A5, SDA=A4       // I2C / TWI 0.96
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);  // SCK=13, SDA=11, CS=10, DC=9, Reset=8   // SPI / TWI 0.96

#define u8g_logo_sat_width 20
#define u8g_logo_sat_height 20

//Satelliten Logo
//const unsigned char u8g_logo_sat[] = {

//0x70,0x00,0x00,
//0x70,0xF8,0x01,
//0x70,0xFE,0x03,
//0x80,0xFC,0x07,
//0x00,0xF9,0x07,
//0x40,0xF2,0x07,
//0xC0,0xE4,0x07,
//0xE0,0xE9,0x03,
//0xE0,0xE3,0x03,
//0xE0,0xFF,0x01,
//0xE0,0xFF,0x01,
//0xE0,0xFF,0x00,
//0xE0,0x7F,0x00,
//0xC0,0x1F,0x00,
//0x80,0x07,0x00,
//0x00,0x00,0x00,
//0x00,0x00,0x00,
//0x00,0x00,0x00,
//0x00,0x00,0x00,
//0x00,0x00,0x00,
//};

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
}

    
void loop() {

  Get_GPS(); //Get GPS data

  //Display info in the OLED
  u8g.firstPage();
  do {
    print_speed();
  } while ( u8g.nextPage() );
}

void print_speed() {

  //u8g.setFont(u8g_font_fur42n);
  u8g.setFont(u8g_font_fur49n);
  u8g.setPrintPos(0, 50);
  u8g.print(gps_speed , DEC);
  
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(115, 28);               // Satelliten Anzahl Position
  u8g.print( num_sat, 5);

  u8g.setPrintPos(0, 62);
  u8g.print("Lat:");

  u8g.setPrintPos(26, 62);
  u8g.print( Lat, 3);

  u8g.setPrintPos(66, 62);
  u8g.print("Long:");

  u8g.setPrintPos(97, 62);
  u8g.print( Long,3);
  
  u8g.setFont(u8g_font_unifont);

  //u8g.drawXBM(107, 0, u8g_logo_sat_width, u8g_logo_sat_height, u8g_logo_sat);   // Sat Icon Position
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
