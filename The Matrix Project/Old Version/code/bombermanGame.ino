byte bmCurentLvMap[8][8];
// 0 - nothing; 1 - wall; 2 - destructible.
byte forest1[8][8] = {{0, 1, 0, 2, 0, 2, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0}, {2, 0, 0, 2, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 2}, {1, 0, 0, 0, 2, 0, 1, 0}, {0, 2, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 1}, {0, 1, 0, 2, 0, 0, 0, 2}};
byte forest2[8][8] = {{1, 0, 0, 2, 0, 0, 1, 0}, {2, 0, 1, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 2, 1}, {0, 2, 0, 1, 0, 0, 0, 0}, {0, 1, 0, 2, 0, 1, 2, 0}, {0, 0, 2, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 0, 2, 0, 0}};
byte forest3[8][8] = {{1, 0, 2, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 2, 2, 0, 1}, {1, 0, 2, 0, 0, 0, 1, 0}, {0, 2, 0, 1, 0, 2, 0, 0}, {0, 0, 0, 0, 2, 0, 1, 0}, {2, 1, 2, 1, 0, 1, 0, 2}, {0, 0, 0, 2, 0, 0, 0, 0}, {0, 1, 0, 1, 0, 2, 0, 1}};
byte forest4[8][8] = {{0, 2, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 2, 0, 1, 0, 2, 0}, {0, 0, 0, 1, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 2, 1, 0, 0}, {2, 0, 0, 1, 0, 0, 0, 2}};
byte maze1[8][8] = {{1, 1, 0, 2, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1, 0, 1}, {1, 1, 0, 0, 0, 2, 0, 0}, {2, 0, 0, 1, 1, 0, 1, 0}, {0, 0, 2, 1, 0, 0, 1, 0}, {1, 1, 0, 2, 0, 0, 0, 2}, {0, 0, 0, 1, 0, 1, 0, 1}, {1, 1, 0, 0, 0, 1, 0, 1}};
byte maze2[8][8] = {{0, 0, 2, 0, 0, 1, 0, 2}, {0, 0, 1, 0, 0, 1, 0, 0}, {0, 1, 1, 1, 0, 1, 1, 0}, {0, 1, 0, 2, 0, 0, 1, 0}, {2, 1, 0, 1, 1, 0, 0, 2}, {1, 1, 0, 1, 0, 2, 1, 1}, {0, 0, 0, 1, 0, 1, 0, 0}, {2, 0, 0, 1, 0, 0, 0, 2}};
byte maze3[8][8] = {{2, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 1, 1, 0, 1}, {0, 1, 1, 0, 2, 0, 0, 0}, {0, 0, 0, 2, 1, 0, 1, 1}, {1, 1, 1, 0, 1, 0, 0, 2}, {0, 0, 1, 0, 1, 1, 1, 0}, {1, 0, 0, 2, 0, 0, 0, 0}, {1, 0, 0, 1, 1, 0, 0, 1}};
byte maze4[8][8] = {{0, 2, 1, 0, 0, 2, 0, 0}, {0, 0, 1, 0, 1, 0, 0, 2}, {0, 0, 0, 0, 1, 1, 0, 0}, {2, 1, 0, 0, 0, 0, 0, 1}, {0, 1, 2, 1, 0, 1, 1, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 2, 0, 0}, {2, 0, 0, 2, 0, 1, 2, 0}};
byte crates1[8][8] = {{0, 0, 2, 0, 0, 2, 0, 2}, {2, 0, 0, 0, 2, 0, 0, 2}, {0, 0, 2, 0, 0, 0, 0, 0}, {2, 2, 0, 0, 2, 2, 0, 2}, {0, 0, 0, 0, 0, 0, 0, 0}, {2, 0, 2, 0, 2, 0, 2, 0}, {2, 0, 0, 0, 0, 2, 0, 0}, {0, 2, 0, 2, 0, 0, 0, 2}};
byte crates2[8][8] = {{2, 0, 0, 2, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 2, 0, 2}, {0, 2, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 2, 0, 0, 2, 0}, {0, 2, 0, 0, 0, 2, 0, 0}, {2, 0, 0, 2, 0, 0, 0, 2}, {0, 0, 0, 0, 2, 0, 0, 0}, {2, 0, 0, 2, 0, 0, 2, 0}};
byte village1[8][8] = {{0, 1, 1, 2, 1, 0, 0, 2}, {0, 0, 1, 0, 1, 0, 0, 0}, {1, 0, 1, 0, 2, 0, 1, 1}, {2, 0, 2, 0, 0, 0, 2, 0}, {1, 1, 1, 0, 2, 2, 0, 0}, {1, 0, 2, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 1, 0, 0, 0}, {1, 1, 1, 2, 1, 0, 0, 2}};
byte village2[8][8] = {{1, 1, 1, 0, 2, 0, 1, 1}, {1, 0, 0, 0, 2, 0, 0, 1}, {1, 0, 1, 2, 1, 1, 0, 0}, {0, 2, 0, 0, 0, 1, 2, 0}, {0, 2, 0, 1, 0, 0, 0, 2}, {1, 0, 1, 2, 0, 1, 0, 1}, {1, 0, 0, 0, 2, 0, 0, 1}, {1, 1, 1, 0, 0, 1, 0, 1}};
byte bmCustomLvMap[8][8];

void inConstruction(String x){
  lcd.setCursor(0,0);
  lcd.print(x);
  lcd.setCursor(0,1);
  lcd.print("                ");
  delay(1000);
}

void bmLvEdit(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      bmCustomLvMap[i][j] = EEPROM.read(bmCustomLvAdr + ((i + 1) * j));
    }
  }
  inConstruction("WORK IN PROGRESS");
}

byte defaultCarry;

typedef struct object{

  byte code;                  // You cannot possibly need more than 256 objects. If you do, arduino will crash anyway..
  byte nrOfFrames;
  unsigned long refreshRate;
  bool colision;
  bool inMotion;
  bool frames[6][4];
  byte lives;
  byte locationH;
  byte locationV;
  byte carry;
  byte carryMax;
  byte attribute;             // 0 - normal; 1 - inverted controls; 2 - ability to push bombs;
                              // 3 - increased maximum carry capacity; 4 - sick (increased maximum carry capacity but also automatically place bombs);
  byte countDown;             // For bombs and animations that need to explode or dissapear after a time. Acts as a counter.
  
}object;

