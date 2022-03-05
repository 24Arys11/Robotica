#ifndef MATRIXMANAGER_H_INCLUDED
#define MATRIXMANAGER_H_INCLUDED

#include "LedControl.h" //  for 8*8 Led Matrices
LedControl lc = LedControl(5, 2, 4, 4); // DIN, CLK, LOAD(CS), No. Driver


class Frame{

private:

  bool led[4];

public:

  bool getLed(int index){
    return led[index];
  }

  void setLed(int index, bool value){
    Set(led[index], value);
  }

};


class Object{

private:

  byte nrOfFrames;
  Frame *frames;
  unsigned int frameDuration;
  byte timeoutFrames;
  bool colision;
  Sound* frameAudio; // a sound to be played every frame.

public:

  Object(byte nrOfFrames, unsigned int frameDuration, byte timeoutFrames = 0){

    Set(this->nrOfFrames, nrOfFrames);
    frames = new Frame[nrOfFrames];
    Set(this->frameDuration, frameDuration);
    Set(colision, false);
    Set(this->timeoutFrames, timeoutFrames);

    frameAudio = NULL;
    
  }

  ~Object(){
    delete[] frames;
  }

  void setFrame(int frameNr, bool led0, bool led1, bool led2, bool led3){

    frames[frameNr].setLed(0, led0);
    frames[frameNr].setLed(1, led1);
    frames[frameNr].setLed(2, led2);
    frames[frameNr].setLed(3, led3);
  }

  bool frameLedVal(int frameNr, int ledNr){
    return frames[frameNr].getLed(ledNr);
  }

  byte noFrames(){
    return nrOfFrames;
  }

  unsigned int frameLength(){
    return frameDuration;
  }

  byte timeoutFrame(){
    return timeoutFrames;
  }

  void setColision(bool colision){
    Set(this->colision, colision);
  }
  
  bool hasColision(){
    return colision;
  }

  bool haslimitedLifetime(){

    if(isEqual(timeoutFrames, byte(0))){
      return false;
    }
    return true;
  }

  void setFrameAudio(Sound* frameAudio){

    this->frameAudio = frameAudio;
  }
  
  Sound* getFrameAudio(){

    return frameAudio;
  }
  
};


struct Icon{

  byte row0;
  byte row1;
  byte row2;
  byte row3;
  byte row4;
  byte row5;
  byte row6;
  byte row7;

  Icon(char *row0, char *row1, char *row2, char *row3, char *row4, char *row5, char *row6, char *row7){

    this->row0 = Math.toByte(row0);
    this->row1 = Math.toByte(row1);
    this->row2 = Math.toByte(row2);
    this->row3 = Math.toByte(row3);
    this->row4 = Math.toByte(row4);
    this->row5 = Math.toByte(row5);
    this->row6 = Math.toByte(row6);
    this->row7 = Math.toByte(row7);
  }
  
};


class Position{

private:

  byte dysplay;
  byte led[4][2];     // A location has 4 dots. each has 2 parameters: coordonate x, coordonate y
  unsigned long nextIntervention;
  byte safety;        // safety = 0 => triggers death ! Other values matters for AI decisions.
  Object *obj;        // It holds the code for the object at that location.
  byte currentFrame;
  byte totalFrames;
  bool expired;       // Some objects only have a limited lifetime.
  
public:

