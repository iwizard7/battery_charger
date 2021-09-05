#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL, 8);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long last = 0UL;

void setup()
{
  Serial.begin(57600);
  ss.begin(GPSBaud);
  myOLED.begin();
  myOLED.setFont(SmallFont);

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
     myOLED.setFont(BigNumbers);
    myOLED.printNumI(gps.speed.kmph(), CENTER, 10);
    myOLED.update();
    
  }



  else if (gps.satellites.isUpdated())
  {
    Serial.print(F("SATELLITES Fix Age="));
    Serial.print(gps.satellites.age());
    Serial.print(F("ms Value="));
    Serial.println(gps.satellites.value());
             myOLED.setFont(SmallFont);
    myOLED.printNumI(gps.satellites.value(), LEFT, 50);
    myOLED.update();
  }

  else if (gps.hdop.isUpdated())
  {
    Serial.print(F("HDOP       Fix Age="));
    Serial.print(gps.hdop.age());
    Serial.print(F("ms raw="));
    Serial.print(gps.hdop.value());
    Serial.print(F(" hdop="));
    Serial.println(gps.hdop.hdop());
     myOLED.setFont(SmallFont);
    myOLED.printNumI(gps.hdop.hdop(), RIGHT, 50);
    myOLED.update();

  }

  else if (millis() - last > 5000)
  {
    Serial.println();
   

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));

    last = millis();
  }
   myOLED.clrScr();
}
