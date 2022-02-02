#include <WiFi.h>
#include <Servo.h>

const byte sensorPin = 4;
static const int servoPin = 2;

bool detected = false;

int slots = 20;

//WiFi
#define WIFI_SSID "Farmaan A10s"
#define WIFI_PASSWORD "ptgp4252"

Servo servo1;

void setup(){
  Serial.begin(115200);
  Wifi_Init();
  servo1.attach(servoPin);
}

void loop(){
  int reading = !digitalRead(sensorPin);

  if(reading){
    if(detected==false){
      inputDetected();
    }
    else{
      inputHeld();
    }
  }
  else{
    if(detected){
      delay(5000);  //close gate 5 seconds after detecting the vehicle (give time for the vehicle to leave the gate)
      inputRemoved();
    }
  }
  delay(20);
}

void Wifi_Init(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void inputDetected(){
  Serial.println("Object detected");
  Serial.print("Opening gate");
  detected = true;
  //opening gate
  for(int posDegrees = 0; posDegrees <= 90; posDegrees++) {
    servo1.write(posDegrees);
    delay(10);
  }
}

void inputHeld(){
  Serial.print(".");
}

void inputRemoved(){
  Serial.println("Removed");
  Serial.println("Closing gate");
  detected = false;
  //closing gate
  for(int posDegrees = 90; posDegrees >= 0; posDegrees--) {
    servo1.write(posDegrees);
    delay(10);
  }
  slots++;
  Serial.println(slots);
}
