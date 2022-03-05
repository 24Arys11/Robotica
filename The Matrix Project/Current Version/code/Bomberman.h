#ifndef BOMBERMAN_H_INCLUDED
#define BOMBERMAN_H_INCLUDED


static struct Assets{
  
  /*  // Could be useful to have all the possible combinations for a future game
  
  Object oooo = Object(1, 500);
  Object ooox = Object(1, 500);
  Object ooxx = Object(1, 500);
  Object oxox = Object(1, 500);
  Object xoox = Object(1, 500);
  Object ooxo = Object(1, 500);
  Object oxxo = Object(1, 500);
  Object xoxo = Object(1, 500);
  Object oxoo = Object(1, 500);
  Object xxoo = Object(1, 500);
  Object xooo = Object(1, 500);
  Object xxxo = Object(1, 500);
  Object xxox = Object(1, 500);
  Object xoxx = Object(1, 500);
  Object oxxx = Object(1, 500);
  Object xxxx = Object(1, 500);
  */
  
  Object nothing = Object(1, 17581);  // To avoid a full render of all 4 matrices at the same time, I used 17581 (a prime) milliseconds frameDuration,
                                      // so that the probability of other objects requiring rendering at the same time with "nothing" objects is minimized.
  Object wall = Object(1, 17579);     // 17579 is another prime, so the walls will not be rendered at the same time with nothing objects.
  Object destructible = Object(4, 541);  // 541 is also prime, so destructibles are less likely to be rendered at the same time with other type of objects.
  Object item = Object(4, 97);
  Object flame = Object(2, 97, 14);
  Object bomb = Object(2, 250, 20);
  Object player1 = Object(1, 500);
  Object player2 = Object(2, 211);
  Object bot = Object(2, 97);
  Object overlap = Object(2, 250);  // when a player place a bomb, the player sits on top of the bomb.
  Object leftMoveStart = Object(6, 90, 6);
  Object leftMoveEnd = Object(6, 90, 6);
  Object rightMoveStart = Object(6, 90, 6);
  Object rightMoveEnd = Object(6, 90, 6);
  Object upMoveStart = Object(5, 90, 5);
  Object upMoveEnd = Object(5, 90, 5);
  Object downMoveStart = Object(5, 90, 5);
  Object downMoveEnd = Object(5, 90, 5);
  
  Assets(){
    
    /*
    oooo.setFrame(0, false, false, false, false);
    ooox.setFrame(0, false, false, false, true);
    ooxx.setFrame(0, false, false, true, true);
    oxox.setFrame(0, false, true, false, true);
    xoox.setFrame(0, true, false, false, true);
    ooxo.setFrame(0, false, false, true, false);
    oxxo.setFrame(0, false, true, true, false);
    xoxo.setFrame(0, true, false, true, false);
    oxoo.setFrame(0, false, true, false, false);
    xxoo.setFrame(0, true, true, false, false);
    xooo.setFrame(0, true, false, false, false);
    xxxo.setFrame(0, true, true, true, false);
    xxox.setFrame(0, true, true, false, true);
    xoxx.setFrame(0, true, false, true, true);
    oxxx.setFrame(0, false, true, true, true);
    xxxx.setFrame(0, true, true, true, true);
    */

    nothing.setFrame(0, false, false, false, false);
    nothing.setColision(false);
    wall.setFrame(0, true, true, true, true);
    wall.setColision(true);
    destructible.setFrame(0, false, true, true, true);
    destructible.setFrame(1, true, false, true, true);
    destructible.setFrame(2, true, true, true, false);
    destructible.setFrame(3, true, true, false, true);
    destructible.setColision(true);
    item.setFrame(0, true, true, false, false);
    item.setFrame(1, false, true, false, true);
    item.setFrame(2, false, false, true, true);
    item.setFrame(3, true, false, true, false);
    item.setColision(false);
    flame.setFrame(0, true, false, false, true);
    flame.setFrame(1, false, true, true, false);
    flame.setColision(false);
    bomb.setFrame(0, true, true, true, true);
    bomb.setFrame(1, false, false, false, false);
    bomb.setColision(true);
    bomb.setFrameAudio(&Playlist.bombBipEffect);
    player1.setFrame(0, false, true, false, true);
    player1.setColision(true);
    player2.setFrame(0, false, true, false, true);
    player2.setFrame(1, false, false, false, true);
    player2.setColision(true);
    bot.setFrame(0, false, true, false, true);
    bot.setFrame(1, false, false, false, true);
    bot.setColision(true);
    overlap.setFrame(0, true, true, true, true);
    overlap.setFrame(1, false, true, false, true);
    overlap.setColision(true);
    overlap.setFrameAudio(&Playlist.bombBipEffect);
    leftMoveStart.setFrame(0, false, true, true, true);
    leftMoveStart.setFrame(1, true, false, true, true);
    leftMoveStart.setFrame(2, true, false, true, false);
    leftMoveStart.setFrame(3, true, false, true, false);
    leftMoveStart.setFrame(4, false, false, true, false);
    leftMoveStart.setFrame(5, false, false, false, false);
    leftMoveStart.setColision(true);
    leftMoveEnd.setFrame(0, false, false, false, false);
    leftMoveEnd.setFrame(1, false, false, false, false);
    leftMoveEnd.setFrame(2, false, false, false, false);
    leftMoveEnd.setFrame(3, false, false, false, true);
    leftMoveEnd.setFrame(4, false, true, false, true);
    leftMoveEnd.setFrame(5, false, true, false, true);
    leftMoveEnd.setColision(true);
    leftMoveEnd.setFrameAudio(&Playlist.walkEffect);  /* only the "__End" animations have sound effect for 2 reasons:
                                                          * if (a player placed a bomb) {only end animation runs}
                                                          * else {start animations run at the same time with the end animations}
                                                      */
    rightMoveStart.setFrame(0, false, true, false, true);
    rightMoveStart.setFrame(1, false, false, false, true);
    rightMoveStart.setFrame(2, false, false, false, false);
    rightMoveStart.setFrame(3, false, false, false, false);
    rightMoveStart.setFrame(4, false, false, false, false);
    rightMoveStart.setFrame(5, false, false, false, false);
    rightMoveStart.setColision(true);
    rightMoveEnd.setFrame(0, false, false, true, false);
    rightMoveEnd.setFrame(1, true, false, true, false);
    rightMoveEnd.setFrame(2, true, false, true, false);
    rightMoveEnd.setFrame(3, true, false, true, true);
    rightMoveEnd.setFrame(4, false, true, true, true);
    rightMoveEnd.setFrame(5, false, true, false, true);
    rightMoveEnd.setColision(true);
    rightMoveEnd.setFrameAudio(&Playlist.walkEffect);
    upMoveStart.setFrame(0, false, true, false, true);
    upMoveStart.setFrame(1, false, true, false, false);
    upMoveStart.setFrame(2, false, true, false, false);
    upMoveStart.setFrame(3, false, false, false, false);
    upMoveStart.setFrame(4, false, false, false, false);
    upMoveStart.setColision(true);
    upMoveEnd.setFrame(0, false, false, false, false);
    upMoveEnd.setFrame(1, false, false, false, false);
    upMoveEnd.setFrame(2, false, false, false, true);
    upMoveEnd.setFrame(3, false, false, false, true);
    upMoveEnd.setFrame(4, false, true, false, true);
    upMoveEnd.setColision(true);
    upMoveEnd.setFrameAudio(&Playlist.walkEffect);
    downMoveStart.setFrame(0, false, true, false, true);
    downMoveStart.setFrame(1, false, false, false, true);
    downMoveStart.setFrame(2, false, false, false, true);
    downMoveStart.setFrame(3, false, false, false, false);
    downMoveStart.setFrame(4, false, false, false, false);
    downMoveStart.setColision(true);
    downMoveEnd.setFrame(0, false, false, false, false);
    downMoveEnd.setFrame(1, false, false, false, false);
    downMoveEnd.setFrame(2, false, true, false, false);
    downMoveEnd.setFrame(3, false, true, false, false);
    downMoveEnd.setFrame(4, false, true, false, true);
    downMoveEnd.setColision(true);
    downMoveEnd.setFrameAudio(&Playlist.walkEffect);
    
  }
  
}Assets;


