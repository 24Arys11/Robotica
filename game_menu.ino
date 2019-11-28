#include <LiquidCrystal.h> // includes the LiquidCrystal Library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int joyPinX = A0;
const int joyPinY = A1;
const int joyPinClick = A2;
int panel = 0; // 0: New game & Settings; 1: Settings & High score.
int menuSize = 3;
int menuOption = 1; // 1: New game; 2: Settings; 3: High score.
int gameDuration = 10; // game duration in seconds.

int coordonateX = 0;
int coordonateY = 0;
int buttonClick = 0;
int stateX = 0;
int stateY = 0;
int isClicked = 0;
int wasClicked = 0;
int stateSW = 0;

int lives = 3;
int level = 1;
int score = 0;
int maxScore = 0;
int maxLevel = 99;
int levelDelay = 2000;

void startGame(int level, int &maxScore){
  int i;
  for(i = 0; i < gameDuration; i = i + (levelDelay / 1000)){
    lcd.setCursor(0,0);
    lcd.print("Lives: ");
    lcd.print(lives);
    lcd.print(" Lvl: ");
    lcd.print(level);
    score = 3*level;
    lcd.setCursor(0,1);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.print("        ");
    delay(levelDelay);
    level++; // We won't modify the starting level, only a copy of it, because we haven't passed level by reference !
  }
  if (score > maxScore){
    maxScore = score;
  }
  wasClicked = 1;
  while(1){
    // printing
    lcd.setCursor(0,0);
    lcd.print("Congrats ! Click");
    lcd.setCursor(0,1);
    lcd.print("to exit !       ");
    // reading button
    buttonClick = analogRead(joyPinClick); // I know it is supposed to be digital, I am supposed to use button pushdown, use a resistor, and make things complicated for the sake of eficiency :)) Sorry :D
    if(buttonClick < 30){
      isClicked = 1;  
    }else if(buttonClick > 100){
      isClicked = 0;
    }
    // check exit condition
    if(isClicked == 1 && wasClicked == 0){
      break;
    }
    wasClicked = isClicked;
  }
}

void settings(int &level){
  wasClicked = 1;
  while(1){
    lcd.setCursor(0,0);
    lcd.print("Starting level: ");
    lcd.setCursor(0,1);
    lcd.print(level);
    lcd.print("               ");
    coordonateX = analogRead(joyPinX);
    coordonateY = analogRead(joyPinY);
      
    if((coordonateX > 850) && (stateX == 1)){
      if(level < maxLevel){
        level++;
      }
      stateX = 0;
    }
    if((coordonateX < 100) && (stateX == 1)){
      if(level > 1){
        level--;
      }
      stateX = 0;
    }
    if((coordonateX > 99) && (coordonateX < 851)){
      stateX = 1;
    }
    buttonClick = analogRead(joyPinClick); // I know it is supposed to be digital, I am supposed to use button pushdown, use a resistor, and make things complicated for the sake of eficiency :)) Sorry :D
    if(buttonClick < 30){
      isClicked = 1;  
    }else if(buttonClick > 100){
      isClicked = 0;
    }
    if((isClicked == 1) && (wasClicked == 0)){
      break;
    }
    wasClicked = isClicked;
  }
}

void highScore(int maxScore){
  wasClicked = 1;
  while(1){
    lcd.setCursor(0,0);
    lcd.print("    ");
    lcd.print(maxScore);
    lcd.print("           ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    buttonClick = analogRead(joyPinClick); // I know it is supposed to be digital, I am supposed to use button pushdown, use a resistor, and make things complicated for the sake of eficiency :)) Sorry :D
    if(buttonClick < 30){
      isClicked = 1;  
    }else if(buttonClick > 100){
      isClicked = 0;
    }
    if((isClicked == 1) && (wasClicked == 0)){
      break;
    }
    wasClicked = isClicked;
  }
}

void selectMenu(int n){
  if (n == 1){
    startGame(level, maxScore);
  }else if(n == 2){
    settings(level);
  }else{
    highScore(maxScore);
  }
}

void setup(){
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(joyPinClick, INPUT);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
}

void loop(){
  // Displaing the menu
  
    if(menuOption == 1){
      panel = 0;
    }
    if(menuOption == 3){
      panel = 1;
    }
    if(panel == 0){
      lcd.setCursor(0,0);
      if(menuOption == 1){
        lcd.print("  ~ New game    ");
      }else{
        lcd.print("    New game    ");
      }
      lcd.setCursor(0,1);
      if(menuOption == 2){
        lcd.print("  ~ Settings    ");
      }else{
        lcd.print("    Settings    ");
      }
      delay(1);
    }else{
      lcd.setCursor(0,0);
      if(menuOption == 2){
        lcd.print("  ~ Settings    ");
      }else{
        lcd.print("    Settings    ");
      }
      lcd.setCursor(0,1);
      if(menuOption == 3){
        lcd.print(" ~ High score   ");
      }else{
        lcd.print("   High score   ");
      }
    }
  // Selecting the menu
    
    coordonateX = analogRead(joyPinX);
    coordonateY = analogRead(joyPinY);
    buttonClick = analogRead(joyPinClick); // I know it is supposed to be digital, I am supposed to use button pushdown, use a resistor, and make things complicated for the sake of eficiency :)) Sorry :D
    if(buttonClick < 30){
      isClicked = 1;  
    }else if(buttonClick > 100){
      isClicked = 0;
    }
  
    if((coordonateX > 850) && (stateX == 1)){
      if(menuOption > 1){
        menuOption--;
      }
      stateX = 0;
    }
    if((coordonateX < 100) && (stateX == 1)){
      if(menuOption < menuSize){
        menuOption++;
      }
      stateX = 0;
    }
    if((coordonateX > 150) && (coordonateX < 850)){
      stateX = 1;
    }
  // Execution
  
    if(isClicked == 1 && wasClicked == 0){
      selectMenu(menuOption);
    }
    wasClicked = isClicked;
  }
