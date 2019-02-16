#include <Servo.h> 

int plant3 = 0;
int plant2 = 90;
int plant1 = 180;
int servoPin = 13;

Servo motor;

void moveTo(int plant) {
  motor.write(plant);
}

void setup() 
{ 
  motor.attach(servoPin);
}

void loop() {
//  moveTo(plant1);
//  delay(2000);
//  moveTo(plant2);
//  delay(2000);
//  moveTo(plant3);
//  delay(2000);
} 
