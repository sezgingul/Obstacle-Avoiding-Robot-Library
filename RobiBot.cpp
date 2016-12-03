/**
 * @file       RobiBot.cpp
 * @author     Sezgin Gül
 * @license    This project is released under The GNU General Public License v3.0
 * @copyright  Copyright (c) 2016 Sezgin Gül
 * @date       December 2016
 * @website    http://www.sezgingul.com/
 * @blog       http://www.robimek.com/
 */



#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
#include "RobiBot.h"
#include <Servo.h>


void RobiBot::begin(int baudrate)
{
    Serial.begin(baudrate);
}



void RobiBot::us_sensor(int USTrigger=Trigger_PIN, int USEcho=Echo_PIN)
{
    _TriggerPin = USTrigger;
    _EchoPin = USEcho;
     pinMode( _TriggerPin , OUTPUT );
  pinMode( _EchoPin , INPUT );
}

void RobiBot::buzzer(int Buzzer=Buzzer_PIN)
{
    _BuzzerPin = Buzzer;
    pinMode(_BuzzerPin,OUTPUT);
}

void RobiBot::left_motor(int M1_ENA, int M1_1 , int M1_2)
{
    _M1_ENA = M1_ENA;
     _M1_1 = M1_1;
    _M1_2 = M1_2;
  pinMode(_M1_ENA,OUTPUT);
  pinMode(_M1_1,OUTPUT);
  pinMode(_M1_2,OUTPUT);
}

void RobiBot::right_motor(int M2_ENB,int M2_1, int M2_2)
{
      _M2_ENB = M2_ENB;
      _M2_1 = M2_1;
      _M2_2 = M2_2;
      pinMode(_M2_ENB,OUTPUT);
      pinMode(_M2_1,OUTPUT);
      pinMode(_M2_2,OUTPUT);
}

void RobiBot::servo(int _Servo = Servo_PIN)
{
    
  _Servo_PIN = _Servo; 
  servo_motor.attach(_Servo_PIN);
  servo_motor.write(90);
}
long RobiBot::TP_init()
{
    digitalWrite(_TriggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(_TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_TriggerPin, LOW);
    long Microseconds= pulseIn(_EchoPin,HIGH); 
    return Microseconds;
} 

float RobiBot::read(){
  long Microseconds = RobiBot::TP_init();
  long distance;
  distance = Microseconds/29.1/2;
  if (distance > 200){
    distance = 200;
  }
  return distance;
}



void RobiBot::motor_speed(uint8_t speed )
{
 switch(speed)
      {
          case slow:
          analogWrite(_M1_ENA,slow);
          analogWrite(_M2_ENB,slow);
          break;
          case normal:
           analogWrite(_M1_ENA,normal);
          analogWrite(_M2_ENB,normal);
          break;
           case fast:
           analogWrite(_M1_ENA,fast);
          analogWrite(_M2_ENB,fast);
          break;
      }
}

void RobiBot::motion(int state, uint8_t speed)
{
  motor_speed(speed);
    switch(state){
    case FORWARD:
      switch(speed)
      {
          case slow:
          analogWrite(_M1_ENA,slow);
          analogWrite(_M2_ENB,slow);
          break;
          case normal:
           analogWrite(_M1_ENA,normal);
          analogWrite(_M2_ENB,normal);
          break;
           case fast:
           analogWrite(_M1_ENA,fast);
          analogWrite(_M2_ENB,fast);
          break;
      }
        
        digitalWrite(_M1_1,HIGH);
        digitalWrite(_M1_2,LOW);
        digitalWrite(_M2_1,HIGH);
        digitalWrite(_M2_2,LOW);
    break;
     case  BACKWARD:
     
       
        digitalWrite(_M1_1,LOW);
        digitalWrite(_M1_2,HIGH);
        digitalWrite(_M2_1,LOW);
        digitalWrite(_M2_2,HIGH);
      break;
     case LEFT:
    
        digitalWrite(_M1_1,LOW);
        digitalWrite(_M1_2,HIGH);
        digitalWrite(_M2_1,HIGH);
        digitalWrite(_M2_2,LOW);
      break;
     case RIGHT:
    
        digitalWrite(_M1_1,HIGH);
        digitalWrite(_M1_2,LOW);
        digitalWrite(_M2_1,LOW);
        digitalWrite(_M2_2,HIGH);
      break;
       case BRAKE:
    
        
        digitalWrite(_M1_1,LOW);
        digitalWrite(_M1_2,LOW);
        digitalWrite(_M2_1,LOW);
        digitalWrite(_M2_2,LOW);
          break;
    }

   
}

void RobiBot::alarm(int value_min,int value_max,int timer)
{
    analogWrite(_BuzzerPin, value_max);
    delay(timer);
    analogWrite(_BuzzerPin,value_min);
    delay(timer);
    analogWrite(_BuzzerPin,0);
}

void RobiBot::look(int _look)
{
    switch(_look){
    case to_left:
    
        servo_motor.write(0);
        delay(500);
        break;
    case to_front:
        servo_motor.write(90);
        delay(500);
    
    case to_right:
        servo_motor.write(180);
        delay(500);
        break;
    }
}



void RobiBot::check(int _dist)
{
    dist = RobiBot::read();
    if(dist>_dist){
        RobiBot::motion(FORWARD);
    }
    else {

    
   RobiBot::motion(BRAKE);
   RobiBot::alarm();
    delay(50);
   RobiBot::look(to_left);
   left_distance = RobiBot::read();
   delay(50);
   RobiBot::look(to_right);
   right_distance = RobiBot::read();
   delay(50);
  RobiBot::look(to_front);
 delay(50);
   if(left_distance > right_distance)
    {
      RobiBot::motion(LEFT);
      delay(500);
      RobiBot::motion(FORWARD);
     return dist;
    }
    else if(left_distance< right_distance)
    {
        RobiBot::motion(RIGHT);
        delay(500);
         RobiBot::motion(FORWARD);
         return dist;
    }
    else
    {
        RobiBot::motion(BACKWARD);
        delay(500);
        RobiBot::motion(RIGHT);
        delay(500);
         RobiBot::check();
         RobiBot::motion(FORWARD);
         return dist;
    }
   }
}