  Position(){

    Set(dysplay, byte(0));
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 2; j++){
        Set(led[i][j], byte(0));
      }
    }
    Set(nextIntervention, (unsigned long)(-1));
    Set(safety, byte(1));
    Set(currentFrame, byte(255)); // On the next update it becomes 0 !
    Set(totalFrames, byte(0));
    Set(expired, false);
  }

  void setDysplay(byte dysplayNr){
    Set(dysplay, dysplayNr);
  }

  void setSafety(byte safety){
    Set(this->safety, safety);
  }

  byte getSafety(){
    return safety;
  }

  void ledConfig(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte x3, byte y3){ // coord x and y for each led !
    
    Set(led[0][0], x0);
    Set(led[0][1], y0);
    Set(led[1][0], x1);
    Set(led[1][1], y1);
    Set(led[2][0], x2);
    Set(led[2][1], y2);
    Set(led[3][0], x3);
    Set(led[3][1], y3);
    
  }

  void lightLeds(bool val1, bool val2, bool val3, bool val4){

    lc.setLed(dysplay, led[0][0], led[0][1], val1);
    lc.setLed(dysplay, led[1][0], led[1][1], val2);
    lc.setLed(dysplay, led[2][0], led[2][1], val3);
    lc.setLed(dysplay, led[3][0], led[3][1], val4);
  }
  
  bool needAttention(){

    if(isLesser(millis(), nextIntervention) || isNull(obj)){
      return false;
    }
    return true;
  }

  void update(){

    currentFrame++;
    if(isGreaterOrEqual(currentFrame, obj->noFrames())){
      Set(currentFrame, byte(0));
    }

    if(obj->haslimitedLifetime() && isGreater(totalFrames, byte(obj->timeoutFrame() - 1))){
      Set(expired, true);
      takeABreak();
      return;
    }

    lightLeds(obj->frameLedVal(currentFrame, 0), obj->frameLedVal(currentFrame, 1),
              obj->frameLedVal(currentFrame, 2), obj->frameLedVal(currentFrame, 3));

    Set(nextIntervention, millis() + obj->frameLength());
    totalFrames++;

    if(isNotNull(obj->getFrameAudio())){

      SoundSystem.addSound(obj->getFrameAudio()); // SoundSystem automatically remove finished sounds in update method.
    }
    
  }

  void placeObject(Object *obj){
    
    this->obj = obj;
    Set(expired, false);
    Set(currentFrame, byte(255)); // On the next update it becomes 0 !
    Set(totalFrames, byte(0));

    update();
  }

  Object* getObject(){

    return obj;
  }
  
  bool isExpired(){

    return expired;
  }

  void takeABreak(){  // Stop rendering the current object. Will function normally when placing a new object.

    Set(nextIntervention, (unsigned long)(-1));
  }

};


struct Matrix{

  char architecture;
  byte intensity;
};


static class MatrixManager{

private:

  Position pos[8][8];
  Matrix matrix[4];

  void updateBrightness(){
    
    lc.setIntensity(0, matrix[0].intensity); // sets brightness (0~15 possible values)
    lc.setIntensity(1, matrix[1].intensity);
    lc.setIntensity(2, matrix[2].intensity);
    lc.setIntensity(3, matrix[3].intensity);
  }

