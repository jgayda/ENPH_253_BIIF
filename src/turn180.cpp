#include<turn180.h>

 bool forkCrossed = false;


 int turn180Robot(int direction180) {
    int direction = 0;
    if(direction180 == TURN_L_180) {
        direction = TURN_L;
    } else {
        direction = TURN_R;
    }
    //Serial.println("turning robot");
    spinRobot180(direction); //THIS IS DIFFERENT FROM TURN LEFT AND RIGHT

     int forkSensor = 0;
    int threshold = analogRead(DETECT_THRESHOLD);

     if (direction180 == TURN_L_180){
        #ifdef TESTING_FORK
            Serial.print("TURN 180 : turning left");
        #endif
      forkSensor = getReflectance(FORK_SENSOR_L, threshold);
    }
    else {
        #ifdef TESTING_FORK
            Serial.print("TURN 180 : turning right");
        #endif
      forkSensor = getReflectance(FORK_SENSOR_R, threshold);
    }

     if(forkSensor == 1 && forkCrossed == false) {
        #ifdef TESTING_FORK
            Serial.print("TURN 180 : detected fork sensor ");
        #endif
        forkCrossed = true;
    }
    int leftSensor = getReflectance(TAPE_FOLLOWER_L,threshold);
    int rightSensor = getReflectance(TAPE_FOLLOWER_R,threshold);
    if(forkCrossed == true && (rightSensor == 1 || leftSensor == 1) && forkSensor == 0){

        //Serial.println("from turn mode back to search mode");
        forkCrossed = false;
        // if(stateBefore180Turn == RETRIEVE_L || stateBefore180Turn == RETRIEVE_R) {
        //     return RETURN; //transition between return and turn
        // }
        // else { //Delete if else statement and just have return stateBefore180Turn;
        //     return stateBefore180Turn;
        // }
        return stateBefore180Turn; 
    }

     return direction180;


 }