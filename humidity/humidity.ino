
#include <Servo.h> 

// humidity
int sensor_pin = A0; 
int sensor_pin2 = A3;
int output_value;
int output_value2;

//servo
int plant2 = 0;
int plant1 = 180;
int servoPin = 13;
Servo motor;

void moveTo(int plant) {
  motor.write(plant);
}

void setup() {
  motor.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}

void loop() {
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  Serial.print("Plant 1: ");
  Serial.print(output_value < 0 ? 0 : output_value);
  Serial.println("%");

  if (output_value < 40){
    moveTo(plant1);
    Serial.println("Moving to plant 1");
  }
  delay(2000);


  output_value2 = analogRead(sensor_pin2);
  output_value2 = map(output_value2,550,0,0,100);
  Serial.print("Plant 2: ");
  Serial.print(output_value2 < 0 ? 0 : output_value2);
  Serial.println("%");

  if (output_value2 < 40){
    moveTo(plant2);
    Serial.println("Moving to plant 2");
  }
  delay(2000);

  Serial.println("--------");
}
