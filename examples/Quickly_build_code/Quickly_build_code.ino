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

/*RobiBot Shield Default Pins
 * Ultrasonic sensor pins : Trig = D11 ; Echo = D10
 * Servo signal pin : D12
 * Buzzer signal pin : D3
 * Lef dc motor : ENA: D5 ; SIGNAL PINS : D4 AND D7
 * Right dc motor: ENA: 5 ; SIGNAL PINS : D8 AND D9
*/
#include <RobiBot.h> // RobiBot library

RobiBot RobiBot; // crate RobiBot

void setup() {
RobiBot.begin(9600); // RobiBot baudrate
 RobiBot.us_sensor(); //Add ultrasonic sensor 
 RobiBot.left_motor(); // Add left motor
 RobiBot.right_motor(); // Add right motor
 RobiBot.servo(); // Add servo motor
 RobiBot.motion(BRAKE); // Motors in stop position
}

void loop() {

RobiBot.check(15); // Robot start function by entering obstacle detection distance
}

