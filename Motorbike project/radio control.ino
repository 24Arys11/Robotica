#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "71993";

const int buttonPin = 5;
const int joyPinX = A1;
const int joyPinY = A2;
const int joyPinSW = 4;

const int highThreshold = 650;
const int lowThreshold = 350;

void setup(){
//  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
  pinMode(joyPinSW, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

int buttonState = 0;
int joyX = 0;
int joyY = 0;
int joySW = 0;

int info = 1000;

void loop(){
  buttonState = digitalRead(buttonPin);
  joyX = analogRead(joyPinX);
  joyY = analogRead(joyPinY);
  joySW = !digitalRead(joyPinSW);
  if(joyY > highThreshold){
    if(joyX > highThreshold){
      info += 200;
    }else if(joyX < lowThreshold){
      info += 800;
    }else{
      info += 100;
    }
  }else if(joyY < lowThreshold){
    if(joyX > highThreshold){
      info += 400;
    }else if(joyX < lowThreshold){
      info += 600;
    }else{
      info += 500;
    }
  }else{
    if(joyX > highThreshold){
      info += 300;
    }else if(joyX < lowThreshold){
      info += 700;
    }
  }
  if(joySW == 1){
    info += 10;
  }
  if(buttonState == 1){
    info += 1;
  }
  radio.write(&info, sizeof(info));
//  Serial.println(info);
  info = 1000;
  delay(1);
}
