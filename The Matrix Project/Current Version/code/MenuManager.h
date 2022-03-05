#ifndef MENUMANAGER_H_INCLUDED
#define MENUMANAGER_H_INCLUDED

#include <LiquidCrystal.h> // for LCD

const int lcdRS = 33;
const int lcdEnable = 32;
const int lcdD4 = 30;
const int lcdD5 = 28;
const int lcdD6 = 26;
const int lcdD7 = 24;

LiquidCrystal lcd(lcdRS, lcdEnable, lcdD4, lcdD5, lcdD6, lcdD7);


static class MenuManager{

private:

  bool leftOwnership;
  byte audioOption; // 0 - Mute, 1 - Music, 2 - Effects, 3 - Both.
  const Sound* menuTheme = &Playlist.keyboardCat;

public:

  MenuManager(){
    
    Set(leftOwnership, EEPROMManager.isLeftTheOwner());
    Set(audioOption, EEPROMManager.getMenuSoundOption());
  }

  void initialize(){
    
    lcd.begin(16, 2);
  }
  
  bool isLeftTheOwner(){
    return leftOwnership;
  }
  
  void setOwnership(bool left){
    
    Set(leftOwnership, left);
    EEPROMManager.setMenuOwner(left);
  }

  byte getAudioOption(){

    return audioOption;
  }

  void setAudioOption(byte option){

    byte prevAudioOption = audioOption;
    
    Set(audioOption, option);
    EEPROMManager.setMenuSoundOption(option);

    if(isEqual(getAudioOption(), byte(0)) || isEqual(getAudioOption(), byte(2))){ // 0 - Mute, 1 - Music, 2 - Effects, 3 - Both.

      stopMusic();
      
    }else if(isEqual(prevAudioOption, byte(0)) || isEqual(prevAudioOption, byte(2))){
      
      beginMusic();
    }
  }

  void beginMusic(){
    
    SoundSystem.addSound(menuTheme);
  }

  void stopMusic(){

    SoundSystem.removeSound(menuTheme);
  }
  
}MenuManager;


static struct MenuInputs{
  
  bool prevBtnValue;
  bool prevSWValue;
  int prevXAxisValue;
  int prevYAxisValue;
  
  bool btnValue;
  bool SWValue;
  int xAxisValue;
  int yAxisValue;

  void savePrevious(){
    
    Set(prevBtnValue, btnValue);
    Set(prevSWValue, SWValue);
    Set(prevXAxisValue, xAxisValue);
    Set(prevYAxisValue, yAxisValue);
  }

  void load(){
    
    if(MenuManager.isLeftTheOwner()){
      
      Set(btnValue, InputManager.LCBtnValue());
      Set(SWValue, InputManager.LCSWValue());
      Set(xAxisValue, InputManager.LCXValue());
      Set(yAxisValue, InputManager.LCYValue());
    }else{
      
      Set(btnValue, InputManager.RCBtnValue());
      Set(SWValue, InputManager.RCSWValue());
      Set(xAxisValue, InputManager.RCXValue());
      Set(yAxisValue, InputManager.RCYValue());
    }
  }
  
}MenuInputs;


class Menu{

private:

  String *options;
  int numOptions;
  int selectedOption;
  bool downwardNav;
  
public:

  Menu(int numOptions){ /// CONSTRUCTOR

    Set(this->numOptions, numOptions);
    Set(selectedOption, 0);
    Set(downwardNav, false);

    options = new String[numOptions];
  }

  ~Menu(){ /// DECONSTRUCTOR

    delete[] options;
  }

  static void clearLcdScreen(){
    
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }

  void setOption(int index, String option){

    if(isLesser(index, numOptions)){
      Set(options[index], option);
    }
  }

  int getSelected(){
    return selectedOption;
  }

  void refresh(){
    
    clearLcdScreen();
    
    if(downwardNav){
      lcd.setCursor(1,0);
      lcd.print(options[selectedOption - 1]);
      lcd.setCursor(0,1);
      lcd.print("~" + options[selectedOption]);
    }else{  // than uppwardNav
      lcd.setCursor(0,0);
      lcd.print("~" + options[selectedOption]);
      lcd.setCursor(1,1);
      if(isGreater(numOptions, selectedOption + 1)){
        lcd.print(options[selectedOption + 1]);
      }
    }
  }

  bool goDown(){

    if(isGreater(numOptions, selectedOption + 1)){
      Set(downwardNav, true);
      selectedOption++;
      refresh();
      return true;
    }
    return false;
  }

  bool goUp(){

    if(isGreater(selectedOption, 0)){
      Set(downwardNav, false);
      selectedOption--;
      refresh();
      return true;
    }
    return false;
  }

  int gatherActions(){

    // Select Option
    if(isEqual(MenuInputs.prevBtnValue, false) && isEqual(MenuInputs.btnValue, true)){
      if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){
        SoundSystem.addSound(&Playlist.menuClickEffect); // SoundSystem automatically remove finished sounds in update method.
      }
      return getSelected(); // positive int
    }
    
    // Going Down
    if(isEqual(MenuInputs.prevXAxisValue, 0) && isGreater(MenuInputs.xAxisValue, 0)){
      if(goDown()){  // goDown returns true if succesfull, or false.
        if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){
          SoundSystem.addSound(&Playlist.menuNavEffect);
        }
      }else{
        if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){
          SoundSystem.addSound(&Playlist.menuEndEffect);
        }
      }
      return -2; // Input -> down
    }
    
    // Going Up
    if(isEqual(MenuInputs.prevXAxisValue, 0) && isLesser(MenuInputs.xAxisValue, 0)){
      if(goUp()){  // goUp returns true if succesfull, or false.
        if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){
          SoundSystem.addSound(&Playlist.menuNavEffect);
        }
      }else{
        if(isEqual(MenuManager.getAudioOption(), byte(2)) || isEqual(MenuManager.getAudioOption(), byte(3))){
          SoundSystem.addSound(&Playlist.menuEndEffect);
        }
      }
      return -3; // Input -> up
    }
    
    // Left signal
    if(isEqual(MenuInputs.prevYAxisValue, 0) && isLesser(MenuInputs.yAxisValue, 0)){
      return -4; // Input -> left
    }
    
    // Right signal
    if(isEqual(MenuInputs.prevYAxisValue, 0) && isGreater(MenuInputs.yAxisValue, 0)){
      return -5; // Input -> right
    }
    return -1; // No input
  }
  
};


#endif /// MENUMANAGER_H_INCLUDED
