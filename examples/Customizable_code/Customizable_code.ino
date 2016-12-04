/* "RobiBot" library created by Sezgin GÜL
 *  Writing the code of the robot that detects the obstacle quickly
 *  /**
 * @author     Sezgin Gül
 * @license    This project is released under The GNU General Public License v3.0
 * @copyright  Copyright (c) 2016 Sezgin Gül
 * @date       December 2016
 * @website    http://www.sezgingul.com/
 * @blog       http://www.robimek.com/
*/
/* 
 *  RobiBot shield pcb design >> https://circuits.io/circuits/3416259-robibot-obstacle-avoiding-robot-shield#pcb
*/

#include <RobiBot.h>

RobiBot myRobot;
void setup() {

  myRobot.begin(9600);
  myRobot.us_sensor(8,9); // Trig, Echo Pin
  myRobot.servo(4); // servo sinyal pin
  myRobot.buzzer(2); // buzzer pin
  myRobot.left_motor(6,11,12); //left motor ena, in1, in2 pin
  myRobot.right_motor(5,7,10); //right motor ena, in1, in2 pin
  myRobot.motion(BRAKE);
  myRobot.look(to_front); //  Turn the sensor to the front
   myRobot.motor_speed(fast); // Speeds of the motors
   // pwm values "fast mode = 255" "normal mode = 180" "slow mode 120"
   // If you want, you can enter a number between 0 and 255 
}

void loop() {

  int distance = myRobot.read(); // Distance measurement from ultrasonic sensor

  if(distance > 15) // If the proximity to the object is more than 15 centimeters 
  {
    myRobot.motion(FORWARD, fast); // Move the robot in fast forward mode.
  }
  else //If the proximity to the object is between 0 and 15 cm
  { 
    myRobot.motion(BRAKE); // Stop the robot
    myRobot.alarm(240,130,1000); // max,min, delay value For the alarm melody
    myRobot.look(to_left); // Turn the sensor to the left
    int lef_dis = myRobot.read(); // Measure left side distance
    myRobot.look(to_right); // Turn the sensor to the right 
    int right_dis = myRobot.read(); // Measure right side distance
    myRobot.look(to_front); // // Turn the sensor to the front
    
    if( lef_dis > right_dis) // If left distance is greater than right
    {
      myRobot.motion(LEFT,normal); // Turn the robot in normal mode to left 
      delay(400); // 400 ms wait
      myRobot.motion(FORWARD,normal); // Move the robot in fast normal mode.
      return distance; // Update front distance value
    }
    else // If the right side is equal to left or greater
    {
      myRobot.motion(RIGHT,normal); // Turn the robot in normal mode to right 
      delay(500); // 500 ms wait
      myRobot.motion(FORWARD,slow); // Move the robot in fast slow mode.
      return distance; // Update front distance value
    }
    
  }
}
