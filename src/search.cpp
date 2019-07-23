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
void printSonarValues(int trigPin, int echoPin);
int detectDistance_cm(int trigPin, int echoPin);

bool fakeFork = false;
bool passedFakeFork = true;

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
    int direction =0;
    int distance = DISTANCE_THRESH + 10 ;
    int fork = NO_FORK;
    int error = 1000;


    if(fork == NO_FORK){
        //Serial.println("Following tape, no fork detected");
        error = followTape();
    }

    // PinName trigPin;
    // PinName echoPin;

    int trigPin;
    int echoPin; 

    #ifdef TESTING_FORK
    printSonarValues(TRIG_R,ECHO_R);
    #endif

    if (abs(error) < 5) {
        fork = detectFork();
        //Serial.println(firstFork);
        // if((fork == FORK_ON_LEFT || fork == FORK_ON_RIGHT) && passedFakeFork == false){
        //     fakeFork = true;
        //     #ifdef TESTING_FORK
        //      Serial.println("I detected my first fork!!!");
        //     #endif 
        //     return SEARCH;
        // }
        // if(fakeFork == true && fork == NO_FORK && passedFakeFork == false) {
        //     passedFakeFork = true;
        //     #ifdef TESTING_FORK
        //      Serial.println("passed fake fork");
        //     #endif 
        //     return SEARCH;
        // }
        if(fork == FORK_ON_LEFT && passedFakeFork == true) {
            stopRobot();
            //Serial.println("I detected a fork on the left");
            trigPin = TRIG_L;
            echoPin = ECHO_L;
            direction = LEFT;  
            distance = detectDistance_cm(trigPin,echoPin);
            if(detectDistance_cm(trigPin, echoPin) <= DISTANCE_THRESH && detectDistance_cm(trigPin, echoPin) > 0) {
                //You have detected a post on the LEFT, lets now begin to retrieve the stone!
                //return RETRIEVE_LEFT;
                #ifdef TESTING_FORK
                    Serial.println("THERE IS A POST on the left");
                    Serial.print(" distance: ");
                    Serial.println(distance);
                #endif
                delay(1000);
                return SEARCH;
            } 
            //} else {
            //You have detected a regular fork on the left, lets check to see what team you are on 
            //And decide which way to turn.
            numFork++;
            return TURN_L; 
        } else if(fork == FORK_ON_RIGHT && passedFakeFork == true) {
            stopRobot();
            //Serial.println("I detected a fork on the right");
            trigPin = TRIG_R;
            echoPin = ECHO_R;
            direction = RIGHT;
            distance = detectDistance_cm(trigPin,echoPin);
            if(detectDistance_cm(trigPin, echoPin) <= DISTANCE_THRESH   && detectDistance_cm(trigPin, echoPin) > 0) {
                //You have detected a post on the RIGHT, lets now begin to retrieve the stone!
                //return RETRIEVE_RIGHT;
                #ifdef TESTING_FORK
                    Serial.println("THERE IS A POST on the right");
                    Serial.print(" distance: ");
                    Serial.println(distance);
                #endif
                delay(1000);
                return SEARCH;
            }
            //} else {
                //You have detected a regular fork on the right, lets check to see what team you are on
                //And decide which way to turn. 
            numFork++; 
            #ifdef TESTING_FORK
                Serial.print("TURNING, sonar distance: ");
                Serial.println(distance);
            #endif
            return TURN_R;
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
    if(millis() % 1000 == 0){
        int distance =  detectDistance_cm(trigPin,echoPin);
        Serial.println("Sonar distance:");
        Serial.println(distance);
    }


}