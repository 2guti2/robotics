#include <Servo.h> 

struct Plant {
  int sensor_pin;
  int servo_location;
  char* name;
};

struct Plant plant1;
struct Plant plant2;
struct Plant plant3;
int blue_led = 11;
int red_led = 10;
int green_led = 9;
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

void turn_on(int led_pin) {
  digitalWrite(led_pin, HIGH);
}

void turn_off(int led_pin) {
  digitalWrite(led_pin, LOW); 
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

void water(Plant plant, int plant_humidity) {
  moveTo(plant.servo_location);
  Serial.print("Moving to ");
  Serial.println(plant.name);

  turn_on(blue_led);
  Serial.print("Watering ");
  Serial.println(plant.name);
  delay(3000);
  turn_off(blue_led);
}

bool is_watered(int plant_humidity) {
  return plant_humidity >= 40;
}

void check_water(Plant plant) {
  int tries = 0;
  int plant_humidity = get_plant_humidity(plant);
  while(!is_watered(plant_humidity)) {
    water(plant, plant_humidity);
      
    tries++;
    if(tries >= 5) 
      break;
    
    plant_humidity = get_plant_humidity(plant);
  } 
}

void check_plants() {
  check_water(plant1);
  check_water(plant2);
  check_water(plant3);

  Serial.println("--------");
}

void setup() {
  // leds
  pinMode(blue_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  // servo
  motor.attach(servo_pin);

  // humidity
  Serial.begin(9600);
  Serial.println("Reading From the Sensor...");
  initPlant1();
  initPlant2();
  initPlant3();
  
  delay(2000);
}

void loop() {
  check_plants();
}
