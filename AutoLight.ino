#include <SoftwareSerial.h>
SoftwareSerial btSerial(3,2);

void adjustLED(int newBrightness, int warmthAmount);
void executeCommand(String commandString);

void setup() {
  Serial.begin(9600); //open the serial port
  btSerial.begin(9600); // open the bluetooth serial port
}

void loop() {
  // Check if data is available from Bluetooth and send it to the Serial Monitor
  if (btSerial.available()) {
    Serial.println(btSerial.readString()); // Send from Bluetooth to Serial
  }

  // Check if data is available from Serial Monitor and send it to Bluetooth
  if (Serial.available()) {
    String serialInput = Serial.readStringUntil('\n'); // Read from Serial Monitor
    btSerial.println(serialInput); // Send it to Bluetooth
    executeCommand(serialInput); // Execute the command if needed
  }
}

void executeCommand(String commandString){

  int commaFirst = commandString.indexOf(',');
  int commaSecond = commandString.indexOf(',', commaFirst + 1);

  String functionToCall = commandString.substring(0, commaFirst);
  String parameter1 = commandString.substring(commaFirst + 1, commaSecond);
  String parameter2 = commandString.substring(commaSecond + 1);

  Serial.print(functionToCall);

  if(functionToCall.startsWith("setWarmth")){
    adjustLED(parameter1.toInt(), parameter2.toInt());
  }
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