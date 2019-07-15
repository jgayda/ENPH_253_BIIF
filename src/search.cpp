#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <sensors.h>
#include <followTape.h>
#include <PWM.h>

int detectFork();
int detectDistance_cm(PinName trigPin, PinName echoPin);
int detectDistance_in(PinName trigPin, PinName echoPin);

/* searchMode
 *
 * Robot is actively following tape and looking for posts
 * POSSIBLE TRANSITION STATES: */
#define search 0
#define approach 1
/*
 */
int searchMode() {
    int direction =0;
    int distance = DISTANCE_THRESH + 10 ;
    int fork = NO_FORK;
    int error = 1000;

    if(fork == NO_FORK){
        Serial.println("Following tape, no fork detected");
        error = followTape();
    }

    PinName trigPin;
    PinName echoPin;

    if (error == 10) {
        fork = detectFork();
        if(fork == FORK_ON_LEFT || fork == FORK_ON_RIGHT){
            Serial.println("I detected a fork");
            stopRobot();
            if(fork == FORK_ON_LEFT) {
                // trigPin = TRIG_L;
                // echoPin = ECHO_L;
                direction = LEFT;
            }
            else {
                trigPin = TRIG_R;
                echoPin = ECHO_R;
                direction = RIGHT;
            }
          // distance = detectDistance_cm (trigPin, echoPin);
                // regular fork
            Serial.print("THE FORK IS ON THE ");
            if (direction == LEFT){
                Serial.println("LEFT");
                return TURN_L;
            } else {
                Serial.println("RIGHT");
                return TURN_R;
            }

            // if(forkHistory.size() ==0) {
            //     // initial turn
            //     // turn 90 degrees
            // } else if {

            // }
        //    if(distance < DISTANCE_THRESH){
        //        // do a 90 degree turn towards the fork, there is a post
        //        Serial.println("I SEE A POST");
        //         if (direction == LEFT){
        //            Serial.println("LEFT");
        //         } else {
        //            Serial.println("RIGHT");
        //         }

        //    }
        //    else {

        //        }
        //   }

        }
    }
    return SEARCH;
}

/* detectDistance_cm
 *
 * Returns the detected sonar distance in cm
 * @param : trigPin - t
 * @return : the distance in cm
 */
int detectDistance_cm(PinName trigPin,PinName echoPin) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); //WATCH OUT
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int distance_cm = pulseIn(echoPin, HIGH) * 0.034 / 2;
  return distance_cm;
}

// /* detectDistance_in
//  *
//  * Returns the detected sonar distance in inches
//  */
// int detectDistance_in(int trigPin) {
//   // Clears the trigPin
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2); //WATCH OUT
//   // Sets the trigPin on HIGH state for 10 microseconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   distance_in = pulseIn(echoPin, HIGH) * 0.034 / 2 * 0.393701;
//   return distance_in;
// }




