#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED


#include <EEPROM.h>


static struct Math{

  byte toByte(char *nr){

    byte result = 0;

    for(int i = 0; i < 8; i++){

      if(isEqual(nr[i], '1')){
        result += ceil(pow(2, (7 - i)));
      }
    }

    return result;
  }

  bool getBitOfByte(byte theBit, byte theByte){

    byte mask = ceil(pow(2, (7 - theBit)));

    return (theByte & mask);
  }
  
  void setBitOfByte(byte theBit, byte &theByte, bool value){

    byte mask = ceil(pow(2, (7 - theBit)));
    if(value){
      Set(theByte, byte(theByte | mask));
    }else{
      Set(theByte, byte(theByte & ~mask));
    }
  }
  
  unsigned int to16Bits(char *nr){

    unsigned int result = 0;

    for(int i = 0; i < 16; i++){

      if(isEqual(nr[i], '1')){
        result += ceil(pow(2, (15 - i)));
      }
    }

    return result;
  }

  bool getBitOfShort(byte theBit, unsigned int theShort){

    unsigned int mask = ceil(pow(2, (15 - theBit)));

    return (theShort & mask);
  }
  
  void setBitOfShort(byte theBit, unsigned int &theShort, bool value){

    unsigned int mask = ceil(pow(2, (15 - theBit)));
    if(value){
      Set(theShort, (unsigned int)(theShort | mask));
    }else{
      Set(theShort, (unsigned int)(theShort & ~mask));
    }
  }
  
  byte getByteOfShort(byte theByte, unsigned int theShort){  // theByte could be 0 or 1

    if(isEqual(theByte, byte(0))){
      return byte(theShort >> 8);
    }
    
    return byte(theShort);
  }
  
  void setByteOfShort(byte theByte, unsigned int &theShort, byte value){ // theByte could be 0 or 1

    // Erase the Byte
    if(isEqual(theByte, byte(0))){
      Set(theShort, (unsigned int)(theShort & to16Bits("0000000011111111")));
    }else{
      Set(theShort, (unsigned int)(theShort & to16Bits("1111111100000000")));
    }
    
    // Set the Byte
    unsigned int mask = value;
    if(isEqual(theByte, byte(0))){
      mask << 8;
    }
    
    Set(theShort, (unsigned int)(theShort | mask));
  }
  
}Math;


static class EEPROMManager{

private:

  const int shiftEEPROM = 0; // if EEPROM gets damaged, we can shift all the adresses just by changing this variable !

  // MENU
  const int playerNameAddress = 0 + shiftEEPROM;          // 16 char = 16 bytes
  const int menuOwnerAddress = 16 + shiftEEPROM;          // 1 bool = 1 byte
  const int muteAudioAddress = 17 + shiftEEPROM;          // 1 bool = 1 byte
  const int menuSoundAddress = 18 + shiftEEPROM;          // 1 byte
  const int displayTypesAddress = 19 + shiftEEPROM;       // 4 char = 4 bytes (one for each matrix)
  const int displayBrightnessAddress = 23 + shiftEEPROM;  // 4 bytes (one for each matrix)

  // BOMBERMAN
  const int lastGameSPConfigAddress = 27 + shiftEEPROM;   // 4 bytes (one for each Spawn Point)
  const int gameLevelAddress = 31 + shiftEEPROM;          // 1 byte
  const int score0NameAddress = 32 + shiftEEPROM;         // 16 char = 16 bytes
  const int score0scoreAddress = 48 + shiftEEPROM;        // 1 byte
  const int score1NameAddress = 49 + shiftEEPROM;         // 16 char = 16 bytes
  const int score1scoreAddress = 65 + shiftEEPROM;        // 1 byte
  const int score2NameAddress = 66 + shiftEEPROM;         // 16 char = 16 bytes
  const int score2scoreAddress = 82 + shiftEEPROM;        // 1 byte

  // Available space from address 83 (+ shiftEEPROM) onward !
  
public:

  void factoryReset(){

    // Clear EEPROM
    for(int i = 0; i < EEPROM.length(); i++){
      EEPROM.update(i, 0);
    }

    setPlayerName("NEW@PLAYER@@@@@@");  // @ is read as space
    setMenuOwner(true);
    setAudioMute(false);
    setMenuSoundOption(3);  // 0 - Mute, 1 - Music, 2 - Effects, 3 - Both.
    setDisplayType(0, 'A');
    setDisplayType(1, 'A');
    setDisplayType(2, 'A');
    setDisplayType(3, 'A');
    setDisplayBrightness(0, 10);
    setDisplayBrightness(1, 10);
    setDisplayBrightness(2, 10);
    setDisplayBrightness(3, 10);

    bombermanReset();
  }