// Defining attributes codes:

byte noAbility = 0;
byte invertedCtrl = 1;
byte pushAbility = 2;
byte carryMore = 3;
byte sick = 4;
byte inflammable = 10; // for bombs & overlaps
byte deadly = 11; // for the bomb flame

typedef struct location{
  
  byte dot[4][3];             // A location has 4 dots. each has 3 parameters: display no, coordonate x, coordonate y
  unsigned long lastRefresh;
  byte safety;                 // safety = 0 triggers death ! Other values matter for bot decisions.
  byte obj;                   // It holds the code for the object at that location.
  byte countDown;
  byte currentFrame;
}location;

struct location pos[8][8];

void copyObj(struct object obj1, struct object &obj2, bool noCode){  // we only need to modify the second object.
  
  if(noCode == 0){          // In most cases we do not want to change the object code, just the rest of the attributes.
    obj2.code = obj1.code;
  }
  obj2.nrOfFrames = obj1.nrOfFrames;
  obj2.refreshRate = obj1.refreshRate;
  obj2.colision = obj1.colision;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 4; j++){
      obj2.frames[i][j] = obj1.frames[i][j];
    }
  }
  obj2.lives = obj1.lives;
  obj2.locationH = obj1.locationH;
  obj2.locationV = obj1.locationV;
  obj2.carry = obj1.carry;
  obj2.carryMax = obj1.carryMax;
  obj2.attribute = obj1.attribute;
  obj2.countDown = obj1.countDown;
}

// Defining object codes:

byte nothing = 0;
byte wall = 1;
byte destructible = 2;
byte item = 3;
byte flame = 4;
byte flameEnd = 5;
byte bomb = 6;
byte player1 = 7;
byte player2 = 8;
byte bot1 = 9;
byte bot2 = 10;
byte bot3 = 11;
byte overlapPlayer1 = 12; // this differentiation matters for animation
byte overlapPlayer2 = 13; // player1, player2 and bots have different animations
byte overlapBot = 14;     // since all 3 bots have the same animation we do not have to make an object for each bot.
byte leftMoveStart = 15;
byte leftMoveEnd = 16;
byte rightMoveStart = 17;
byte rightMoveEnd = 18;
byte upMoveStart = 19;
byte upMoveEnd = 20;
byte downMoveStart = 21;
byte downMoveEnd = 22;

// We do not want to remember the codes so we store it in variables. This is usefull because we will make an array of objects. We want to use, for example obj[bomb], instead of obj[6] since obj[6] is the bomb.

struct object obj[23];

void bmGameSetupObjects(){

  for(int i = 0; i < 23; i++){  // This will assign the right code for every bomberman object.
    obj[i].code = i;
  }

// nothing:

  obj[nothing].nrOfFrames = 1;
  obj[nothing].refreshRate = 47000;  // nothing has only one frame (all leds off) It do not need to be rendered often.
                                     // I choose 47 seconds because it is a prime number and it will not intersect with other objects with only one frame.
  obj[nothing].colision = 0;
  for(int i = 0; i < 4; i++){
    obj[nothing].frames[0][i] = 0;
  }
  
// wall:

  obj[wall].nrOfFrames = 1;
  obj[wall].refreshRate = 43000; // same explanation as obj[nothing]
  obj[wall].colision = 1;
  for(int i = 0; i < 4; i++){
    obj[wall].frames[0][i] = 1;
  }

// destructible:

  obj[destructible].nrOfFrames = 4;
  obj[destructible].refreshRate = 503; // I am using prime numbers for fast refresh rates so the probability for more objects to need rendering at the same time would be lower.
  obj[destructible].colision = 1;
  for(int i = 0; i < 4; i++){
    obj[destructible].frames[i][1] = 1;
    obj[destructible].frames[i][2] = 1;
    obj[destructible].frames[i][0] = 0;
    obj[destructible].frames[i][3] = 0;
  }
  obj[destructible].frames[0][0] = 1;
  obj[destructible].frames[2][3] = 1;

// item:

  obj[item].nrOfFrames = 4;
  obj[item].refreshRate = 97;  // I am using prime numbers for fast refresh rates so the probability for more objects to need rendering at the same time would be lower.
  obj[item].colision = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      obj[item].frames[i][j] = 1;
    }
  }
  obj[item].frames[0][0] = 0;
  obj[item].frames[0][1] = 0;
  obj[item].frames[1][1] = 0;
  obj[item].frames[1][3] = 0;
  obj[item].frames[2][3] = 0;
  obj[item].frames[2][2] = 0;
  obj[item].frames[3][2] = 0;
  obj[item].frames[3][0] = 0;

// flame:

  copyObj(obj[wall], obj[flame], 1);
  obj[flame].refreshRate = 150;
  obj[flame].colision = 0;
  obj[flame].attribute = deadly;

// flameEnd:

  obj[flameEnd].nrOfFrames = 2;
  obj[flameEnd].refreshRate = 150;
  obj[flameEnd].colision = 0;
  for(int i = 0; i < 4; i++){
    obj[flameEnd].frames[0][i] = 0;
    obj[flameEnd].frames[1][i] = 0;
  }
  obj[flameEnd].frames[0][0] = 1;
  obj[flameEnd].frames[0][3] = 1;
  obj[flameEnd].frames[1][1] = 1;
  obj[flameEnd].frames[1][2] = 1;
  obj[flameEnd].attribute = deadly;

// bomb:

  obj[bomb].nrOfFrames = 2;
  obj[bomb].refreshRate = 200;
  obj[bomb].colision = 1;
  obj[bomb].inMotion = 0;
  for(int i = 0; i < 4; i++){
    obj[bomb].frames[0][i] = 1;
    obj[bomb].frames[1][i] = 0;
  }
  obj[bomb].attribute = inflammable;
  obj[bomb].countDown = 20;     // 20 * refreshRate = 20 * 0,2 sec = 4 sec;

