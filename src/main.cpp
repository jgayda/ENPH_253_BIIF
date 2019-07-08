#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <search.h>

//TAPE FOLLOWER
#define DETECT_THRESHOLD PA0
#define TAPE_FOLLOWER_L PA5
#define TAPE_FOLLOWER_R PA6

//POST DETECTORS
#define FORK_SENSOR_L PA7
#define FORK_SENSOR_R PA8
#define ECHO_L PB4
#define TRIG_L PB5
#define ECHO_R PB6
#define TRIG_R PB7
#define DISTANCE_THRESH 14 //inches

#define OLED_RESET -1

#define INTERRUPTPIN PA4

//MODES
#define search 0
#define approachMode 1
#define retrieveMode 2
#define pathfinderMode 3
#define returnMode 4
#define depositMode 5
#define retreatMode 6
#define defenseMode 7

volatile int setMode = search;

//int searchMode();

void setup() {
  Serial.begin(115200);

  //TAPE FOLLOWER
  pinMode(DETECT_THRESHOLD, INPUT);
  pinMode(TAPE_FOLLOWER_L,INPUT);
  pinMode(TAPE_FOLLOWER_R,INPUT);

  //POST DETECTORS
  pinMode(FORK_SENSOR_L, INPUT);
  pinMode(FORK_SENSOR_R, INPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
}

void loop() {
  switch (setMode) {
    case search :
      setMode = searchMode();
    case approachMode :
      //
    case retrieveMode :
      //
    case pathfinderMode :
      //
    case returnMode :
      //
    case depositMode :
      //
    case defenseMode : 
      //
      break; 
  }
}