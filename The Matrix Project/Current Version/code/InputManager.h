#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED


const int leftConsoleBtnPin = 51;
const int leftConsoleSwPin = 53;
const int leftConsoleXPin = A6;
const int leftConsoleYPin = A7;

const int rightConsoleBtnPin = 52;
const int rightConsoleSwPin = 50;
const int rightConsoleXPin = A5;
const int rightConsoleYPin = A4;

const unsigned long debounceTime = 50;
const int sensitivityLevels = 4; // for Joystick X and Y axies, 4 means they get mapped from -4 to +4 !


class DebouncedBtn{

private:

  unsigned long beginPressTime;
  bool persistentPress;
  bool validatedPress;

public:

  DebouncedBtn(){ /// CONSTRUCTOR
    Set(persistentPress, false);
    Set(validatedPress, false);
  }

  void feedValue(int btnRead){

    if(isEqual(btnRead, 0)){
      Set(persistentPress, false);
      Set(validatedPress, false);
      return;
    }
    // btnRead is 1 !
    // Case 1: Btn got pressed just now
    if(isEqual(persistentPress, false)){
      Set(beginPressTime, millis());
      Set(persistentPress, true);
      return;
    }
    
    // Case 2: Btn is pressed for longer than debounceTime
    if(isEqual(persistentPress, true) && isGreater(millis(), beginPressTime + debounceTime)){
      Set(validatedPress, true);
    }
    
    // Case 3: Btn is pressed but no longer than debounceTime => doNothing();
  }

  bool state(){
    return validatedPress;
  }
  
};


class ResponsiveScale{

private:

  int value;

public:

  ResponsiveScale(){
    Set(value, 0);
  }

  void feedValue(int axisRead){

    int levels = sensitivityLevels + 2; // 1 for safe zone expansion and 1 for border zone expansion.
    int pos = map(axisRead, 0, 1024, 0 - levels, levels);
    /// outcome example (sensitivityLevels = 4): [  -6| -5| -4| -3| -2| -1| 0 | 1 | 2 | 3 | 4 | 5 | 6]
    //  Expanding safe zone range (position 0), to account for joystick potential deviation.
    if(isLesser(pos, 0)){
      pos++;
    }
    if(isGreater(pos, 0)){
      pos--;
    }
    /// outcome example (sensitivityLevels = 4): [  -5| -4| -3| -2| -1| 0 | 0 | 0 | 1 | 2 | 3 | 4 | 5]
    //  Expanding border zone range, to account for joystick potential deviation.
    if(isLesser(pos, 0 - sensitivityLevels)){
      Set(pos, 0 - sensitivityLevels);
    }
    if(isGreater(pos, sensitivityLevels)){
      Set(pos, sensitivityLevels);
    }
    /// outcome example (sensitivityLevels = 4): [  -4| -4| -3| -2| -1| 0 | 0 | 0 | 1 | 2 | 3 | 4 | 4]
    
    Set(value, pos);
  }

  int state(){
    return value;
  }
  
};


static class InputManager{

private:

  DebouncedBtn leftConsoleBtn;
  DebouncedBtn leftConsoleSW;
  ResponsiveScale leftConsoleAxisX;
  ResponsiveScale leftConsoleAxisY;

  DebouncedBtn rightConsoleBtn;
  DebouncedBtn rightConsoleSW;
  ResponsiveScale rightConsoleAxisX;
  ResponsiveScale rightConsoleAxisY;

public:

  InputManager(){   /// CONSTRUCTOR
    update();
  }

  void initialize(){

    pinMode(leftConsoleBtnPin, INPUT);
    pinMode(leftConsoleSwPin, INPUT_PULLUP);
    pinMode(rightConsoleBtnPin, INPUT);
    pinMode(rightConsoleSwPin, INPUT_PULLUP);
  }

