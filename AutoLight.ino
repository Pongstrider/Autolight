#include <SoftwareSerial.h>
SoftwareSerial btSerial(3,2);

void adjustLED(int newBrightness, int warmthAmount);

void setup() {
  Serial.begin(9600); //open the serial port
  btSerial.begin(9600); // open the bluetooth serial port
}

void loop() {
  
  if(btSerial.available()){
    Serial.println(btSerial.readString()); // send from serial to bluetooth
  }
  if(Serial.available()){
    btSerial.println(Serial.readString()); // send from bluetooth to serial
  }
  
  adjustLED(255,-5);
}

void adjustLED(int newBrightness = 255, int warmthAmount = 0){
  int newGreen = newBrightness;
  int newRed = newBrightness;
  int newBlue = newBrightness;


  if(warmthAmount < 0){
    newRed = newBrightness + warmthAmount*(newBrightness/5);
  } else if (warmthAmount > 0){
    newBlue = newBrightness - warmthAmount*(newBrightness/5);
    newGreen = newBrightness - warmthAmount*(newBrightness/8);
  }
  

  analogWrite(9, newRed);
  analogWrite(10, newGreen);
  analogWrite(11, newBlue);
}