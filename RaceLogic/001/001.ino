#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);   // SCK=A5, SDA=A4       // I2C / TWI 0.96

#define u8g_logo_sat_width 20
#define u8g_logo_sat_height 20
//Satelliten Logo
const unsigned char u8g_logo_sat[] = {

0x70,0x00,0x00,
0x70,0xF8,0x01,
0x70,0xFE,0x03,
0x80,0xFC,0x07,
0x00,0xF9,0x07,
0x40,0xF2,0x07,
0xC0,0xE4,0x07,
0xE0,0xE9,0x03,
0xE0,0xE3,0x03,
0xE0,0xFF,0x01,
0xE0,0xFF,0x01,
0xE0,0xFF,0x00,
0xE0,0x7F,0x00,
0xC0,0x1F,0x00,
0x80,0x07,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00,
};

int num_sat, gps_speed;
double Lat;
double Long;
int num_sat, gps_speed;
String heading;
/*
   This sample code demonstrates just about every built-in operation of TinyGPS++ (TinyGPSPlus).
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long last = 0UL;

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("KitchenSink.ino"));
  Serial.println(F("Demonstrating nearly every feature of TinyGPS++"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated())
  {
    Serial.print(F("LOCATION   Fix Age="));
    Serial.print(gps.location.age());
    Serial.print(F("ms Raw Lat="));
    Serial.print(gps.location.rawLat().negative ? "-" : "+");
    Serial.print(gps.location.rawLat().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLat().billionths);
    Serial.print(F(" billionths],  Raw Long="));
    Serial.print(gps.location.rawLng().negative ? "-" : "+");
    Serial.print(gps.location.rawLng().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLng().billionths);
    Serial.print(F(" billionths],  Lat="));
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(" Long="));
    Serial.println(gps.location.lng(), 6);
  }

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

  else if (gps.time.isUpdated())
  {
    Serial.print(F("TIME       Fix Age="));
    Serial.print(gps.time.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.time.value());
    Serial.print(F(" Hour="));
    Serial.print(gps.time.hour());
    Serial.print(F(" Minute="));
    Serial.print(gps.time.minute());
    Serial.print(F(" Second="));
    Serial.print(gps.time.second());
    Serial.print(F(" Hundredths="));
    Serial.println(gps.time.centisecond());
  }

  else if (gps.speed.isUpdated())
  {
    Serial.print(F("SPEED      Fix Age="));
    Serial.print(gps.speed.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.speed.value());
    Serial.print(F(" Knots="));
    Serial.print(gps.speed.knots());
    Serial.print(F(" MPH="));
    Serial.print(gps.speed.mph());
    Serial.print(F(" m/s="));
    Serial.print(gps.speed.mps());
    Serial.print(F(" km/h="));
    Serial.println(gps.speed.kmph());
  }

  else if (gps.course.isUpdated())
  {
    Serial.print(F("COURSE     Fix Age="));
    Serial.print(gps.course.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.course.value());
    Serial.print(F(" Deg="));
    Serial.println(gps.course.deg());
  }

  else if (gps.altitude.isUpdated())
  {
    Serial.print(F("ALTITUDE   Fix Age="));
    Serial.print(gps.altitude.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.altitude.value());
    Serial.print(F(" Meters="));
    Serial.print(gps.altitude.meters());
    Serial.print(F(" Miles="));
    Serial.print(gps.altitude.miles());
    Serial.print(F(" KM="));
    Serial.print(gps.altitude.kilometers());
    Serial.print(F(" Feet="));
    Serial.println(gps.altitude.feet());
  }

  else if (gps.satellites.isUpdated())
  {
    Serial.print(F("SATELLITES Fix Age="));
    Serial.print(gps.satellites.age());
    Serial.print(F("ms Value="));
    Serial.println(gps.satellites.value());
  }

  else if (gps.hdop.isUpdated())
  {
    Serial.print(F("HDOP       Fix Age="));
    Serial.print(gps.hdop.age());
    Serial.print(F("ms raw="));
    Serial.print(gps.hdop.value());
    Serial.print(F(" hdop="));
    Serial.println(gps.hdop.hdop());
  }

  else if (millis() - last > 5000)
  {
    Serial.println();
    if (gps.location.isValid())
    {
      static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
      double distanceToLondon =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT, 
          LONDON_LON);
      double courseToLondon =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT, 
          LONDON_LON);

      Serial.print(F("LONDON     Distance="));
      Serial.print(distanceToLondon/1000, 6);
      Serial.print(F(" km Course-to="));
      Serial.print(courseToLondon, 6);
      Serial.print(F(" degrees ["));
      Serial.print(TinyGPSPlus::cardinal(courseToLondon));
      Serial.println(F("]"));
    }

    Serial.print(F("DIAGS      Chars="));
    Serial.print(gps.charsProcessed());
    Serial.print(F(" Sentences-with-Fix="));
    Serial.print(gps.sentencesWithFix());
    Serial.print(F(" Failed-checksum="));
    Serial.print(gps.failedChecksum());
    Serial.print(F(" Passed-checksum="));
    Serial.println(gps.passedChecksum());

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));

    last = millis();
    Serial.println();
  }
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
  u8g.print( gps.time.hour(), 3);

  u8g.setPrintPos(32, 62);
  u8g.print( gps.time.minute(),3);

 u8g.setPrintPos(62, 62);
  u8g.print( gps.time.second(),3);
  
  u8g.setFont(u8g_font_unifont);

  u8g.drawXBM(107, 0, u8g_logo_sat_width, u8g_logo_sat_height, u8g_logo_sat);   // Sat Icon Position
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

smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
   // Serial.println(F("No GPS detected: Please check you wiring."));
  resetFunc();
  delay(1000);
  }
}
