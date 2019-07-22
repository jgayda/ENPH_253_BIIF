#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <stack>

//#define TESTING 1

#define THANOS
//#define METHANOS

//MODES
#define SEARCH 0
#define APPROACH 1
#define RETRIEVE 2
#define PATHFINDER 3
#define RETURN 4
#define DEPOSIT 5
#define RETREAT 6
#define DEFENSE 7
#define TURN_L 8
#define TURN_R 9

//TAPE FOLLOWER
#define DETECT_THRESHOLD PA_3
#define TAPE_FOLLOWER_L PA_6
#define TAPE_FOLLOWER_R PA_5
#define LEFT_WHEEL_FWD PB_7
#define LEFT_WHEEL_BKWD PB_6
#define RIGHT_WHEEL_FWD PB_8
#define RIGHT_WHEEL_BKWD PB_9

//POST DETECTORS
#define FORK_SENSOR_L PA_7
#define FORK_SENSOR_R PA_4

//SONAR
#define ECHO_L PB_3
#define TRIG_L PA_12
#define ECHO_R PA_15
#define TRIG_R PA_11
#define DISTANCE_THRESH 14 //inches

// #define OLED_RESET -1
// #define INTERRUPTPIN PA_4

#define NO_FORK 0
#define FORK_ON_LEFT 1
#define FORK_ON_RIGHT 2

#define SPEED 4000
#define LEFT  3
#define RIGHT 4

// FORK
extern std :: stack <int> forkHistory;
extern int storageDirection;
extern int initialTurn;
extern bool forkPathCrossed;

//SLAVE BLUE PILL
#define SLAVE_ADDRESS 69;
extern bool pingSlave;

//POINT COUNTER
extern int stonesScored;

#endif