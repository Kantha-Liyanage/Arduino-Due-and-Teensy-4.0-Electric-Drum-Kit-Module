//Drum Pads Note numbers
//These are the number values that are sent via Serial output to the Teensy board.
byte SNARE        = 0;
byte BASS         = 1;
byte SNARE_TWO    = 2;
byte HIGH_TOM     = 3;
byte MID_TOM      = 4;
byte LOW_TOM      = 5;
byte CYMBAL_ONE   = 6;
byte CYMBAL_TWO   = 7;
byte CYMBAL_THREE = 8;
byte PERCUSSION   = 9;

//Two characters assinged to drum kits navation buttons
char KIT_UP      = '+';
char KIT_DOWN    = '-';
char kitsUpDownFlag = 'X';

//Note statues
bool isSnarePlayed       = true;
bool isBassPlayed        = true;
bool isSnareTwoPlayed    = true;
bool isHighTomPlayed     = true;
bool isMidTomPlayed      = true;
bool isLowTomPlayed      = true;
bool isCymbalOnePlayed   = true;  
bool isCymbalTwoPlayed   = true;  
bool isCymbalThreePlayed = true;  
bool isPercussionPlayed  = true;

//Time from last trigger
unsigned long lastSnarePlayedTime;
unsigned long lastBassPlayedTime;
unsigned long lastSnareTwoPlayedTime;
unsigned long lastHighTomPlayedTime;
unsigned long lastMidTomPlayedTime;
unsigned long lastLowTomPlayedTime;
unsigned long lastCymbalOnePlayedTime;
unsigned long lastCymbalTwoPlayedTime;
unsigned long lastCymbalThreePlayedTime;
unsigned long lastPercussionPlayedTime;
unsigned long timeFromLastPlay;

//Trigger pin voltage readings
float pinVoltageSnare       = 0;
float pinVoltageBass        = 0;
float pinVoltageSnareTwo    = 0;
float pinVoltageHighTom     = 0;
float pinVoltageMidTom      = 0;
float pinVoltageLowTom      = 0;
float pinVoltageCymbalOne   = 0;
float pinVoltageCymbalTwo   = 0;
float pinVoltageCymbalThree = 0;
float pinVoltagePercussion  = 0;

//Triggers handling Parameters
const short TRIGGER_TIME_GAP = 20;
const short TRIGGER_THRESHOLD_VOLTAGE = 100;
const short TRIGGER_THRESHOLD_VOLTAGE_OFF = 30;

void setup(){
  
  //MIDI settings
  Serial.begin(115200);

  //Drum Kits Up/Down buttons
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  //Grounded pin
  //To overcome arduino bleeding problems(electronic), ground an analog pin and read it between drum pad pins readings
  pinMode(A10, INPUT);
    
  //Pad trigger pins
  pinMode(A0, INPUT); //Snare
  pinMode(A1, INPUT); //Bass
  pinMode(A2, INPUT); //Snare Two
  pinMode(A3, INPUT); //High-Tom
  pinMode(A4, INPUT); //Mid-Tom
  pinMode(A5, INPUT); //Low-Tom
  pinMode(A6, INPUT); //Cymbal One
  pinMode(A7, INPUT); //Cymbal Two
  pinMode(A8, INPUT); //Cymbal Three
  pinMode(A9, INPUT); //Percussion

  //Initialize
  lastSnarePlayedTime       =
  lastHighTomPlayedTime     = 
  lastMidTomPlayedTime      =
  lastLowTomPlayedTime      =
  lastBassPlayedTime        =
  lastSnareTwoPlayedTime    =
  lastCymbalOnePlayedTime   =
  lastCymbalTwoPlayedTime   =
  lastCymbalThreePlayedTime = 
  lastPercussionPlayedTime  = 
  timeFromLastPlay          = millis();
}

