#include <Servo.h> 

struct Plant {
  int sensor_pin;
  int servo_location;
  char* name;
};

int max_amount_of_tries = 2;

int play_button = 2;
int play_button_val = 0;
int play_button_state = 0;
int play_button_old_val = 0; 

struct Plant plant2;
struct Plant plant3;

int green_led = 9;
int servo_pin = 13;
Servo motor;

int watering_time = 2000;
int water_pump = 7;

void initPlant2() {
  plant2.sensor_pin = A3;
  plant2.servo_location = 90;
  plant2.name = (char*) "Plant A";
}

void initPlant3() {
  plant3.sensor_pin = A4;
  plant3.servo_location = 0;
  plant3.name = (char*) "Plant B";
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

void turn_on_pump(){
  digitalWrite(water_pump, LOW); 
}

void turn_off_pump(){
  digitalWrite(water_pump, HIGH); 
}

void water(Plant plant, int plant_humidity) {
  moveTo(plant.servo_location);
  Serial.print("Moving to ");
  Serial.println(plant.name);

  turn_on_pump(); 
  Serial.print("Watering ");
  Serial.println(plant.name);
  delay(watering_time);
  turn_off_pump(); 
  delay(3000);
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
    if(tries >= max_amount_of_tries) 
      break;
    
    plant_humidity = get_plant_humidity(plant);
  } 
}

void check_plants() {
  check_water(plant2);
  check_water(plant3);

  Serial.println("--------");
}

void turn_off_in_next_loop() {
  if(play_button_state != 1) {
    Serial.println("Turning on");
    turn_on(green_led);
  }
  play_button_state = 1;
}

void setup() {
  pinMode(play_button, INPUT);
  pinMode(water_pump, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), turn_off_in_next_loop, FALLING);

  turn_off_pump();
  
  // leds
  pinMode(green_led, OUTPUT);

  // servo
  motor.attach(servo_pin);

  // humidity
  Serial.begin(9600);
  initPlant2();
  initPlant3();
  
  Serial.println("Ready to water plants.");
  Serial.println("Initial state:");
  get_plant_humidity(plant2);
  get_plant_humidity(plant3);
}

void loop() {
  if (play_button_state==1) {
   check_plants();
  }
  else {
   turn_off(green_led);
  }
  delay(2000);
}