// player1:

  obj[player1].nrOfFrames = 1;
  obj[player1].refreshRate = 41000;
  obj[player1].colision = 1;
  obj[player1].inMotion = 0;
  obj[player1].frames[0][0] = 0;
  obj[player1].frames[0][1] = 1;
  obj[player1].frames[0][2] = 0;
  obj[player1].frames[0][3] = 1;
  obj[player1].lives = 1;
  obj[player1].carry = 2;
  obj[player1].carryMax = 2;
  obj[player1].locationH = 0;
  obj[player1].locationV = 0;

// player2:

  obj[player2].nrOfFrames = 2;
  obj[player2].refreshRate = 211;
  obj[player2].colision = 1;
  obj[player2].inMotion = 0;
  obj[player2].frames[0][0] = 0;
  obj[player2].frames[0][1] = 1;
  obj[player2].frames[0][2] = 0;
  obj[player2].frames[0][3] = 1;
  obj[player2].lives = 1;
  obj[player2].carry = 2;
  obj[player2].carryMax = 2;
  obj[player2].locationH = 0;
  obj[player2].locationV = 0;
  for(int i = 0; i < 3; i++){
    obj[player2].frames[1][i] = 0;
  }
  obj[player2].frames[1][3] = 1;

// bot1:

  copyObj(obj[player2], obj[bot1], 1);
  obj[bot1].refreshRate = 97;
  // same animation but the blink is slower.

// bot2 & bot3:

  copyObj(obj[bot1], obj[bot2], 1);
  copyObj(obj[bot1], obj[bot3], 1); // 1 - without the object code !

// overlapPlayer1:

  obj[overlapPlayer1].nrOfFrames = 2;
  obj[overlapPlayer1].refreshRate = 200;
  obj[overlapPlayer1].colision = 1;
  for(int i = 0; i < 4; i++){
    obj[overlapPlayer1].frames[0][i] = 1;
  }
  obj[overlapPlayer1].frames[1][0] = 0;
  obj[overlapPlayer1].frames[1][1] = 1;
  obj[overlapPlayer1].frames[1][2] = 0;
  obj[overlapPlayer1].frames[1][3] = 1;
  obj[overlapPlayer1].attribute = inflammable;

// overlapPlayer2:

  copyObj(obj[overlapPlayer1], obj[overlapPlayer2], 1);

// overlapBot:       // since all 3 bots have the same animation we do not have to make an object for each bot.

  copyObj(obj[overlapPlayer1], obj[overlapBot], 1);
  obj[overlapBot].nrOfFrames = 4;
  obj[overlapBot].refreshRate = 100;
  obj[overlapBot].colision = 1;
  for(int i = 0; i < 4; i++){
    obj[overlapBot].frames[0][i] = 1;
    obj[overlapBot].frames[1][i] = 1;
  }
  obj[overlapBot].frames[2][0] = 0;
  obj[overlapBot].frames[2][1] = 1;
  obj[overlapBot].frames[2][2] = 0;
  obj[overlapBot].frames[2][3] = 1;
  obj[overlapBot].frames[3][0] = 0;
  obj[overlapBot].frames[3][1] = 0;
  obj[overlapBot].frames[3][2] = 0;
  obj[overlapBot].frames[3][3] = 1;

// leftMoveStart:

  obj[leftMoveStart].nrOfFrames = 5;
  obj[leftMoveStart].refreshRate = 90;
  obj[leftMoveStart].colision = 1;
  for(int i = 0; i < 4; i++){
    obj[leftMoveStart].frames[0][i] = 1;
    obj[leftMoveStart].frames[1][i] = 1;
    obj[leftMoveStart].frames[2][i] = 1;
    obj[leftMoveStart].frames[3][i] = 1;
    obj[leftMoveStart].frames[4][i] = 0;
  }
  obj[leftMoveStart].frames[0][0] = 0;
  obj[leftMoveStart].frames[1][0] = 0;
  obj[leftMoveStart].frames[2][1] = 0;
  obj[leftMoveStart].frames[2][3] = 0;
  obj[leftMoveStart].frames[3][1] = 0;
  obj[leftMoveStart].frames[3][3] = 0;
  obj[leftMoveStart].frames[4][2] = 1;

// leftMoveEnd:

  obj[leftMoveEnd].nrOfFrames = 5;
  obj[leftMoveEnd].refreshRate = 90;
  obj[leftMoveEnd].colision = 1;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      obj[leftMoveEnd].frames[i][j] = 0;
    }
  }
  obj[leftMoveEnd].frames[3][3] = 1;
  obj[leftMoveEnd].frames[4][1] = 1;
  obj[leftMoveEnd].frames[4][3] = 1;

// rightMoveStart:

  obj[rightMoveStart].nrOfFrames = 5;
  obj[rightMoveStart].refreshRate = 90;
  obj[rightMoveStart].colision = 1;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      obj[rightMoveStart].frames[i][j] = 0;
    }
  }
  obj[rightMoveStart].frames[0][1] = 1;
  obj[rightMoveStart].frames[0][3] = 1;
  obj[rightMoveStart].frames[1][3] = 1;

// rightMoveEnd:

  obj[rightMoveEnd].nrOfFrames = 5;
  obj[rightMoveEnd].refreshRate = 90;
  obj[rightMoveEnd].colision = 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      obj[rightMoveEnd].frames[i][j] = 0;
    }
  }
  for(int i = 3; i < 5; i++){
    for(int j = 0; j < 4; j++){
      obj[rightMoveEnd].frames[i][j] = 1;
    }
  }
  obj[rightMoveEnd].frames[0][2] = 1;
  obj[rightMoveEnd].frames[1][0] = 1;
  obj[rightMoveEnd].frames[1][2] = 1;
  obj[rightMoveEnd].frames[2][0] = 1;
  obj[rightMoveEnd].frames[2][2] = 1;
  obj[rightMoveEnd].frames[3][1] = 0;
  obj[rightMoveEnd].frames[4][0] = 0;

// upMoveStart:

  obj[upMoveStart].nrOfFrames = 3;
  obj[upMoveStart].refreshRate = 150;
  obj[upMoveStart].colision = 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      obj[upMoveStart].frames[i][j] = 0;
    }
  }
  obj[upMoveStart].frames[0][1] = 1;
  obj[upMoveStart].frames[1][1] = 1;

