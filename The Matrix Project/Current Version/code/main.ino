//#define FIRST_RUN   // Need to setup the EEPROM on the first run !

//#define DEBUG_ENABLED
//#define DEBUG_MENU
//#define DEBUG_INPUTS
//#define DEBUG_SOUND
//#define DEBUG_MATRIX
//#define DEBUG_BBMM
//#define DEBUG_BBMPVP
//#define DEBUG_BBMPVAI

/// INFRASTRUCTURE: (the order of includes matters !)
#include "safetyProcedures.h" // used in every header file !
#include "utilities.h"

#include "InputManager.h"
#include "SoundSystem.h"
#include "SongLibrary.h"    // needs "SoundSystem.h"
#include "MatrixManager.h"
#include "MenuManager.h"    // needs everything included above
#include "MenuIcons.h"      // needs "MenuManager.h"
#include "DeviceManager.h"  // needs everything included above

/// DEVELOPED GAMES:
#include "Bomberman.h"


void setup(){

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // Internal LED is blinking randomly.
  
  SoundSystem.initialize();
  MenuManager.initialize();
  MatrixManager.initialize();
  InputManager.initialize();

  #ifdef FIRST_RUN
  EEPROMManager.factoryReset();
  #endif

  #ifdef DEBUG_ENABLED
  Serial.begin(9600);
  #endif
  
  Playlist.loadPlaylist();

  Device.welcome();
  
  delay(1);
}


static struct MainMenu{

  unsigned long messageDisplayTime = 1000;

public:

