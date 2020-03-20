#include "pitches.h"

//notes in the melody
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

//digital pin 12 has a button attached to it.
const int buttonPin = 12;

//pin 11 has a buzzer attached to it.
const int buzzerPin = A2;

//note durations. 4 = quarter note / 8 = eighth note
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

int buzzerState;
int buttonState;

void setup(){

  //make the button's pin input
  pinMode(buttonPin, INPUT);
  //make the buzzer's pin input
  pinMode(buzzerPin, INPUT);
  Serial.begin(9600);
}


void loop(){

  buzzerState = analogRead(buzzerPin);

  Serial.println(buzzerState);
  //Serial.println(buttonState);
  //if the button is pressed
  if (buzzerState < 100){

    //iterate over the notes of the melody
    for (int thisNote = 0; thisNote < 8; thisNote++){
      buttonState = digitalRead(buttonPin);
      if (buttonState == 1){
        break;
      }
      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(8, melody [thisNote], noteDuration);

      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      //stop the tone playing
      noTone(8);
    }
  }
}