// upMoveEnd:

  obj[upMoveEnd].nrOfFrames = 3;
  obj[upMoveEnd].refreshRate = 150;
  obj[upMoveEnd].colision = 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      obj[upMoveEnd].frames[i][j] = 0;
    }
  }
  obj[upMoveEnd].frames[1][3] = 1;
  obj[upMoveEnd].frames[2][3] = 1;

// downMoveStart:

  obj[downMoveStart].nrOfFrames = 3;
  obj[downMoveStart].refreshRate = 150;
  obj[downMoveStart].colision = 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      obj[downMoveStart].frames[i][j] = 0;
    }
  }
  obj[downMoveStart].frames[0][3] = 1;
  obj[downMoveStart].frames[1][3] = 1;

// downMoveEnd:

  obj[downMoveEnd].nrOfFrames = 3;
  obj[downMoveEnd].refreshRate = 150;
  obj[downMoveEnd].colision = 1;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      obj[downMoveEnd].frames[i][j] = 0;
    }
  }
  obj[downMoveEnd].frames[1][1] = 1;
  obj[downMoveEnd].frames[2][1] = 1;
}


void place(struct object o, struct location &pos){
  pos.currentFrame = 0;
  pos.obj = o.code;
}

void render(struct location &pos){
  for(byte i = 0; i < 4; i++){
    lc.setLed(pos.dot[i][0], pos.dot[i][1], pos.dot[i][2], obj[pos.obj].frames[pos.currentFrame][i]); // turns on/off LED at col, row
  }
  pos.currentFrame++;
  if (pos.currentFrame == obj[pos.obj].nrOfFrames){
    pos.currentFrame = 0;
  }
  
  pos.lastRefresh = millis();
}


void spawnPlayer(struct object &player){

  byte spawnPoint = random() % 4;

  if(spawnPoint == 0){
    if(obj[pos[1][1].obj].colision == 0){
      player.locationV = 1;
      player.locationH = 1;
      place(player, pos[1][1]);
      render(pos[1][1]);
    }else{
      spawnPlayer(player);
    }
  }else if(spawnPoint == 1){
    if(obj[pos[1][6].obj].colision == 0){
      player.locationV = 1;
      player.locationH = 6;
      place(player, pos[1][6]);
      render(pos[1][6]);
    }else{
      spawnPlayer(player);
    }
  }else if(spawnPoint == 2){
    if(obj[pos[6][1].obj].colision == 0){
      player.locationV = 6;
      player.locationH = 1;
      place(player, pos[6][1]);
      render(pos[6][1]);
    }else{
      spawnPlayer(player);
    }
  }else if(spawnPoint == 3){
    if(obj[pos[6][6].obj].colision == 0){
      player.locationV = 6;
      player.locationH = 6;
      place(player, pos[6][6]);
      render(pos[6][6]);
    }else{
      spawnPlayer(player);
    }
  }
}

void renderAll(){
  for(byte i = 0; i < 8; i++){
    for(byte j = 0; j < 8; j++){
      render(pos[i][j]);
    }
  }
}

void moveObj(char inDirection, struct object &o){ // direction is a keyword :(
  
  o.inMotion = 1;

  if(inDirection == 'U'){
    if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer1].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer2].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else{
      place(obj[upMoveStart], pos[o.locationV][o.locationH]);
    }
    render(pos[o.locationV][o.locationH]);
    o.locationV--;
    place(obj[upMoveEnd], pos[o.locationV][o.locationH]);
    render(pos[o.locationV][o.locationH]);
  }else if(inDirection == 'D'){
    if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer1].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer2].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else{
      place(obj[downMoveStart], pos[o.locationV][o.locationH]);
    }
    render(pos[o.locationV][o.locationH]);
    o.locationV++;
    place(obj[downMoveEnd], pos[o.locationV][o.locationH]);
    render(pos[o.locationV][o.locationH]);
  }else if(inDirection == 'L'){
    if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer1].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer2].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else{
      place(obj[leftMoveStart], pos[o.locationV][o.locationH]);
    }
    render(pos[o.locationV][o.locationH]);
    o.locationH--;
    place(obj[leftMoveEnd], pos[o.locationV][o.locationH]);
    render(pos[o.locationV][o.locationH]);
  }else if(inDirection == 'R'){
    if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer1].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else if(obj[pos[o.locationV][o.locationH].obj].code == obj[overlapPlayer2].code){
      place(obj[bomb], pos[o.locationV][o.locationH]);
    }else{
      place(obj[rightMoveStart], pos[o.locationV][o.locationH]);
    }
    render(pos[o.locationV][o.locationH]);
    o.locationH++;
    place(obj[rightMoveEnd], pos[o.locationV][o.locationH]);
    render(pos[o.locationV][o.locationH]);
  }
}

String attributes[5] = {"Healthy ", "Drunk   ", "Strong  ", "Smart   ", "Sick    "}; // the spaces are so we will not have to clear the screen when we overlap a scorter attribute over a longer one

void showBmScreen(bool mode){
  clearLcdScreen();
    lcd.setCursor(0,0);
    lcd.print(attributes[obj[player1].attribute]);
    lcd.setCursor(0,1);
    lcd.print("Bombs:");
    lcd.setCursor(6,1);
    lcd.print(obj[player1].carry);
  if(mode == 1){
    lcd.setCursor(8,0);
    lcd.print(attributes[obj[player2].attribute]);
    lcd.setCursor(8,1);
    lcd.print("Bombs:");
    lcd.setCursor(14,1);
    lcd.print(obj[player2].carry);
  }
}

