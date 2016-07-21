/*
This Sketch works with the Skylab SKM53 GPS module
 RXD Arduino Pin 4
 TXD Arduino Pin 3
 RST Leave Open 
 NC Leave Open
 GND Ground
 VCC +5

 eMaker Studio 2016
*/

#include <TinyGPS.h>
#include <SoftwareSerial.h>

unsigned long fix_age;

SoftwareSerial GPS(3,4);
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon;
float LAT, LON;

void setup(){
  GPS.begin(9600);
  Serial.begin(115200);
}

void loop(){
  long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;

  // retrieves +/- lat/long in 1/1000000 of a degree
  // this gives us the right format that can be put into Google Maps for example
  gps.get_position(&lat, &lon, &fix_age);

  getGPS();
  Serial.print("Latitude : ");
  Serial.print(LAT/1000000,7);
  Serial.print(" :: Longitude : ");
  Serial.println(LON/1000000,7);
}

void getGPS(){
  bool newdata = false;
  unsigned long start = millis();
  // Every 1 seconds we print an update
  while (millis() - start < 1000)
  {
    if (feedgps ()){
      newdata = true;
    }
  }
  if (newdata)
  {
    gpsdump(gps);
  }
}

bool feedgps(){
  while (GPS.available())
  {
    if (gps.encode(GPS.read()))
      return true;
  }
  return 0;
}

void gpsdump(TinyGPS &gps)
{
  //byte month, day, hour, minute, second, hundredths;
  gps.get_position(&lat, &lon);
  LAT = lat;
  LON = lon;
  {
    feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors
  }
}

