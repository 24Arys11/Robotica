#include <EEPROM.h>
#include "pitches.h"

#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include "LedControl.h" //  need the library

LiquidCrystal lcd(27, 2, 4, 5, 6, 7);
LedControl lc = LedControl(32, 28, 30, 4); //DIN, CLK, LOAD(CS), No. DRIVER

const int c1JoyPinX = A1;
const int c1JoyPinY = A2;
const int c1JoyPinSW = 51;
const int c1ButtonPin = 50;
const int c2JoyPinX = A4;
const int c2JoyPinY = A5;
const int c2ButtonPin = 26;
const int buzzerPin = 45;
const int annoyingLedPin = 13;

/*
  We must save to EEPROM the followings:
    * Nr of bots in single player mode...............DONE
    * Nr of bots in two player mode..................DONE
    * Bot dificulty..................................DONE
    * Selected level.................................DONE
    * Player name (10 characters)....................DONE
    * Music On/Off...................................DONE
    * High score: 5x (player name and player score)..IN_PROGRESS
    * Mapping of level editor........................PENDING...
 */

const int shiftEEPROM = 0; // if EEPROM gets damaged, we can shift all the adresses just by changing this variable !
const int noOfLetters = 27;
const char letters[noOfLetters] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const int difficultyAdr = 0 + shiftEEPROM;
const int bmSpBotsAdr = 1 + shiftEEPROM;
const int bmTpBotsAdr = 2 + shiftEEPROM;
const int bmSelectedLvAdr = 3 + shiftEEPROM;
const int musicAdr = 4 + shiftEEPROM;

// I left some space for other variables just in case..
const int bmPlayerAdr = 10 + shiftEEPROM; // It needs 10 bytes !

int bmPlayerName[10];
int bmHighScore[5][11];
int score = 0;
const int scoreSupplement = 27;
const int scoreMultiply = 54;

bool music = EEPROM.read(musicAdr);
unsigned long songTime;
unsigned long consoleTime;
unsigned long inputsDefer = 100;
unsigned int songCounter = 0;

// I left one byte in between the arrays just to feel safe..

const int bmHighScoreAdr[5] = {21 + shiftEEPROM, 33 + shiftEEPROM, 45 + shiftEEPROM, 57 + shiftEEPROM, 70 + shiftEEPROM}; // There will be saved the top 5 highscores ! Each needs 11 bytes. (10 for name, 1 for score).
const int bmCustomLvAdr = 90 + shiftEEPROM;

void place(struct object o, struct location &pos);
void render(struct location &pos);
void spawnPlayer(struct object &player);

void loadBmPlayerName(){
  for(int i = 0; i < 10; i++){
    bmPlayerName[i] = EEPROM.read(bmPlayerAdr + i);
  }
}

void loadHighScores(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 11; j++){
      bmHighScore[i][j] = EEPROM.read(bmHighScoreAdr[i] + j);
    }
  }
}

void saveBmPlayerName(){
  for(int i = 0; i < 10; i++){
    EEPROM.update(bmPlayerAdr + i, bmPlayerName[i]);
  }
}

int difficulty = EEPROM.read(difficultyAdr);
int bmSpBots = EEPROM.read(bmSpBotsAdr); // Number of bots in "single player" mode
int bmTpBots = EEPROM.read(bmTpBotsAdr); // Number of bots in "two players" mode
int bmSelectedLv = EEPROM.read(bmSelectedLvAdr); // Number of bots in "two players" mode