void generateLevel(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      bmCurentLvMap[i][j] = random() % 4; // 0 - nothing; 1 - wall; 2 - destructible.
      if(bmCurentLvMap[i][j] == 3){ // we double the chance for nothing to be placed
        bmCurentLvMap[i][j] = 0;
      }
    }
  }
  // we make sure nothing is placed at the spawning points
  bmCurentLvMap[1][1] = nothing;
  bmCurentLvMap[1][6] = nothing;
  bmCurentLvMap[6][1] = nothing;
  bmCurentLvMap[6][6] = nothing;
  
  // we create some space at the spawning points
  bmCurentLvMap[0][0] = nothing;
  bmCurentLvMap[0][7] = nothing;
  bmCurentLvMap[7][0] = nothing;
  bmCurentLvMap[7][7] = nothing;
  
  if(random() % 2 == 0){
    bmCurentLvMap[0][1] = nothing;
  }else{
    bmCurentLvMap[1][0] = nothing;
  }
    if(random() % 2 == 0){
    bmCurentLvMap[0][6] = nothing;
  }else{
    bmCurentLvMap[1][7] = nothing;
  }
  if(random() % 2 == 0){
    bmCurentLvMap[7][1] = nothing;
  }else{
    bmCurentLvMap[6][0] = nothing;
  }
  if(random() % 2 == 0){
    bmCurentLvMap[7][6] = nothing;
  }else{
    bmCurentLvMap[6][7] = nothing;
  }

  // we create a path without walls that connects the spawning points.

  for(int i = 2; i < 6; i++){
    for(int j = 2; j < 6; j++){
      if(bmCurentLvMap[i][j] == 1){ // remove walls
        bmCurentLvMap[i][j] = 0;
      }
    }
  }
  for(int i = 3; i < 5; i++){   // In the center we could have walls.
    for(int j = 3; j < 5; j++){ // This process might be a little redundant but it only runs once. Not in the loop !
      bmCurentLvMap[i][j] = random() % 3; // 0 - nothing; 1 - wall; 2 - destructible.
    }
  }
  if(random() % 2 == 0){
    bmCurentLvMap[1][2] = random() % 3; // 0 - nothing; 2 - destructible.
    if(bmCurentLvMap[1][2] == 1){ // we double the chance for nothing to be placed
      bmCurentLvMap[1][2] = 0;
    }
  }else{
    bmCurentLvMap[2][1] = 2 * (random() % 2); // 0 - nothing; 2 - destructible.
  }
  if(random() % 2 == 0){
    bmCurentLvMap[5][1] = random() % 3; // 0 - nothing; 2 - destructible.
    if(bmCurentLvMap[5][1] == 1){ // we double the chance for nothing to be placed
      bmCurentLvMap[5][1] = 0;
    }
  }else{
    bmCurentLvMap[6][2] = 2 * (random() % 2); // 0 - nothing; 2 - destructible.
  }
  if(random() % 2 == 0){
    bmCurentLvMap[1][5] = random() % 3; // 0 - nothing; 2 - destructible.
    if(bmCurentLvMap[1][5] == 1){ // we double the chance for nothing to be placed
      bmCurentLvMap[1][5] = 0;
    }
  }else{
    bmCurentLvMap[2][6] = 2 * (random() % 2); // 0 - nothing; 2 - destructible.
  }
  if(random() % 2 == 0){
    bmCurentLvMap[5][6] = random() % 3; // 0 - nothing; 2 - destructible.
    if(bmCurentLvMap[5][6] == 1){ // we double the chance for nothing to be placed
      bmCurentLvMap[5][6] = 0;
    }
  }else{
    bmCurentLvMap[6][5] = 2 * (random() % 2); // 0 - nothing; 2 - destructible.
  }
}

void copyLv(byte level[8][8]){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      bmCurentLvMap[i][j] = level[i][j];
    }
  }
}

void primeCurrentLevel(){

  // Generate random; Forest 1; Forest 2; Forest 3; Forest 4; Maze 1; Maze 2; Maze 3; Maze 4; Crates 1; Crates 2; Vilage 1; Village 2; Level editor
  if(bmSelectedLv == 0){
    generateLevel();
  }else if(bmSelectedLv == 1){
    copyLv(forest1);
  }else if(bmSelectedLv == 2){
    copyLv(forest2);
  }else if(bmSelectedLv == 3){
    copyLv(forest3);
  }else if(bmSelectedLv == 4){
    copyLv(forest4);
  }else if(bmSelectedLv == 5){
    copyLv(maze1);
  }else if(bmSelectedLv == 6){
    copyLv(maze2);
  }else if(bmSelectedLv == 7){
    copyLv(maze3);
  }else if(bmSelectedLv == 8){
    copyLv(maze4);
  }else if(bmSelectedLv == 9){
    copyLv(crates1);
  }else if(bmSelectedLv == 10){
    copyLv(crates2);
  }else if(bmSelectedLv == 11){
    copyLv(village1);
  }else if(bmSelectedLv == 12){
    copyLv(village2);
  }else{
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        bmCurentLvMap[i][j] = EEPROM.read(bmCustomLvAdr + ((i + 1) * j));
      }
    }
  }
}

void loadCurrentLevel(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      place(obj[bmCurentLvMap[i][j]], pos[i][j]);
    }
  }
}