  void configPositions(){

    // Display 0:
    if(isEqual(matrix[0].architecture, 'A')){
      
      pos[0][0].ledConfig(7, 0, 6, 0, 7, 1, 6, 1);
      pos[0][1].ledConfig(5, 0, 4, 0, 5, 1, 4, 1);
      pos[0][2].ledConfig(3, 0, 2, 0, 3, 1, 2, 1);
      pos[0][3].ledConfig(1, 0, 0, 0, 1, 1, 0, 1);
      
      pos[1][0].ledConfig(7, 2, 6, 2, 7, 3, 6, 3);
      pos[1][1].ledConfig(5, 2, 4, 2, 5, 3, 4, 3);
      pos[1][2].ledConfig(3, 2, 2, 2, 3, 3, 2, 3);
      pos[1][3].ledConfig(1, 2, 0, 2, 1, 3, 0, 3);
      
      pos[2][0].ledConfig(7, 4, 6, 4, 7, 5, 6, 5);
      pos[2][1].ledConfig(5, 4, 4, 4, 5, 5, 4, 5);
      pos[2][2].ledConfig(3, 4, 2, 4, 3, 5, 2, 5);
      pos[2][3].ledConfig(1, 4, 0, 4, 1, 5, 0, 5);
      
      pos[3][0].ledConfig(7, 6, 6, 6, 7, 7, 6, 7);
      pos[3][1].ledConfig(5, 6, 4, 6, 5, 7, 4, 7);
      pos[3][2].ledConfig(3, 6, 2, 6, 3, 7, 2, 7);
      pos[3][3].ledConfig(1, 6, 0, 6, 1, 7, 0, 7);
        
    }else{
      
      pos[0][0].ledConfig(0, 7, 0, 6, 1, 7, 1, 6);
      pos[0][1].ledConfig(0, 5, 0, 4, 1, 5, 1, 4);
      pos[0][2].ledConfig(0, 3, 0, 2, 1, 3, 1, 2);
      pos[0][3].ledConfig(0, 1, 0, 0, 1, 1, 1, 0);
      
      pos[1][0].ledConfig(2, 7, 2, 6, 3, 7, 3, 6);
      pos[1][1].ledConfig(2, 5, 2, 4, 3, 5, 3, 4);
      pos[1][2].ledConfig(2, 3, 2, 2, 3, 3, 3, 2);
      pos[1][3].ledConfig(2, 1, 2, 0, 3, 1, 3, 0);
      
      pos[2][0].ledConfig(4, 7, 4, 6, 5, 7, 5, 6);
      pos[2][1].ledConfig(4, 5, 4, 4, 5, 5, 5, 4);
      pos[2][2].ledConfig(4, 3, 4, 2, 5, 3, 5, 2);
      pos[2][3].ledConfig(4, 1, 4, 0, 5, 1, 5, 0);
      
      pos[3][0].ledConfig(6, 7, 6, 6, 7, 7, 7, 6);
      pos[3][1].ledConfig(6, 5, 6, 4, 7, 5, 7, 4);
      pos[3][2].ledConfig(6, 3, 6, 2, 7, 3, 7, 2);
      pos[3][3].ledConfig(6, 1, 6, 0, 7, 1, 7, 0);
    }
    
    // Display 1:
    if(isEqual(matrix[1].architecture, 'A')){
      
      pos[0][4].ledConfig(7, 0, 6, 0, 7, 1, 6, 1);
      pos[0][5].ledConfig(5, 0, 4, 0, 5, 1, 4, 1);
      pos[0][6].ledConfig(3, 0, 2, 0, 3, 1, 2, 1);
      pos[0][7].ledConfig(1, 0, 0, 0, 1, 1, 0, 1);
      
      pos[1][4].ledConfig(7, 2, 6, 2, 7, 3, 6, 3);
      pos[1][5].ledConfig(5, 2, 4, 2, 5, 3, 4, 3);
      pos[1][6].ledConfig(3, 2, 2, 2, 3, 3, 2, 3);
      pos[1][7].ledConfig(1, 2, 0, 2, 1, 3, 0, 3);
      
      pos[2][4].ledConfig(7, 4, 6, 4, 7, 5, 6, 5);
      pos[2][5].ledConfig(5, 4, 4, 4, 5, 5, 4, 5);
      pos[2][6].ledConfig(3, 4, 2, 4, 3, 5, 2, 5);
      pos[2][7].ledConfig(1, 4, 0, 4, 1, 5, 0, 5);
      
      pos[3][4].ledConfig(7, 6, 6, 6, 7, 7, 6, 7);
      pos[3][5].ledConfig(5, 6, 4, 6, 5, 7, 4, 7);
      pos[3][6].ledConfig(3, 6, 2, 6, 3, 7, 2, 7);
      pos[3][7].ledConfig(1, 6, 0, 6, 1, 7, 0, 7);
        
    }else{
      
      pos[0][4].ledConfig(0, 7, 0, 6, 1, 7, 1, 6);
      pos[0][5].ledConfig(0, 5, 0, 4, 1, 5, 1, 4);
      pos[0][6].ledConfig(0, 3, 0, 2, 1, 3, 1, 2);
      pos[0][7].ledConfig(0, 1, 0, 0, 1, 1, 1, 0);
      
      pos[1][4].ledConfig(2, 7, 2, 6, 3, 7, 3, 6);
      pos[1][5].ledConfig(2, 5, 2, 4, 3, 5, 3, 4);
      pos[1][6].ledConfig(2, 3, 2, 2, 3, 3, 3, 2);
      pos[1][7].ledConfig(2, 1, 2, 0, 3, 1, 3, 0);
      
      pos[2][4].ledConfig(4, 7, 4, 6, 5, 7, 5, 6);
      pos[2][5].ledConfig(4, 5, 4, 4, 5, 5, 5, 4);
      pos[2][6].ledConfig(4, 3, 4, 2, 5, 3, 5, 2);
      pos[2][7].ledConfig(4, 1, 4, 0, 5, 1, 5, 0);
      
      pos[3][4].ledConfig(6, 7, 6, 6, 7, 7, 7, 6);
      pos[3][5].ledConfig(6, 5, 6, 4, 7, 5, 7, 4);
      pos[3][6].ledConfig(6, 3, 6, 2, 7, 3, 7, 2);
      pos[3][7].ledConfig(6, 1, 6, 0, 7, 1, 7, 0);
    }
    
    // Display 2:
    if(isEqual(matrix[2].architecture, 'A')){
      
      pos[4][0].ledConfig(0, 7, 1, 7, 0, 6, 1, 6);
      pos[4][1].ledConfig(2, 7, 3, 7, 2, 6, 3, 6);
      pos[4][2].ledConfig(4, 7, 5, 7, 4, 6, 5, 6);
      pos[4][3].ledConfig(6, 7, 7, 7, 6, 6, 7, 6);
      
      pos[5][0].ledConfig(0, 5, 1, 5, 0, 4, 1, 4);
      pos[5][1].ledConfig(2, 5, 3, 5, 2, 4, 3, 4);
      pos[5][2].ledConfig(4, 5, 5, 5, 4, 4, 5, 4);
      pos[5][3].ledConfig(6, 5, 7, 5, 6, 4, 7, 4);
      
      pos[6][0].ledConfig(0, 3, 1, 3, 0, 2, 1, 2);
      pos[6][1].ledConfig(2, 3, 3, 3, 2, 2, 3, 2);
      pos[6][2].ledConfig(4, 3, 5, 3, 4, 2, 5, 2);
      pos[6][3].ledConfig(6, 3, 7, 3, 6, 2, 7, 2);
      
      pos[7][0].ledConfig(0, 1, 1, 1, 0, 0, 1, 0);
      pos[7][1].ledConfig(2, 1, 3, 1, 2, 0, 3, 0);
      pos[7][2].ledConfig(4, 1, 5, 1, 4, 0, 5, 0);
      pos[7][3].ledConfig(6, 1, 7, 1, 6, 0, 7, 0);
        
    }else{
      
      pos[4][0].ledConfig(7, 0, 7, 1, 6, 0, 6, 1);
      pos[4][1].ledConfig(7, 2, 7, 3, 6, 2, 6, 3);
      pos[4][2].ledConfig(7, 4, 7, 5, 6, 4, 6, 5);
      pos[4][3].ledConfig(7, 6, 7, 7, 6, 6, 6, 7);
      
      pos[5][0].ledConfig(5, 0, 5, 1, 4, 0, 4, 1);
      pos[5][1].ledConfig(5, 2, 5, 3, 4, 2, 4, 3);
      pos[5][2].ledConfig(5, 4, 5, 5, 4, 4, 4, 5);
      pos[5][3].ledConfig(5, 6, 5, 7, 4, 6, 4, 7);
      
      pos[6][0].ledConfig(3, 0, 3, 1, 2, 0, 2, 1);
      pos[6][1].ledConfig(3, 2, 3, 3, 2, 2, 2, 3);
      pos[6][2].ledConfig(3, 4, 3, 5, 2, 4, 2, 5);
      pos[6][3].ledConfig(3, 6, 3, 7, 2, 6, 2, 7);
      
      pos[7][0].ledConfig(1, 0, 1, 1, 0, 0, 0, 1);
      pos[7][1].ledConfig(1, 2, 1, 3, 0, 2, 0, 3);
      pos[7][2].ledConfig(1, 4, 1, 5, 0, 4, 0, 5);
      pos[7][3].ledConfig(1, 6, 1, 7, 0, 6, 0, 7);
    }
    
    // Display 3:
    if(isEqual(matrix[3].architecture, 'A')){
      
      pos[4][4].ledConfig(0, 7, 1, 7, 0, 6, 1, 6);
      pos[4][5].ledConfig(2, 7, 3, 7, 2, 6, 3, 6);
      pos[4][6].ledConfig(4, 7, 5, 7, 4, 6, 5, 6);
      pos[4][7].ledConfig(6, 7, 7, 7, 6, 6, 7, 6);
      
      pos[5][4].ledConfig(0, 5, 1, 5, 0, 4, 1, 4);
      pos[5][5].ledConfig(2, 5, 3, 5, 2, 4, 3, 4);
      pos[5][6].ledConfig(4, 5, 5, 5, 4, 4, 5, 4);
      pos[5][7].ledConfig(6, 5, 7, 5, 6, 4, 7, 4);
      
      pos[6][4].ledConfig(0, 3, 1, 3, 0, 2, 1, 2);
      pos[6][5].ledConfig(2, 3, 3, 3, 2, 2, 3, 2);
      pos[6][6].ledConfig(4, 3, 5, 3, 4, 2, 5, 2);
      pos[6][7].ledConfig(6, 3, 7, 3, 6, 2, 7, 2);
      
      pos[7][4].ledConfig(0, 1, 1, 1, 0, 0, 1, 0);
      pos[7][5].ledConfig(2, 1, 3, 1, 2, 0, 3, 0);
      pos[7][6].ledConfig(4, 1, 5, 1, 4, 0, 5, 0);
      pos[7][7].ledConfig(6, 1, 7, 1, 6, 0, 7, 0);
        
    }else{
      
      pos[4][4].ledConfig(7, 0, 7, 1, 6, 0, 6, 1);
      pos[4][5].ledConfig(7, 2, 7, 3, 6, 2, 6, 3);
      pos[4][6].ledConfig(7, 4, 7, 5, 6, 4, 6, 5);
      pos[4][7].ledConfig(7, 6, 7, 7, 6, 6, 6, 7);
      
      pos[5][4].ledConfig(5, 0, 5, 1, 4, 0, 4, 1);
      pos[5][5].ledConfig(5, 2, 5, 3, 4, 2, 4, 3);
      pos[5][6].ledConfig(5, 4, 5, 5, 4, 4, 4, 5);
      pos[5][7].ledConfig(5, 6, 5, 7, 4, 6, 4, 7);
      
      pos[6][4].ledConfig(3, 0, 3, 1, 2, 0, 2, 1);
      pos[6][5].ledConfig(3, 2, 3, 3, 2, 2, 2, 3);
      pos[6][6].ledConfig(3, 4, 3, 5, 2, 4, 2, 5);
      pos[6][7].ledConfig(3, 6, 3, 7, 2, 6, 2, 7);
      
      pos[7][4].ledConfig(1, 0, 1, 1, 0, 0, 0, 1);
      pos[7][5].ledConfig(1, 2, 1, 3, 0, 2, 0, 3);
      pos[7][6].ledConfig(1, 4, 1, 5, 0, 4, 0, 5);
      pos[7][7].ledConfig(1, 6, 1, 7, 0, 6, 0, 7);
    }
  }

public:

