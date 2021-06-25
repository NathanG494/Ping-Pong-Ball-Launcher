#ifndef BluetoothController_h
#define BluetoothController_h

class BluetoothController
{
  private:

  /*
   * X_JOY - analog stick pin
   * POT - potentiometer pin
   * FIRE_BUTTON - push button pin
   * str - string that holds values
   */
  const uint8_t X_JOY = 0, POT = 2, FIRE_BUTTON = 12;
  uint8_t x,pot,button;
  String str;
  
  public:
  
  BluetoothController();
  void buildString(char charArray[]); //builds the string to be sent
  void bluetoothSend(char charArray[]); //sends the string
};
#endif
