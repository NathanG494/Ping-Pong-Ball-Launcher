/*
 * 
 * MotorControl.h is a library for controlling 
 * the Motors in my PingPong Ball Launcher Project
 * 
 * by Nathan Gray
 * G00379837
*/

#include "Arduino.h"
#include "MotorControl.h"
#include <ESP32Servo.h>

//constructor
MotorControl::MotorControl(uint8_t dcMotorPin,uint8_t xServo,uint8_t ammoServo,uint8_t freq,uint8_t pwmCH,uint8_t resolution)
{
  pwmChannel = pwmCH;
  
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(dcMotorPin, pwmChannel);

  //Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  xServoObj.setPeriodHertz(50);       // standard 50 hz
  ammoServoObj.setPeriodHertz(50);    // standard 50 hz

  
  pinMode(dcMotorPin, OUTPUT);
  
  /*
   * attaches the pins 18 & 19 to the servo objects
   * using min/max of 500us - 2400us
   * 
   */
  xServoObj.attach(xServo, 500, 2300);
  ammoServoObj.attach(ammoServo, 500, 2300); 
}

/*
 * Variable x is the position of the x-axis on the analog stick
 * the switch has a range of values creating deadzones on the analog stick
 * when the analog stick is moved slightly to the left or right the xaxis
 * servo will move slowly
 * 
 * when the analog stick is moved all the way to the left or right the motor will move
 * fast
 */
void MotorControl::xAxis(uint8_t x)
{
  switch(x)  
  {
    case 0 ... 49 : xServoObj.write(xServoObj.read() + 3);
      break;
  
    case  50 ... 80 : xServoObj.write(xServoObj.read() + 1);
      break;
  
    case 90 ... 110 : xServoObj.write(xServoObj.read() - 1);
      break;
  
    case 111 ... 180 : xServoObj.write(xServoObj.read() - 3);
      break;
  
    default: xServoObj.write(xServoObj.read());
      break;
  }
}

//sends PWM signal to dc motor
void MotorControl::speedControl(uint8_t pot)
{
  ledcWrite(pwmChannel, pot);
}

//writes a position to the servo depending if ammo is 1 or 0
void MotorControl::ammoRelease(uint8_t ammo)
{
  if(ammo == 1)
  {
    ammoServoObj.write(200);
  }
  else
  {
    ammoServoObj.write(100);
  }
}