  void launcher(){

    MenuInputs.load();
    if(isEqual(MenuManager.getAudioOption(), byte(1)) || isEqual(MenuManager.getAudioOption(), byte(3))){ // 0 - Mute, 1 - Music, 2 - Effects, 3 - Both.
      MenuManager.beginMusic();
    }
    
    Menu menu(4);
    menu.setOption(0, "Select game");
    menu.setOption(1, "Configuration");
    menu.setOption(2, "Diagnostics");
    menu.setOption(3, "Credits");
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
          selectGame();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          configuration();
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          diagnostics();
          menu.refresh();
          prevSelected = -1;
          break;
        case 3:
          credits();
          menu.refresh();
          prevSelected = -1;
          break;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.playGame);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.configuration);
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.diagnostics);
            break;
          case 3:
            MatrixManager.displayIcon(-1, MenuIcons.star);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void selectGame(){

    Menu menu(2);
    menu.setOption(0, "Bomberman");
    menu.setOption(1, "Back");
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
          BombermanMenu.launcher();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.bomberman);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void configuration(){

    Menu menu(5);
    menu.setOption(0, "Player name");
    menu.setOption(1, "Menu owner");
    menu.setOption(2, "Audio config");
    menu.setOption(3, "Matrix config");
    menu.setOption(4, "Back");
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
          setPlayerName();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          configMenuOwner();
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          configAudio();
          menu.refresh();
          prevSelected = -1;
          break;
        case 3:
          configMatrix();
          menu.refresh();
          prevSelected = -1;
          break;
        case 4:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.playerName);
            break;
          case 1:
            if(MenuManager.isLeftTheOwner()){
              MatrixManager.displayIcon(-1, MenuIcons.left);
            }else{
              MatrixManager.displayIcon(-1, MenuIcons.right);
            }
            break;
          case 2:
            if(SoundSystem.isMute()){
              MatrixManager.displayIcon(-1, MenuIcons.mute);
            }else{
              MatrixManager.displayIcon(-1, MenuIcons.speaker);
            }
            break;
          case 3:
            MatrixManager.displayIcon(-1, MenuIcons.matrix);
            break;
          case 4:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void setPlayerName(){

    String newOwner = Device.getOwner();
    int selectedChar = 0;

    Menu::clearLcdScreen();
    lcd.setCursor(0,0);
    lcd.print(Device.formatName(newOwner));
    lcd.setCursor(selectedChar, 1);
    lcd.print("^");

    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      // Click
      if(isEqual(MenuInputs.prevBtnValue, false) && isEqual(MenuInputs.btnValue, true)){
        SoundSystem.addSound(&Playlist.menuClickEffect); // SoundSystem automatically remove finished sounds in update method.
        Device.setOwner(newOwner);  // Also updates EEPROM !
        Device.printMessage("Welcome,", Device.formatName(newOwner), messageDisplayTime);
        return;
      }
      
      // Left signal
      if(isEqual(MenuInputs.prevYAxisValue, 0) && isLesser(MenuInputs.yAxisValue, 0)){
        if(isGreater(selectedChar, 0)){
          lcd.setCursor(selectedChar, 1);
          lcd.print(" ");
          selectedChar--;
          lcd.setCursor(selectedChar, 1);
          lcd.print("^");
          //
        }
      }
      
      // Right signal
      if(isEqual(MenuInputs.prevYAxisValue, 0) && isGreater(MenuInputs.yAxisValue, 0)){
        if(isLesser(selectedChar, 15)){
          lcd.setCursor(selectedChar, 1);
          lcd.print(" ");
          selectedChar++;
          lcd.setCursor(selectedChar, 1);
          lcd.print("^");
        }
      }

      // Down Signal
      if(isEqual(MenuInputs.prevXAxisValue, 0) && isGreater(MenuInputs.xAxisValue, 0)){
        SoundSystem.addSound(&Playlist.menuNavEffect);
        if(isGreater(newOwner[selectedChar], '@')){ // one char before 'A' - will replace space !
          newOwner[selectedChar]--;
        }else{
          newOwner[selectedChar] = 'Z';
        }
        lcd.setCursor(0,0);
        lcd.print(Device.formatName(newOwner));
      }
      
      // Up Signal
      if(isEqual(MenuInputs.prevXAxisValue, 0) && isLesser(MenuInputs.xAxisValue, 0)){
        SoundSystem.addSound(&Playlist.menuNavEffect);
        if(isLesser(newOwner[selectedChar], 'Z')){
          newOwner[selectedChar]++;
        }else{
          newOwner[selectedChar] = '@'; // one char before 'A' - will replace space !
        }
        lcd.setCursor(0,0);
        lcd.print(Device.formatName(newOwner));
      }
    }
  }

  void configMenuOwner(){

    Menu menu(2);
    menu.setOption(0, "Left console");
    menu.setOption(1, "Right console");
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
          MenuManager.setOwnership(true); // true = leftOwnership
          Device.printMessage("Owner: Left", "Selected !", messageDisplayTime);
          return;
        case 1:
          MenuManager.setOwnership(false); // false = not leftOwnership
          Device.printMessage("Owner: Right", "Selected !", messageDisplayTime);
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.left);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.right);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void configAudio(){

    Menu menu(3);
    menu.setOption(0, "Mute");
    menu.setOption(1, "Menu sound");
    menu.setOption(2, "Back");
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
          setMute();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          setMenuSound();
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){

        switch(menu.getSelected()){
          case 0:
            if(SoundSystem.isMute()){
              MatrixManager.displayIcon(-1, MenuIcons.mute);
            }else{
              MatrixManager.displayIcon(-1, MenuIcons.speaker);
            }
            break;
          case 1:
            switch(MenuManager.getAudioOption()){ // 0 - Mute, 1 - Music, 2 - Effects, 3 - Both.
              case 0: // 0 - Mute
                MatrixManager.displayIcon(-1, MenuIcons.mute);
                break;
              case 1: // 1 - Music
                MatrixManager.displayIcon(-1, MenuIcons.musicNote);
                break;
              case 2: // 2 - Effects
                MatrixManager.displayIcon(-1, MenuIcons.bell);
                break;
              case 3: // 3 - Both
                MatrixManager.displayIcon(-1, MenuIcons.bellAndNote);
                break;
            }
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void configMatrix(){

    Menu menu(5);
    menu.setOption(0, "Display 0");
    menu.setOption(1, "Display 1");
    menu.setOption(2, "Display 2");
    menu.setOption(3, "Display 3");
    menu.setOption(4, "Back");
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
          configDisplay(0);
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          configDisplay(1);
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          configDisplay(2);
          menu.refresh();
          prevSelected = -1;
          break;
        case 3:
          configDisplay(3);
          menu.refresh();
          prevSelected = -1;
          break;
        case 4:
          // cleanup the mess before going back !
          MatrixManager.paint(0, 0, false, false, false, false);
          MatrixManager.paint(0, 3, false, false, false, false);
          MatrixManager.paint(3, 0, false, false, false, false);
          
          MatrixManager.paint(0, 4, false, false, false, false);
          MatrixManager.paint(0, 7, false, false, false, false);
          MatrixManager.paint(3, 7, false, false, false, false);
          
          MatrixManager.paint(4, 0, false, false, false, false);
          MatrixManager.paint(7, 0, false, false, false, false);
          MatrixManager.paint(7, 3, false, false, false, false);
          
          MatrixManager.paint(4, 7, false, false, false, false);
          MatrixManager.paint(7, 4, false, false, false, false);
          MatrixManager.paint(7, 7, false, false, false, false);
          
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
        
        MatrixManager.displayIcon(-1, MenuIcons.clean);
        
        MatrixManager.paint(0, 0, false, false, false, false);
        MatrixManager.paint(0, 3, false, false, false, false);
        MatrixManager.paint(3, 0, false, false, false, false);
        
        MatrixManager.paint(0, 4, false, false, false, false);
        MatrixManager.paint(0, 7, false, false, false, false);
        MatrixManager.paint(3, 7, false, false, false, false);
        
        MatrixManager.paint(4, 0, false, false, false, false);
        MatrixManager.paint(7, 0, false, false, false, false);
        MatrixManager.paint(7, 3, false, false, false, false);
        
        MatrixManager.paint(4, 7, false, false, false, false);
        MatrixManager.paint(7, 4, false, false, false, false);
        MatrixManager.paint(7, 7, false, false, false, false);
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.paint(0, 0, true, true, true, false);
            MatrixManager.paint(0, 3, true, true, false, true);
            MatrixManager.paint(3, 0, true, false, true, true);
            MatrixManager.paint(3, 3, false, true, true, true);
            break;
          case 1:
            MatrixManager.paint(0, 4, true, true, true, false);
            MatrixManager.paint(0, 7, true, true, false, true);
            MatrixManager.paint(3, 4, true, false, true, true);
            MatrixManager.paint(3, 7, false, true, true, true);
            break;
          case 2:
            MatrixManager.paint(4, 0, true, true, true, false);
            MatrixManager.paint(4, 3, true, true, false, true);
            MatrixManager.paint(7, 0, true, false, true, true);
            MatrixManager.paint(7, 3, false, true, true, true);
            break;
          case 3:
            MatrixManager.paint(4, 4, true, true, true, false);
            MatrixManager.paint(4, 7, true, true, false, true);
            MatrixManager.paint(7, 4, true, false, true, true);
            MatrixManager.paint(7, 7, false, true, true, true);
            break;
          case 4:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void setMute(){

    Menu menu(2);
    menu.setOption(0, "On");
    menu.setOption(1, "Off");
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
          SoundSystem.setMute(true);
          return;
        case 1:
          SoundSystem.setMute(false);
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.mute);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.speaker);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void setMenuSound(){

    Menu menu(4);
    menu.setOption(0, "Mute");
    menu.setOption(1, "Music");
    menu.setOption(2, "Effects");
    menu.setOption(3, "Both");
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
          MenuManager.setAudioOption(0);
          Device.printMessage("Menu audio:", "Muted !", messageDisplayTime);
          return;
        case 1:
          MenuManager.setAudioOption(1);
          Device.printMessage("Menu audio:", "Play music !", messageDisplayTime);
          return;
        case 2:
          MenuManager.setAudioOption(2);
          Device.printMessage("Menu audio:", "Play effects !", messageDisplayTime);
          return;
        case 3:
          MenuManager.setAudioOption(3);
          Device.printMessage("Menu audio:", "Music & Effects!", messageDisplayTime);
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.mute);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.musicNote);
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.bell);
            break;
          case 3:
            MatrixManager.displayIcon(-1, MenuIcons.bellAndNote);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void configDisplay(int displayNo){

    MatrixManager.displayIcon(-1, MenuIcons.clean);
    Menu menu(3);
    menu.setOption(0, "Type");
    menu.setOption(1, "Brightness");
    menu.setOption(2, "Back");
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
          setDisplayType(displayNo);
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          setDisplayBrightness(displayNo);
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          // cleanup the mess before return;
          MatrixManager.displayIcon(displayNo, MenuIcons.clean);
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            if(isEqual(MatrixManager.getMatrixArchitecture(displayNo), 'A')){
              MatrixManager.displayIcon(displayNo, MenuIcons.typeA);
            }else{
              MatrixManager.displayIcon(displayNo, MenuIcons.typeB);
            }
            break;
          case 1:
            MatrixManager.displayIcon(displayNo, MenuIcons.brightness);
            break;
          case 2:
            MatrixManager.displayIcon(displayNo, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void setDisplayType(int displayNo){

    Menu menu(2);
    menu.setOption(0, "As");
    menu.setOption(1, "Bs");
    menu.refresh();

    int prevSelected = -1;  // need to be different than selectedOption first time.
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case 0:
          MatrixManager.setMatrixArchitecture(displayNo, 'A');
          Device.printMessage("Matrix type: As", "Selected !", messageDisplayTime);
          return;
        case 1:
          MatrixManager.setMatrixArchitecture(displayNo, 'B');
          Device.printMessage("Matrix type: Bs", "Selected !", messageDisplayTime);
          return;
        default:  // no action -> nothing to do..
          break;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(displayNo, MenuIcons.typeA);
            break;
          case 1:
            MatrixManager.displayIcon(displayNo, MenuIcons.typeB);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void setDisplayBrightness(int displayNo){

    byte brightnessVal = MatrixManager.getMatrixIntensity(displayNo);
    Menu menu(1);
    menu.setOption(0, "      " + String(brightnessVal));
    menu.refresh();

    MatrixManager.displayIcon(displayNo, MenuIcons.brightness);
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case -4:  // Left
          if(isGreater(brightnessVal, byte(1))){
            brightnessVal--;
          }
          menu.setOption(0, "      " + String(brightnessVal));
          menu.refresh();
          break;
        case -5:  // Right
          if(isLesser(brightnessVal, byte(15))){
            brightnessVal++;
          }
          menu.setOption(0, "      " + String(brightnessVal));
          menu.refresh();
          break;
        case 0:
          MatrixManager.setMatrixIntensity(displayNo, brightnessVal);
          Device.printMessage("Brightness: " + String(brightnessVal), "Selected !", messageDisplayTime);
          return;
        default:  // no action -> nothing to do..
          break;
      }
    }
  }

  void diagnostics(){

    Menu menu(3);
    menu.setOption(0, "Inputs");
    menu.setOption(1, "Matrix");
    menu.setOption(2, "Back");
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
          diagInputs();
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          diagMatrix();
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          return;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.inputs);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.matrix);
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void diagInputs(){

    Menu menu(3);
    menu.setOption(0, "Left console");
    menu.setOption(1, "Right console");
    menu.setOption(2, "Back");
    menu.refresh();

    int prevSelected = -1;  // need to be different than selectedOption first time.
    
    while(true){
      
      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      switch(menu.gatherActions()){
        case 0:
          if(MenuManager.isLeftTheOwner()){
            Device.printMessage("Change owner", "in configuration", messageDisplayTime);
          }else{
            printInputs(true);
          }
          menu.refresh();
          prevSelected = -1;
          break;
        case 1:
          if(MenuManager.isLeftTheOwner()){
            printInputs(false);
          }else{
            Device.printMessage("Change owner", "in configuration", messageDisplayTime);
          }
          menu.refresh();
          prevSelected = -1;
          break;
        case 2:
          return;
        default:  // no action -> nothing to do..
          break;
      }

      if(isNotEqual(menu.getSelected(), prevSelected)){
            
        switch(menu.getSelected()){
          case 0:
            MatrixManager.displayIcon(-1, MenuIcons.left);
            break;
          case 1:
            MatrixManager.displayIcon(-1, MenuIcons.right);
            break;
          case 2:
            MatrixManager.displayIcon(-1, MenuIcons.back);
            break;
        }
        
        Set(prevSelected, menu.getSelected());
      }
    }
  }

  void printInputs(bool leftConsole){

    String space = "";
    String message = "";
    String prevMessage;
    
    while(true){

      Device.updateAll();

      MenuInputs.savePrevious();
      MenuInputs.load();

      Set(prevMessage, message);
      
      if(leftConsole){

        if(isLesser(InputManager.LCXValue(), 0)){
          space = "";
        }else{
          space = " ";
        }
        
        message = "B:" + String(InputManager.LCBtnValue()) + " J:" + String(InputManager.LCSWValue()) +
                  " X:" + String(InputManager.LCXValue()) + space + "Y:" + String(InputManager.LCYValue());
      }else{

        if(isLesser(InputManager.RCXValue(), 0)){
          space = "";
        }else{
          space = " ";
        }
        
        message = "B:" + String(InputManager.RCBtnValue()) + " J:" + String(InputManager.RCSWValue()) +
                  " X:" + String(InputManager.RCXValue()) + space + "Y:" + String(InputManager.RCYValue());
      }

      if(isNotEqual(prevMessage, message)){ // only update LCD when necessary !
        
        Device.printMessage(message, "~Back (owner)");
      }

      // Back action
      if(isEqual(MenuInputs.prevBtnValue, false) && isEqual(MenuInputs.btnValue, true)){
        SoundSystem.addSound(&Playlist.menuClickEffect); // SoundSystem automatically remove finished sounds in update method.
        return;
      }
    }
  }

  void diagMatrix(){

    MatrixManager.displayIcon(-1, MenuIcons.clean);
    
    const unsigned long stepTime = 25;
    
    for(int displayNr = 0; displayNr < 4; displayNr++){

      Device.printMessage("Display nr: " + String(displayNr), "Testing...");
      for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
          lc.setLed(displayNr, col, row, true); // turns on LED at col, row
          Device.wait(stepTime);
        }
      }
      for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
          lc.setLed(displayNr, col, row, false); // turns off LED at col, row
          Device.wait(stepTime);
        }
      }
    }
  }

  void credits(){
    
    MatrixManager.displayIcon(-1, MenuIcons.score);
    
    Device.printMessage("");  // to clear the screen; Args: String message1, String message2 = "", unsigned long duration = 0
    Device.animateTextLCD("Creator", 30, false, 0);  // Args: String text, unsigned long frameLength, bool leftRight = false, int row = 0
    Device.animateTextLCD("Dima Darius", 30, false, 1);
    Device.printMessage("Dima Darius");
    Device.animateTextLCD("----------------", 10, true, 1);
    Device.printMessage("----------------");
    Device.animateTextLCD("Teacher", 30, false, 1);
    Device.printMessage("Teacher");
    Device.animateTextLCD("Andrei Dumitriu", 30, false, 1);
    Device.printMessage("Andrei Dumitriu");
    Device.animateTextLCD("----------------", 10, true, 1);
    Device.printMessage("----------------");
    Device.animateTextLCD("Unibuc Robotics", 30, false, 1);
    Device.printMessage("Unibuc Robotics", "", 1200);

    MatrixManager.displayIcon(-1, MenuIcons.star);
  }
  
}MainMenu;


