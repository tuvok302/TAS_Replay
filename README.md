# ARDUINO TAS REPLAY DEVICE

Included:

- Code to load onto the arduino once it has been configured to use it
- The serial transfer code to transfer files from a Windows desktop 
- The writeup document

Required:

- A cable to connect your arduino to your console
- The scripts to generate .r16m and .r08 files found [here](https://github.com/dwangoac/TASBot-Projects/tree/master/Dump_Scripts)

*For further information, compile writeup/tex/TASReplay.tex as a PDF 
or check NESTASReplay.png or SNESTASReplay.png for wiring information for the respective NES and SNES 
controller cables.*

## Getting started

*NOTE: Everything has been designed to run on an Arduino Uno or an Uno clone.*

1. Open the .ino file in the arduino IDE and upload to the Arduino.

2. Compile tasSerialTransfer after updating the COM port in main.cpp
> For NES Playback:
```
tasSerialTransfer.exe "LOCATION OF .r08 file" NES
```
> For SNES playback:
```
tasSerialTransfer.exe "LOCATION OF .r16m file" SNES
```

3. Sit back and watch your game of choice beat itself!
