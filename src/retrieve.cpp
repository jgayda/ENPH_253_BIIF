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
#include <stdint.h>

#include <sensors.h>
#include <search.h>
#include <time.h>
#include <math.h>

int slaveCommTimeout = 20000;

byte masterRequest();
void masterTransmit(byte buffer [3]);

//TODO: DISABLE INTERRUPTS

int retrieveMode(int direction) {
  byte slaveAction = PICKUP;
  byte slaveDirection = (direction == LEFT) ? SLAVE_LEFT:SLAVE_RIGHT;
  byte slaveDistance = (direction == LEFT) ? detectDistance_cm(TRIG_L,ECHO_L):detectDistance_cm(TRIG_R,ECHO_R);

  byte buffer [] = {slaveAction,slaveDirection,slaveDistance};

  volatile byte a = 1;

  int transmisstionTimer = millis(); 

  masterTransmit(buffer);
  byte masterResponse = masterRequest();
  while(masterResponse == IN_PROGRESS) {
    masterResponse = masterRequest();
    if(millis() - transmisstionTimer > slaveCommTimeout) return RESET; 
  }
  return (masterResponse == COMPLETE) ? RETURN : RESET; 
}



byte masterRequest() { 
  byte reply = Wire.requestFrom(SLAVE_ADDRESS,1);
  while (Wire.available()) {
    byte a = Wire.read(); 
  }
  return reply;
}



void masterTransmit(byte buffer[3]) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(buffer,3);
  Wire.endTransmission();
}