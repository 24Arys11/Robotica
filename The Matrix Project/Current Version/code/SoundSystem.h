#ifndef SOUNDSYSTEM_H_INCLUDED
#define SOUNDSYSTEM_H_INCLUDED

#include <stdarg.h>


const int buzzerPin = 25;

const int trackListCapacity = 30;


static struct Tempo{

  const int precisionFactor = 10; // to avoid having a float for the duration, we multiply by 10.
  
  // One measure is 4 beats ! Measure = 10000 => a beat occurs every 2500ms (2.5 sec) => 24 bpm
  const int larghissimo = precisionFactor * 10000; // 24 bpm - very very slow
  const int grave = precisionFactor * 8000; // 30 bpm - very slow
  const int largo = precisionFactor * 6000; // 40 bpm - broadly
  const int lento = precisionFactor * 4800; // 50 bpm - slowly
  const int larghetto = precisionFactor * 4000; // 60 bpm - rather broadly
  const int adagio = precisionFactor * 3600; // 66.(6) bpm - slow and stately
  const int adagietto = precisionFactor * 3200; // 75 bpm - slower than andante
  const int andante = precisionFactor * 3000; // 80 bpm - at a walking pace
  const int andantino = precisionFactor * 2560; // 93.75 bpm - also use for: [andanteModerato]
  const int marciaModerato = precisionFactor * 2856; // ~84.034 bpm - moderately, in the manner of a march
  const int moderato = precisionFactor * 2400; // 100 bpm
  const int allegretto = precisionFactor * 2096; // ~109.09 bpm - moderately fast 
  const int allegroModerato = precisionFactor * 2000; // 120 bpm - close to but not quite allegro
  const int allegro = precisionFactor * 1600; // 150 bpm - fast, quickly, and bright
  const int vivacissimo = precisionFactor * 1380; // ~173.91 bpm - very fast - also use for: [vivace] and [allegrissimo]
  const int presto = precisionFactor * 1280; // 187.5 bpm - – very, very fast
  const int prestissimo = precisionFactor * 1200; // 200 bpm - even faster than Presto
  const int insanity = precisionFactor * 800; // 300 bpm - bonus !
}Tempo;


class Sound{  // could be a song or a sound effect

private:
  
  int tempo;
  int *notes;
  int *durations;

  int nrOfNotes;
  int currentNote;
  unsigned long nextIntervention;
  
  int priority; // only the highest priority sound will be played.
  bool repeat;
  bool stopped;

public:

  #ifdef DEBUG_SOUND
  String songName;
  #endif

  Sound(int nrOfNotes){   /// CONSTRUCTOR

    Set(this->nrOfNotes, nrOfNotes);
    notes = new int[nrOfNotes];
    durations = new int[nrOfNotes];
    
    Set(repeat, false);
    Set(stopped, false);
    Set(currentNote, -1); // first time "update()" is called, currentNote increments by 1 !
  }

  ~Sound(){   /// DECONSTRUCTOR

    delete[] notes;
    delete[] durations;
  }

  void defineNotes(int nrOfNotes, ...){

    if(isNotEqual(this->nrOfNotes, nrOfNotes)){
      return;
    }
    
    va_list valist;
    va_start(valist, nrOfNotes);  // initialize valist for nrOfNotes number of arguments
    for (int i = 0; i < nrOfNotes; i++) {   // access all the arguments assigned to valist
      Set(notes[i], va_arg(valist, int));
    }
    va_end(valist); // clean memory reserved for valist
  }

  void defineDuration(int nrOfNotes, ...){

    if(isNotEqual(this->nrOfNotes, nrOfNotes)){
      return;
    }
    va_list valist;
    va_start(valist, nrOfNotes);  // initialize valist for nrOfNotes number of arguments
    for (int i = 0; i < nrOfNotes; i++) {   // access all the arguments assigned to valist
      Set(durations[i], va_arg(valist, int));
    }
    va_end(valist); // clean memory reserved for valist
  }

  void setTempo(int tempo){
    Set(this->tempo, tempo);
  }

  void setPriority(int priority){
    Set(this->priority, priority);
  }

  int getPriority(){
    return priority;
  }

  void setRepeat(bool repeat){
    Set(this->repeat, repeat);
  }

