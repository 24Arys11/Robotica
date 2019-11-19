// joystick
const int pinX = A0;
const int pinY = A1;
const int pinClick = 1;

// display
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

// segments array, similar to before
int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
// digits array, to switch between them easily
int digits[noOfDisplays] = {
pinD1, pinD2, pinD3, pinD4
};
byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1}  // 9
};

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
  digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}


void displayNrOnScreen(int number, int screen){
  showDigit(screen);
  for(int i = 0; i < segSize - 1; i++){
    if(digitMatrix[number][i] == HIGH){
      digitalWrite(segments[i], HIGH);
    }else{
      digitalWrite(segments[i], LOW);
    }
  }
}

  int number[noOfDisplays] = {0, 0, 0, 0};
  int screen = 0;
  int coordonateX;
  int coordonateY;
  int buttonClick;
  int stateX = 0;
  int stateY = 0;

void setup() {
  for (int i = 0; i < segSize - 1; i++){
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++){
    pinMode(digits[i], OUTPUT);
  }
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinClick, INPUT);
  Serial.begin(9600);
}

void loop() {
  coordonateX = analogRead(pinX);
  coordonateY = analogRead(pinY);
  buttonClick = digitalRead(pinClick);

  if((coordonateX > 850) && (stateX == 1)){
    number[screen]++;
    stateX = 0;
  }
  if((coordonateX < 100) && (stateX == 1)){
    number[screen]--;
    stateX = 0;
  }
  if((coordonateY > 900) && (stateY == 1)){
    screen--;
    stateY = 0;
  }
  if((coordonateY < 150) && (stateY == 1)){
    screen++;
    stateY = 0;
  }
  if(number[screen] > 9){
    number[screen] = 0;
  }
  if(screen > 3){
    screen = 0;
  }
  if(number[screen] < 0){
    number[screen] = 9;
  }
  if(screen < 0){
    screen = 3;
  }
  displayNrOnScreen(number[screen], screen);
  if((coordonateX > 150) && (coordonateX < 850)){
    stateX = 1;
  }
  if((coordonateY > 150) && (coordonateY < 900)){
    stateY = 1;
  }
}
