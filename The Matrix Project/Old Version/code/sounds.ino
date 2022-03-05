// Every function that starts with "play..." is a sound effect or mellody

void playMenuSelect(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_D6, 75);
}

void playMenuEnd(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_D5, 75);
}

void playMenuClick(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_C6, 75);
}

void playPlayerMove(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_GS6, 75);
}

void playPlaceBomb(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_GS4, 75);
}

void playWellcome(){

  // This song will only run in wellcome screen !

  noTone(buzzerPin);
  tone(buzzerPin, NOTE_C6, 120);
  delay(170);
  tone(buzzerPin, NOTE_D6, 120);
  delay(170);
  tone(buzzerPin, NOTE_E6, 120);
  delay(170);
  tone(buzzerPin, NOTE_C6, 120);
  delay(170);
  tone(buzzerPin, NOTE_D6, 120);
  delay(170);
  tone(buzzerPin, NOTE_E6, 120);
  delay(170);
  tone(buzzerPin, NOTE_E6, 120);
  delay(170);
  tone(buzzerPin, NOTE_D6, 120);
  delay(170);
  tone(buzzerPin, NOTE_C6, 120);
  delay(170);
  tone(buzzerPin, NOTE_D6, 120);
  delay(170);
  tone(buzzerPin, NOTE_G6, 270);
  delay(300);
}

/*
void playGameOver(){
  
}
*/

void playError(){
  noTone(buzzerPin);
  tone(buzzerPin, NOTE_AS7, 500);
}

void playMenuSong(){
  unsigned long duration = 180; // all notes have the same duration.
  int nrOfNotes = 31;
  int notes[32] = {NOTE_E4, NOTE_DS5, NOTE_E4, NOTE_DS5, NOTE_E4, NOTE_DS5, NOTE_F5, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A5, NOTE_A5, NOTE_GS4, NOTE_GS4, NOTE_B5, NOTE_E4, NOTE_D3, NOTE_E4, NOTE_E4, NOTE_DS5, NOTE_G5, NOTE_E4, NOTE_B5, NOTE_D4, NOTE_GS4, NOTE_D4, NOTE_GS4, NOTE_AS4, NOTE_FS4, NOTE_GS4,};
  if(millis() > songTime + duration){
    songTime = millis();
    noTone(buzzerPin);
    tone(buzzerPin, notes[songCounter], 140);
    songCounter++;
    if(songCounter > nrOfNotes){
      songCounter = 0;
    }
  }
}