#ifdef DEBUG_ENABLED
void testingAndDebugging(){

/*
  Player P1 = Player(&Assets.player1);

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){

      MatrixManager.placeObject(&Assets.nothing, i, j);
    }
  }

  P1.spawn(6, 1);
  // MatrixManager.placeObject(&Assets.bomb, 1, 2);
  
  while(true){

    Device.updateAll();
    if(P1.isAlive() && !P1.isMoving()){
      P1.goUp();
    }

    if(P1.isAlive()){P1.update();}

    // Exploding bombs and cleaning up the waste:
    for(int row = 0; row < 8; row++){
      for(int col = 0; col < 8; col++){

        if((MatrixManager.getPosition(row, col)).isExpired()){
          
          // cleaning up the waste:
          if(isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.flame) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.leftMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.rightMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.upMoveStart) ||
                   isEqual((MatrixManager.getPosition(row, col)).getObject(), &Assets.downMoveStart)){

            MatrixManager.placeObject(&Assets.nothing, row, col);
          }
        }
        
      }
    }

  }
  */

  //MatrixManager.placeObject(&Assets.bomb, 1, 1);

  /*
  while(true){
    Device.updateAll();

    SoundSystem.addSound(&Playlist.bombExplodeEffect);
    // SoundSystem.addSound(&Playlist.itemPickUpEffect);
    Device.wait(4000);
  }
  */
}
#endif

void loop(){
  
  // testingAndDebugging();
  MainMenu.launcher();
  delay(1);
}
