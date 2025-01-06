#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
//Teensy Audio Objects
AudioControlSGTL5000 sgtl5000_1;

//10 Audio Players
AudioPlaySdWav           playSdWav1; 
AudioPlaySdWav           playSdWav2;         
AudioPlaySdWav           playSdWav3;     
AudioPlaySdWav           playSdWav4;  
AudioPlaySdWav           playSdWav5; 
AudioPlaySdWav           playSdWav6;         
AudioPlaySdWav           playSdWav7; 
AudioPlaySdWav           playSdWav8; 
AudioPlaySdWav           playSdWav9; 
AudioPlaySdWav           playSdWav10; 

//Mixers
AudioMixer4              mixer1;
AudioMixer4              mixer2;         
AudioMixer4              mixer3;
AudioMixer4              mixer4;
AudioMixer4              mixer5;
AudioMixer4              mixer6;
AudioMixer4              mixerMaster;
AudioOutputI2S           i2s1;

AudioConnection          patchCord01_(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord02_(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord03_(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord04_(playSdWav2, 1, mixer1, 3);

AudioConnection          patchCord05_(playSdWav3, 0, mixer2, 0);
AudioConnection          patchCord06_(playSdWav3, 1, mixer2, 1);
AudioConnection          patchCord07_(playSdWav4, 0, mixer2, 2);
AudioConnection          patchCord08_(playSdWav4, 1, mixer2, 3);

AudioConnection          patchCord09_(playSdWav5, 0, mixer3, 0);
AudioConnection          patchCord10_(playSdWav5, 1, mixer3, 1);
AudioConnection          patchCord11_(playSdWav6, 0, mixer3, 2);
AudioConnection          patchCord12_(playSdWav6, 1, mixer3, 3);

AudioConnection          patchCord13_(playSdWav7, 0, mixer4, 0);
AudioConnection          patchCord14_(playSdWav7, 1, mixer4, 1);
AudioConnection          patchCord15_(playSdWav8, 0, mixer4, 2);
AudioConnection          patchCord16_(playSdWav8, 1, mixer4, 3);

AudioConnection          patchCord17_(playSdWav9, 0, mixer5, 0);
AudioConnection          patchCord18_(playSdWav9, 1, mixer5, 1);
AudioConnection          patchCord19_(playSdWav10, 0, mixer5, 2);
AudioConnection          patchCord20_(playSdWav10, 1, mixer5, 3);

AudioConnection          patchCord21_(mixer1, 0, mixer6, 0);
AudioConnection          patchCord22_(mixer2, 0, mixer6, 1);
AudioConnection          patchCord23_(mixer3, 0, mixer6, 2);
AudioConnection          patchCord24_(mixer4, 0, mixer6, 3);

AudioConnection          patchCord25_(mixer6, 0, mixerMaster, 0);
AudioConnection          patchCord26_(mixer5, 0, mixerMaster, 3);

AudioConnection          patchCord27_(mixerMaster, 0, i2s1, 0);
AudioConnection          patchCord28_(mixerMaster, 0, i2s1, 1);
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

#define HWSERIAL Serial1

//Kits count
int KITS_COUNT = 0;
int kit = 1;
char tonePath[9]; //Example: "01/X.wav" : has only 8 visible chars but 9th one is for the array end null character

void setup() {
  HWSERIAL.begin(115200);
  
  AudioMemory(100);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))){ // stop here, but print a message repetitively
    while (1){
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }  

  // Get kits count from the text file
  File kitsFile = SD.open("kits.txt");
  if (kitsFile) {
    String kitsFileContent = "";
    while (kitsFile.available()) {
      kitsFileContent += (char)kitsFile.read();
    }
    kitsFile.close();
    KITS_COUNT = kitsFileContent.toInt();
    Serial.print("Sound Module started. Kits Count:");
    Serial.print(kitsFileContent);
    
    tonePath[0] = '0';
    tonePath[1] = '1';
    tonePath[2] = '/';
    tonePath[3] = '0';
    tonePath[4] = '.';
    tonePath[5] = 'w';
    tonePath[6] = 'a';
    tonePath[7] = 'v';
  } 
  else {
    Serial.println("Error opening kits.txt");
  }
}

void loop() {
  if(HWSERIAL.available() > 0) {
    byte note = HWSERIAL.read();
    if(note > 40){
      playNote(note);
    }
  }
}

void kitUp(){
  if(kit == KITS_COUNT){
    return;  
  }
  kit++;
  setKitNumber();
}

void kitDown(){
  if(kit == 1){
    return;  
  }
  kit--;
  setKitNumber();
}

void setKitNumber(){
  String kitStr = String(kit);  
  if(kitStr.length() < 2){
    kitStr = '0' + kitStr;
  }
  
  tonePath[0] = kitStr[0];
  tonePath[1] = kitStr[1];
}

void playNote(byte note){
  AudioNoInterrupts();
  switch(note){
    case 48:
      tonePath[3] = '0';
      playSdWav1.play(tonePath);break;
    case 49:
      tonePath[3] = '1';
      playSdWav2.play(tonePath);break;
    case 50:
      tonePath[3] = '2';
      playSdWav3.play(tonePath);break;
    case 51:
      tonePath[3] = '3';
      playSdWav4.play(tonePath);break;
    case 52:
      tonePath[3] = '4';
      playSdWav5.play(tonePath);break;
    case 53:
      tonePath[3] = '5';
      playSdWav6.play(tonePath);break;
    case 54:
      tonePath[3] = '6';
      playSdWav7.play(tonePath);break;
    case 55:
      tonePath[3] = '7';
      playSdWav8.play(tonePath);break;
    case 56:
      tonePath[3] = '8';
      playSdWav9.play(tonePath);break;
     case 57:
      tonePath[3] = '9';
      playSdWav10.play(tonePath);break;
    case 45:
      kitDown();break;
    case 43:
      kitUp();break;
  }
  AudioInterrupts();
}
