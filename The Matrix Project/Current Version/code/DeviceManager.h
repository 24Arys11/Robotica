#ifndef DEVICEANAGER_H_INCLUDED
#define DEVICEANAGER_H_INCLUDED


static class Device{

private:

  String owner;

  void animeCharLCD(char c, int shyFromMargin, unsigned long animationStart, unsigned long frameLength, bool leftRight = false, int row = 0){

    int numIterations = 16 - shyFromMargin;
    
    if(leftRight){

      for(int i = 0; i < numIterations; i++){
  
        if(isGreater(millis(), animationStart + (i + 1)*frameLength)){
  
          if(isNotEqual(i, 0)){
  
            lcd.setCursor(i - 1, row);
            lcd.print(" ");
          }
          
          lcd.setCursor(i, row);
          lcd.print(c);
        }
      }
      return;
    }

    for(int i = 0; i < numIterations; i++){

      if(isGreater(millis(), animationStart + (i + 1)*frameLength)){

        if(isNotEqual(i, 0)){

          lcd.setCursor(16 - i, row);
          lcd.print(" ");
        }
        
        lcd.setCursor(15 - i, row);
        lcd.print(c);
      }
    }
  }

public:

  Device(){
    
    owner = EEPROMManager.getPlayerName();
  }

  String formatName(String name){

    String result = name;

    for(int i = 0; i < 16; i++){
      if(isEqual(result[i], '@')){
        Set(result[i], ' ');
      }
    }

    return result;
  }

  void setOwner(String name){
    
    Set(owner, name);
    EEPROMManager.setPlayerName(name);
  }

  String getOwner(){  // get the owner as it is !

    return owner;
  }

  void animateTextLCD(String text, unsigned long frameLength, bool leftRight = false, int row = 0){

    unsigned long animeStart;
    char c;

    for(int i = 0; i < text.length(); i++){
      
      animeStart = millis();

      if(leftRight){
        while(isLesser(millis(), animeStart + 16*frameLength)){
          
          updateAll();
          c = text[text.length() - 1 - i];
          animeCharLCD(c, i + (16 - text.length()), animeStart, frameLength, leftRight, row);
          lcd.setCursor(i - 1 + text.length(), row);
          lcd.print(c);
        }
      }else{
        while(isLesser(millis(), animeStart + 16*frameLength)){
          
          updateAll();
          c = text[i];
          animeCharLCD(c, i, animeStart, frameLength, leftRight, row);
          lcd.setCursor(i, row);
          lcd.print(c);
        }
      }
    }
  }
  
  void printMessage(String message1, String message2 = "", unsigned long duration = 0){

    Menu::clearLcdScreen();
    
    lcd.setCursor(0,0);
    lcd.print(message1);
    lcd.setCursor(0,1);
    lcd.print(message2);

    wait(duration); // sounds & animeMatrix are still updated !
  }

  void wait(unsigned long duration){  // Similar to delay, but the background "processes" are still working (sound, matrix animations.. are updated)
    
    unsigned long initialTime = millis();
    
    while(isLesser(millis(), initialTime + duration)){
      updateAll();  
    }
  }

  void updateAll(){
  
    SoundSystem.update();
    InputManager.update();
    MatrixManager.update();
  }

  void welcome(){

    SoundSystem.addSound(&Playlist.welcomeSong);
    animateTextLCD("Welcome,", 50, false, 0);
    animateTextLCD(formatName(getOwner()), 60, false, 1);
  }
  
}Device;


#endif /// DEVICEANAGER_H_INCLUDED