class LevelMap{

private:

  char level[8][8];
  
public:

  LevelMap(char* rows0, char* rows1, char* rows2, char* rows3, char* rows4, char* rows5, char* rows6, char* rows7){
    
    for(int i = 0; i < 8; i++){

      level[0][i] = rows0[i];
      level[1][i] = rows1[i];
      level[2][i] = rows2[i];
      level[3][i] = rows3[i];
      level[4][i] = rows4[i];
      level[5][i] = rows5[i];
      level[6][i] = rows6[i];
      level[7][i] = rows7[i];
    }
  }

  String iconifyRow(int rowIndex){
    
    String rows = "";
    
    for(int i = 0; i < 8; i++){
      
      if(isEqual(level[rowIndex][i], '2') || isEqual(level[rowIndex][i], '1')){
        
        rows += '1';
      }else{
        
        rows += '0';
      }
    }
    return rows;
  }

  char query(int row, int col){

    return level[row][col];
  }
  
};


static class Level{

private:

  byte currentLevelIndex;
  
  // 0 - nothing; 1 - wall; 2 - destructible.
  LevelMap level[12] = {{"01020201", "00001000", "20020100", "00100002", "10002010", "02010000", "00000101", "01020002"},
                        {"10020010", "20101000", "10000021", "02010000", "01020120", "00200000", "10001001", "00100200"},
                        {"10201000", "00012201", "10200010", "02010200", "00002010", "21210102", "00020000", "01010201"},
                        {"02000100", "00101001", "00000001", "11201020", "00010010", "10100001", "00002100", "20010002"},
                        {"11020101", "00010101", "11000200", "20011010", "00210010", "11020002", "00010101", "11000101"},
                        {"00200102", "00100100", "01110110", "01020010", "21011002", "11010211", "00010100", "20010002"},
                        {"20001001", "00101101", "01102000", "00021011", "11101002", "00101110", "10020000", "10011001"},
                        {"02100200", "00101002", "00001100", "21000001", "01210110", "00000000", "00110200", "20020120"},
                        {"00200202", "20002002", "00200000", "22002202", "00000000", "20202020", "20000200", "02020002"},
                        {"20020000", "00000202", "02002000", "00020020", "02000200", "20020002", "00002000", "20020020"},
                        {"01121002", "00101000", "10102011", "20200020", "11102200", "10201011", "10001000", "11121002"},
                        {"11102011", "10002001", "10121100", "02000120", "02010002", "10120101", "10002001", "11100101"}};

  void loadLevel(LevelMap lvl){

    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){

        if(isEqual(lvl.query(row, col), '0')){
          
          MatrixManager.placeObject(&(Assets.nothing), row, col);
          
        }else if(isEqual(lvl.query(row, col), '1')){
          
          MatrixManager.placeObject(&(Assets.wall), row, col);
          
        }else{  // => isEqual( ... , '2')
          
          MatrixManager.placeObject(&(Assets.destructible), row, col);
        }
      }
    }
  }
  
public:

  struct Index{

    const byte forest1 = 0;
    const byte forest2 = 1;
    const byte forest3 = 2;
    const byte forest4 = 3;
    const byte maze1 = 4;
    const byte maze2 = 5;
    const byte maze3 = 6;
    const byte maze4 = 7;
    const byte crates1 = 8;
    const byte crates2 = 9;
    const byte village1 = 10;
    const byte village2 = 11;
    const byte generateRandom = 12;
    
  }Index;

  Level(){  /// CONSTRUCTOR
    
    Set(currentLevelIndex, EEPROMManager.getGameLevel());
  }

  void setLevel(byte selectedLevel){

    Set(currentLevelIndex, selectedLevel);
    EEPROMManager.setGameLevel(selectedLevel);
  }

  byte getCurrentLevelIndex(){

    return currentLevelIndex;
  }

  Icon levelIcon(byte levelIndex){

    if(isGreater(levelIndex, byte(11))){
      
      return MenuIcons.randomLevel;
    }

    char rows[8][8];

    String s;
    
    for(int i = 0; i < 8; i++){

      s = level[levelIndex].iconifyRow(i);
      s.toCharArray(rows[i], s.length());
      Set(rows[i][7], s[7]);
    }
    
    return Icon(rows[0],
                rows[1],
                rows[2],
                rows[3],
                rows[4],
                rows[5],
                rows[6],
                rows[7]);
  }

  void loadCurrent(){

    // For the random generated level:
    if(isGreater(currentLevelIndex, byte(11))){

      char rows[8][8];

      // Step 1: Generate a completely random level
      for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){

          switch(random() % 3){
            case 0:
              rows[row][col] = '0'; // nothing
              break;
            case 1:
              rows[row][col] = '1'; // wall
              break;
            case 2:
              rows[row][col] = '2'; // destructible
              break;
          }
          
        }
      }

      // Step 2: Free space for and around the spawn points
      rows[1][0] = rows[1][1] = rows[2][1] = rows[1][6] = rows[1][7] = rows[2][6] = '0';
      rows[6][0] = rows[6][1] = rows[5][1] = rows[6][6] = rows[6][7] = rows[5][6] = '0';
      
      // Step 3: Make a "H" path with no walls, so players may reach each other.
      for(int i = 2; i < 6; i++){
        switch(random() % 2){
            case 0:
              rows[i][2] = '0'; // nothing
              break;
            case 1:
              rows[i][2] = '2'; // destructible
              break;
          }
          switch(random() % 2){
            case 0:
              rows[i][5] = '0'; // nothing
              break;
            case 1:
              rows[i][5] = '2'; // destructible
              break;
          }
          switch(random() % 2){
            case 0:
              rows[3][i] = '0'; // nothing
              break;
            case 1:
              rows[3][i] = '2'; // destructible
              break;
          }
      }
      
      LevelMap randomLevel = LevelMap(rows[0], rows[1], rows[2], rows[3], rows[4], rows[5], rows[6], rows[7]);
      
      loadLevel(randomLevel);
      return;
    }

    // For the other levels:
    loadLevel(level[currentLevelIndex]);
  }

}Level;


struct Score{

  String playerName;
  byte playerScore; // max opponents defeated. Could be 1, 2 or 3 !
  
  Score(String playerName = "", byte playerScore = 0){ // CONSTRUCTOR

    Set(this->playerName, playerName);
    Set(this->playerScore, playerScore);
  }

  Score(const Score& s){ // COPY CONSTRUCTOR

    Set(playerName, s.playerName);
    Set(playerScore, s.playerScore);
  }

  Score& operator=(const Score& s){

    Set(playerName, s.playerName);
    Set(playerScore, s.playerScore);

    return *this;
  }
  
};


class Player{

private:

  Object* avatar;
  bool alive;
  byte hPos;
  byte vPos;
  bool sleeping;  // for AI to rest from time to time
  bool inMotion;
  byte bombs;
  byte carryCapacity;
  byte state; // 0 - normal, 1 - drunk, 2 - sick, 3 - strong, 4 - invincible
  unsigned long timeToNormalize;
  unsigned long timeToRefill;
  unsigned long timeToWakeUp;

  static const unsigned long refillInterval = 5100;
  static const unsigned long normalizeInterval = 15000;
  static const unsigned long sleepDuration = 500;

public:

  Player(Object* avatar){

    Set(this->avatar, avatar);
    initialize();
  }

  void initialize(){
    
    Set(alive, false);  // Becomes alive when it is selected to be spawned in the game. Some players could be missing from the match.
                        // Example: P1 and AI (no P2) or P1 and P2 (no AI)...
    Set(inMotion, false);
    Set(sleeping, false);
    Set(bombs, byte(2));
    Set(carryCapacity, byte(2));
    Set(state, byte(0));  // 0 - normal, 1 - drunk, 2 - sick, 3 - strong, 4 - invincible
  }

  void spawn(byte row, byte col){

    Set(vPos, row);
    Set(hPos, col);

    Set(alive, true);

    MatrixManager.placeObject(avatar, vPos, hPos);
  }
  
  void goLeft(){

    if(isEqual(state, byte(1))){  // if (is drunk)

      Set(state, byte(0));  // 0 - normal
      goRight();
      Set(state, byte(1));  // 1 - drunk
      return;
    }

    if(isLesser(hPos - 1, 0)){
      return;
    }
    
    if((MatrixManager.getPosition(vPos, hPos - 1).getObject())->hasColision()){
      return;
    }
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos - 1).getObject(), &Assets.item)){
      pickItem();
    }

    if(isEqual(MatrixManager.getPosition(vPos, hPos).getObject(), &Assets.overlap)){ // a bomb has been placed
      
      MatrixManager.placeObject(&Assets.bomb, vPos, hPos);
      
    }else{
      
      MatrixManager.placeObject(&Assets.leftMoveStart, vPos, hPos);
    }
    
    hPos--;
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos).getSafety(), byte(0))){
      
      if(die()){  // Could be in the invincible state => it will not die
        return;
      }
    }
    
    MatrixManager.placeObject(&Assets.leftMoveEnd, vPos, hPos);
    Set(inMotion, true);
  }

  void goRight(){

    if(isEqual(state, byte(1))){  // if (is drunk)

      Set(state, byte(0));  // 0 - normal
      goLeft();
      Set(state, byte(1));  // 1 - drunk
      return;
    }

    if(isGreater(hPos + 1, 7)){
      return;
    }
    
    if((MatrixManager.getPosition(vPos, hPos + 1).getObject())->hasColision()){
      return;
    }
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos + 1).getObject(), &Assets.item)){
      pickItem();
    }

    if(isEqual(MatrixManager.getPosition(vPos, hPos).getObject(), &Assets.overlap)){ // a bomb has been placed
      
      MatrixManager.placeObject(&Assets.bomb, vPos, hPos);
      
    }else{
      
      MatrixManager.placeObject(&Assets.rightMoveStart, vPos, hPos);
    }
    
    hPos++;
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos).getSafety(), byte(0))){
      
      if(die()){  // Could be in the invincible state => it will not die
        return;
      }
    }
    
    MatrixManager.placeObject(&Assets.rightMoveEnd, vPos, hPos);
    Set(inMotion, true);
  }

  void goUp(){

    if(isEqual(state, byte(1))){  // if (is drunk)

      Set(state, byte(0));  // 0 - normal
      goDown();
      Set(state, byte(1));  // 1 - drunk
      return;
    }

    if(isLesser(vPos - 1, 0)){
      return;
    }
    
    if((MatrixManager.getPosition(vPos - 1, hPos).getObject())->hasColision()){
      return;
    }
    
    if(isEqual(MatrixManager.getPosition(vPos - 1, hPos).getObject(), &Assets.item)){
      pickItem();
    }

    if(isEqual(MatrixManager.getPosition(vPos, hPos).getObject(), &Assets.overlap)){ // a bomb has been placed
      
      MatrixManager.placeObject(&Assets.bomb, vPos, hPos);
      
    }else{
      
      MatrixManager.placeObject(&Assets.upMoveStart, vPos, hPos);
    }
    
    vPos--;
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos).getSafety(), byte(0))){
      
      if(die()){  // Could be in the invincible state => it will not die
        return;
      }
    }
    
    MatrixManager.placeObject(&Assets.upMoveEnd, vPos, hPos);
    Set(inMotion, true);
  }

  void goDown(){

    if(isEqual(state, byte(1))){  // if (is drunk)

      Set(state, byte(0));  // 0 - normal
      goUp();
      Set(state, byte(1));  // 1 - drunk
      return;
    }

    if(isGreater(vPos + 1, 7)){
      return;
    }
    
    if((MatrixManager.getPosition(vPos + 1, hPos).getObject())->hasColision()){
      return;
    }
    
    if(isEqual(MatrixManager.getPosition(vPos + 1, hPos).getObject(), &Assets.item)){
      pickItem();
    }

    if(isEqual(MatrixManager.getPosition(vPos, hPos).getObject(), &Assets.overlap)){ // a bomb has been placed
      
      MatrixManager.placeObject(&Assets.bomb, vPos, hPos);
      
    }else{
      
      MatrixManager.placeObject(&Assets.downMoveStart, vPos, hPos);
    }
    
    vPos++;
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos).getSafety(), byte(0))){
      
      if(die()){  // Could be in the invincible state => it will not die
        return;
      }
    }
    
    MatrixManager.placeObject(&Assets.downMoveEnd, vPos, hPos);
    Set(inMotion, true);
  }

  void placeBomb(){

    if(isGreater(bombs, byte(0))){

      if(isEqual(bombs, carryCapacity)){

        Set(timeToRefill, millis() + refillInterval);
      }
      
      MatrixManager.placeObject(&Assets.overlap, vPos, hPos);
      bombs--;
    }
  }

  void update(){
    
    if(isEqual(MatrixManager.getPosition(vPos, hPos).getSafety(), byte(0))){
      
      if(die()){  // Could be in the invincible state => it will not die
        return;
      }
    }

    // finish a move:
    if(inMotion && (MatrixManager.getPosition(vPos, hPos)).isExpired()){ // avatar never expires => a walking animation is complete.
                                                                    // nothing else can exist at player's location because the player has colision !
      MatrixManager.placeObject(avatar, vPos, hPos);
      Set(inMotion, false);
    }

    // refill inventory:
    if(isLesser(bombs, carryCapacity) && isGreater(millis(), timeToRefill)){

      bombs++;
      Set(timeToRefill, millis() + refillInterval);
    }

    // deal with different states
    if(isNotEqual(state, byte(0))){ // 0 - normal

      // reset to normal state:
      if(isGreater(millis(), timeToNormalize)){

        if(isEqual(state, byte(3))){ // 3 - strong
          
          Set(carryCapacity, byte(2));  // in strong state, carryCapacity is 4.
          if(isGreater(bombs, carryCapacity)){
            Set(bombs, byte(2));
          }
        }

        if(isEqual(state, byte(2))){ // 2 - sick
          
          Set(carryCapacity, byte(2));  // in sick state, carryCapacity is 0.
          Set(bombs, byte(2));
        }
        
        Set(state, byte(0));  // 0 - normal
      }
      
    }

    // Awake AI
    if(sleeping && isGreater(millis(), timeToWakeUp)){

      Set(sleeping, false);
    }
    
  }

  byte getVPos(){

    return vPos;
  }

  byte getHPos(){

    return hPos;
  }

  bool isAlive(){

    return alive;
  }

  bool die(){
    
    if(isEqual(state, byte(4))){  // 4 - invincible
      
      return false;
    }
    
    Set(alive, false);
    return true;
  }

  void sleep(){ // used for AI to rest from time to time.

    Set(sleeping, true);
    Set(timeToWakeUp, millis() + sleepDuration);
  }

  bool isSleeping(){

    return sleeping;
  }

  bool isNear(byte row, byte col){  // needed by AI

    if( (isEqual(vPos, row) && (isEqual(hPos, byte(col - 1)) || isEqual(hPos, byte(col + 1)))) ||
        (isEqual(hPos, col) && (isEqual(vPos, byte(row - 1)) || isEqual(vPos, byte(row + 1)))) ){

      return true;
    }

    return false;
    
  }
  
  void pickItem(){

    SoundSystem.addSound(&Playlist.itemPickUpEffect);

    switch(random() % 4){ // state: 0 - normal, 1 - drunk, 2 - sick, 3 - strong, 4 - invincible
      case 0:
        Set(state, byte(1));  // 1 - drunk
        break;
      case 1:
        Set(state, byte(2));  // 2 - sick
        Set(carryCapacity, byte(0));
        Set(bombs, byte(0));
        break;
      case 2:
        Set(state, byte(3));  // 3 - strong
        Set(carryCapacity, byte(4));
        Set(bombs, byte(bombs + 2));
        break;
      default:
        Set(state, byte(4));  // 4 - invincible
        break;
    }

    Set(timeToNormalize, millis() + normalizeInterval);
  }

  byte capacity(){

    return carryCapacity;
  }

  byte nrOfBombs(){

    return bombs;
  }

  byte getState(){

    return state;
  }

  String expressState(){

    switch(state){
      case 1:
        return "DRUNK";
      case 2:
        return "SICK";
      case 3:
        return "STRONG";
      case 4:
        return "GODMODE";
      default:  // case 0 - the only one left.
        return "NORMAL";
    }
  }

  bool isMoving(){

    return inMotion;
  }
  
};