void clearLcdScreen(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void wellcome(int player[10]){
  lcd.setCursor(0,0);
  lcd.print("  Hello,        ");
  lcd.setCursor(0,1);
  lcd.print("  ");
  for(int i = 0; i < 10; i++){
    lcd.setCursor(i + 2, 1);
    lcd.print(letters[player[i]]);
  }
  playWellcome(); // Audio with delay (takes 2 sec)
}

void setup(){

  // Serial.begin(9600); // for debuging
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display

  pinMode(annoyingLedPin, OUTPUT);
  digitalWrite(annoyingLedPin, LOW); // Was blinking randomly
  
  pinMode(c1JoyPinX, INPUT);
  pinMode(c1JoyPinY, INPUT);
  pinMode(c1JoyPinSW, INPUT_PULLUP);
  pinMode(c1ButtonPin, INPUT);
  pinMode(c2JoyPinX, INPUT);
  pinMode(c2JoyPinY, INPUT);
  pinMode(c2ButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 1); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  lc.shutdown(1, false); // turn off power saving, enables display
  lc.setIntensity(1, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(1);// clear screen
  lc.shutdown(2, false); // turn off power saving, enables display
  lc.setIntensity(2, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(2);// clear screen
  lc.shutdown(3, false); // turn off power saving, enables display
  lc.setIntensity(3, 1); // sets brightness (0~15 possible values)
  lc.clearDisplay(3);// clear screen

  clearLcdScreen();
  loadBmPlayerName();
  wellcome(bmPlayerName);
  clearLcdScreen();
  
  loadHighScores();
  songTime = millis();
  consoleTime = millis();

  delay(1);
}

// Every function that starts with "play..." is a sound effect or mellody

void displayPanel(int curentPanel, int selectedOption, int entries, String options[]){

  clearLcdScreen();

  if(entries < 2){
    
    lcd.setCursor(1,0);
    lcd.print(options[curentPanel]);
    lcd.setCursor(0,0);
    lcd.print("~");
  }else{
    
    lcd.setCursor(1,0);
    lcd.print(options[curentPanel]);
    lcd.setCursor(1,1);
    lcd.print(options[curentPanel + 1]);
    if (selectedOption == curentPanel){
      lcd.setCursor(0,0);
      lcd.print("~");
    }else{
      lcd.setCursor(0,1);
      lcd.print("~");
    }
  }
}

  char c1JoyX;
  char c1JoyY;
  bool c1JoySW;
  bool c1Button;
  char c2JoyX;
  char c2JoyY;
  bool c2Button;

  char prevC1JoyX = 'N';
  char prevC1JoyY = 'N';
  bool prevC1JoySW = 0;
  bool prevC1Button = 0;
  char prevC2JoyX = 'N';
  char prevC2JoyY = 'N';
  bool prevC2Button = 0;

char interpret(int analogValue, bool orientation){ // 0 - horizontal; 1 - vertical
  if(analogValue > 850){
    if(orientation == 0){
      return 'R'; // Right
    }else{
      return 'D'; // Down
    }
  }else if(analogValue < 150){
    if(orientation == 0){
      return 'L'; // Left
    }else{
      return 'U'; // Up
    }
  }else{
    return 'N'; // Normal
  }
}

void readInputs(){
  c1JoyX = interpret(analogRead(c1JoyPinX), 0);
  c1JoyY = interpret(analogRead(c1JoyPinY), 1);
  c1JoySW = !digitalRead(c1JoyPinSW);
  c1Button = digitalRead(c1ButtonPin);
  c2JoyX = interpret(analogRead(c2JoyPinX), 0);
  c2JoyY = interpret(analogRead(c2JoyPinY), 1);
  c2Button = digitalRead(c2ButtonPin);
}

void saveInputs(){
  prevC1JoyX = c1JoyX;
  prevC1JoyY = c1JoyY;
  prevC1JoySW = c1JoySW;
  prevC1Button = c1Button;
  prevC2JoyX = c2JoyX;
  prevC2JoyY = c2JoyY;
  prevC2Button = c2Button;
}

void returnTrigger(){ // It's a fake function !
  return;
}


void createMenu(int &selected, int entries, String options[], void *actions[]){

  void (*function)();
  int panel;
  if((selected == (entries - 1)) && (entries > 1)){
    panel = entries - 2;
  }else{
    panel = selected;
  }  
  int lastSelected = selected;

  displayPanel(panel, selected, entries, options);
  consoleTime = millis();
  prevC1Button = 1;

  while(1){

    readInputs();
  
    if(selected < panel){
      panel--;
    }else if(selected > (panel + 1)){ 
      panel++;
    }
    
    if(selected != lastSelected){ // No need to refresh the LCD if there is no change
      displayPanel(panel, selected, entries, options);
    }
      lastSelected = selected;
  
    if(c1JoyY == 'D' && prevC1JoyY == 'N' && (millis() > consoleTime + inputsDefer)){
      consoleTime = millis();
      if(selected < (entries - 1)){
        selected++;
        playMenuSelect(); // Sound Effect
      }else{
        playMenuEnd();  // Sound Effect
      }
    }else if(c1JoyY == 'U' && prevC1JoyY == 'N' && (millis() > consoleTime + inputsDefer)){
      consoleTime = millis();
      if(selected > 0){
        selected--;
        playMenuSelect(); // Sound Effect
      }else{
        playMenuEnd();  // Sound Effect
      }
    }
  
    if(c1Button == 1 && prevC1Button == 0 && (millis() > consoleTime + inputsDefer)){
      consoleTime = millis();
      prevC1Button = 1;
      playMenuClick(); // Sound Effect
      function = actions[selected];
      if(function == &returnTrigger){
        return;
      }else{
        function();
      }

      //when function returns we need to refresh the LCD screen
      displayPanel(panel, selected, entries, options);
    }
    
    saveInputs(); // Saving last button states
      
    if(music == 1){
      playMenuSong();
    }
  }
}

const int installedGames = 1;
int selectedGame = 0;
const String games[installedGames] = {"Bomberman"}; // Max 15 characters
void *actions[installedGames] = {&bombermanMenu};

void loop(){
  
    createMenu(selectedGame, installedGames, games, actions);
    
  delay(1);
}