void loop(){  
  //Read trigger voltages
  pinVoltageSnare = analogRead(A10); //Grounded pin
  pinVoltageSnare = analogRead(A0);
  processTrigger(SNARE, pinVoltageSnare, isSnarePlayed, lastSnarePlayedTime);

  pinVoltageBass = analogRead(A10);
  pinVoltageBass = analogRead(A1);
  processTrigger(BASS, pinVoltageBass, isBassPlayed, lastBassPlayedTime);

  pinVoltageSnareTwo = analogRead(A10);
  pinVoltageSnareTwo = analogRead(A2);
  processTrigger(SNARE_TWO, pinVoltageSnareTwo, isSnareTwoPlayed, lastSnareTwoPlayedTime);

  pinVoltageHighTom = analogRead(A10);
  pinVoltageHighTom = analogRead(A3);
  processTrigger(HIGH_TOM, pinVoltageHighTom, isHighTomPlayed, lastHighTomPlayedTime);

  pinVoltageMidTom = analogRead(A10);
  pinVoltageMidTom = analogRead(A4);
  processTrigger(MID_TOM, pinVoltageMidTom, isMidTomPlayed, lastMidTomPlayedTime);

  pinVoltageLowTom = analogRead(A10);
  pinVoltageLowTom = analogRead(A5);
  processTrigger(LOW_TOM, pinVoltageLowTom, isLowTomPlayed, lastLowTomPlayedTime);

  pinVoltageCymbalOne = analogRead(A10);
  pinVoltageCymbalOne = analogRead(A6);
  processTrigger(CYMBAL_ONE, pinVoltageCymbalOne, isCymbalOnePlayed, lastCymbalOnePlayedTime);

  pinVoltageCymbalTwo = analogRead(A10);
  pinVoltageCymbalTwo = analogRead(A7);
  processTrigger(CYMBAL_TWO, pinVoltageCymbalTwo, isCymbalTwoPlayed, lastCymbalTwoPlayedTime);

  pinVoltageCymbalThree = analogRead(A10);
  pinVoltageCymbalThree = analogRead(A8);
  processTrigger(CYMBAL_THREE, pinVoltageCymbalThree, isCymbalThreePlayed, lastCymbalThreePlayedTime);

  pinVoltagePercussion = analogRead(A10);
  pinVoltagePercussion = analogRead(A9);
  processTrigger(PERCUSSION, pinVoltagePercussion, isPercussionPlayed, lastPercussionPlayedTime);

  processKitsUpDownButtons();
}

void processTrigger(byte midiNote, float currentVoltage, bool &isPlayed, unsigned long &lastPlayedTime){    
  //To optimize and to run the loops faster
  if(isPlayed){
    timeFromLastPlay = millis() - lastPlayedTime;
  }
  else if( !isPlayed &&  (currentVoltage < TRIGGER_THRESHOLD_VOLTAGE) ){
    return;  
  }

  //Play
  if(!isPlayed && currentVoltage >= TRIGGER_THRESHOLD_VOLTAGE && ( timeFromLastPlay >= TRIGGER_TIME_GAP ) ){  
    noteOn(midiNote);
    lastPlayedTime = millis();
    isPlayed = true;
    return;
  }

  //Stop
  if( isPlayed && (timeFromLastPlay > TRIGGER_TIME_GAP) && (currentVoltage <= TRIGGER_THRESHOLD_VOLTAGE_OFF) ){
    isPlayed = false;
    return;
  }
}

void noteOn(byte midiNote){
  if(kitsUpDownFlag == 'X'){
    Serial.println(midiNote);
  }
  else if(kitsUpDownFlag == 'U'){
    Serial.println(KIT_UP);
    Serial.println(midiNote);
    kitsUpDownFlag = 'X';
  }  
  else if(kitsUpDownFlag == 'D'){
    Serial.println(KIT_DOWN);
    Serial.println(midiNote);
    kitsUpDownFlag = 'X';
  } 
}

void processKitsUpDownButtons(){  
  kitsUpDownFlag = 'X';
  //Kits UP button
  if(digitalRead(2) == HIGH){ 
    kitsUpDownFlag = 'U';
  }
  //Kits DOWN button
  else if(digitalRead(3) == HIGH){ 
    kitsUpDownFlag = 'D';
  } 
}
