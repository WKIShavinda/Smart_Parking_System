const byte sensorPin = 4;

bool detected = false;

void setup(){
  Serial.begin(115200);
  Serial.println(__FILE__ __DATE__);
}

void inputDetected(){
  Serial.print("New input detected");
  detected = true;
}

void inputHeld(){
  Serial.print(".");
}

void inputRemoved(){
  Serial.print("Removed");
  Serial.print("\n");
  detected = false;
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
      inputRemoved();
    }
  }
  delay(20);
}
