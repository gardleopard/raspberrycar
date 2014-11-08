#include "TM1638.h"
TM1638 module(6, 7, 5);

 int rightMotor[] = { 9, A2, A3 };
 int leftMotor[] = { 10, A4, A5 };
 boolean armed = false;
 int loopCount = 0;
 String inputString = "";
 boolean stringComplete = false;
 int currentThrottle = 0;
 int currentSteering = 0;
 

void setup() {
  initMotor(rightMotor);
  initMotor(leftMotor);
  Serial.begin(9600);
  Serial.println("Booting");
  module.setDisplayToString("boot", 0, false);
  delay(100);
}

void initMotor(int motor[]){
  for(int i = 0; i <= sizeof(motor); i++){
    pinMode(motor[i], OUTPUT);
  }
}

void enableMotor(int motor[]){
  digitalWrite(motor[0], HIGH);
}

void stopMotor(int motor[]){
  digitalWrite(motor[0], LOW);
}

void forwardMotor(int motor[]){
  digitalWrite(motor[1], HIGH);

  digitalWrite(motor[2], LOW);
}

void brakeMotor(int motor[]){
  digitalWrite(motor[1], HIGH);
  digitalWrite(motor[2], HIGH);
}

void coastMotor(int motor[]){
  digitalWrite(motor[1], LOW);
  digitalWrite(motor[2], LOW);
}

void reverseMotor(int motor[]){
  digitalWrite(motor[1], LOW);
  digitalWrite(motor[2], HIGH);
}

void forward(){
  enableMotor(leftMotor);
  enableMotor(rightMotor);
  forwardMotor(leftMotor);
  forwardMotor(rightMotor);
}

void reverse(){
  enableMotor(leftMotor);
  enableMotor(rightMotor);
  reverseMotor(leftMotor);
  reverseMotor(rightMotor);
}

void stop(){
  stopMotor(leftMotor);
  stopMotor(rightMotor);
}
void coast(){
  coastMotor(leftMotor);
  coastMotor(rightMotor);
}

void brake(){
  brakeMotor(leftMotor);
  brakeMotor(rightMotor);
}

void testForward(){
  forward();
}

void speedTest(){
  enableMotor(leftMotor);
  enableMotor(rightMotor);
  for(int i = 0; i < 255; i++){
    forwardMotor(leftMotor, i);
    forwardMotor(rightMotor, i);
    delay(100);
  }
  for(int i = 255; i > 0; i--){
    forwardMotor(leftMotor, i);
    forwardMotor(rightMotor, i);
    delay(100);
  }
}

void forwardMotor(int motor[], int throttle){
  analogWrite(motor[0], throttle);
  digitalWrite(motor[1], HIGH);
  digitalWrite(motor[2], LOW);
}

int getThrottle(String input){
  return input.substring(1,input.indexOf("S")).toInt();
}

int getSteering(String input){
  return input.substring(input.indexOf("S")+1, input.length()).toInt();
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    currentThrottle = getThrottle(inputString);
    currentSteering = getSteering(inputString);
    inputString = "";
    stringComplete = false;
    module.setDisplayToDecNumber(currentThrottle, 0, false);
  }
  module.setDisplayToString("loop", 0, false);
 // speedTest();
 // delay(500);
 // stop();
 // delay(5000);
//reverse();
  //delay(500);
  
  //turn();
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}