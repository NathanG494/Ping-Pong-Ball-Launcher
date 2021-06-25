/*
 * 
 * BluetoothWiFi.h is a library for connecting to wifi, bluetooth
 * and displaying the website for my PingPong Ball Launcher Project
 * 
 * by Nathan Gray
 * G00379837
*/

#ifndef BluetoothWiFi_h
#define BluetoothWiFi_h

#include <WiFi.h>
#include <Arduino.h>
#include "BluetoothSerial.h"

class BluetoothWiFi
{
  private:
    
    BluetoothSerial SerialBT;
    WiFiServer server;
    WiFiClient client;
    
  public:
  
    BluetoothWiFi();        //default Constructor
    void wifiConnect();     //connects to wifi
    String webControl();    //displays webpage and returns a string of values
    bool btConnect();       //connects bluetooth returns a bool
    bool isBTConnect();     //a bool that returns if bluetooth is connected or not
    void receiveBTData(char receivedChars[]);   //receives chars from bluetooth device 
    void parseData(String str, int *x, int *pot, int *ammo);  //parses the String and assigns them to their variables  
};
#endif