static class HighScores{

private:

  Score score[3];

  void updateEEPROM(){

    EEPROMManager.setHighScore(0, score[0].playerName, score[0].playerScore);
    EEPROMManager.setHighScore(1, score[1].playerName, score[1].playerScore);
    EEPROMManager.setHighScore(2, score[2].playerName, score[2].playerScore);
  }

  void orderScore(int index){

    if(isEqual(index, 0)){
      return;
    }

    if(isGreater(score[index].playerScore, score[index - 1].playerScore)){

      Score temp;
      Set(temp, score[index - 1]);
      Set(score[index - 1], score[index]);
      Set(score[index], temp);

      orderScore(index - 1);
    }
  }

public:

  HighScores(){ // CONSTRUCTOR

    Set(score[0].playerName, EEPROMManager.getHighScoreName(0));
    Set(score[1].playerName, EEPROMManager.getHighScoreName(1));
    Set(score[2].playerName, EEPROMManager.getHighScoreName(2));
    
    Set(score[0].playerScore, EEPROMManager.getHighScoreScore(0));
    Set(score[1].playerScore, EEPROMManager.getHighScoreScore(1));
    Set(score[2].playerScore, EEPROMManager.getHighScoreScore(2));
  }
  
  void update(Score newScore){  // struct Score{ String playerName; byte playerScore; // max opponents defeated. Could be 1, 2 or 3 !

    if(isGreater(newScore.playerScore, score[2].playerScore)){
      
      Set(score[2].playerName, newScore.playerName);
      Set(score[2].playerScore, newScore.playerScore);
      
      orderScore(2);
      updateEEPROM();
    }
  }

  String castScore(int index){

    String result = "";

    for(int i = 0; i < 8; i++){
      result += score[index].playerName[i];
    }
    result += ".. vs ";
    result += String(score[index].playerScore);

    return result;
  }
  
}HighScores;


static class SpawnPoints{

private:

  byte spawnPoint[4]; // 0 - "--", 1 - "P1", 2 - "P2", 3 - "AI".

  bool isAvailable(String value){

    for(int i = 0; i < 4; i++){
      if(isEqual(expressPoint(i), value)){
        
        return false;
      }
    }
    
    return true;
  }
  
public:

  SpawnPoints(){

    EEPROMManager.loadSpawnConfig(spawnPoint[0], spawnPoint[1], spawnPoint[2], spawnPoint[3]);
  }

  void saveSpawnPoints(){
    EEPROMManager.saveSpawnConfig(spawnPoint[0], spawnPoint[1], spawnPoint[2], spawnPoint[3]);
  }

  void setPoint(int index, String value){

    if(isEqual(value, String("P1"))){
      
      Set(spawnPoint[index], byte(1));
      
    }else if(isEqual(value, String("P2"))){
      
      Set(spawnPoint[index], byte(2));

    }else if(isEqual(value, String("AI"))){
      
      Set(spawnPoint[index], byte(3));

    }else{
      
      Set(spawnPoint[index], byte(0));
    }
  }

  void changePoint(int index){

    // P1 -> P2 -> AI -> --
    switch(spawnPoint[index]){
      case 0: // --
        if(isAvailable("P1")){
          setPoint(index, "P1");
        }else if(isAvailable("P2")){
          setPoint(index, "P2");
        }else{
          setPoint(index, "AI");
        }
        break;
      case 1: // P1
        if(isAvailable("P2")){
          setPoint(index, "P2");
        }else{
          setPoint(index, "AI");
        }
        break;
      case 2: // P2
        setPoint(index, "AI");
        break;
      case 3: // AI
        setPoint(index, "--");
        break;
    }
  }

  byte getPoint(int index){

    return spawnPoint[index];
  }

  String expressPoint(int index){

    switch(spawnPoint[index]){
      case 1:
        return "P1";
      case 2:
        return "P2";
      case 3:
        return "AI";
      default:
        return "--";
    }
  }

}SpawnPoints;


static class BombermanGame{

private:

  unsigned long messageDisplayTime = 5000;

  Player P1 = Player(&Assets.player1);
  Player P2 = Player(&Assets.player2);
  Player AI1 = Player(&Assets.bot);
  Player AI2 = Player(&Assets.bot);
  Player AI3 = Player(&Assets.bot);
  Player AI4 = Player(&Assets.bot);

  String padOption(String option, bool selected){
    
    if(selected){

      return "[" + option + "]";
    }
    
    return " " + option + " ";
  }

  void launcherMenuSetup(Menu &menu, int horizontalOption){
    
    String back = String(char(127));
    back += "BACK";
    
    menu.setOption(0, padOption(SpawnPoints.expressPoint(0), (isEqual(horizontalOption, 0) && isEqual(menu.getSelected(), 0)))
                      + padOption("START", (isEqual(horizontalOption, 1) && isEqual(menu.getSelected(), 0)))
                      + padOption(SpawnPoints.expressPoint(1), (isEqual(horizontalOption, 2) && isEqual(menu.getSelected(), 0))));
    menu.setOption(1, padOption(SpawnPoints.expressPoint(2), (isEqual(horizontalOption, 0) && isEqual(menu.getSelected(), 1)))
                      + padOption(back, (isEqual(horizontalOption, 1) && isEqual(menu.getSelected(), 1)))
                      + padOption(SpawnPoints.expressPoint(3), (isEqual(horizontalOption, 2) && isEqual(menu.getSelected(), 1))));
  }

