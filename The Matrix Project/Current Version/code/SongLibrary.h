#ifndef SONGSLIBRARY_H_INCLUDED
#define SONGSLIBRARY_H_INCLUDED

#include "pitches.h"


static struct Playlist{

  Sound welcomeSong = Sound(41);
  Sound keyboardCat = Sound(59);
  Sound menuNavEffect = Sound(1);
  Sound menuEndEffect = Sound(1);
  Sound menuClickEffect = Sound(1);
  Sound walkEffect = Sound(1);
  Sound bombBipEffect = Sound(1);
  Sound bombExplodeEffect = Sound(4);
  Sound itemPickUpEffect = Sound(2);
  
  /*  // More songs - Could be useful for a future game (CAUTION ! songs are memory hungry, and they are allocated dynamically)
  Sound vampireKiller = Sound(126);
  Sound takeOnMe = Sound(96);
  Sound tetris = Sound(99);
  */

  void loadPlaylist(){
    
    // Although I have not used his code, I would not have found the scores below
    // if not for Robson Couto's github: https://github.com/robsoncouto/arduino-songs
    
    // Pink Panther theme
    // Score available at https://musescore.com/benedictsong/the-pink-panther
    // Theme by Masato Nakamura, arranged by Teddy Mason
    welcomeSong.defineNotes(41, NOTE_DS4, NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
                            NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4,
                            NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4,
                            REST, REST, NOTE_DS4, NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST,
                            NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4,
                            NOTE_B4, NOTE_E5, NOTE_DS5, NOTE_D5, REST);
    // measures are multiplied by 10 for precision. 40 = 1 beat (1/4 measures); 27 = 1.5 beats (40 / 1.5 = 26.(6))
    // 80 = 1/2 beats (1/8 measures); 160 = 1/4 beats (1/16 measures); 107 = 1/16 measures with a dot (*1.5)
    welcomeSong.defineDuration(41, 80, 27, 80, 80, 27, 80, 80, 53, 80, 53, 80, 53, 80, 53, 80,
                                   20, 107, 107, 107, 107, 20, 40, 80, 40, 27, 80, 80, 27, 80,
                                   80, 53, 80, 53, 80, 53, 80, 53, 80, 10, 20, 40);
    welcomeSong.setTempo(Tempo.allegroModerato);
    welcomeSong.setPriority(0);
    welcomeSong.setRepeat(false);
    
    // Keyboard cat
    // Score available at https://musescore.com/user/142788/scores/147371
    keyboardCat.defineNotes(59, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4,
                            NOTE_E4, NOTE_G4, NOTE_E4, NOTE_A3, NOTE_C4, NOTE_E4, NOTE_C4,
                            NOTE_A3, NOTE_C4, NOTE_E4, NOTE_C4, NOTE_G3, NOTE_B3, NOTE_D4,
                            NOTE_B3, NOTE_G3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_G3, NOTE_G3,
                            NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3,
                            NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4,
                            NOTE_E4, NOTE_A3, NOTE_C4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_C4,
                            NOTE_E4, NOTE_C4, NOTE_G3, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_G3,
                            NOTE_B3, NOTE_D4, NOTE_B3, NOTE_G3, REST);
    // measures are multiplied by 10 for precision. 40 = 1 beat (1/4 measures); 27 = 1.5 beats (40 / 1.5 = 26.(6))
    // 80 = 1/2 beats (1/8 measures); 160 = 1/4 beats (1/16 measures); 107 = 1/16 measures with a dot (*1.5)
    keyboardCat.defineDuration(59, 40, 40, 40, 40, 40, 40, 27, 40, 40, 40, 40, 40, 40, 80,
                                    27, 40, 40, 40, 40, 40, 40, 80, 27, 40, 40, 80, 27, 80,
                                    40, 40, 40, 80, 40, 40, 40, 40, 40, 40, 80, 27, 40, 40,
                                    40, 40, 40, 40, 80, 27, 40, 40, 40, 40, 40, 40, 80, 27,
                                    40, 10, 20);  // last 2 notes differ slightly from original to sound better on the buzzer !
    keyboardCat.setTempo(Tempo.allegro);
    keyboardCat.setPriority(0);
    keyboardCat.setRepeat(true);

    menuNavEffect.defineNotes(1, NOTE_FS4);
    menuNavEffect.defineDuration(1, 214);
    menuNavEffect.setTempo(Tempo.allegroModerato);
    menuNavEffect.setPriority(1);
    menuNavEffect.setRepeat(false);

    menuEndEffect.defineNotes(1, NOTE_GS3);
    menuEndEffect.defineDuration(1, 214);
    menuEndEffect.setTempo(Tempo.allegroModerato);
    menuEndEffect.setPriority(1);
    menuEndEffect.setRepeat(false);

    menuClickEffect.defineNotes(1, NOTE_DS4);
    menuClickEffect.defineDuration(1, 214);
    menuClickEffect.setTempo(Tempo.allegroModerato);
    menuClickEffect.setPriority(1);
    menuClickEffect.setRepeat(false);

    walkEffect.defineNotes(1, NOTE_FS3);
    walkEffect.defineDuration(1, 320);
    walkEffect.setTempo(Tempo.allegroModerato);
    walkEffect.setPriority(1);
    walkEffect.setRepeat(false);

    bombBipEffect.defineNotes(1, NOTE_G5);
    bombBipEffect.defineDuration(1, 320);
    bombBipEffect.setTempo(Tempo.allegroModerato);
    bombBipEffect.setPriority(2);
    bombBipEffect.setRepeat(false);

    bombExplodeEffect.defineNotes(4, NOTE_A4, NOTE_B4, NOTE_G3, NOTE_AS4);
    bombExplodeEffect.defineDuration(4, 214, 160, 160, 80);
    bombExplodeEffect.setTempo(Tempo.allegroModerato);
    bombExplodeEffect.setPriority(4);
    bombExplodeEffect.setRepeat(false);

    itemPickUpEffect.defineNotes(2, NOTE_F4, NOTE_AS5);
    itemPickUpEffect.defineDuration(2, 320, 160);
    itemPickUpEffect.setTempo(Tempo.allegroModerato);
    itemPickUpEffect.setPriority(3);
    itemPickUpEffect.setRepeat(false);

    /*  // More songs - Could be useful for a future game
    // Vamire Killer, from castlevania
    // Score available at https://musescore.com/user/28972071/scores/5425616
    vampireKiller.defineNotes(126, NOTE_E5, NOTE_E5, NOTE_D5, REST, NOTE_CS5, NOTE_E4, NOTE_FS4,
                                   NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_A4, NOTE_D5,
                                   NOTE_E5, NOTE_E5, NOTE_D5, REST, NOTE_CS5, NOTE_E4, NOTE_FS4,
                                   NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_A4, NOTE_D4,
                                   REST, NOTE_E5, REST, NOTE_B5, REST, NOTE_AS5, NOTE_B5, NOTE_AS5,
                                   NOTE_G5, REST, NOTE_B5, NOTE_B5, NOTE_AS5, REST, NOTE_AS5,
                                   NOTE_A5, REST, NOTE_B5, NOTE_G5, NOTE_B5, NOTE_AS5, REST,
                                   NOTE_B5, NOTE_A5, NOTE_G5, REST, NOTE_E5, REST, NOTE_B5, REST,
                                   NOTE_AS5, NOTE_B5, NOTE_AS5, NOTE_G5, REST, NOTE_B5, NOTE_B5,
                                   NOTE_AS5, REST, NOTE_AS5, NOTE_A5, REST, NOTE_B5, NOTE_G5,
                                   NOTE_B5, NOTE_AS5, REST, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_DS4,
                                   NOTE_FS4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_E4, NOTE_DS4, NOTE_FS4,
                                   NOTE_C5, NOTE_B4, NOTE_G4, REST, NOTE_DS4, NOTE_FS4, NOTE_C5,
                                   NOTE_B4, NOTE_G4, NOTE_E4, NOTE_DS4, NOTE_FS4, NOTE_C5, NOTE_B4,
                                   NOTE_CS5, NOTE_DS5, NOTE_E5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_C4,
                                   NOTE_C4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_FS4, NOTE_A4,
                                   NOTE_E5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_E4,
                                   NOTE_G4, NOTE_D4, NOTE_D4, NOTE_B3, NOTE_D4);
    // measures are multiplied by 10 for precision. 40 = 1 beat (1/4 measures); 27 = 1.5 beats (40 / 1.5 = 26.(6))
    // 80 = 1/2 beats (1/8 measures); 160 = 1/4 beats (1/16 measures); 107 = 1/16 measures with a dot (*1.5)
    vampireKiller.defineDuration(126, 160, 80, 160, 160, 27, 80, 160, 160, 160, 53, 53, 80, 160, 27,
                                      160, 80, 160, 160, 27, 80, 160, 160, 160, 53, 53, 80, 160, 27,
                                      80, 80, 160, 160, 80, 160, 160, 160, 160, 40, 80, 160, 160, 160,
                                      160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 80, 80,
                                      160, 160, 80, 160, 160, 160, 160, 40, 80, 160, 160, 160, 160,
                                      160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 53, 53, 80,
                                      53, 53, 80, 53, 53, 80, 53, 53, 80, 53, 53, 80, 53, 53, 80, 53,
                                      53, 80, 53, 53, 80, 160, 160, 160, 14, 80, 80, 160, 53, 80, 80,
                                      160, 53, 160, 160, 160, 14, 80, 80, 160, 53, 80, 80, 160, 53);
    vampireKiller.setTempo(Tempo.allegroModerato);
    vampireKiller.setPriority(0);
    vampireKiller.setRepeat(true);

    // Take on me, by A-ha
    // Score available at https://musescore.com/user/27103612/scores/4834399
    // Arranged by Edward Truong
    takeOnMe.defineNotes(96, NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,
                             REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
                             NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
                             REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5,
                             NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,
                             REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
                             NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
                             REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5,
                             NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,
                             REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
                             NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
                             REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5);
    // measures are multiplied by 10 for precision. 40 = 1 beat (1/4 measures); 27 = 1.5 beats (40 / 1.5 = 26.(6))
    // 80 = 1/2 beats (1/8 measures); 160 = 1/4 beats (1/16 measures); 107 = 1/16 measures with a dot (*1.5)
    takeOnMe.defineDuration(96, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
                                80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
                                80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
                                80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
                                80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
                                80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80);
    takeOnMe.setTempo(Tempo.allegro);
    takeOnMe.setPriority(0);
    takeOnMe.setRepeat(true);

    //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
    tetris.defineNotes(99, NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4,
                           NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
                           NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_F5,
                           NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
                           NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,
                           REST, NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4,
                           NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5,
                           NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5,
                           NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5,
                           NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4,
                           NOTE_A4, REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_A4,
                           NOTE_GS4, NOTE_B4, REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_C5,
                           NOTE_E5, NOTE_A5, NOTE_GS5);
    tetris.defineDuration(99, 40, 80, 80, 40, 80, 80, 40, 80, 80, 40, 80, 80, 27, 80, 40, 40,
                              40, 40, 80, 40, 80, 80, 27, 80, 40, 80, 80, 27, 80, 40, 80, 80,
                              40, 80, 80, 40, 40, 40, 40, 40, 40, 40, 80, 80, 40, 80, 80, 40,
                              80, 80, 40, 80, 80, 27, 80, 40, 40, 40, 40, 80, 40, 80, 80, 27,
                              80, 40, 80, 80, 27, 80, 40, 80, 80, 40, 80, 80, 40, 40, 40, 40,
                              40, 40, 20, 20, 20, 20, 20, 20, 20, 40, 80, 20, 20, 20, 20, 40,
                              40, 20, 20);
    tetris.setTempo(Tempo.allegroModerato);
    tetris.setPriority(0);
    tetris.setRepeat(true);
    */

    #ifdef DEBUG_SOUND
    welcomeSong.songName = "welcomeSong";
    keyboardCat.songName = "keyboardCat";
    menuNavEffect.songName = "menuNavEffect";
    menuEndEffect.songName = "menuEndEffect";
    menuClickEffect.songName = "menuClickEffect";
    walkEffect.songName = "walkEffect";
    bombBipEffect.songName = "bombBipEffect";
    bombExplodeEffect.songName = "bombExplodeEffect";
    itemPickUpEffect.songName = "itemPickUpEffect";
    
    /*  // More songs - Could be useful for a future game
    vampireKiller.songName = "vampireKiller";
    takeOnMe.songName = "takeOnMe";
    tetris.songName = "tetris";
    */
    #endif
    
  }
  
}Playlist;


#endif /// SONGSLIBRARY_H_INCLUDED
