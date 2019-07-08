/* RETRIEVE MODE
 * 
 * STATUS : Robot has approached the infinity stone post such that it is aligned with the post and ready to begin
 *          to try and retrieve the stone.
 * 
 * PROTOCOL : Ensure that the arm starts at 3" off of the ground (the lowest point where a midway tape marker can be located) and move up until
 *            the tape has been detected. 
 * 
 * POSSIBLE PREVIOUS MODES : Approach Mode
 * 
 * POSSIBLE NEXT MODES : Pathfinder Mode
 *           
 */

//Describes the maximum amount of times the robot will try to pick up the claw before giving up. 

#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

#define MAX_ATTEMPTS 2
#define HEIGHT_THRESHOLD 8

#define HEIGHT_SENSOR PA7
#define DETECT_THRESHOLD PA3

#define LEADSCREW_MOTOR PA0
#define CLAW_SERVO PA1

volatile int attempts = 0;

void findStone();
void retrieveMode();
double readHeight();
void raiseArm(double);

void retrieveMode() { 
    pinMode(HEIGHT_SENSOR, INPUT);
    findStone();
    // double currentHeight = readHeight();
    // boolean tapeDetected = false;

    // while(currentHeight >= HEIGHT_THRESHOLD) {
    //     raiseArm(0.1);
    //     currentHeight = readHeight();
    //     if(analogRead(HEIGHT_SENSOR) < DETECT_THRESHOLD) {
    //         tapeDetected = true; 
    //         raiseArm(currentHeight);
    //         break;
    //     }
    // }

    // if(tapeDetected == false) attempts++;
    // if(attempts < MAX_ATTEMPTS) retrieveMode();
    //else go into approach mode
}

void findStone() {
    double currentHeight = readHeight();
    boolean tapeDetected = false;

    while(currentHeight >= HEIGHT_THRESHOLD) {
        raiseArm(0.1);
        currentHeight = readHeight();
        if(analogRead(HEIGHT_SENSOR) > DETECT_THRESHOLD) {
            tapeDetected = true; 
            //raiseArm(currentHeight);
            break;
        }
    }

    if(tapeDetected == false) attempts++;
    if(attempts < MAX_ATTEMPTS) retrieveMode();
}

/* readHeight()
 * 
 */
double readHeight() {
    double height = 0.0;
    //TODO
    /* Reads the height of the lead screw nut encoder?*/
    return height; 
}

/* raiseArm()
 * 
 * Raises the arm by a certain height. If height is positive, will move the arm upwards. If height
 * is negative, will move the arm down.
 * @param : height - The displacement in height to move the arm by
 * @returns : 
 */
void raiseArm(double height) {
    //TODO
    /* Raises or Lowers the arm by the amount x cm*/
}

/* armHeightDefault()
 *
 * Returns the arm to its default height (3 inches from the competition floor)
 * @param : 
 * @returns :
 */
void armHeightDefault() {
    double offset = readHeight();
    raiseArm(3 - offset); //Lower arm to 3 inches off of the ground (should be negative number)
}