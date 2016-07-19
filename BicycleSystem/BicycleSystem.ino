// SECURITY & INFOTAINMENT SYSTEM FOR BICYCLES
// Already in place: Tilt, Buzzer
// Todo: GPS, camera, 3G or TTN, RTOS
// 
// eMaker Studio 2016


int inPin = 2;   // the number of the input pin
int reading;     // the current reading from the input pin
const int SpeakerPin = 8; // the number of the Speaker/Buzzer pin

void setup(){
  pinMode (inPin, INPUT);
  Serial.begin(9600);
}

void loop () {
  reading = digitalRead(inPin);
  if (reading == 1) {
   tone(SpeakerPin, 494, 500);      // if tilted, turn the Speaker ON
   delay(500);
   
  } else {
    noTone(SpeakerPin);
  }
  Serial.println(reading); // only for debugging

  delay(200);   // pause 200 milliseconds between readings
}


