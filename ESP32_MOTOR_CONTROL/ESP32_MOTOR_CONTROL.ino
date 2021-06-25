/*
 * PingPong BallLauncher ESP-32
 * 
 * by Nathan Gray
 * G00379837
 */


#include "BluetoothWiFi.h"
#include "MotorControl.h"

/*
 * NUMCHARS - array size 
 * DC_MOTOR - dc motor pin
 * X_SERVO - xaxis servo motor pin
 * AMMO_SERVO - ammo servo pin
 * FREQ - frequency for pwm
 * PWMCHANNEL - channel for pwm
 * RESOLUTION - resolution for pwm
 */
const uint8_t NUMCHARS = 13,DC_MOTOR = 4, X_SERVO = 18, AMMO_SERVO = 19, FREQ = 1000, PWMCHANNEL = 4, RESOLUTION = 8;

//motorControl object
MotorControl motors(DC_MOTOR, X_SERVO, AMMO_SERVO, FREQ, PWMCHANNEL, RESOLUTION);

//BluetoothWiFi object
BluetoothWiFi btW;

void setup() 
{
 Serial.begin(115200);

 //connects to a bluetooth device 
 btW.btConnect();

 //connects to wifi signal 
 btW.wifiConnect();
  
}

void loop() 
{

  /*
   * receivedChars - stores charaters received from HC - 06
   * strToParse - String that stores values from receivedChars
   * webStr - stores values from website
   */
   
  char receivedChars[NUMCHARS];
  String strToParse;
  String webStr;
  
  /*
   * variables to control the motors
   * 
   * x - stores x axis position
   * pot - stores potentiometer value
   * ammo - stores push button state
   * 
   */
  uint8_t x,pot,ammo;

  delay(10);

  if(btW.isBTConnect() == 1)
  {  
    btW.receiveBTData(receivedChars);        //receives chars from bluetooth device 
    strToParse = receivedChars;              //puts values from a char array into a String 
    btW.parseData(strToParse,&x,&pot,&ammo); //parses the values and assigns them to the variables
  }
 
  webStr = btW.webControl(); //displays webpage and gets values for the motor variables
  
  if(webStr != "")
  {
    btW.parseData(webStr, &x, &pot, &ammo); //parses the string and assigns them to the variables
  }
  
  motors.xAxis(x);               //controls x axis servo
  motors.speedControl(pot);      //controls Dc_motor
  motors.ammoRelease(ammo);      //controls ammo release servo
}
