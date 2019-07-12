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

//int searchMode();

void setup() {
  /* if team switch on -> define THANOS
     else -> define METHANOS */
  delay(5000);
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Starting Setup... ");

  //TAPE FOLLOWER
  pinMode(DETECT_THRESHOLD, INPUT);
  pinMode(TAPE_FOLLOWER_L,INPUT);
  pinMode(TAPE_FOLLOWER_R,INPUT);
  startDriving();

  //POST DETECTORS
  pinMode(FORK_SENSOR_L, INPUT);
  pinMode(FORK_SENSOR_R, INPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
  Serial.println("Setup Completed!");
}

void loop() {
  Serial.println(setMode);
  switch (setMode) {
    case SEARCH:
      setMode = searchMode();
      Serial.println("search mode");
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
}