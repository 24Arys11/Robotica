#include <Servo.h>
// for gyro sensor
#include "Wire.h"
#include <SPI.h>
// for radio
#include <nRF24L01.h>
#include <RF24.h>
// for ballance
#include <PID_v1.h>

const byte address[6] = "71993";
const int dcPin1 = 9;
const int dcPin2 = 10;
const int buzzerPin = 4;
const int permanentStopPin = 2;
const int stopPin = 17;
const int servoBallancePin = 6;
const int servoSteeringPin = 5;
const int CE = 7;
const int CSN = 8;
const int lightPin = 14;
const int rightTurningSignalPin = 15;
const int leftTurningSignalPin = 16;

const int mpuAddress = 0x68;
int16_t tilt; // variables for gyro raw data

RF24 radio(CE, CSN); // CE, CSN

Servo servoSteering;
Servo servoBallance;

double setPoint ; // will be the desired value
double input; // Gyro tilt
double output ; // Servo Angle
//PID parameters
double kp = 1500, ki = 0.4, kd = 3100; 
 
//create PID instance 
PID ballancePID(&input, &output, &setPoint, kp, ki, kd, DIRECT);

void setup() { 
  Serial.begin(9600);
  pinMode(dcPin1, OUTPUT);
  pinMode(dcPin2, OUTPUT);
  pinMode(servoBallancePin, OUTPUT);
  pinMode(servoSteeringPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(permanentStopPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(rightTurningSignalPin, OUTPUT);
  pinMode(leftTurningSignalPin, OUTPUT);
  digitalWrite(dcPin1, LOW);
  digitalWrite(dcPin2, LOW);
  digitalWrite(permanentStopPin, HIGH);
  digitalWrite(stopPin, HIGH);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servoBallance.attach(servoBallancePin);
  servoSteering.attach(servoSteeringPin);

  Wire.begin();
  Wire.beginTransmission(mpuAddress); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //Hardcode the ballance state
  setPoint = 133;
  //Turn the PID on
  ballancePID.SetMode(AUTOMATIC);
  ballancePID.SetSampleTime(1);
  //Adjust PID values
  ballancePID.SetTunings(kp, ki, kd);
}

int info = 1000;
int lastInfo = 1000;

int horn;
unsigned long lastHornCall = 0;
unsigned long hornDuration = 50;
int hornTone = 640;
int lightInput;
int lastLightInput;
int directional;

bool lightState = 0;

unsigned long lightDebounceDelay = 50;
unsigned long lightLastDebounce = 0;

unsigned long TurningSignalBlinkInterval = 300;
unsigned long lastBlinkTime = 0;
bool leftTurningSignalState = 0;
bool rightTurningSignalState = 0;

int steerengAngle = 90;
int ballanceAngle = 90;

void readGyro(){

  Wire.beginTransmission(mpuAddress);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(mpuAddress, 14, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  tilt = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  tilt = map(tilt, -16384, 16384, -1020, 1275);
  if (tilt < 0){          // we will only account for 10 degree left and 10 degree right,
    tilt = 0;             // since if the motorbike is tilted more than that it is already
  }else if(tilt > 255){   // too late anyway..
    tilt = 255;
  }

  // print out data
  //  Serial.print("tilt = ");
    Serial.print(tilt);
  //  Serial.println();
}

void readInputs(int radioInput){
  horn = radioInput % 10;
  radioInput = radioInput / 10;
  if ((millis() - lightLastDebounce) > lightDebounceDelay){
    lightInput = radioInput % 10;
  }
  radioInput = radioInput / 10;
  directional = radioInput % 10;
}

void updateLight (){
  if (info != lastInfo){
    lightLastDebounce = millis();
  }
  if (lightInput == 1 && lastLightInput == 0){
    lightState = !(lightState);
    digitalWrite(lightPin, lightState);
  }
  lastLightInput = lightInput;
  lastInfo = info;
}

void turnRight(bool choice){
  if(choice == true){
    if((millis() - lastBlinkTime) > TurningSignalBlinkInterval){
      rightTurningSignalState = !(rightTurningSignalState);
      digitalWrite(rightTurningSignalPin, rightTurningSignalState);
      lastBlinkTime = millis();
    }
    steerengAngle = 135;
  }else{
    digitalWrite(rightTurningSignalPin, LOW);
  }
}

void turnLeft(bool choice){
  if(choice == true){
    if((millis() - lastBlinkTime) > TurningSignalBlinkInterval){
      leftTurningSignalState = !(leftTurningSignalState);
      digitalWrite(leftTurningSignalPin, leftTurningSignalState);
      lastBlinkTime = millis();
    }
    steerengAngle = 45;
  }else{
    digitalWrite(leftTurningSignalPin, LOW);
  }
}

void noTurn(){
  steerengAngle = 90;
}

void ballance(){
  readGyro();
/*
  ballanceAngle = tilt;
  if (ballanceAngle > 60){
    ballanceAngle = 60;
  }
  if (ballanceAngle < -60){
    ballanceAngle = -60;
  }
  ballanceAngle += 90;
  servoBallance.write(ballanceAngle);
  */
  // Read the value from the gyro sensor. tilt : 0 to 255.
  input = tilt;
  //PID calculation
  ballancePID.Compute();
  //Write the output as calculated by the PID function
  ballanceAngle = map(output, 0, 255, 150, 30);
  
  servoBallance.write(ballanceAngle);
  //Send data by serial for plotting 
  Serial.print(" ");
  Serial.print(input);
  Serial.print(" ");
  Serial.println(ballanceAngle);
  Serial.print(" ");  
  Serial.print(setPoint);
  Serial.println(" ");
}

void loop() {
  ballance();
  if (radio.available()) {
    radio.read(&info, sizeof(int));
    readInputs(info);
  // Serial.println(info);
  }
  updateLight();
  // Right turn with turningsignal
  if ((directional == 1) /*RIGHT*/ || (directional == 2) /*RIGHT-froward*/ || (directional == 8) /*RIGHT-backward*/){
    turnRight(true);
  }else{
    turnRight(false);
  }
  // Move forward
  if ((directional == 2) /*right-FORWARD*/ || (directional == 3) /*FORWARD*/ || (directional == 4) /*left-FORWARD*/){
    digitalWrite(dcPin1, HIGH);
    digitalWrite(stopPin, LOW);
  }else{
    digitalWrite(dcPin1, LOW);
    digitalWrite(stopPin, HIGH);
  }
  // Move backward
  if ((directional == 6) /*left-BACKWARD*/ || (directional == 7) /*BACKWARD*/ || (directional == 8) /*right-BACKWARD*/){
    digitalWrite(dcPin2, HIGH);
  }else{
    digitalWrite(dcPin2, LOW);
  }
  // Left turn with turningsignal
  if ((directional == 4) /*LEFT-forward*/ || (directional == 5) /*LEFT*/ || (directional == 6) /*LEFT-backward*/){
    turnLeft(true);
  }else{
    turnLeft(false);
  }
  if ((directional == 3) /*FORWARD*/ || (directional == 7) /*BACKWARD*/ || (directional == 0 /*NEUTRAL*/)){
    noTurn();
  }
  // horn:
  if((horn == 1) && ((millis() - lastHornCall) > hornDuration)){ // if we call the tone function as fast as possible, the sound gets a little distorted.
    tone(buzzerPin, hornTone, hornDuration + 30); // we add 50 to give the arduino time to run through the rest of the loop
    lastHornCall = millis();
  }
  
  servoSteering.write(steerengAngle + 24); // +24 defect de fabricatie :))
}
