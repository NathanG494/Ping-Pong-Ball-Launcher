#include <BluetoothController.h>

//creating BluetoothController object
BluetoothController btc;

void setup() 
{
  Serial.begin(115200); 
}

void loop() 
{
  //char array to store values
  char strA[13];
  
  btc.buildString(strA);

  delay(30);
  
  btc.bluetoothSend(strA);
}
