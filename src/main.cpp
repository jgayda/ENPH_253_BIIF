#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>

#include <search.h>
#include <approach.h>
#include <turn.h>
#include <sensors.h>
#include <followTape.h>

// TAPE FOLLOWER GLOBAL VARIABLE INITIALIZATION

unsigned long start_prev_error = 0; //Errors should all be 0 initially since robot won't begin following
unsigned long start_curr_error = 0; //tape unless both TFL and TFR are on the tape :)

volatile int previousError = 0; //The immediate previous sensed error we recieved
volatile int previousDiffError = 0; //The previous DIFFERENT error value that we were sensing

volatile int setMode = SEARCH; //Robot will initially be in search mode (following tape and looking for posts)

//TODO: Include Methanos / Thanos Switch!
int storageDirection = RIGHT; // CHANGE FOR TEAM
int initialTurn = RIGHT; //CHANGE FOR TEAM

bool forkPathCrossed = false; // have we crossed the tape completely

bool pingSlave = false;

void debugSensorReadings(int setMode);
void exitModeAlerts(int setMode);



void setup() {

  Serial.begin(9600);
  //DO NOT inlucde Wire.begin() --> Interferes with the TX&RX functions of the bluepill!

  //Delay added for debugging (allows time to catch beginning of Serial Monitor)
  //Delete for competition
  delay(2000);

 // TAPE FOLLOWER
  pinMode(DETECT_THRESHOLD, INPUT);
  pinMode(TAPE_FOLLOWER_L,INPUT);
  pinMode(TAPE_FOLLOWER_R,INPUT);

  //POST DETECTORS
  pinMode(FORK_SENSOR_L, INPUT);
  pinMode(FORK_SENSOR_R, INPUT);

  //WHEEL MOTOR PWMs
  pinMode(LEFT_WHEEL_FWD, OUTPUT);
  pinMode(LEFT_WHEEL_BKWD, OUTPUT);
  pinMode(RIGHT_WHEEL_FWD, OUTPUT);
  pinMode(RIGHT_WHEEL_BKWD, OUTPUT);

  //SET THRESHOLD
  float threshold = analogRead(DETECT_THRESHOLD);

  //Do not uncomment before figuring out what the fuck is going on (the pins are weird )
  // // pinMode(ECHO_L, INPUT);
  //  pinMode(TRIG_L, OUTPUT);
  // // pinMode(ECHO_R, INPUT);
  //  pinMode(TRIG_R,OUTPUT);

  //TODO: Add function that initially checks what team we are on

  //Check to see if robot is initially on tape
  int initialCondition = 0;
  int counter = 0;
  while(analogRead(TAPE_FOLLOWER_L) < threshold || analogRead(TAPE_FOLLOWER_R) < threshold) {
    if(initialCondition == 0) {
      initialCondition++;
      Serial.println("Robot Initially off tape, please fix :)");
    }
    counter++;
    if(counter % 10000 == 0) {
      Serial.print("Threshold: ");
      Serial.print(threshold);
      Serial.print("Left Sensor Value: ");
      Serial.print(analogRead(TAPE_FOLLOWER_L));
      Serial.print(" | Right Sensor Value: ");
      Serial.println(analogRead(TAPE_FOLLOWER_R));
    }
  }

  //Start driving the robot forward once the initial conditions have been meet
  pwm_start(LEFT_WHEEL_FWD, 100000, SPEED, 0, 1);
  pwm_start(RIGHT_WHEEL_FWD, 100000, SPEED, 0, 1);
  pwm_start(LEFT_WHEEL_BKWD, 100000, SPEED, 0, 1);
  pwm_start(RIGHT_WHEEL_BKWD, 100000, SPEED, 0, 1);
  startDriving();
  Serial.println("Setup Completed");
}



//MAIN STATE SWITCH BOX
void loop() {
  //To see the values for all of the sensors, uncomment the next line
  #ifdef TESTING
  //debugSensorReadings(setMode);
  #endif
  switch (setMode) {
    case SEARCH:
      setMode = searchMode();
      break;
    case APPROACH:
      //setMode = approachMode();
      break;
    case RETRIEVE:
      //setMode = retrieveMode();
      break;
    case PATHFINDER:
      //setMode = pathfinderMode();
      break;
    case DEPOSIT:
      //setMode = depositMode();
      break;
    case DEFENSE:
      //setMode = defenseMode();
      break;
    case TURN_L:
     //setMode = turnMode(TURN_L);
     Serial.println("Found fork on the left, turning to left");
     delay(4000);
     setMode = SEARCH;
     break;
    case TURN_R:
      Serial.println("Found fork on the right, turning to right");
      delay(4000);
      setMode = SEARCH;
      //setMode = turnMode(TURN_R);
      // Serial.println("Turning Right");
      // turnRobot(RIGHT);
      // delay(2000);
      // stopRobot();
      // setMode = DEPOSIT;
      break;
  }
  //To debug and see the mode that the robot exited with, uncomment the next line
  //exitModeAlerts(setMode);
}



/* debugSensorReadings()
 *
 * Prints out the sensor readings for all of the QRD sensors on the front of the robot
 * For debugging purposes only :)
 * @param : setMode - the current mode/state of the robot
 */
void debugSensorReadings(int setMode) {
  Serial.print("FSL Value: ");
  Serial.print(analogRead(FORK_SENSOR_L));
  Serial.print(" | TFL Value: ");
  Serial.print(analogRead(TAPE_FOLLOWER_L));
  Serial.print(" | TFR Value: ");
  Serial.print(analogRead(TAPE_FOLLOWER_R));
  Serial.print(" | FSR Value: ");
  Serial.print(analogRead(FORK_SENSOR_R));
  Serial.print(" | THRESH Value: ");
  Serial.print(analogRead(DETECT_THRESHOLD));
  Serial.print(" | MODE: ");
  Serial.println(setMode);
}



/* exitModeAlerts()
 *
 * Prints the mode that the robot exited the loop with
 * For debugging purposes only :)
 * @param : setMode - the current mode/state of the robot
 */
void exitModeAlerts(int setMode) {
  Serial.print("Exited with mode: ");
  Serial.println(setMode);
}