  void start(){
    
    Set(currentNote, -1); // first time "update()" is called, currentNote increments by 1 !
    Set(stopped, false);
    Set(nextIntervention, millis());
  }

  void stop(){

    Set(stopped, true);
    Set(currentNote, nrOfNotes - 1);  // unnecessary, but as a safety measure, we prevent "currentNote" to go outside of "notes" array !
  }

  bool isStopped(){
    
    return stopped;
  }

  void update(){
    
    currentNote++;
    
    if(isGreater(currentNote, nrOfNotes - 1)){  // At the end of the song:

      // if it repeats, reset to the first note, else stop the song !
      switch(repeat) {
        case true:
          Set(currentNote, 0);
          break;
        case false:
          stop();
          return;
      }
    }

    Set(nextIntervention, millis() + (tempo / durations[currentNote]));
    
    if(isGreater(millis(), nextIntervention)){  // in case a song is more than one note behind.
      update();
    }
  }

  bool needAttention(){

    if(stopped || isLesser(millis(), nextIntervention)){
      return false;
    }
    return true;
  }

  int theCurrentNote(){

    return notes[currentNote];
  }

  void accountForPause(unsigned long pausedTime){

    nextIntervention += pausedTime;
  }

};


static class TrackList{  // TrackList can hold 30 songs references, prealocated to protect the Arduino.

private:

  int nrOfElements;
  Sound* list[trackListCapacity];
  int currentPosition;

  int iteratorForward(int iter){
    
    iter++;
    if(isGreater(iter, trackListCapacity - 1)){
      return 0;
    }
    return iter;
  }
  
  int iteratorBackward(int iter){
    
    iter--;
    if(isLesser(iter, 0)){
      return trackListCapacity - 1;
    }
    return iter;
  }

public:

  TrackList(){  /// CONSTRUCTOR

    Set(nrOfElements, 0);
    Set(currentPosition, 0);

    for(int i = 0; i < trackListCapacity; i++){
      list[i] = NULL;
    }
  }

  int numel(){  // returns the number of elements (name inspired from pyTorch :D )

    return nrOfElements;
  }

  bool isEmpty(){

    if(isEqual(nrOfElements, 0)){
      return true;
    }
    return false;
  }

  void insert(Sound *song){

    #ifdef DEBUG_SOUND
    Serial.print("Inserting: ");
    if(isNull(song)){
      Serial.println("NULL");
    }else{
      Serial.println(song->songName);
    }
    #endif
    
    if(isGreater(nrOfElements, trackListCapacity - 1)){
      return;
    }
    
    Set(list[currentPosition], song);
    Set(currentPosition, iteratorForward(currentPosition));
    nrOfElements++;
  }

  Sound* at(int position){

    return list[position % trackListCapacity];
  }

  void cleanUp(){ // Remove all stopped songs from TrackList

    Sound* backupList[trackListCapacity];
    for(int i = 0; i < trackListCapacity; i++){
      Set(backupList[i], list[i]);
    }

    int iterator = 0;
    
    // Adding the valid elements to the beginning list.
    for(int i = currentPosition; i != iteratorBackward(currentPosition); i = iteratorForward(i)){
      
      if(!(backupList[i])->isStopped()){
        
        Set(list[iterator], backupList[i]);
        iterator++;
      }
    }

    Set(nrOfElements, iterator);
    
    if(isLesser(iterator, trackListCapacity)){
      Set(currentPosition, iterator);
    }else{
      Set(currentPosition, 0);
    }
    
    // Filling the end of the list with NULL elements.
    for(int i = iterator; i < trackListCapacity; i++){
      
      list[i] = NULL;
    }
  }

  Sound* topDog(){ // Returns the song with the highest priority

    if(isEqual(nrOfElements, 0)){
      return NULL;
    }
    
    Sound* topDog = list[0];
    
    for(int i = 0; i < nrOfElements; i++){

      if(isNotNull(list[i])){
        
        if(isNull(topDog)){
          Set(topDog, list[i]);
          continue;
        }
        
        if(isGreater((list[i])->getPriority(), topDog->getPriority())){
          Set(topDog, list[i]);
        }
      }
    }
    
    return topDog;
  }

}TrackList;


static class SoundSystem{

private:

  // Buzzer can only play the highest priority song. (like layers in a picture, the front layer cover the rest)
  Sound *currentSong; // the highest priority song
  unsigned long pausedTime;
  bool mute;
  
