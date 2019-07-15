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
unsigned long start_prev_error = 0;
unsigned long start_curr_error = 0;

volatile int previousError = 0; //The previous different error value that we were getting
volatile int previousDiffError = 0;

volatile int setMode = SEARCH;

int storageDirection = RIGHT; // CHANGE FOR TEAM
int initialTurn = RIGHT;
bool forkPathCrossed = false; // have we crossed the tape completely

int searchMode();

void setup() {
  /* if team switch on -> define THANOS
     else -> define METHANOS */
  Serial.begin(9600);
  Wire.begin();
  delay(5000);
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

  //Check to see if robot is initially on tape
  int initialCondition = 0;
  while(analogRead(TAPE_FOLLOWER_L) < threshold || analogRead(TAPE_FOLLOWER_R) < threshold) {
    if(initialCondition == 0) {
      initialCondition++;
      Serial.println("Robot Initially off tape, please fix :)");
    }
  }
  startDriving();
  Serial.println("Setup Completed!");
}

void loop() {
   Serial.print("LEFT FORK: ");
   Serial.print(analogRead(FORK_SENSOR_L));
   Serial.print(" | TF LEFT: ");
   Serial.print(analogRead(TAPE_FOLLOWER_L));
   Serial.print(" | TF RIGHT: ");
   Serial.print(analogRead(TAPE_FOLLOWER_R));
   Serial.print(" | RIGHT FORK: ");
   Serial.print(analogRead(FORK_SENSOR_R));
   Serial.print(" | THRESHOLD: ");
   Serial.print(analogRead(DETECT_THRESHOLD));
   Serial.print(" | MODE: ");
   Serial.println(setMode);
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
     setMode = turnMode(TURN_L);
      break;
    case TURN_R:
      setMode = turnMode(TURN_R);
      break;
  }
  Serial.print("Exited with mode: ");
  Serial.println(setMode);
  //delay(5000);
}