void explode(int i, int j){ // i & j are the coordonates
  place(obj[flame], pos[i][j]);
  byte flameCountDown = 12;
  pos[i][j].countDown = flameCountDown;
  pos[i][j].safety = 0;
  // extend flame uppward
  if(i > 0){
    if(pos[i - 1][j].obj != wall){
      if(pos[i - 1][j].obj == destructible){
        if(random() % 8 == 0){
          place(obj[item], pos[i - 1][j]);
        }else{
          place(obj[nothing], pos[i - 1][j]);
        }
        render(pos[i - 1][j]);
      }else if(obj[pos[i - 1][j].obj].attribute == inflammable){
        explode(i - 1, j);
      }else{
        place(obj[flame], pos[i - 1][j]);
        render(pos[i - 1][j]);
        pos[i - 1][j].countDown = flameCountDown;
        pos[i - 1][j].safety = 0;
        if((i - 1) > 0){
          if(pos[i - 2][j].obj != wall){
            if(pos[i - 2][j].obj == destructible){
              if(random() % 5 == 0){
                place(obj[item], pos[i - 2][j]);
              }else{
                place(obj[nothing], pos[i - 2][j]);
              }
              render(pos[i - 2][j]);
            }else if(obj[pos[i - 2][j].obj].attribute == inflammable){
              explode(i - 2, j);
            }else{
              place(obj[flameEnd], pos[i - 2][j]);
              render(pos[i - 2][j]);
              pos[i - 2][j].countDown = flameCountDown;
              pos[i - 2][j].safety = 0;
            }
          }
        }
      }
    }
  }
  // extend flame downward
  if(i < 7){
    if(pos[i + 1][j].obj != wall){
      if(pos[i + 1][j].obj == destructible){
        if(random() % 5 == 0){
          place(obj[item], pos[i + 1][j]);
        }else{
          place(obj[nothing], pos[i + 1][j]);
        }
        render(pos[i + 1][j]);
      }else if(obj[pos[i + 1][j].obj].attribute == inflammable){
        explode(i + 1, j);
      }else{
        place(obj[flame], pos[i + 1][j]);
        render(pos[i + 1][j]);
        pos[i + 1][j].countDown = flameCountDown;
        pos[i + 1][j].safety = 0;
        if((i + 1) < 7){
          if(pos[i + 2][j].obj != wall){
            if(pos[i + 2][j].obj == destructible){
              if(random() % 5 == 0){
                place(obj[item], pos[i + 2][j]);
              }else{
                place(obj[nothing], pos[i + 2][j]);
              }
              render(pos[i + 2][j]);
            }else if(obj[pos[i + 2][j].obj].attribute == inflammable){
              explode(i + 2, j);
            }else{
              place(obj[flameEnd], pos[i + 2][j]);
              render(pos[i + 2][j]);
              pos[i + 2][j].countDown = flameCountDown;
              pos[i + 2][j].safety = 0;
            }
          }
        }
      }
    }
  }
  // extend flame to the left
  if(j > 0){
    if(pos[i][j - 1].obj != wall){
      if(pos[i][j - 1].obj == destructible){
        if(random() % 5 == 0){
          place(obj[item], pos[i][j - 1]);
        }else{
          place(obj[nothing], pos[i][j - 1]);
        }
        render(pos[i][j - 1]);
      }else if(obj[pos[i][j - 1].obj].attribute == inflammable){
        explode(i, j - 1);
      }else{
        place(obj[flame], pos[i][j - 1]);
        render(pos[i][j - 1]);
        pos[i][j - 1].countDown = flameCountDown;
        pos[i][j - 1].safety = 0;
        if((j - 1) > 0){
          if(pos[i][j - 2].obj != wall){
            if(pos[i][j - 2].obj == destructible){
              if(random() % 5 == 0){
                place(obj[item], pos[i][j - 2]);
              }else{
                place(obj[nothing], pos[i][j - 2]);
              }
              render(pos[i][j - 2]);
            }else if(obj[pos[i][j - 2].obj].attribute == inflammable){
              explode(i, j - 2);
            }else{
              place(obj[flameEnd], pos[i][j - 2]);
              render(pos[i][j - 2]);
              pos[i][j - 2].countDown = flameCountDown;
              pos[i][j - 2].safety = 0;
            }
          }
        }
      }
    }
  }
  // extend flame to the right
  if(j < 7){
    if(pos[i][j + 1].obj != wall){
      if(pos[i][j + 1].obj == destructible){
        if(random() % 5 == 0){
          place(obj[item], pos[i][j + 1]);
        }else{
          place(obj[nothing], pos[i][j + 1]);
        }
        render(pos[i][j + 1]);
      }else if(obj[pos[i][j + 1].obj].attribute == inflammable){
        explode(i, j + 1);
      }else{
        place(obj[flame], pos[i][j + 1]);
        render(pos[i][j + 1]);
        pos[i][j + 1].countDown = flameCountDown;
        pos[i][j + 1].safety = 0;
        if((j + 1) < 7){
          if(pos[i][j + 2].obj != wall){
            if(pos[i][j + 2].obj == destructible){
              if(random() % 5 == 0){
                place(obj[item], pos[i][j + 2]);
              }else{
                place(obj[nothing], pos[i][j + 2]);
              }
              render(pos[i][j + 2]);
            }else if(obj[pos[i][j + 2].obj].attribute == inflammable){
              explode(i, j + 2);
            }else{
              place(obj[flameEnd], pos[i][j + 2]);
              render(pos[i][j + 2]);
              pos[i][j + 2].countDown = flameCountDown;
              pos[i][j + 2].safety = 0;
            }
          }
        }
      }
    }
  }
}

void gameOver(String result){
  if(result == "singlePlayerVictory"){
    lcd.setCursor(0,0);
    lcd.print("    YOU WIN !   ");
    lcd.setCursor(0,1);
    lcd.print("Score: ");
    lcd.setCursor(7,1);
    lcd.print(score);
  }else if(result == "singlePlayerDefeat"){
    lcd.setCursor(0,0);
    lcd.print("     DEFEAT !   ");
    lcd.setCursor(0,1);
    lcd.print("Score: ");
    lcd.setCursor(7,1);
    lcd.print(" 0      ");
  }else if(result == "player1Wins"){
    lcd.setCursor(0,0);
    lcd.print("   GAME OVER !  ");
    lcd.setCursor(0,1);
    lcd.print("Player 1 wins ! ");
  }else if(result == "player2Wins"){
    lcd.setCursor(0,0);
    lcd.print("   GAME OVER !  ");
    lcd.setCursor(0,1);
    lcd.print("Player 2 wins ! ");
  }else if(result == "equality"){
    lcd.setCursor(0,0);
    lcd.print("   GAME OVER !  ");
    lcd.setCursor(0,1);
    lcd.print("    EQUALITY !  ");
  }else{
    lcd.setCursor(0,0);
    lcd.print("   GAME OVER !  ");
    lcd.setCursor(0,1);
    lcd.print("    ERROR !!!   ");
  }
  delay(7000);
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      place(obj[nothing], pos[i][j]);
    }
  }
  renderAll();
  loop();
}

