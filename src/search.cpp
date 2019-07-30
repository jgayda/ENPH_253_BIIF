#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <sensors.h>
#include <followTape.h>
#include <PWM.h>
#include <strategy.h>
#include <timer.h>

void printSonarValues(int trigPin, int echoPin);
int detectDistance_cm(int trigPin, int echoPin);


#define search 0
#define approach 1

/* searchMode()
 *
 * Robot is actively following tape and looking for posts
 * POSSIBLE TRANSITION STATES:
 *      (1) searchMode - no fork detected, the robot continues to search
 *      (2) turnMode (left or right) - robot detects fork
 * @returns : setMode - the mode that the robot switches to post searchMode
 */
int searchMode() {
    stateBeforeTurn = SEARCH;
    if(forkHistory.size() > 0) {
        speedFactor = 0.18;
    }
    int direction =0;
    int distance = DISTANCE_THRESH + 10 ;
    int fork = NO_FORK;
    int error = 10;


    if(fork == NO_FORK){
        //Serial.println("Following tape, no fork detected");
        error = followTape();
    }


    if(millis() - forkTimer < forkTimerLimit) {
        #ifdef TESTING_FORK
            Serial.print("I'm not supposed to detect a fork, forkTimer: ");
            Serial.print(forkTimer);
            Serial.print(" | currentTimer: ");
            Serial.print(millis());
            Serial.print(" | forkTimerLimit: ");
            Serial.println(forkTimer);
        #endif
        error = followTape(); // don't check for fork
        return SEARCH; // don't detect forks;
    }

    if(millis() - followTapeTimer < followTapeTimerLimit){
        error = followTape();
        return SEARCH;
    }

    // PinName trigPin;
    // PinName echoPin;

    int trigPin;
    int echoPin;

    #ifdef TESTING_FORK
        //printSonarValues(TRIG_L,ECHO_L);
       // Serial.println(" ");
        //printSonarValues(TRIG_R,ECHO_R);
    #endif



    if (abs(error) <= forkDetectionCondition) {

        fork = detectFork();

        #ifdef TESTING_FORK
            Serial.print("in search mode: fork val: ");
            Serial.println(fork);
        #endif

        if(fork == FORK_ON_LEFT) {
            forkTimer = millis();
            stopRobot();
            digitalWrite(LEFT_FORK_LED,HIGH);
            ledTimer = millis();
            direction = LEFT;
            #ifdef TESTING_FORK
                Serial.print("I detected a fork on the left with: ");
                Serial.print(analogRead(FORK_SENSOR_L));
             #endif

            //Serial.println("I detected a fork on the left");
            trigPin = TRIG_L;
            echoPin = ECHO_L;
            distance = detectDistance_cm(trigPin,echoPin);
            // if(detectDistance_cm(trigPin, echoPin) <= DISTANCE_THRESH && detectDistance_cm(trigPin, echoPin) > 0) {
            //     //You have detected a post on the LEFT, lets now begin to retrieve the stone!
            //     //return RETRIEVE_LEFT;
            //     #ifdef TESTING_FORK
            //         Serial.println("THERE IS A POST on the left");
            //         Serial.print(" distance: ");
            //         Serial.println(distance);
            //     #endif
            //     delay(1000);
            //     // return TURN_R_180; CHANGE
            //     return RETURN;
            // }
            //} else {
            //You have detected a regular fork on the left, lets check to see what team you are on
            //And decide which way to turn.
            //return TURN_Ll

            #ifdef FORK_HISTORY_TEST
                Serial.print(forksInPath);
                Serial.print("Current Fork Map: ");
                for (int i=0; i<forksInPath; i++) {
                    Serial.print(currentPostMap[i]);
                    Serial.print(" ");
                }
                Serial.print(" | Number of Forks Taken: ");
                Serial.print(forkHistory.size());
                Serial.print(" Last Fork We took: ");
                Serial.println(forkHistory.top());
            #endif

            int nextTurn = currentPostMap[numForksTaken];
            int forkNumber  = forkHistory.size();
            if(forkHistory.size() == forksInPath - 1){
                stopRobot();
                postLineUpTimer = millis();
                return RETRIEVE_L;
            }
            numForksTaken ++;

            if(direction == nextTurn) {
                forkHistory.push(LEFT);
                turnTimer = millis();
                return TURN_L;
            } else {
                forkHistory.push(RIGHT);
                //turnRobot(TURN_R);
                return SEARCH;
            }

        } else if(fork == FORK_ON_RIGHT) {
            forkTimer = millis();
            stopRobot();
            digitalWrite(RIGHT_FORK_LED,HIGH);
            ledTimer = millis();

            direction = RIGHT;
            #ifdef TESTING_FORK
                Serial.print("I detected a fork on the right with: ");
                Serial.print(analogRead(FORK_SENSOR_R));
             #endif
            //Serial.println("I detected a fork on the right");

            trigPin = TRIG_R;
            echoPin = ECHO_R;
            distance = detectDistance_cm(trigPin,echoPin);
            // if(detectDistance_cm(trigPin, echoPin) <= DISTANCE_THRESH   && detectDistance_cm(trigPin, echoPin) > 0) {
            //     //You have detected a post on the RIGHT, lets now begin to retrieve the stone!
            //     //return RETRIEVE_RIGHT;
            //     #ifdef TESTING_FORK
            //         Serial.println("THERE IS A POST on the right");
            //         Serial.print(" distance: ");
            //         Serial.println(distance);
            //     #endif
            //     delay(1000);
            //    // return TURN_L_180;  CHANGE
            //     return RETURN;
            // }
            //} else {
                //You have detected a regular fork on the right, lets check to see what team you are on
                //And decide which way to turn.
            #ifdef TESTING_FORK
                // Serial.print("TURNING, sonar distance: ");
                // Serial.println(distance);
            #endif
            #ifdef FORK_HISTORY_TEST
                Serial.print(forksInPath);
                Serial.print("Current Fork Map: ");
                for (int i=0; i<forksInPath; i++) {
                    Serial.print(currentPostMap[i]);
                    Serial.print(" ");
                }
                Serial.print(" | Number of Forks Taken: ");
                Serial.print(forkHistory.size());
                Serial.print(" Last Fork We took: ");
                Serial.println(forkHistory.top());
            #endif
            int nextTurn = currentPostMap[numForksTaken];
            if(forkHistory.size() == forksInPath - 1 ){
                stopRobot();
                postLineUpTimer = millis();
                return RETRIEVE_R;
            }
            numForksTaken ++;
            if(direction == nextTurn) {
                forkHistory.push(RIGHT);
                turnTimer = millis();
                return TURN_R;
            } else {
                forkHistory.push(LEFT);
                followTapeTimer = millis();
                //turnRobot(TURN_L);
                return SEARCH;
            }
        }
    }
    return SEARCH;
}



/* detectDistance_cm
 *
 * Returns the detected sonar distance in cm
 * @param : trigPin - trig pin for the corresponding sonar
 *          echoPin - echo pin for the corresponding sonar
 * @return : the distance in cm
 */
int detectDistance_cm(int trigPin,int echoPin) {
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

void printSonarValues(int trigPin, int echoPin){

        int distance =  detectDistance_cm(trigPin,echoPin);
        Serial.println("Sonar distance:");
        Serial.println(distance);



}