/*
 * 
 * MotorControl.h is a library for controlling 
 * the Motors in my PingPong Ball Launcher Project
 * 
 * by Nathan Gray
 * G00379837
 */

#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"
#include <ESP32Servo.h>

class MotorControl
{
  private:
  
  Servo xServoObj, ammoServoObj; //servo objects
  uint8_t pwmChannel; //channel for pwm
  
  public: 
    MotorControl(uint8_t dcMotorPin,uint8_t xServo,uint8_t ammoServo,uint8_t freq,uint8_t pwmCH,uint8_t resolution);
    void xAxis(uint8_t x);      //controls xaxis 
    void speedControl(int pot); //controls speed of dc motor
    void ammoRelease(int ammo); //controls ammo servo
};

#endif