void bombermanGame(bool mode){ // 0 - Single Player; 1 - Two players.

//Setup:
  prevC1Button = 1;
  
  randomSeed(millis()); // the time you start the game depends of when you decide to sellect "Start game" from the menu, so it is not the same every time !
  
  int bots;
  if(mode == 0){
    bots = bmSpBots;
  }else{
    bots = bmTpBots;
  }
  defaultCarry = 2;

  unsigned long currentTime = millis();
  unsigned long prevTime  = currentTime;
  unsigned long pausedTime = 0;

  byte bombCountDown = 20;

  bmGameSetupObjects();
  bmGameSetupPositions();
  
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      pos[i][j].lastRefresh = currentTime;
      pos[i][j].safety = 1;
    }
  }

  primeCurrentLevel();
  loadCurrentLevel();

  renderAll();
  
  spawnPlayer(obj[player1]);
//  if(mode == 0){ // Single player
//    for(int i = 0; i < bmSpBots){
//      spawnPlayer(bot);
//    }
//  }else{ // Two players
//    for(int i = 0; i < bmTpBots){
//      spawnPlayer(bot);
//    }
//    spawnPlayer(player2);
//  }

  if(mode == 1){
    spawnPlayer(obj[player2]);
  }

  unsigned long cooldownPlayer1 = 0;
  unsigned long cooldownPlayer2 = 0;

  bool lcdChanged = 1;

  unsigned long reloadTime = 4000;

