void bmCredits(){

  // Since you clicked on this options it means you want to see the Credits !
  // It only takes 6 sec so you don't have the option to skip it. That is why delay is ok here.
  consoleTime = millis();
  while(1){
    if(millis() > consoleTime + 6000UL){
      break;
    }
    if(millis() > consoleTime + 5125UL){
      lcd.setCursor(0,0);
      lcd.print("Unibuc Robotics ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }else if(millis() > consoleTime + 4275UL){
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("Unibuc Robotics ");
    }else if(millis() > consoleTime + 3425UL){
      lcd.setCursor(0,0);
      lcd.print("Andrei Dumitriu ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }else if(millis() > consoleTime + 2575UL){
      lcd.setCursor(0,0);
      lcd.print("    Teacher:    ");
      lcd.setCursor(0,1);
      lcd.print("Andrei Dumitriu ");
    }else if(millis() > consoleTime + 1725UL){
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("    Teacher:    ");
    }else if(millis() > consoleTime + 875UL){
      lcd.setCursor(0,0);
      lcd.print("  Dima Darius   ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }else{
      lcd.setCursor(0,0);
      lcd.print("    Creator:    ");
      lcd.setCursor(0,1);
      lcd.print("  Dima Darius   ");
    }
    if(music == 1){
      playMenuSong();
    }
  }
}

void bombermanMenu(){

  int selected = 0;
  const int entries = 6;
  const String options[entries] = {"Single player", "Two players", "Settings", "High Scores", "Credits", "Quit"}; // Max 15 characters
  void *actions[entries] = {&bmSinglePlayer, &bmTwoPlayers, &bmSettings, &bmHighScores, &bmCredits, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void bmSinglePlayer(){

  int selected = 0;
  const int entries = 3;
  const String options[entries] = {"Start game", "Options", "Back"}; // Max 15 characters
  void *actions[entries] = {&bmSpStartGame, &bmSPOptions, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void bmSPOptions(){

  int selected = 0;
  const int entries = 3;
  const String options[entries] = {"Difficulty", "Bots", "Back"}; // Max 15 characters
  void *actions[entries] = {&setDifficulty, &setBmSpBots, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void setDifficulty(){

  const int entries = 6;
  const String options[entries] = {"Very easy", "Easy", "Normal", "Hard", "IMPOSIBLE !!!", "No! Just don't!"}; // Max 15 characters
  void *actions[entries] = {&returnTrigger, &returnTrigger, &returnTrigger, &returnTrigger, &returnTrigger, &returnTrigger};
  createMenu(difficulty, entries, options, actions);
  EEPROM.update(difficultyAdr, difficulty);
}

void setBmSpBots(){

  int selected = 0;
  const int entries = 3;
  const String options[entries] = {"1", "2", "3"}; // Max 15 characters
  void *actions[entries] = {&returnTrigger, &returnTrigger, &returnTrigger};
  createMenu(selected, entries, options, actions);
  EEPROM.update(bmSpBotsAdr, selected + 1);
}

void bmTwoPlayers(){

  int selected = 0;
  const int entries = 3;
  const String options[entries] = {"Start game", "Options", "Back"}; // Max 15 characters
  void *actions[entries] = {&bmTpStartGame, &bmTPOptions, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void bmTPOptions(){

  int selected = 0;
  const int entries = 3;
  const String options[entries] = {"Difficulty", "Bots", "Back"}; // Max 15 characters
  void *actions[entries] = {&setDifficulty, &setBmTpBots, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void setBmTpBots(){

  const int entries = 3;
  const String options[entries] = {"0", "1", "2"}; // Max 15 characters
  void *actions[entries] = {&returnTrigger, &returnTrigger, &returnTrigger};
  createMenu(bmTpBots, entries, options, actions);
  EEPROM.update(bmTpBotsAdr, bmTpBots);
}

void setMusic(){
  int selected = 0;
  const int entries = 2;
  const String options[entries] = {"Off", "On"}; // Max 15 characters
  void *actions[entries] = {&returnTrigger, &returnTrigger};
  createMenu(selected, entries, options, actions);
  music = selected;
  EEPROM.update(musicAdr, music);
}

void bmSettings(){

  int selected = 0;
  const int entries = 5;
  const String options[entries] = {"Player Name", "Bot dificulty", "Music", "Level", "Back"}; // Max 15 characters
  void *actions[entries] = {&setPlayerName, &setDifficulty, &setMusic, &selectLevel, &returnTrigger};
  createMenu(selected, entries, options, actions);
}

void setPlayerName(){
  
  prevC1Button = 1;
  
  clearLcdScreen();
  for(int i = 0; i < 10; i++){
    lcd.setCursor(i, 0);
    lcd.print(letters[bmPlayerName[i]]);
  }
  lcd.setCursor(0, 1);
  lcd.print("^");

  int selectedLetter = 0;
  int prevSelectedLetter = 0;

  while(1){

    readInputs();

    if(selectedLetter != prevSelectedLetter){
      lcd.setCursor(prevSelectedLetter, 1);
      lcd.print(" ");
      lcd.setCursor(selectedLetter, 1);
      lcd.print("^");
    }
    prevSelectedLetter = selectedLetter;

    if(c1JoyX == 'R' && prevC1JoyX == 'N'){
      if(selectedLetter < 9){
        selectedLetter++;
        playMenuSelect(); // Sound Effect
      }
    }else if(c1JoyX == 'L' && prevC1JoyX == 'N'){
      if(selectedLetter > 0){
        selectedLetter--;
        playMenuSelect(); // Sound Effect
      }
    }

    if(c1JoyY == 'U' && prevC1JoyY == 'N'){
      bmPlayerName[selectedLetter]++;
      if(bmPlayerName[selectedLetter] > 26){
        bmPlayerName[selectedLetter] = 0;
      }
      playMenuSelect(); // Sound Effect
      lcd.setCursor(selectedLetter, 0);
      lcd.print(letters[bmPlayerName[selectedLetter]]);
    }else if(c1JoyY == 'D' && prevC1JoyY == 'N'){
      bmPlayerName[selectedLetter]--;
      if(bmPlayerName[selectedLetter] < 0){
        bmPlayerName[selectedLetter] = 26;
      }
      playMenuSelect(); // Sound Effect
      lcd.setCursor(selectedLetter, 0);
      lcd.print(letters[bmPlayerName[selectedLetter]]);
    }
    if(c1Button == 1 && prevC1Button == 0){
      prevC1Button = 1;
      playMenuClick(); // Sound Effect
      saveBmPlayerName(); // Saves the new player name to EEPROM  using update method for each letter (because we care about EEPROM lifespan)
      return;
    }
    
    saveInputs(); // Saving last button states
      
    delay(1);
  }
}

void selectLevel(){

  const int entries = 14;
  const String options[entries] = {"Generate random", "Forest 1", "Forest 2", "Forest 3", "Forest 4", "Maze 1", "Maze 2", "Maze 3", "Maze 4", "Crates 1", "Crates 2", "Village 1", "Village 2", "Level editor"}; // Max 15 characters
  void *actions[entries];
  for(int i = 0; i < entries; i++){
    actions[i] = &returnTrigger;
  }
  createMenu(bmSelectedLv, entries, options, actions);
  EEPROM.update(bmSelectedLvAdr, bmSelectedLv);
  if(bmSelectedLv == 13){
        bmLvEdit();
  }
}

void bmHighScores(){

  int bmHSPanel = 0;
  int bmHSSelected = 0;
  const int bmHSEntries = 5;
  int lastBmHSSelected = -1;
  prevC1Button = 1;
  
  while(1){

    readInputs();
  
    if(bmHSSelected < bmHSPanel){
      bmHSPanel--;
    }else if(bmHSSelected > (bmHSPanel + 1)){ 
      bmHSPanel++;
    }
    
    if(bmHSSelected != lastBmHSSelected){ // No need to refresh the LCD if there is no change
      clearLcdScreen();

      for(int i = 0; i < 10; i++){
        lcd.setCursor(i + 1, 0);
        lcd.print(letters[bmHighScore[bmHSPanel][i]]);
      }
      lcd.setCursor(13, 0);
      lcd.print(scoreMultiply * bmHighScore[bmHSPanel][10]);
      for(int i = 0; i < 10; i++){
        lcd.setCursor(i + 1, 1);
        lcd.print(letters[bmHighScore[bmHSPanel + 1][i]]);
      }
      lcd.setCursor(13, 1);
      lcd.print(scoreMultiply * bmHighScore[bmHSPanel + 1][10]);
    
      if(bmHSSelected == bmHSPanel){
        lcd.setCursor(0,0);
        lcd.print("~");
      }else{
        lcd.setCursor(0,1);
        lcd.print("~");
      }
      
    }
      lastBmHSSelected = bmHSSelected;
  
    if(c1JoyY == 'D' && prevC1JoyY == 'N'){
      if(bmHSSelected < (bmHSEntries - 1)){
        bmHSSelected++;
        playMenuSelect(); // Sound Effect
      }
    }else if(c1JoyY == 'U' && prevC1JoyY == 'N'){
      if(bmHSSelected > 0){
        bmHSSelected--;
        playMenuSelect(); // Sound Effect
      }
    }
  
    if(c1Button == 1 && prevC1Button == 0){
      prevC1Button = 1;
      playMenuClick(); // Sound Effect
      return;
    }
    
    saveInputs(); // Saving last button states
      
    delay(1);
  }
}

void bmSpStartGame(){
  bombermanGame(0);
  
}

void bmTpStartGame(){
  bombermanGame(1);
}

void quitGame(){
  clearLcdScreen();
  int selected = 0;
  int lastSelected = 1;
  lcd.setCursor(0,0);
  lcd.print(" Are you sure ? ");
  lcd.setCursor(0,1);
  lcd.print("  Yes        No ");
  consoleTime = millis();
    while(1){
      readInputs();
      if(selected != lastSelected){ // No need to refresh the LCD if there is no change
        if (selected == 0){
          lcd.setCursor(12,1);
          lcd.print("~");
          lcd.setCursor(1,1);
          lcd.print(" ");
        }else{
          lcd.setCursor(12,1);
          lcd.print(" ");
          lcd.setCursor(1,1);
          lcd.print("~");
        }
      }
      lastSelected = selected;

      if(c1JoyX == 'L' && prevC1JoyX == 'N' && (millis() > consoleTime + inputsDefer)){
        consoleTime = millis();
        if(selected < 1){
          selected++;
          playMenuSelect(); // Sound Effect
        }else{
          playMenuEnd();  // Sound Effect
        }
      }else if(c1JoyX == 'R' && prevC1JoyX == 'N' && (millis() > consoleTime + inputsDefer)){
        consoleTime = millis();
        if(selected > 0){
          selected--;
          playMenuSelect(); // Sound Effect
        }else{
          playMenuEnd();  // Sound Effect
        }
      }

      if(c1Button == 1 && prevC1Button == 0 && (millis() > consoleTime + inputsDefer)){
        consoleTime = millis();
        prevC1Button = 1;
        playMenuClick(); // Sound Effect
        if(selected == 0){
          return;
        }else{
          for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
              place(obj[nothing], pos[i][j]);
              render(pos[i][j]);
            }
          }
          loop();
        }
      }
      saveInputs();
      if(music == 1){
        playMenuSong();
      }
    }
}

void pause(){

  int selected = 0;
  const int entries = 2;
  const String options[entries] = {"Resune", "Quit"}; // Max 15 characters
  void *actions[entries] = {&returnTrigger, &quitGame};
  createMenu(selected, entries, options, actions);
}