  void computeSafety(){

    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){

        if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.wall) ||
           isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.destructible)){

          (MatrixManager.getPosition(row, col)).setSafety(1); // 0 - deadly, 1 - danger, 2 - safe
        }else if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.flame)){

          (MatrixManager.getPosition(row, col)).setSafety(0); // 0 - deadly, 1 - danger, 2 - safe
        }else{

          (MatrixManager.getPosition(row, col)).setSafety(2); // 0 - deadly, 1 - danger, 2 - safe
        }
        
      }
    }
    
    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){

        // cannot do this in the same "double-loop" because "explode(...)" goes up, down, left, right,
        // and the next row iteration will overwrite the work of the virtualized explode function
        if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.bomb)){
          
          // explode(int row, int col, bool virtualize = false){...}
          explode(row, col, true);  // virtualize = true <=> don't actually explode, just mark dangerous positions.
        }
        
      }
    }
    
  }

  void AIExplore(Player &bot, bool onlyToSafety = false){

    byte leftSafety = 0; // 0 - forbidden (as if it's deadly)
    byte rightSafety = 0;
    byte aboveSafety = 0;
    byte belowSafety = 0;

    if(isGreater(bot.getHPos(), byte(0))){

      leftSafety = (MatrixManager.getPosition(bot.getVPos(), bot.getHPos() - 1)).getSafety();
    }

    if(isLesser(bot.getHPos(), byte(7))){

      rightSafety = (MatrixManager.getPosition(bot.getVPos(), bot.getHPos() + 1)).getSafety();
    }

    if(isGreater(bot.getVPos(), byte(0))){

      aboveSafety = (MatrixManager.getPosition(bot.getVPos() - 1, bot.getHPos())).getSafety();
    }

    if(isLesser(bot.getVPos(), byte(7))){

      belowSafety = (MatrixManager.getPosition(bot.getVPos() + 1, bot.getHPos() - 1)).getSafety();
    }

    byte safeMoves = 0;

    if(isEqual(leftSafety, byte(2))){safeMoves++;}
    if(isEqual(rightSafety, byte(2))){safeMoves++;}
    if(isEqual(aboveSafety, byte(2))){safeMoves++;}
    if(isEqual(belowSafety, byte(2))){safeMoves++;}

    if(isEqual(safeMoves, byte(0))){  // There are NO safe moves

      if(onlyToSafety){
        
        return;
      }

      switch(random() % 4){
        case 0:
          if(isEqual(leftSafety, byte(1))){ // 1 - dangerous, but not deadly !
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(1))){
            bot.goUp();
          }else if(isEqual(rightSafety, byte(1))){
            bot.goRight();
          }else if(isEqual(belowSafety, byte(1))){
            bot.goDown();
          }
          return;
        case 1:
          if(isEqual(aboveSafety, byte(1))){  // 1 - dangerous, but not deadly !
            bot.goUp();
          }else if(isEqual(rightSafety, byte(1))){
            bot.goRight();
          }else if(isEqual(belowSafety, byte(1))){
            bot.goDown();
          }else if(isEqual(leftSafety, byte(1))){
            bot.goLeft();
          }
          return;
        case 2:
          if(isEqual(rightSafety, byte(1))){  // 1 - dangerous, but not deadly !
            bot.goRight();
          }else if(isEqual(belowSafety, byte(1))){
            bot.goDown();
          }else if(isEqual(leftSafety, byte(1))){
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(1))){
            bot.goUp();
          }
          return;
        default:
          if(isEqual(belowSafety, byte(1))){ // 1 - dangerous, but not deadly !
            bot.goDown();
          }else if(isEqual(leftSafety, byte(1))){
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(1))){
            bot.goUp();
          }else if(isEqual(rightSafety, byte(1))){
            bot.goRight();
          }
          return;
      }
    }else{

      switch(random() % 4){
        case 0:
          if(isEqual(leftSafety, byte(2))){ // 2 - safe
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(2))){
            bot.goUp();
          }else if(isEqual(rightSafety, byte(2))){
            bot.goRight();
          }else if(isEqual(belowSafety, byte(2))){
            bot.goDown();
          }
          return;
        case 1:
          if(isEqual(aboveSafety, byte(2))){  // 2 - safe
            bot.goUp();
          }else if(isEqual(rightSafety, byte(2))){
            bot.goRight();
          }else if(isEqual(belowSafety, byte(2))){
            bot.goDown();
          }else if(isEqual(leftSafety, byte(2))){
            bot.goLeft();
          }
          return;
        case 2:
          if(isEqual(rightSafety, byte(2))){  // 2 - safe
            bot.goRight();
          }else if(isEqual(belowSafety, byte(2))){
            bot.goDown();
          }else if(isEqual(leftSafety, byte(2))){
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(2))){
            bot.goUp();
          }
          return;
        default:
          if(isEqual(belowSafety, byte(2))){ // 2 - safe
            bot.goDown();
          }else if(isEqual(leftSafety, byte(2))){
            bot.goLeft();
          }else if(isEqual(aboveSafety, byte(2))){
            bot.goUp();
          }else if(isEqual(rightSafety, byte(2))){
            bot.goRight();
          }
          return;
      }
    }
    
  }

  int AIBombingChance(byte vPos, byte hPos){

    // chance to drop bomb = 5 * (safeCorners + 1) * (1 + nearbyPlayers);
    // 25% chance in open space, if all corners are safe (it has where to go)
    // 50% chance near destructible, if all corners are safe
    // 100% chance if surounded by 3 players and a destructible, and also all corners are safe.
    
    byte safeCorners = 0;
    bool nearDestructible = false;
    byte nearbyPlayers = 0;

    // check if nearDestructible:
    if(isGreater(hPos, byte(0)) && isEqual((MatrixManager.getPosition(vPos, hPos - 1)).getObject(), &Assets.destructible)){

      Set(nearDestructible, true);
    }

    if(isLesser(hPos, byte(7)) && isEqual((MatrixManager.getPosition(vPos, hPos + 1)).getObject(), &Assets.destructible)){

      Set(nearDestructible, true);
    }

    if(isGreater(vPos, byte(0)) && isEqual((MatrixManager.getPosition(vPos - 1, hPos)).getObject(), &Assets.destructible)){

      Set(nearDestructible, true);
    }

    if(isLesser(vPos, byte(7)) && isEqual((MatrixManager.getPosition(vPos + 1, hPos)).getObject(), &Assets.destructible)){

      Set(nearDestructible, true);
    }

    // counting safeCorners:
    if(isGreater(hPos, byte(0))){

      if(isGreater(vPos, byte(0))){
        
        if(isEqual((MatrixManager.getPosition(vPos - 1, hPos - 1)).getSafety(), byte(2))){
          safeCorners++;
        }
      }
      
      if(isLesser(vPos, byte(7))){
        
        if(isEqual((MatrixManager.getPosition(vPos + 1, hPos - 1)).getSafety(), byte(2))){
          safeCorners++;
        }
      }
    }
    
    if(isLesser(hPos, byte(7))){

      if(isGreater(vPos, byte(0))){
        
        if(isEqual((MatrixManager.getPosition(vPos - 1, hPos + 1)).getSafety(), byte(2))){
          safeCorners++;
        }
      }
      
      if(isLesser(vPos, byte(7))){
        
        if(isEqual((MatrixManager.getPosition(vPos + 1, hPos + 1)).getSafety(), byte(2))){
          safeCorners++;
        }
      }
    }

    // counting nearbyPlayers:
    if(P1.isAlive() && P1.isNear(vPos, hPos)){nearbyPlayers++;}
    if(P2.isAlive() && P2.isNear(vPos, hPos)){nearbyPlayers++;}
    if(AI1.isAlive() && AI1.isNear(vPos, hPos)){nearbyPlayers++;}
    if(AI2.isAlive() && AI2.isNear(vPos, hPos)){nearbyPlayers++;}
    if(AI3.isAlive() && AI3.isNear(vPos, hPos)){nearbyPlayers++;}
    if(AI4.isAlive() && AI4.isNear(vPos, hPos)){nearbyPlayers++;}
    if(nearDestructible){nearbyPlayers++;}
    
    return (5 * (safeCorners + 1) * (1 + nearbyPlayers));
    
  }
  
  void AIControl(Player &bot){
    // Bots should NOT be perfect ! (would make the game frustrating). But, they sould provide a decent challange
    // I designed what I consider a resonable behaviour.
    
    if(bot.isSleeping()){

      return;
    }
      
    switch((MatrixManager.getPosition(bot.getVPos(), bot.getHPos())).getSafety()){
      case 1: // in danger
        AIExplore(bot);
        break;
      case 2: // safe
        if(isLesser(int(random() % 100), AIBombingChance(bot.getVPos(), bot.getHPos()))){
          
          bot.placeBomb();
        }else if(isLesser(int(random() % 100), 30)){ // 30% chance to rest 0,5 sec

          bot.sleep();
        }else{  // 70% chance to move, if safe position nearby

          AIExplore(bot, true); // true - move only to safety
        }
        break;
    }
    
  }

  bool ignite(int row, int col, bool virtualize){ // returns: true (ignited successfully) / false (cannot be ignited)
    
    if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.wall)){ // if(object == wall)

      return false;
    }

    if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.destructible)){ // if(object == destructible)

      if(!virtualize){
        
        // destroy destructible with 10% chance to spawn item
        switch(random() % 10){
          case 0:
            MatrixManager.placeObject(&Assets.item, row, col);
            break;
          default:
            MatrixManager.placeObject(&Assets.nothing, row, col);
            break;
        }
      }
      
      return false;
    }

    if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.bomb) ||
       isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.overlap)){ // if(object == bomb || object == overlap)

      if(!virtualize){
        explode(row, col);
      }
      // the new explosion will cover more than the rest of the path anyway.
      return false; // so there is no need to continue computing this one.
    }

    // The remaining possible objects are: nothing, item, flame, a player or a bot, a movement animation.
    if(virtualize){
      
      if(isEqual((MatrixManager.getPosition(row, col)).getSafety(), byte(2))){
        
        (MatrixManager.getPosition(row, col)).setSafety(1);
      }
    }else{
      MatrixManager.placeObject(&Assets.flame, row, col);
      (MatrixManager.getPosition(row, col)).setSafety(0);
    }
    
    return true;
  }
  
  void explode(int row, int col, bool virtualize = false){ // virtualize - used to "computeRatings()" for AI decisions
    
    if(virtualize){ 

      if(isEqual((MatrixManager.getPosition(row, col)).getSafety(), byte(2))){
        
        (MatrixManager.getPosition(row, col)).setSafety(1); // 0 - deadly, 1 - dangerous (in range), 2 - safe
      }
    }else{

      SoundSystem.addSound(&Playlist.bombExplodeEffect); // SoundSystem automatically remove finished sounds in update method.
      MatrixManager.placeObject(&Assets.flame, row, col);
      (MatrixManager.getPosition(row, col)).setSafety(0);
    }

    bool noRoadBlock;
    
    // extend flame (or virtual flame) uppward
    if(isGreater(row, 0)){

      Set(noRoadBlock, ignite(row - 1, col, virtualize));
      if(noRoadBlock && isGreater(row - 1, 0)){

        ignite(row - 2, col, virtualize);
      }
    }

    // extend flame (or virtual flame) downward
    if(isLesser(row, 7)){

      Set(noRoadBlock, ignite(row + 1, col, virtualize));
      if(noRoadBlock && isLesser(row + 1, 7)){

        ignite(row + 2, col, virtualize);
      }
    }
    
    // extend flame (or virtual flame) to the left
    if(isGreater(col, 0)){

      Set(noRoadBlock, ignite(row, col - 1, virtualize));
      if(noRoadBlock && isGreater(col - 1, 0)){

        ignite(row, col - 2, virtualize);
      }
    }

    // extend flame (or virtual flame) to the right
    if(isLesser(col, 7)){

      Set(noRoadBlock, ignite(row, col + 1, virtualize));
      if(noRoadBlock && isLesser(col + 1, 7)){

        ignite(row, col + 2, virtualize);
      }
    }
    
  }

  void gameplayUpdate(){
    
    handleEvents(); // Inputs and AI decisions
    
    if(P1.isAlive()){P1.update();}
    if(P2.isAlive()){P2.update();}
    if(AI1.isAlive()){AI1.update();}
    if(AI2.isAlive()){AI2.update();}
    if(AI3.isAlive()){AI3.update();}
    if(AI4.isAlive()){AI4.update();}

    // Exploding bombs and cleaning up the waste:
    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){

        if((MatrixManager.getPosition(row, col)).isExpired()){
          
          // exploding bombs:
          if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.bomb)){
  
            explode(row, col);

          // cleaning up the waste:
          }else if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.flame) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.leftMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.rightMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.upMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.downMoveStart)){

            MatrixManager.placeObject(&Assets.nothing, row, col);
          }
        }
        
      }
    }

    computeSafety();
    
  }

  int leftAlive(){

    int alivePlayers = 0;

    if(P1.isAlive()){alivePlayers++;}
    if(P2.isAlive()){alivePlayers++;}
    if(AI1.isAlive()){alivePlayers++;}
    if(AI2.isAlive()){alivePlayers++;}
    if(AI3.isAlive()){alivePlayers++;}
    if(AI4.isAlive()){alivePlayers++;}

    return alivePlayers;
  }

  bool isGameOver(){

    if(isLesser(leftAlive(), 2)){

      return true;
    }
    
    return false;
  }

  void gameOutcome(){

    switch(leftAlive()){
      case 0:
        Device.printMessage("The game is", "a draw !", messageDisplayTime);
        return;
      case 1:
        if(P1.isAlive()){
          Device.printMessage("Player 1", "wins the game !", messageDisplayTime);
        }
        if(P2.isAlive()){
          Device.printMessage("Player 2", "wins the game !", messageDisplayTime);
        }
        if(AI1.isAlive() || AI2.isAlive() || AI3.isAlive() || AI4.isAlive()){
          Device.printMessage("AI", "wins the game !", messageDisplayTime);
        }
        return;
      default:
        return;
    }
  }

  bool pauseMenu(){ // returns true if exit game requested

    Menu menu(2);
    menu.setOption(0, "Resume");
    menu.setOption(1, "Exit");
    menu.refresh();
    
    while(true){
      
      SoundSystem.update();
      InputManager.update();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -1:  // no action -> nothing to do..
          break;
        case 0:
          return false;
        case 1:
          if(confirmation()){
            return true;
          }
          menu.refresh();
          break;
      }
    }
  }

  bool confirmation(){

    bool selected = false;
    bool prevSelected = true;

    bool soundEffects;
    if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){

      Set(soundEffects, true);
    }else{
      
      Set(soundEffects, false);
    }

    while(true){

      if(isNotEqual(selected, prevSelected)){

        if(selected){
          Device.printMessage(" Are you sure ?", " [Yes]      No  ");
        }else{
          Device.printMessage(" Are you sure ?", "  Yes      [No] ");
        }
        
        Set(prevSelected, selected);
      }
      
      SoundSystem.update();
      InputManager.update();

      MenuInputs.savePrevious();
      MenuInputs.load();

      // Click
      if(isEqual(MenuInputs.prevBtnValue, false) && isEqual(MenuInputs.btnValue, true)){
        
        return selected;
      }

      // Left signal
      if(isEqual(MenuInputs.prevYAxisValue, 0) && isLesser(MenuInputs.yAxisValue, 0)){
        
        if(soundEffects){
          if(selected){
            SoundSystem.addSound(&Playlist.menuEndEffect);
          }else{
            SoundSystem.addSound(&Playlist.menuNavEffect);
          }
        }
        
        Set(selected, true);
        
      }
      
      // Right signal
      if(isEqual(MenuInputs.prevYAxisValue, 0) && isGreater(MenuInputs.yAxisValue, 0)){
        
        if(soundEffects){
          if(selected){
            SoundSystem.addSound(&Playlist.menuNavEffect);
          }else{
            SoundSystem.addSound(&Playlist.menuEndEffect);
          }
        }
        
        Set(selected, false);
      }
    }
  }

  void spawnPlayers(){
    
    switch(SpawnPoints.getPoint(0)){  // case 0: nothing to spawn !
      case 1:
        P1.spawn(1, 1);
        break;
      case 2:
        P2.spawn(1, 1);
        break;
      case 3:
        AI1.spawn(1, 1);
        break;
      default:
        break;
    }
    
    switch(SpawnPoints.getPoint(1)){  // case 0: nothing to spawn !
      case 1:
        P1.spawn(1, 6);
        break;
      case 2:
        P2.spawn(1, 6);
        break;
      case 3:
        AI2.spawn(1, 6);
        break;
      default:
        break;
    }
    
    switch(SpawnPoints.getPoint(2)){  // case 0: nothing to spawn !
      case 1:
        P1.spawn(6, 1);
        break;
      case 2:
        P2.spawn(6, 1);
        break;
      case 3:
        AI3.spawn(6, 1);
        break;
      default:
        break;
    }
    
    switch(SpawnPoints.getPoint(3)){  // case 0: nothing to spawn !
      case 1:
        P1.spawn(6, 6);
        break;
      case 2:
        P2.spawn(6, 6);
        break;
      case 3:
        AI4.spawn(6, 6);
        break;
      default:
        break;
    }
  }

  void handleEvents(){

    // Player 1
    if(P1.isAlive() && !P1.isMoving()){
      
      if(isEqual(GeneralInputs.prevLeftBtnValue, false) && isEqual(GeneralInputs.leftBtnValue, true)){
        P1.placeBomb();
      }
      
      if(isEqual(GeneralInputs.prevLeftYAxisValue, 0) && isLesser(GeneralInputs.leftYAxisValue, 0)){
        P1.goLeft();
      }
      
      if(isEqual(GeneralInputs.prevLeftYAxisValue, 0) && isGreater(GeneralInputs.leftYAxisValue, 0)){
        P1.goRight();
      }
      
      if(isEqual(GeneralInputs.prevLeftXAxisValue, 0) && isLesser(GeneralInputs.leftXAxisValue, 0)){
        P1.goUp();
      }
      
      if(isEqual(GeneralInputs.prevLeftXAxisValue, 0) && isGreater(GeneralInputs.leftXAxisValue, 0)){
        P1.goDown();
      }
    }
    
    // Player 2
    if(P2.isAlive() && !P2.isMoving()){
      
      if(isEqual(GeneralInputs.prevRightBtnValue, false) && isEqual(GeneralInputs.rightBtnValue, true)){
        P2.placeBomb();
      }
      
      if(isEqual(GeneralInputs.prevRightYAxisValue, 0) && isLesser(GeneralInputs.rightYAxisValue, 0)){
        P2.goLeft();
      }
      
      if(isEqual(GeneralInputs.prevRightYAxisValue, 0) && isGreater(GeneralInputs.rightYAxisValue, 0)){
        P2.goRight();
      }
      
      if(isEqual(GeneralInputs.prevRightXAxisValue, 0) && isLesser(GeneralInputs.rightXAxisValue, 0)){
        P2.goUp();
      }
      
      if(isEqual(GeneralInputs.prevRightXAxisValue, 0) && isGreater(GeneralInputs.rightXAxisValue, 0)){
        P2.goDown();
      }
    }
    
    // AIs
    if(AI1.isAlive() && !AI1.isMoving()){
      AIControl(AI1);
    }
    
    if(AI2.isAlive() && !AI2.isMoving()){
      AIControl(AI2);
    }
    
    if(AI3.isAlive() && !AI3.isMoving()){
      AIControl(AI3);
    }
    
    if(AI4.isAlive() && !AI4.isMoving()){
      AIControl(AI4);
    }
  }

  String organizePlayerInfo(int playerNr, byte nrOfBombs, byte carryCapacity, String playerState){

    String result = "";

    switch(playerNr){
      case 1:
        if(!P1.isAlive()){
          
          return result;
        }
        result += "P1 - ";
        break;
      default:
        if(!P2.isAlive()){
          
          return result;
        }
        result += "P2 - ";
        break;
    }
    
    result += String(nrOfBombs);
    result += "/";
    result += String(carryCapacity);
    result += " ";
    result += playerState;

    return result;
    
  }
  
