#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL, 8);

extern uint8_t SmallFont[];
//extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

// The serial connection to the GPS device
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 115200;
SoftwareSerial ss(RXPin, TXPin);

//GPS Library
#include <TinyGPS++.h>
TinyGPSPlus gps;

//Program variables
double Lat;
double Long;
//int day, month, year;
//int hour, minute, second;

int num_sat, gps_speed;
String heading;


void setup() {
Serial.begin(115200);
  myOLED.begin();
  myOLED.setFont(SmallFont);

  ss.begin(GPSBaud);

}

void loop() {

  Get_GPS(); //Get GPS data


}

void print_speed() {

  myOLED.setFont(BigNumbers);
  myOLED.printNumI(num_sat, RIGHT, 40);
  myOLED.update();
  Serial.println(num_sat);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
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



  /*
    if (gps.date.isValid())
    {
      day = gps.date.day();
      month = gps.date.month();
      year = gps.date.year();
    }

    if (gps.time.isValid())
    {

      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();
    }

  */

  smartDelay(1000);


  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    // Serial.println(F("No GPS detected: check wiring."));

  }


  myOLED.clrScr();
}
