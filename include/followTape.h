#ifndef FOLLOWTAPE_H
#define FOLLOWTAPE_H

#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <PWM.h>
#include <ReflectanceReading.h>
#include <PID.h>
#include <sensors.h>

int followTape ();
void startDriving ();
int detectFork ();
void printMotorVal(int error);

extern volatile float left_reflect_memory,right_reflect_memory;
extern unsigned long start_prev_error;
extern unsigned long start_curr_error;

extern volatile int previousError; //The previous different error value that we were getting
extern volatile int previousDiffError;
#endif