  #ifdef DEBUG_INPUTS
  void leftConsoleInputTest(){
    
    Serial.print("Btn: ");
    Serial.print(LCBtnValue());
    Serial.print(" | Switch: ");
    Serial.print(LCSWValue());
    Serial.print(" | X: ");
    Serial.print(LCXValue());
    Serial.print(" | Y: ");
    Serial.print(LCYValue());
    Serial.println(" |");
    delay(100);
  }

  void rightConsoleInputTest(){
    
    Serial.print("Btn: ");
    Serial.print(RCBtnValue());
    Serial.print(" | Switch: ");
    Serial.print(RCSWValue());
    Serial.print(" | X: ");
    Serial.print(RCXValue());
    Serial.print(" | Y: ");
    Serial.print(RCYValue());
    Serial.println(" |");
    delay(100);
  }
  #endif

  void update(){

    leftConsoleBtn.feedValue(digitalRead(leftConsoleBtnPin));
    leftConsoleSW.feedValue(!digitalRead(leftConsoleSwPin));  // (!) because is pullup
    leftConsoleAxisX.feedValue(analogRead(leftConsoleXPin));
    leftConsoleAxisY.feedValue(analogRead(leftConsoleYPin));
    
    rightConsoleBtn.feedValue(digitalRead(rightConsoleBtnPin));
    rightConsoleSW.feedValue(!digitalRead(rightConsoleSwPin));  // (!) because is pullup
    rightConsoleAxisX.feedValue(analogRead(rightConsoleXPin));
    rightConsoleAxisY.feedValue(analogRead(rightConsoleYPin));
  }

  bool LCBtnValue(){
    return leftConsoleBtn.state();
  }

  bool LCSWValue(){
    return leftConsoleSW.state();
  }

  int LCXValue(){
    return leftConsoleAxisX.state();
  }

  int LCYValue(){
    return leftConsoleAxisY.state();
  }

  bool RCBtnValue(){
    return rightConsoleBtn.state();
  }

  bool RCSWValue(){
    return rightConsoleSW.state();
  }

  int RCXValue(){
    return rightConsoleAxisX.state();
  }

  int RCYValue(){
    return rightConsoleAxisY.state();
  }

}InputManager;


static struct GeneralInputs{
  
  bool prevLeftBtnValue;
  bool prevLeftSWValue;
  int prevLeftXAxisValue;
  int prevLeftYAxisValue;
  
  bool leftBtnValue;
  bool leftSWValue;
  int leftXAxisValue;
  int leftYAxisValue;
  
  bool prevRightBtnValue;
  bool prevRightSWValue;
  int prevRightXAxisValue;
  int prevRightYAxisValue;
  
  bool rightBtnValue;
  bool rightSWValue;
  int rightXAxisValue;
  int rightYAxisValue;

  void savePrevious(){
    
    Set(prevLeftBtnValue, leftBtnValue);
    Set(prevLeftSWValue, leftSWValue);
    Set(prevLeftXAxisValue, leftXAxisValue);
    Set(prevLeftYAxisValue, leftYAxisValue);
    
    Set(prevRightBtnValue, rightBtnValue);
    Set(prevRightSWValue, rightSWValue);
    Set(prevRightXAxisValue, rightXAxisValue);
    Set(prevRightYAxisValue, rightYAxisValue);
  }

  void load(){
    
    Set(leftBtnValue, InputManager.LCBtnValue());
    Set(leftSWValue, InputManager.LCSWValue());
    Set(leftXAxisValue, InputManager.LCXValue());
    Set(leftYAxisValue, InputManager.LCYValue());
    
    Set(rightBtnValue, InputManager.RCBtnValue());
    Set(rightSWValue, InputManager.RCSWValue());
    Set(rightXAxisValue, InputManager.RCXValue());
    Set(rightYAxisValue, InputManager.RCYValue());
  }
  
}GeneralInputs;


#endif /// INPUTMANAGER_H_INCLUDED
