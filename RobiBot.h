/**
 * @file       RobiBot.h
 * @author     Sezgin Gül
 * @license    This project is released under The GNU General Public License v3.0
 * @copyright  Copyright (c) 2016 Sezgin Gül
 * @date       December 2016
 * @website    http://www.sezgingul.com/
 * @blog       http://www.robimek.com/
 */


#ifndef RobiBot__h
#define RobiBot_h
#include "Arduino.h"
#include <Servo.h>
// motor pins
#define M1_ENA_PIN 5
#define M2_ENB_PIN 6
#define M1_1_PIN 4 
#define M1_2_PIN 7 
#define M2_1_PIN 8 
#define M2_2_PIN 9 

#define Buzzer_PIN  3 
#define Trigger_PIN 11
#define Echo_PIN   10
#define Servo_PIN 12


#define BRAKE 0
#define FORWARD 1   
#define BACKWARD  2  
#define LEFT   3   
#define RIGHT   4 
#define to_left 5
#define to_right 6
#define to_front 7

#define _time  500
#define _value_min  0
#define _value_max  255
#define slow 120
#define normal  180
#define fast  255
#define _dist_ 20
#define _baudrate 9600
class RobiBot 
{
    public:
void begin(int baudrate = _baudrate);
void left_motor(int M1_ENA = M1_ENA_PIN , int M1_1 = M1_1_PIN, int M1_2 = M1_2_PIN);
void right_motor(int M2_ENB = M2_ENB_PIN,int M2_1 = M2_1_PIN, int M2_2 = M2_2_PIN);
void us_sensor(int USTrigger=Trigger_PIN, int USEcho=Echo_PIN);
void buzzer(int Buzzer=Buzzer_PIN);
void servo(int _Servo = Servo_PIN);
void motion(int state = FORWARD, uint8_t speed = fast);
void motor_speed(uint8_t speed );
 void alarm(int value_min = _value_min,int value_max = _value_max,int timer = _time);
 void look(int _look = to_front);
void check(int _dist = _dist_);  

	float read();
    private:
    int _BuzzerPin;
    int _TriggerPin;
	int _EchoPin;
    int _M1_ENA;
    int _M2_ENB;
    int _M1_1;
    int _M1_2;
    int  _M2_1;
    int _M2_2;
    int _Servo_PIN;
    int left_distance;
    int right_distance;
    int dist;
    Servo servo_motor;
    long TP_init();
};



#endif