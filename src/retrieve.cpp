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
#include <sensors.h>
#include <search.h>
#include <Wire.h>
#include <time.h>
#include <math.h>

int retrieveMode(int direction) {
//   int slaveAction = PICKUP;
//   int slaveDirection = (direction == LEFT) ? SLAVE_LEFT:SLAVE_RIGHT;
//   int slaveDistance = (direction == LEFT) ? detect
}