  void bombermanReset(){

    saveSpawnConfig(1, 0, 0, 3);  // P1, --, --, AI.
    setGameLevel(0);  // generateRandom
    setHighScore(0, "@@@@@@@@@@@@@@@@", 0);
    setHighScore(1, "@@@@@@@@@@@@@@@@", 0);
    setHighScore(2, "@@@@@@@@@@@@@@@@", 0);
  }

  void setPlayerName(String name){

    for(int i = 0; i < 16; i++){

      EEPROM.update(playerNameAddress + i, name[i]);
    }
  }

  String getPlayerName(){

    String name = "";
    
    for(int i = 0; i < 16; i++){

      name += char(EEPROM.read(playerNameAddress + i));
    }

    return name;
  }

  void setMenuOwner(bool leftOwnership){

    EEPROM.update(menuOwnerAddress, leftOwnership);
  }

  bool isLeftTheOwner(){

    return bool(EEPROM.read(menuOwnerAddress));
  }

  void setAudioMute(bool mute){

    EEPROM.update(muteAudioAddress, mute);
  }

  bool isAudioMute(){

    return bool(EEPROM.read(muteAudioAddress));
  }

  void setMenuSoundOption(byte option){

    EEPROM.update(menuSoundAddress, option);
  }

  byte getMenuSoundOption(){

    return EEPROM.read(menuSoundAddress);
  }

  void setDisplayType(int displayNr, char displayType){

    if(isGreater(displayNr, 3)){  // There are only 4 display matrices: 0, 1, 2 and 3 !
      return;
    }
    
    EEPROM.update(displayTypesAddress + displayNr, displayType);
  }

  char getDisplayType(int displayNr){

    return char(EEPROM.read(displayTypesAddress + displayNr));
  }

  void setDisplayBrightness(int displayNr, byte displayBrightness){

    if(isGreater(displayNr, 3)){  // There are only 4 display matrices: 0, 1, 2 and 3 !
      return;
    }
    
    EEPROM.update(displayBrightnessAddress + displayNr, displayBrightness);
  }

  byte getDisplayBrightness(int displayNr){

    return EEPROM.read(displayBrightnessAddress + displayNr);
  }

  void saveSpawnConfig(byte SpawnPoint0, byte SpawnPoint1, byte SpawnPoint2, byte SpawnPoint3){
    
    EEPROM.update(lastGameSPConfigAddress, SpawnPoint0);
    EEPROM.update(lastGameSPConfigAddress + 1, SpawnPoint1);
    EEPROM.update(lastGameSPConfigAddress + 2, SpawnPoint2);
    EEPROM.update(lastGameSPConfigAddress + 3, SpawnPoint3);
  }

  void loadSpawnConfig(byte &SpawnPoint0, byte &SpawnPoint1, byte &SpawnPoint2, byte &SpawnPoint3){

    Set(SpawnPoint0, EEPROM.read(lastGameSPConfigAddress));
    Set(SpawnPoint1, EEPROM.read(lastGameSPConfigAddress + 1));
    Set(SpawnPoint2, EEPROM.read(lastGameSPConfigAddress + 2));
    Set(SpawnPoint3, EEPROM.read(lastGameSPConfigAddress + 3));
  }

  void setGameLevel(byte level){

    EEPROM.update(gameLevelAddress, level);
  }

  byte getGameLevel(){

    return EEPROM.read(gameLevelAddress);
  }

  void setHighScore(byte index, String name, byte score){

    switch(index){

      case 0:
        for(int i = 0; i < 16; i++){
          EEPROM.update(score0NameAddress + i, name[i]);
        }
        EEPROM.update(score0scoreAddress, score);
        break;
      case 1:
        for(int i = 0; i < 16; i++){
          EEPROM.update(score1NameAddress + i, name[i]);
        }
        EEPROM.update(score1scoreAddress, score);
        break;
      case 2:
        for(int i = 0; i < 16; i++){
          EEPROM.update(score2NameAddress + i, name[i]);
        }
        EEPROM.update(score2scoreAddress, score);
        break;
    }
  }

  String getHighScoreName(byte index){

    String name = "";
    
    switch(index){

      case 0:
        for(int i = 0; i < 16; i++){
          name += char(EEPROM.read(score0NameAddress + i));
        }
        break;
      case 1:
        for(int i = 0; i < 16; i++){
          name += char(EEPROM.read(score1NameAddress + i));
        }
        break;
      case 2:
        for(int i = 0; i < 16; i++){
          name += char(EEPROM.read(score2NameAddress + i));
        }
        break;
    }
    
    return name;
  }

  byte getHighScoreScore(byte index){
    
    switch(index){
      
      case 0:
        return EEPROM.read(score0scoreAddress);
      case 1:
        return EEPROM.read(score1scoreAddress);
      case 2:
        return EEPROM.read(score2scoreAddress);
    }
    
    return 0;
  }

}EEPROMManager;


#endif /// UTILITIES_H_INCLUDED
