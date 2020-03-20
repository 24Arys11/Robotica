int pot_blue_value = 0;
int led_blue_value = 0;
const int led_blue_pin = 9;
const int pot_blue_pin = A0;
int pot_green_value = 0;
int led_green_value = 0;
const int led_green_pin = 10;
const int pot_green_pin = A1;
int pot_red_value = 0;
int led_red_value = 0;
const int led_red_pin = 11;
const int pot_red_pin = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_blue_pin, INPUT);
  pinMode(led_blue_pin, OUTPUT);
  pinMode(led_green_pin, INPUT);
  pinMode(led_green_pin, OUTPUT);
  pinMode(led_red_pin, INPUT);
  pinMode(led_red_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // blue pot & led
  pot_blue_value = analogRead(pot_blue_pin);
  led_blue_value = map(pot_blue_value, 0, 1023, 0, 255);
  Serial.println(led_blue_value);
  analogWrite(led_blue_pin, led_blue_value);
  // green pot & led
  pot_green_value = analogRead(pot_green_pin);
  led_green_value = map(pot_green_value, 0, 1023, 0, 255);
  Serial.println(led_green_value);
  analogWrite(led_green_pin, led_green_value);
  // red pot & led
  pot_red_value = analogRead(pot_red_pin);
  led_red_value = map(pot_red_value, 0, 1023, 0, 255);
  Serial.println(led_red_value);
  analogWrite(led_red_pin, led_red_value);
  delay(1);
}
