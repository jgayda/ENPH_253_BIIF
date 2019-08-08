#include <Arduino.h>
#include <sensors.h>
#include <return.h>
#include<followTape.h>
#include <PWM.h>
#include <strategy.h>

int returnMode(int returnState) {
    int direction = 0;
    stateBeforeTurn = returnState;
    int fork = NO_FORK;
    int error = 10;
    int forkLocation =0;

    if(fork == NO_FORK){
        error = followTape();
    }


    if(millis() - forkTimer < forkTimerLimit) {
        error = followTape(); // don't check for fork
        return returnState;
    }



    if (abs(error) <= 5) { //change

        fork = detectFork();

        #ifdef TESTING_FORK
            // Serial.print("in search mode: fork val: ");
            // Serial.println(fork);
        #endif

        if(fork == FORK_ON_LEFT) {
            forkTimer = millis();
            #ifdef FORK_TESTING
                Serial.print("restarted fork timer: ");
                Serial.print(forkTimer);
                Serial.println("");
            #endif
            stopRobot();
            digitalWrite(LEFT_FORK_LED,HIGH);
            ledTimer = millis();
            forkLocation = LEFT;
            #ifdef TESTING_FORK
                Serial.print("I detected a fork on the left with: ");
                Serial.print(analogRead(FORK_SENSOR_L));
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

            //int nextTurn = currentPostMap[numForksTaken-1];
            int forkNumber  = forkHistory.size();
            if(forkNumber == 1){
                //you're at home fork
                // if(TEAM ==METHANOS) {
                //     turnTimer = millis();
                //     return TURN_R; //CHANGE
                // } else {
                //     turnTimer = millis();
                //     return TURN_L;
                // }
                if(returnState == RETURN) {
                    forkHistory.pop();
                    turnTimer = millis();
                    stateBeforeTurn = DEPOSIT;
                    return (TEAM == METHANOS) ? TURN_R : TURN_L;
                } else {
                    stateBefore180Turn = SEARCH;
                    return (TEAM == METHANOS) ? TURN_R_180 : TURN_L_180;
                }
            }
            if(forkNumber == 2) {
                forkHistory.pop();
                followTape();
                return returnState;
            }
            if(forkNumber == 0) { // THIS SHOULD NEVER HAPPEN

                stopRobot();// CHANGE
                return DEPOSIT;

            }
            int direction = forkHistory.top();

            if(direction == RIGHT){
                direction = LEFT;
            }else {
                direction = RIGHT;
            }
            forkHistory.pop();

            numForksTaken --;

            if(forkLocation == direction) {
                turnTimer = millis();
                return TURN_L;
            } else {
                turnTimer = millis();
                return TURN_R;
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
                        //int nextTurn = currentPostMap[numForksTaken-1];
            int forkNumber  = forkHistory.size();
            if(forkNumber == 1){
                forkHistory.pop();
                // //you're at home fork
                // if(TEAM == METHANOS) {
                //     turnTimer = millis();
                //     return TURN_R; //CHANGE
                // } else {
                //     turnTimer = millis();
                //     return TURN_L;
                // }
                if(returnState == RETURN) {
                    turnTimer = millis();
                    stateBeforeTurn = DEPOSIT;
                    return (TEAM == METHANOS) ? TURN_R : TURN_L;
                } else {
                    stateBefore180Turn = SEARCH;
                    return (TEAM == METHANOS) ? TURN_R_180 : TURN_L_180;
                }
            }
            if(forkNumber == 2) {
                forkHistory.pop(); //change
                followTape();
                return returnState;
            }
            if(forkNumber == 0) {
                stopRobot(); //CHANGE
                return DEPOSIT;
            }
            int direction = forkHistory.top();

            if(direction == RIGHT){
                direction = LEFT;
            }else {
                direction = RIGHT;
            }
            forkHistory.pop();

            numForksTaken --;

            if(forkLocation == direction) {
                turnTimer = millis();
                return TURN_R;
            } else {
                turnTimer = millis();
                return TURN_L;
            }

        }
    }
    return returnState;
    //ok
}

//Serial.print("mejans macbook air, mejans macbook air, fuck a bitch on mejans macbook air");