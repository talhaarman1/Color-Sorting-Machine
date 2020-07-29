#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color=0;
LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
  lcd.init(); 
  lcd.backlight();

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);
}
void loop() {
  topServo.write(115);
  delay(500);
  
  for(int i = 135; i > 60; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  color = readColor();
  delay(10);  
  switch (color) {
//    case 1:
//    bottomServo.write(50);
//   lcd.setCursor(0,0);
//     lcd.print("Red");
//
//    break;
    case 2:
    bottomServo.write(70);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Orange");
    break;
    case 3:
    bottomServo.write(120);
     lcd.clear();
    lcd.setCursor(0,0);
     lcd.print("Green");
    break;
    case 4:
    bottomServo.write(170);
     lcd.clear();
    lcd.setCursor(0,0);
     lcd.print("Yellow");
    break;
//    case 5:
//    bottomServo.write(150);
//     lcd.clear();
//    lcd.setCursor(0,0);
//     lcd.print("hello 5");
//    break;
//    case 6:
//    bottomServo.write(175);
//     bottomServo.write(150);
//     lcd.clear();
//    lcd.setCursor(0,0);
//     lcd.print("hello 5");
//    break;
    
    case 0:
    break;
  }
  delay(300);
  

  for(int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
//  if(R<155 & R>125 & G<215 & G>180){
//    color = 1; // Red
//  }
//  if(R<128 & R>115 & B<145 & G>128){
//     color = 2; // Orange
//  }
  if(R<160 & R>128 & B<140 & B>115){
    color = 3; // Green
  }
  if(R<130 & R>105 & G<170 & G>140){
    color = 4; // Yellow
  }
//  if(R<56 & R>46 & G<65 & G>55){
//    color = 5; // Brown
//  }
//  if (G<58 & G>45 & B<40 &B>26){
//    color = 6; // Blue
//  }
  return color;  
}