public:
  
  void launcher(){

    randomSeed(millis());
    Level.loadCurrent();

    int horizontalOption = 0;
    
    Menu menu(2);
    launcherMenuSetup(menu, horizontalOption);
    menu.refresh();

    bool soundEffects;
    if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){

      Set(soundEffects, true);
    }else{
      
      Set(soundEffects, false);
    }
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -2:  // down
          launcherMenuSetup(menu, horizontalOption);
          menu.refresh();
          break;
        case -3:  // up
          launcherMenuSetup(menu, horizontalOption);
          menu.refresh();
          break;
        case -4:  // left
          if(isGreater(horizontalOption, 0)){
            horizontalOption--;
            launcherMenuSetup(menu, horizontalOption);
            if(soundEffects){
              SoundSystem.addSound(&Playlist.menuNavEffect);
            }
            menu.refresh();
          }else if(soundEffects){
            SoundSystem.addSound(&Playlist.menuEndEffect);
          }
          break;
        case -5:  // right
          if(isLesser(horizontalOption, 2)){
            horizontalOption++;
            launcherMenuSetup(menu, horizontalOption);
            if(soundEffects){
              SoundSystem.addSound(&Playlist.menuNavEffect);
            }
            menu.refresh();
          }else if(soundEffects){
            SoundSystem.addSound(&Playlist.menuEndEffect);
          }
          break;
        case 0:
          //  S0 __START__S1_ (S0, S1 - Spawn Points)
          switch(horizontalOption){
            case 0: // S0
              SpawnPoints.changePoint(0);
              launcherMenuSetup(menu, horizontalOption);
              menu.refresh();
              break;
            case 1: // START
              MenuManager.stopMusic();
              startGame();
              menu.refresh();
              Level.loadCurrent();
              if(isEqual(MenuManager.getAudioOption(), byte(1)) || isEqual(MenuManager.getAudioOption(), byte(3))){

                MenuManager.beginMusic();
              }
              break;
            case 2: // S1
              SpawnPoints.changePoint(1);
              launcherMenuSetup(menu, horizontalOption);
              menu.refresh();
              break;
          }
          break;
        case 1:
          //  S2 __<BACK__S3_ (S2, S3 - Spawn Points)
          switch(horizontalOption){
            case 0: // S2
              SpawnPoints.changePoint(2);
              launcherMenuSetup(menu, horizontalOption);
              menu.refresh();
              break;
            case 1: // BACK
              // cleanup the display
              MatrixManager.lightsOff();
              return;
            case 2: // S3
              SpawnPoints.changePoint(3);
              launcherMenuSetup(menu, horizontalOption);
              menu.refresh();
              break;
          }
          break;
        default:  // no action -> nothing to do..
          break;
      }
    }
  }

  void startGame(){

    P1.initialize();
    P2.initialize();
    AI1.initialize();
    AI2.initialize();
    AI3.initialize();
    AI4.initialize();
    
    spawnPlayers();

    // checking initial conditions
    if(isGameOver()){

      Device.printMessage("Add some", "opponents !", messageDisplayTime);
      return;
    }

    SpawnPoints.saveSpawnPoints();  // saves last played configuration in EEPROM.

    String prevInfoPlayer1 = "";
    String prevInfoPlayer2 = "";
    String infoPlayer1 = "";
    String infoPlayer2 = "";

    byte nrOfOpponents = 0;  // need this for highscore
    
    if(P1.isAlive() || P2.isAlive()){

      Set(nrOfOpponents, byte(leftAlive() - 1));
    }

    bool oneHuman = false;
    
    if(isNotEqual(P1.isAlive(), P2.isAlive())){
      
      Set(oneHuman, true);  // If one (and only one) player spawns, score counts !
    }
    
    // MenuInputs.load() is allready done from previous menues !
    GeneralInputs.load();
    
    while(true){

      Device.updateAll();
      
      MenuInputs.savePrevious();
      MenuInputs.load();

      GeneralInputs.savePrevious();
      GeneralInputs.load();
      
      gameplayUpdate();
      
      // pause menu:
      if(isEqual(MenuInputs.prevSWValue, false) && isEqual(MenuInputs.SWValue, true)){  // enter pause menu
        
        if(pauseMenu()){  // returns bool: true (exit), false (continue)
          return;
        }

        prevInfoPlayer1 = "";
        prevInfoPlayer2 = ""; // to refresh LCD !
      }

      // in-game info:
      if(P1.isAlive() || P2.isAlive()){
        
        Set(infoPlayer1, organizePlayerInfo(1, P1.nrOfBombs(), P1.capacity(), P1.expressState()));
        Set(infoPlayer2, organizePlayerInfo(2, P2.nrOfBombs(), P2.capacity(), P2.expressState()));
        
        if(isNotEqual(infoPlayer1, prevInfoPlayer1) || isNotEqual(infoPlayer2, prevInfoPlayer2)){
          
          Device.printMessage(infoPlayer1, infoPlayer2);
          
          Set(prevInfoPlayer1, infoPlayer1);
          Set(prevInfoPlayer2, infoPlayer2);
        }
      }

      if(isGameOver()){

        // declare winner:
        gameOutcome();

        // update highscores
        if(oneHuman && (P1.isAlive() || P2.isAlive())){
          
          HighScores.update(Score(Device.formatName(Device.getOwner()), nrOfOpponents));
        }
        
        return;
      }
    }
    
  }

}BombermanGame;


