# ARDUINO TAS REPLAY DEVICE

This contains the code to load onto the arduino after the hardware has been setup and configured to use 
this.  Contains the serial transfer code to transfer files from a windows desktop, as well as the 
writeup document.  This assumes you already have the cable necessary to connect your arduino to your 
console, and can use the scripts in 
https://github.com/dwangoac/TASBot-Projects/tree/master/Dump_Scripts to generate .r16m and .r08 files.  
For further information on those, please check in write/tex/TASReplay.tex and compile it into a PDF.  
NESTASReplay.png and SNESTASReplay.png have the wiring information for the NES and SNES controller 
cables respectively.  

## Getting started

Open the .ino file in the arduino IDE and upload to the arduino.  Everything was designed to run on an 
arduino uno or uno clone.  

Compile tasSerialTransfer after updating the COM port in main.cpp, and for NES playback:
```
tasSerialTransfer.exe "LOCATION OF .r08 file" NES
```
for SNES playback:
```
tasSerialTransfer.exe "LOCATION OF .r16m file" SNES
```

Sit back and watch your game of choice beat itself!
