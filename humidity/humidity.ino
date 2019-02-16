
#include <Servo.h> 

struct Plant {
  int sensor_pin;
  int servo_location;
  char* name;
};

struct Plant plant1;
struct Plant plant2;
struct Plant plant3;
int servo_pin = 13;
Servo motor;

void initPlant1() {
  plant1.sensor_pin = A0;
  plant1.servo_location = 180;
  plant1.name = (char*) "Plant 1";
}

void initPlant2() {
  plant2.sensor_pin = A3;
  plant2.servo_location = 90;
  plant2.name = (char*) "Plant 2";
}

void initPlant3() {
  plant3.sensor_pin = A4;
  plant3.servo_location = 0;
  plant3.name = (char*) "Plant 3";
}

void moveTo(int plant_servo_location) {
  motor.write(plant_servo_location);
}

int get_plant_humidity(Plant plant) {
  int output_value = analogRead(plant.sensor_pin);
  output_value = map(output_value, 550, 0, 0, 100);
  Serial.print(plant.name);
  Serial.print(": ");
  Serial.print(output_value < 0 ? 0 : output_value);
  Serial.println("%");
  return output_value;
}

void analyze(Plant plant, int plant_humidity) {
  if (plant_humidity < 40) {
    moveTo(plant.servo_location);
    Serial.print("Moving to ");
    Serial.println(plant.name);
  }
  delay(2000);
}

void setup() {
  motor.attach(servo_pin);
  Serial.begin(9600);
  Serial.println("Reading From the Sensor...");
  initPlant1();
  initPlant2();
  initPlant3();
  delay(2000);
}

void loop() {
  int plant1_humidity = get_plant_humidity(plant1);
  analyze(plant1, plant1_humidity);

  int plant2_humidity = get_plant_humidity(plant2);
  analyze(plant2, plant2_humidity);

  int plant3_humidity = get_plant_humidity(plant3);
  analyze(plant3, plant3_humidity);

  Serial.println("--------");
}