static struct BombermanMenu{

  unsigned long messageDisplayTime = 1000;
  
  void launcher(){

    Menu menu(4);
    menu.setOption(0, "Play");
    menu.setOption(1, "Change Level");
    menu.setOption(2, "High Scores");
    menu.setOption(3, "Back");
    menu.refresh();

    int prevSelected = -1;  // need to be different than selectedOption first time.
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -1:  // no action -> nothing to do..
          break;
        case 0:
          BombermanGame.launcher();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          changeLevel();
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          highScores();
          menu.refresh();
          prevSelected = -1;
          break;
        case 3:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.playGame);
            break;
          case 1:
            MatrixManager.displayIcon(-1, Level.levelIcon(Level.getCurrentLevelIndex()));
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.score);
            break;
          case 3:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void changeLevel(){

    Menu menu(14);
    menu.setOption(0, "Forest 1");
    menu.setOption(1, "Forest 2");
    menu.setOption(2, "Forest 3");
    menu.setOption(3, "Forest 4");
    menu.setOption(4, "Maze 1");
    menu.setOption(5, "Maze 2");
    menu.setOption(6, "Maze 3");
    menu.setOption(7, "Maze 4");
    menu.setOption(8, "Crates 1");
    menu.setOption(9, "Crates 2");
    menu.setOption(10, "Village 1");
    menu.setOption(11, "Village 2");
    menu.setOption(12, "Generate Random");
    menu.setOption(13, "Back");
    menu.refresh();

    int prevSelected = -1;  // need to be different than selectedOption first time.
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -1:  // no action -> nothing to do..
          break;
        case 0:
          Level.setLevel(Level.Index.forest1);
          Device.printMessage("Level: Forest 1", "Selected !", messageDisplayTime);
          return;
        case 1:
          Level.setLevel(Level.Index.forest2);
          Device.printMessage("Level: Forest 2", "Selected !", messageDisplayTime);
          return;
        case 2:
          Level.setLevel(Level.Index.forest3);
          Device.printMessage("Level: Forest 3", "Selected !", messageDisplayTime);
          return;
        case 3:
          Level.setLevel(Level.Index.forest4);
          Device.printMessage("Level: Forest 4", "Selected !", messageDisplayTime);
          return;
        case 4:
          Level.setLevel(Level.Index.maze1);
          Device.printMessage("Level: Maze 1", "Selected !", messageDisplayTime);
          return;
        case 5:
          Level.setLevel(Level.Index.maze2);
          Device.printMessage("Level: Maze 2", "Selected !", messageDisplayTime);
          return;
        case 6:
          Level.setLevel(Level.Index.maze3);
          Device.printMessage("Level: Maze 3", "Selected !", messageDisplayTime);
          return;
        case 7:
          Level.setLevel(Level.Index.maze4);
          Device.printMessage("Level: Maze 4", "Selected !", messageDisplayTime);
          return;
        case 8:
          Level.setLevel(Level.Index.crates1);
          Device.printMessage("Level: Crates 1", "Selected !", messageDisplayTime);
          return;
        case 9:
          Level.setLevel(Level.Index.crates2);
          Device.printMessage("Level: Crates 2", "Selected !", messageDisplayTime);
          return;
        case 10:
          Level.setLevel(Level.Index.village1);
          Device.printMessage("Level: Village 1", "Selected !", messageDisplayTime);
          return;
        case 11:
          Level.setLevel(Level.Index.village2);
          Device.printMessage("Level: Village 2", "Selected !", messageDisplayTime);
          return;
        case 12:
          Level.setLevel(Level.Index.generateRandom);
          Device.printMessage("Level: Random", "Selected !", messageDisplayTime);
          return;
        case 13:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          default:
            MatrixManager.displayIcon(-1, Level.levelIcon(menu.getSelected()));
            break;
          case 13:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void highScores(){

    Menu menu(3);
    menu.setOption(0, Device.formatName(HighScores.castScore(0)));
    menu.setOption(1, Device.formatName(HighScores.castScore(1)));
    menu.setOption(2, Device.formatName(HighScores.castScore(2)));
    menu.refresh();
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -1:  // no action -> nothing to do..
          break;
        case 0:
          return;
        case 1:
          return;
        case 2:
          return;
      }
    }
  }

}BombermanMenu;


#endif /// BOMBERMAN_H_INCLUDED
