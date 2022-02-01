#include <Servo.h>

const byte sensorPin = 4;
static const int servoPin = 2;

bool detected = false;

Servo servo1;

void setup(){
  Serial.begin(115200);
  servo1.attach(servoPin);
}

void loop(){
  int reading = !digitalRead(sensorPin);

  if(reading){
    if(detected==false){
      inputDetected();
      //opening gate
      for(int posDegrees = 0; posDegrees <= 90; posDegrees++) {
        servo1.write(posDegrees);
        delay(10);
      }
    }
    else{
      inputHeld();
    }
  }
  else{
    if(detected){
      delay(5000);  //close gate 5 seconds after detecting the vehicle (give time for the vehicle to leave the gate)
      inputRemoved();
      //closing gate
      for(int posDegrees = 90; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(10);
      }
    }
  }
  delay(20);
}

void inputDetected(){
  Serial.println("Object detected");
  Serial.print("Opening gate");
  detected = true;
}

void inputHeld(){
  Serial.print(".");
}

void inputRemoved(){
  Serial.println("Removed");
  Serial.println("Closing gate");
  detected = false;
}
