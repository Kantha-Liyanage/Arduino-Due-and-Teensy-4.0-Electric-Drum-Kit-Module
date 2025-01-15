# Arduino Due and Teensy 4.0 Electric Drum Kit Module
Electric Drum Kit Module using Arduino Due and Teensy 4.0 

![e-drum](https://raw.githubusercontent.com/Kantha-Liyanage/Arduino-Due-and-Teensy-4.0-Electric-Drum-Kit-Module/refs/heads/main/Arduino-Teensy%20E-Drum.jpeg)

## Motives:
- Fun of doing DIY projects
- Expandability of drum kits
- Low cost

## Features:
- No latacy issues. The latancy is below the recognizable level. Less than 50ms from hitting to a drum pad and hearing the actual sound from the speakers.
- Supports 10 drum triggers
- Drum Kits can be added to the module using the SD card
- Supports 16bits 44.1kHz Wav drum samples

## Components Used
- Arduino Due X 1
- Teensy 4.0 X 1
- Teensy 4.0 Audio Adaptor Board X 1
- Teensy Recommended micro SD Card X 1
- 6.3mm mono sockets X 10
- 1M Resister X 10
- Push Button X 2
- 10k Resister X 2
- Jumper wires
- Project box X 1
- 3.5mm stereo jack X 1 (optional)
- 3.5mm stereo output socket X 1 (optional)
  DC jack (optional)
- DC socket (optional)

MicroSD Card <br/>
<img src="https://raw.githubusercontent.com/Kantha-Liyanage/Arduino-Due-and-Teensy-4.0-Electric-Drum-Kit-Module/refs/heads/main/microSD%20card.jpg" alt="Description" width="300">

### SD Card Folder Structure
The current code can handle 99 drum kits. You need to create separate folders for each kit giving a two-digit folder name. Inside those folders you need to place the drum pad tones giving a single digit file name for each wav file. The current code support 0 to 9, that is 10 drum triggers. Number of kits (in below example it is 2) need to be saved in the kits.txt file. Teensy code reads this text file to identify the number of kits to handle the kit up down buttons.

- 01
   + 0.wav (Stereo 16bits 44.1kHz Wav)
   + 1.wav
   + 2.wav
   + .....
   + 9.wav
- 02
   + 0.wav
   + 1.wav
   + 2.wav
   + .....
   + 9.wav
- kits.txt
  
## Wav Audio Conversion Tools
- [Audacity](https://www.audacityteam.org/)
- [Online Audioconverter](https://onlineaudioconverter.com/)

## Teensy 4.0 Programming
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [Teensy IDE](https://www.pjrc.com/teensy/gui/index.html)
- [Teensy Audio Adaptor Boards - Use Teensy Recommended SD Cards](https://www.pjrc.com/store/teensy3_audio.html)