  MatrixManager(){

    Set(matrix[0].architecture, EEPROMManager.getDisplayType(0));
    Set(matrix[1].architecture, EEPROMManager.getDisplayType(1));
    Set(matrix[2].architecture, EEPROMManager.getDisplayType(2));
    Set(matrix[3].architecture, EEPROMManager.getDisplayType(3));
    
    Set(matrix[0].intensity, EEPROMManager.getDisplayBrightness(0));
    Set(matrix[1].intensity, EEPROMManager.getDisplayBrightness(1));
    Set(matrix[2].intensity, EEPROMManager.getDisplayBrightness(2));
    Set(matrix[3].intensity, EEPROMManager.getDisplayBrightness(3));

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        pos[i][j].setDysplay(0);
      }
    }
    
    for(int i = 0; i < 4; i++){
      for(int j = 4; j < 8; j++){
        pos[i][j].setDysplay(1);
      }
    }

    for(int i = 4; i < 8; i++){
      for(int j = 0; j < 4; j++){
        pos[i][j].setDysplay(2);
      }
    }
    
    for(int i = 4; i < 8; i++){
      for(int j = 4; j < 8; j++){
        pos[i][j].setDysplay(3);
      }
    }
  }

  void initialize(){
    
    lc.shutdown(0, false); // turn off power saving, enables display
    lc.shutdown(1, false);
    lc.shutdown(2, false);
    lc.shutdown(3, false);

    updateBrightness();
    configPositions();
    
    lc.clearDisplay(0); // clear screen
    lc.clearDisplay(1);
    lc.clearDisplay(2);
    lc.clearDisplay(3);
  }

  void setMatrixArchitecture(int index, char value){
    
    Set(matrix[index].architecture, value);
    EEPROMManager.setDisplayType(index, value);

    configPositions();
  }

  void setMatrixIntensity(int index, byte value){
    
    Set(matrix[index].intensity, value);
    EEPROMManager.setDisplayBrightness(index, value);

    updateBrightness();
  }

  char getMatrixArchitecture(int index){
    
    return matrix[index].architecture;
  }

  byte getMatrixIntensity(int index){
    
    return matrix[index].intensity;
  }

  Position& getPosition(int row, int col){
    return pos[row][col];
  }

  void placeObject(Object *obj, int x, int y){
    pos[x][y].placeObject(obj);
  }

  void update(){
    
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        
        if(pos[i][j].needAttention()){
          
          pos[i][j].update();
        }
        
      }
    }
  }

  void lightsOn(){
    
    for(int displayNr = 0; displayNr < 4; displayNr++){
      for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
          lc.setLed(displayNr, col, row, true); // turns on LED at col, row
        }
      }
    }
  }

  void lightsOff(){
    
    for(int displayNr = 0; displayNr < 4; displayNr++){
      for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
          lc.setLed(displayNr, col, row, false); // turns off LED at col, row
        }
      }
    }

    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){
        
        pos[row][col].takeABreak();
      }
    }
    
  }

  void displayIcon(int index, Icon I){

    int rs; // row shift
    int cs; // col shift
    
    switch(index){
      case 0:   // Upper-Left
        rs = 0;
        cs = 0;
        break;
      case 1:   // Upper-Right
        rs = 0;
        cs = 4;
        break;
      case 2:   // Lower-Left
        rs = 4;
        cs = 0;
        break;
      case 3:   // Lower-Right
        rs = 4;
        cs = 4;
        break;
      default:   // Center (for any other index)
        rs = 2;
        cs = 2;
        break;
    }
    
    pos[0 + rs][0 + cs].lightLeds(Math.getBitOfByte(0, I.row0), Math.getBitOfByte(1, I.row0), Math.getBitOfByte(0, I.row1), Math.getBitOfByte(1, I.row1));
    pos[0 + rs][1 + cs].lightLeds(Math.getBitOfByte(2, I.row0), Math.getBitOfByte(3, I.row0), Math.getBitOfByte(2, I.row1), Math.getBitOfByte(3, I.row1));
    pos[0 + rs][2 + cs].lightLeds(Math.getBitOfByte(4, I.row0), Math.getBitOfByte(5, I.row0), Math.getBitOfByte(4, I.row1), Math.getBitOfByte(5, I.row1));
    pos[0 + rs][3 + cs].lightLeds(Math.getBitOfByte(6, I.row0), Math.getBitOfByte(7, I.row0), Math.getBitOfByte(6, I.row1), Math.getBitOfByte(7, I.row1));
    pos[1 + rs][0 + cs].lightLeds(Math.getBitOfByte(0, I.row2), Math.getBitOfByte(1, I.row2), Math.getBitOfByte(0, I.row3), Math.getBitOfByte(1, I.row3));
    pos[1 + rs][1 + cs].lightLeds(Math.getBitOfByte(2, I.row2), Math.getBitOfByte(3, I.row2), Math.getBitOfByte(2, I.row3), Math.getBitOfByte(3, I.row3));
    pos[1 + rs][2 + cs].lightLeds(Math.getBitOfByte(4, I.row2), Math.getBitOfByte(5, I.row2), Math.getBitOfByte(4, I.row3), Math.getBitOfByte(5, I.row3));
    pos[1 + rs][3 + cs].lightLeds(Math.getBitOfByte(6, I.row2), Math.getBitOfByte(7, I.row2), Math.getBitOfByte(6, I.row3), Math.getBitOfByte(7, I.row3));
    pos[2 + rs][0 + cs].lightLeds(Math.getBitOfByte(0, I.row4), Math.getBitOfByte(1, I.row4), Math.getBitOfByte(0, I.row5), Math.getBitOfByte(1, I.row5));
    pos[2 + rs][1 + cs].lightLeds(Math.getBitOfByte(2, I.row4), Math.getBitOfByte(3, I.row4), Math.getBitOfByte(2, I.row5), Math.getBitOfByte(3, I.row5));
    pos[2 + rs][2 + cs].lightLeds(Math.getBitOfByte(4, I.row4), Math.getBitOfByte(5, I.row4), Math.getBitOfByte(4, I.row5), Math.getBitOfByte(5, I.row5));
    pos[2 + rs][3 + cs].lightLeds(Math.getBitOfByte(6, I.row4), Math.getBitOfByte(7, I.row4), Math.getBitOfByte(6, I.row5), Math.getBitOfByte(7, I.row5));
    pos[3 + rs][0 + cs].lightLeds(Math.getBitOfByte(0, I.row6), Math.getBitOfByte(1, I.row6), Math.getBitOfByte(0, I.row7), Math.getBitOfByte(1, I.row7));
    pos[3 + rs][1 + cs].lightLeds(Math.getBitOfByte(2, I.row6), Math.getBitOfByte(3, I.row6), Math.getBitOfByte(2, I.row7), Math.getBitOfByte(3, I.row7));
    pos[3 + rs][2 + cs].lightLeds(Math.getBitOfByte(4, I.row6), Math.getBitOfByte(5, I.row6), Math.getBitOfByte(4, I.row7), Math.getBitOfByte(5, I.row7));
    pos[3 + rs][3 + cs].lightLeds(Math.getBitOfByte(6, I.row6), Math.getBitOfByte(7, I.row6), Math.getBitOfByte(6, I.row7), Math.getBitOfByte(7, I.row7));
  }

  void paint(int x, int y, bool led0, bool led1, bool led2, bool led3){
    
    pos[x][y].lightLeds(led0, led1, led2, led3);
  }

}MatrixManager;


#endif /// MATRIXMANAGER_H_INCLUDED