//Loop:
  while(1){
    if(lcdChanged == 1){
      showBmScreen(mode);
      lcdChanged = 0;
    }
    currentTime = millis();
    readInputs();

    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        if(currentTime > (pos[i][j].lastRefresh + obj[pos[i][j].obj].refreshRate)){
          if(pos[i][j].obj > 14){ // If it is an animation. (15 - 22 - movement animations) (!) obj[22] is the last object
            if(pos[i][j].currentFrame == 0){ // If the animation ended and restarted (animations should only run once)
              if(pos[i][j].obj % 2 == 1){ // If it is a starting motion (the code for starting movements is odd and the code for ending movements is even)
                place(obj[nothing], pos[i][j]);
              }else{  // else means it is an ending movement !
                if(obj[player1].locationV == i && obj[player1].locationH == j){
                  place(obj[player1], pos[i][j]);
                  obj[player1].inMotion = 0;
                }else if(obj[player2].locationV == i && obj[player2].locationH == j){
                  obj[player2].inMotion = 0;
                  place(obj[player2], pos[i][j]);
                }else if(obj[bot1].locationV == i && obj[bot1].locationH == j){
                  obj[bot1].inMotion = 0;
                  place(obj[bot1], pos[i][j]);
                }else if(obj[bot2].locationV == i && obj[bot2].locationH == j){
                  obj[bot2].inMotion = 0;
                  place(obj[bot2], pos[i][j]);
                }else if(obj[bot3].locationV == i && obj[bot3].locationH == j){
                  obj[bot3].inMotion = 0;
                  place(obj[bot3], pos[i][j]);
                }else{
                  playError(); // (Sound effect) This should never happen !
                }
              }
            }
          }
          if(obj[pos[i][j].obj].attribute == inflammable){
            pos[i][j].countDown--;
            if(pos[i][j].countDown == 0){
              explode(i, j);
            }
          }
          if(obj[pos[i][j].obj].attribute == deadly){
            pos[i][j].countDown--;
            if(pos[i][j].countDown == 0){
              place(obj[nothing], pos[i][j]);
              pos[i][j].safety = 1;
            }
          }
          render(pos[i][j]);
        }
      }
    }

  if(c1JoyY == 'D' && obj[player1].inMotion == 0){
    if(obj[player1].locationV < 7){   // If it is not on the edge of the screen
      if(obj[pos[obj[player1].locationV + 1][obj[player1].locationH].obj].colision == 0){  // If there is no solid object at the destination
        if(pos[obj[player1].locationV + 1][obj[player1].locationH].safety == 0){
          obj[player1].lives--;
        }else{
        moveObj('D', obj[player1]);
        playPlayerMove(); // Sound Effect
        }
      }else if((pos[obj[player1].locationV + 1][obj[player1].locationH].obj == bomb) && (obj[player1].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
        // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
        // move bomb up to 3 squares
        // move player
      }
    }
  }else if(c1JoyY == 'U' && obj[player1].inMotion == 0){
    if(obj[player1].locationV > 0){   // If it is not on the edge of the screen
      if(obj[pos[obj[player1].locationV - 1][obj[player1].locationH].obj].colision == 0){  // If there is no solid object at the destination
        if(pos[obj[player1].locationV - 1][obj[player1].locationH].safety == 0){
          obj[player1].lives--;
        }else{
        moveObj('U', obj[player1]);
        playPlayerMove(); // Sound Effect
        }
      }else if((pos[obj[player1].locationV - 1][obj[player1].locationH].obj == bomb) && (obj[player1].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
        // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
        // move bomb up to 3 squares
        // move player
      }
    }
  }
  if(c1JoyX == 'R' && obj[player1].inMotion == 0){
    if(obj[player1].locationH < 7){   // If it is not on the edge of the screen
      if(obj[pos[obj[player1].locationV][obj[player1].locationH + 1].obj].colision == 0){  // If there is no solid object at the destination
        if(pos[obj[player1].locationV][obj[player1].locationH + 1].safety == 0){
          obj[player1].lives--;
        }else{
        moveObj('R', obj[player1]);
        playPlayerMove(); // Sound Effect
        }
      }else if((pos[obj[player1].locationV][obj[player1].locationH + 1].obj == bomb) && (obj[player1].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
        // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
        // move bomb up to 3 squares
        // move player
      }
    }
  }else if(c1JoyX == 'L' && obj[player1].inMotion == 0){
    if(obj[player1].locationH > 0){  // If it is not on the edge of the screen
      if(obj[pos[obj[player1].locationV][obj[player1].locationH - 1].obj].colision == 0){  // If there is no solid object at the destination
        if(pos[obj[player1].locationV][obj[player1].locationH - 1].safety == 0){
          obj[player1].lives--;
        }else{
        moveObj('L', obj[player1]);
        playPlayerMove(); // Sound Effect
        }
      }else if((pos[obj[player1].locationV][obj[player1].locationH - 1].obj == bomb) && (obj[player1].attribute == pushAbility)){
        // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
        // move bomb up to 3 squares
        // move player
      }
    }
  }

  if(c1Button == 1 && prevC1Button == 0 && obj[player1].inMotion == 0){
    prevC1Button = 1;
    if((obj[player1].carry > 0) && (pos[obj[player1].locationV][obj[player1].locationH].obj != overlapPlayer1)){
      playPlaceBomb(); // Sound effect
      pos[obj[player1].locationV][obj[player1].locationH].countDown = bombCountDown;
      obj[player1].carry--;
      lcdChanged = 1;
      cooldownPlayer1 = millis();
      place(obj[overlapPlayer1], pos[obj[player1].locationV][obj[player1].locationH]);
      render(pos[obj[player1].locationV][obj[player1].locationH]);
    }
  }
  if((obj[player1].carry < obj[player1].carryMax) && (millis() > cooldownPlayer1 + reloadTime)){
    cooldownPlayer1 = millis();
    obj[player1].carry++;
    lcdChanged = 1;
  }
  if(c1JoySW == 1 && prevC1JoySW == 0){
    prevC1JoySW = 1;
    clearLcdScreen();
    pausedTime = millis();  // save currentTime
    pause();
    pausedTime = millis() - pausedTime; // calculate pausedTime
    currentTime += pausedTime; // update currentTime;
    prevTime += pausedTime; // update prevTime;
    cooldownPlayer1 += pausedTime;  // we update everything that cares about the time !
    cooldownPlayer2 += pausedTime;
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        pos[i][j].lastRefresh += pausedTime;
      }
    }
    showBmScreen(mode);
  }
  if(pos[obj[player1].locationV][obj[player1].locationH].safety == 0){
    obj[player1].lives--;
  }
  if (mode == 1){
    if(c2JoyY == 'D' && obj[player2].inMotion == 0){
      if(obj[player2].locationV < 7){   // If it is not on the edge of the screen
        if(obj[pos[obj[player2].locationV + 1][obj[player2].locationH].obj].colision == 0){  // If there is no solid object at the destination
          if(pos[obj[player2].locationV + 1][obj[player2].locationH].safety == 0){
            obj[player2].lives--;
          }else{
          moveObj('D', obj[player2]);
          playPlayerMove(); // Sound Effect
          }
        }else if((pos[obj[player2].locationV + 1][obj[player2].locationH].obj == bomb) && (obj[player2].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
          // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
          // move bomb up to 3 squares
          // move player
        }
      }
    }else if(c2JoyY == 'U' && obj[player2].inMotion == 0){
      if(obj[player2].locationV > 0){   // If it is not on the edge of the screen
        if(obj[pos[obj[player2].locationV - 1][obj[player2].locationH].obj].colision == 0){  // If there is no solid object at the destination
          if(pos[obj[player2].locationV - 1][obj[player2].locationH].safety == 0){
            obj[player2].lives--;
          }else{
          moveObj('U', obj[player2]);
          playPlayerMove(); // Sound Effect
          }
        }else if((pos[obj[player2].locationV - 1][obj[player2].locationH].obj == bomb) && (obj[player2].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
          // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
          // move bomb up to 3 squares
          // move player
        }
      }
    }
    if(c2JoyX == 'R' && obj[player2].inMotion == 0){
      if(obj[player2].locationH < 7){   // If it is not on the edge of the screen
        if(obj[pos[obj[player2].locationV][obj[player2].locationH + 1].obj].colision == 0){  // If there is no solid object at the destination
          if(pos[obj[player2].locationV][obj[player2].locationH + 1].safety == 0){
            obj[player2].lives--;
          }else{
          moveObj('R', obj[player2]);
          playPlayerMove(); // Sound Effect
          }
        }else if((pos[obj[player2].locationV][obj[player2].locationH + 1].obj == bomb) && (obj[player2].attribute == pushAbility)){ // if the blocking object is a bomb and player1 has the ability to push bombs
          // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
          // move bomb up to 3 squares
          // move player
        }
      }
    }else if(c2JoyX == 'L' && obj[player2].inMotion == 0){
      if(obj[player2].locationH > 0){  // If it is not on the edge of the screen
        if(obj[pos[obj[player2].locationV][obj[player2].locationH - 1].obj].colision == 0){  // If there is no solid object at the destination
          if(pos[obj[player2].locationV][obj[player2].locationH - 1].safety == 0){
            obj[player2].lives--;
          }else{
          moveObj('L', obj[player2]);
          playPlayerMove(); // Sound Effect
          }
        }else if((pos[obj[player2].locationV][obj[player2].locationH - 1].obj == bomb) && (obj[player2].attribute == pushAbility)){
          // if the bomb is not on the edge of the screen and there is no solid object at the bomb destination
          // move bomb up to 3 squares
          // move player
        }
      }
    }
  
    if(c2Button == 1 && prevC2Button == 0 && obj[player2].inMotion == 0){
      prevC2Button = 1;
      if((obj[player2].carry > 0) && (pos[obj[player2].locationV][obj[player2].locationH].obj != overlapPlayer2)){
        playPlaceBomb(); // Sound effect
        pos[obj[player2].locationV][obj[player2].locationH].countDown = bombCountDown;
        obj[player2].carry--;
        lcdChanged = 1;
        cooldownPlayer2 = millis();
        place(obj[overlapPlayer2], pos[obj[player2].locationV][obj[player2].locationH]);
        render(pos[obj[player2].locationV][obj[player2].locationH]);
      }
    }
    if((obj[player2].carry < obj[player2].carryMax) && (millis() > cooldownPlayer2 + reloadTime)){
      cooldownPlayer2 = millis();
      obj[player2].carry++;
      lcdChanged = 1;
    }
    if(pos[obj[player2].locationV][obj[player2].locationH].safety == 0){
      obj[player2].lives--;
    }
    if(obj[player2].lives == 0){
      if(obj[player1].lives != 0){
        gameOver("player1Wins");
      }else{
        gameOver("equality");
      }
    }
  }
  if(obj[player1].lives == 0){
    if(mode == 0){
      gameOver("singlePlayerDefeat");
    }else{
      if(obj[player2].lives != 0){
        gameOver("player2Wins");
      }else{
        gameOver("equality");
      }
    }
  }
  saveInputs();
  }
}
