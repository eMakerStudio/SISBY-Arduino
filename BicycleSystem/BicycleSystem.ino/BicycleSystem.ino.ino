/*
 * Security & Infotainment for Bicycles
 * 
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
int inPin = 2;   // tilt sensor
int reading;     // the current reading from the input pin
const int SpeakerPin = 8; // the number of the Speaker/Buzzer pin

SoftwareSerial GPS(3,4);
TinyGPS gps;
void gpsdump(TinyGPS &gps);
bool feedgps();
void getGPS();
long lat, lon;
float LAT, LON;


void setup(){
  GPS.begin(9600);
  pinMode (inPin, INPUT);
  Serial.begin(115200);
}

void loop () {
  reading = digitalRead(inPin);
  if (reading == 1) {
   tone(SpeakerPin, 494, 500);      // if tilted, turn the Speaker ON
   delay(500);
   
  } else {
    noTone(SpeakerPin);
  }
  //Serial.println(reading); // only for debugging

  delay(200);   // pause 200 milliseconds between readings

  //GPS
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