  void sillance(){
    noTone(buzzerPin);
  }

  void play(int note){

    #ifdef DEBUG_SOUND
    Serial.print("play (");
    Serial.print(note);
    Serial.println(")");
    #endif

    if(!mute){
      tone(buzzerPin, note);
    }
  }

  bool isTracked(Sound *song){

    int nrOfTrackedSongs = TrackList.numel();
    
    for(int i = 0; i < nrOfTrackedSongs; i++){
      if(isEqual(TrackList.at(i), song)){
        return true;
      }
    }
    return false;
  }

  Sound* beginElections(){

    #ifdef DEBUG_SOUND
    Serial.print("currentSong: ");
    if(isNull(currentSong)){
      Serial.println("NULL");
    }else{
      Serial.println(currentSong->songName);
      Serial.print("isStopped: ");
      Serial.println(currentSong->isStopped());
    }
    printTrackList();
    #endif
    
    sillance();
    currentSong = NULL;
    
    if(TrackList.isEmpty()){
      return NULL;
    }

    currentSong = TrackList.topDog();

    TrackList.cleanUp(); // Removes any stopped song from trackedSongs

    return currentSong;
  }
  
  #ifdef DEBUG_SOUND
  void printTrackList(){
    
    Serial.println("TrackList:");
    for(int i = 0; i < trackListCapacity; i++){

      if(isNotNull(TrackList.at(i))){
        Serial.print((TrackList.at(i))->songName);
      }else{
        Serial.print("NULL");
      }
      
      Serial.print("; ");
    }
    Serial.println("");
  }
  #endif
  
public:

  SoundSystem(){

    currentSong = NULL;
    Set(mute, EEPROMManager.isAudioMute());
  }

  void initialize(){
    
    pinMode(buzzerPin, OUTPUT);
  }

  bool isMute(){
    return mute;
  }

  void setMute(bool value){

    Set(mute, value);
    EEPROMManager.setAudioMute(value);
  }

  void addSound(Sound *candidate){
    
    #ifdef DEBUG_SOUND
    Serial.print("adding ");
    Serial.println(candidate->songName);
    #endif
    
    candidate->start();
    
    if(isNull(currentSong)){
      Set(currentSong, candidate);
      
      return;
    }
    
    if(isGreater(candidate->getPriority(), currentSong->getPriority())){

      // currentSong falls into trackedSongs and candidate becomes the currentSong.
      if(!isTracked(currentSong)){
        TrackList.insert(currentSong);
      }
      Set(currentSong, candidate);
      
      return;
    }
      
    // candidate gets into trackedSongs
    if(!isTracked(candidate)){
      TrackList.insert(candidate);
    }
  }

  void removeSound(Sound *candidate){
    
    #ifdef DEBUG_SOUND
    Serial.print("removing ");
    Serial.println(candidate->songName);
    #endif
    
    candidate->stop();
  }

  void update(){

    if(isNull(currentSong)){

      // pick the currentSong
      if(isNull(beginElections())){ // if failed => no candidates
        return;
      }
      
    }else if(currentSong->isStopped()){

      // pick the currentSong
      if(isNull(beginElections())){ // if failed => no candidates
        return;
      }
      
    }else if(currentSong->needAttention()){
      
      currentSong->update();
      
      if(!currentSong->isStopped()){ // after update, it might reach the end of the song
        sillance();
        play(currentSong->theCurrentNote());
      }
    }
  }

  void pauseAudio(){
    
    sillance();
    Set(pausedTime, millis());
  }

  void resumeAudio(){
    
    Set(pausedTime, millis() - pausedTime);

    if(!TrackList.isEmpty()){

      int nrOfTrackedSongs = TrackList.numel();
      for(int i = 0; i < nrOfTrackedSongs; i++){
        
        (TrackList.at(i))->accountForPause(pausedTime);
      }
    }

    if(isNotNull(currentSong)){

      currentSong->accountForPause(pausedTime);
      
      if(currentSong->isStopped()){

        // pick the currentSong
        if(isNull(beginElections())){ // if failed => no candidates
          return;
        }
      }
      
      play(currentSong->theCurrentNote());
    }
  }

}SoundSystem;


#endif /// SOUNDSYSTEM_H_INCLUDED
