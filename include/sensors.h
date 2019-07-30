#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <stack>

 //#define TESTING 1
 //#define TESTING_FORK 2
//#define FORK_HISTORY_TEST 3

/*Thanos starts from the right side of the course
 *  1) The first fork we will detect will be the safe storage marker and will be on the LEFT (ignore this)
 *  2) The next fork we will detect will be the fork between the safe storage and the rest of the course,
 *     we will want to take another LEFT and then we will arrive at our home fork
 */
#define THANOS 10
/*Methanos starts from the left side of the course
 *  1) The first fork we will detect will be the safe storage marker and will be on the RIGHT (ignore this)
 *  2) The next fork we will detect will be the fork between the safe storage and the rest of the course,
 *     we will want to take another RIGHT and then we will arrive at our home fork
 */
#define METHANOS 20
//TEAM
extern int TEAM;

//MODES
#define SEARCH 0
#define APPROACH 1
#define RETRIEVE_L 2
#define RETRIEVE_R 3
#define PATHFINDER 4
#define RETURN 5
#define DEPOSIT 6
#define RETREAT 7
#define DEFENSE 8
#define TURN_L 9
#define TURN_R 10
#define TURN_L_180 11
#define TURN_R_180 12

extern int stateBeforeTurn;

//TAPE FOLLOWER
#define DETECT_THRESHOLD PB0 //PB_0
#define LIGHT_SENSOR PA1

#define TAPE_FOLLOWER_L PA_5
#define TAPE_FOLLOWER_R PA_6
#define LEFT_WHEEL_FWD PA_2
#define LEFT_WHEEL_BKWD PA_3
#define RIGHT_WHEEL_FWD PB_9
#define RIGHT_WHEEL_BKWD PB_8

#define FORK_THRESHOLD_OFFSET 80 // CHANGE

//POST DETECTORS
#define FORK_SENSOR_L PA_4
#define FORK_SENSOR_R PA_7

//SONAR
// #define ECHO_L PB_3
// #define TRIG_L PB_11
// #define ECHO_R PB12
// #define TRIG_R PB13

extern const int ECHO_R;
extern const int TRIG_R;
extern const int ECHO_L;
extern const int TRIG_L;

#define DISTANCE_THRESH 20 //cm

// #define OLED_RESET -1
// #define INTERRUPTPIN PA_4

#define NO_FORK 0
#define FORK_ON_LEFT 1
#define FORK_ON_RIGHT 2

extern const int LEFT_FORK_LED;
extern const int RIGHT_FORK_LED;
extern int ledTimer;

extern int numForksTaken; //number of seen forks in total

#define SPEED 4000
#define LEFT  3
#define RIGHT 4

// FORK
extern std :: stack <int> forkHistory;
extern int storageDirection;
extern int initialTurn;
extern bool forkPathCrossed;
extern int forksInPath; //number of forks in one strategy
extern int forkTimer;
#define forkTimerLimit 2000
#define turnTimerLimit 200
#define followTapeTimerLimit 200

//Speed
extern float speedFactor;

//POST LINE UP
extern int postLineUpTimer;

//TURN alignment
extern int turnTimer;
extern int followTapeTimer;
extern int forkDetectionCondition;
//SLAVE BLUE PILL
#define SLAVE_ADDRESS 69;
extern bool pingSlave;

//POINT COUNTER
extern int stonesScored;



#endif