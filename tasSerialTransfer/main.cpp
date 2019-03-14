#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <vector>
#include "SerialPort.h"

#define DATA_LENGTH 64 //send 512 byte blobs of data to the arduino at a time
using namespace std;

char* portName = "\\\\.\\COM5";

SerialPort *arduino;
int main(int argc, char *argv[])
{
    //cout << "Hello world!" << endl;
    ifstream tasdata (argv[1], ios::in | ios::binary | ios::ate);
    uint64_t filesize;
    struct stat results; //blindly following instructions for file size
    char * controllerBytes;
    char * sendBytes = new char [DATA_LENGTH];
    char * frameRequest = new char [5];
    cout << "Watching: " << argv[1] << endl;
    arduino = new SerialPort(portName);
    if (!arduino->isConnected()){
        delete sendBytes;
        delete arduino;
        delete frameRequest;
        return -1;
    }
    std::cout << "is connected: " << arduino->isConnected() << std::endl;
//    if (stat(argv[1], &results) == 0){
//        filesize = results.st_size;
//    }
//    else {
//        cout << "DANGER WILL ROBINSON! DANGER! Either file handle invalid, or ... something. GOOD LUCK Star Fox!" << endl;
//        return -1;
//    }
    if (tasdata.is_open()){
        filesize = tasdata.tellg();
        tasdata.seekg(0, ios::beg);
        //transmit via serial to the arduino
        //cout << "Well it worked.  Good job hero.  File size: " << filesize << endl;
        controllerBytes = new char [filesize];
        tasdata.read(controllerBytes,filesize);
        tasdata.close();
        //cout << argv[2] << endl;
        if(!strcmp(argv[2], "NES")){
            cout << "NES Video" << endl;
            for (int i = 0; i < filesize/2; i++){
                controllerBytes[i] = controllerBytes[i*2];
            }
            filesize = filesize/2;
        }
        if(!strcmp(argv[2], "SNES")){
            cout << "SNES Video" << endl;
            for (int i = 0; i < filesize/16; i += 2){
                controllerBytes[i] = controllerBytes[i*8];
                controllerBytes[i+1] = controllerBytes[i*8 + 1];
            }
            filesize = filesize/8;
        }
//        for(int i = 0; i < filesize+1; i++){
//            tasdata.read(&controllerBytes[i],1);
//            cout << (controllerBytes[i]) << endl;
//        }
    }
    else cout << "Shit broke yo" << endl;
    cout << "Beggining Serial communication:" << endl;
    //arduino = new SerialPort(portName);
    bool hasWritten = 0;
    uint64_t hasRead = 0;
    uint64_t writeCount = 0;
    cout << "filesize: " << filesize << " , Transmission length: "<< DATA_LENGTH << " , Number of transmissions: " << filesize/DATA_LENGTH << endl;
    cout << "START" << endl;
    for(int i = 0; i < filesize/DATA_LENGTH + 1; i++){
        for(int j = 0; j < DATA_LENGTH; j++){
            //cout << "inside for\n";
            sendBytes[j] = controllerBytes[(i*DATA_LENGTH)+j];
        }
        while((hasRead == 0)){
            hasRead = arduino->readSerialPort(frameRequest, 5);
        }
        hasRead = arduino->readSerialPort(frameRequest,5);
        hasRead = arduino->readSerialPort(frameRequest,5);
        //cout << frameRequest;
        if(writeCount % 15 == 0){
            cout << writeCount << endl;
        }
        if (arduino->isConnected()){
            hasWritten = arduino->writeSerialPort(sendBytes, DATA_LENGTH);
            if (hasWritten) {
                writeCount++;
                //std::cout << "Data Written Successfully" << std::endl;
            }
            hasWritten = 0;
            //else std::cout << "Data was not written" << std::endl;
        }
        //cout << i << endl;
    }
    return 0;
}
