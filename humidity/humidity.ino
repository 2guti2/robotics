
#include <Servo.h> 

// humidity
int plant1_sensor_pin = A0; 
int plant2_sensor_pin = A3;
int plant3_sensor_pin = A4;

//servo
int plant3_servo_location = 0;
int plant2_servo_location = 90;
int plant1_servo_location = 180;
int servo_pin = 13;
Servo motor;

void moveTo(int plant_servo_location) {
  motor.write(plant_servo_location);
}

int get_plant_humidity(char* plant_name, int sensor_pin) {
  int output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 0, 0, 100);
  Serial.print(plant_name);
  Serial.print(output_value < 0 ? 0 : output_value);
  Serial.println("%");
  return output_value;
}

void analyze(int plant_humidity, int plant_servo_location, char* plant_name){
  if (plant_humidity < 40){
    moveTo(plant_servo_location);
    Serial.print("Moving to ");
    Serial.println(plant_name);
  }
  delay(2000);
}

void setup() {
  motor.attach(servo_pin);
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}

void loop() {
  int plant1_humidity = get_plant_humidity((char*)"Plant 1: ", plant1_sensor_pin);
  analyze(plant1_humidity, plant1_servo_location, (char*) "Plant 1");

  int plant2_humidity = get_plant_humidity((char*)"Plant 2: ", plant2_sensor_pin);
  analyze(plant2_humidity, plant2_servo_location, (char*) "Plant 2");

  int plant3_humidity = get_plant_humidity((char*)"Plant 3: ", plant3_sensor_pin);
  analyze(plant3_humidity, plant3_servo_location, (char*) "Plant 3");

  Serial.println("--------");
}
