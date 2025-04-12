#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial btSerial(3,2);

void adjustLED(int newBrightness, int warmthAmount);
void executeCommand(String commandString);

void setup() {
  Serial.begin(9600); //open the serial port
  btSerial.begin(9600); // open the bluetooth serial port

  adjustLED(EEPROM.read(4), EEPROM.read(5));
}

void loop() {
if (Serial.available()) {
    String serialInput = Serial.readStringUntil('\n'); // Read from Serial Monitor
    executeCommand(serialInput); // Execute the command if needed
  }

}

void executeCommand(String commandString){
  int commaFirst = commandString.indexOf(',');
  int commaSecond = commandString.indexOf(',', commaFirst + 1);
  String functionToCall = commandString.substring(0, commaFirst);

  if(functionToCall.startsWith("readMemory")){
    Serial.print(EEPROM.read(4));
    Serial.print(",");
    Serial.println(EEPROM.read(5));
  }

  int parameter1 = commandString.substring(commaFirst + 1, commaSecond).toInt();
  int parameter2 = commandString.substring(commaSecond + 1).toInt();

  
    
  if(functionToCall.startsWith("setWarmth")){
    if(parameter1 >= 0 && parameter1 <= 255 && parameter2 >= 0 && parameter2 <= 10){
      adjustLED(parameter1, parameter2);
    } 
  }
}

void adjustLED(const int newBrightness = 255, const int warmthAmount = 0){
  EEPROM.write(4, newBrightness);
  EEPROM.write(5, warmthAmount);

  int newGreen = newBrightness;
  int newRed = newBrightness;
  int newBlue = newBrightness;

  int adjustedWarmth = warmthAmount - 5;

  if(warmthAmount < 5){
    newRed = newBrightness + adjustedWarmth*(newBrightness/5);
  } else if (warmthAmount > 5){
    newBlue = newBrightness - adjustedWarmth*(newBrightness/5);
    newGreen = newBrightness - adjustedWarmth*(newBrightness/8);
  }
  
  analogWrite(9, newRed);
  analogWrite(10, newGreen);
  analogWrite(11, newBlue);
}