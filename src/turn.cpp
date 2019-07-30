#include <sensors.h>
#include <ReflectanceReading.h>
#include <PWM.h>
#include <turn180.h>



int turnMode (int direction) {
    int nightTimeModeTurn = 0;
    turnRobot(direction);

    if(millis() - turnTimer < turnTimerLimit){
        return direction;
    }

    int forkSensor = 0;
    int threshold = analogRead(DETECT_THRESHOLD);


    if (direction == TURN_L){
      forkSensor = getReflectance(FORK_SENSOR_R,threshold + nightTimeModeTurn);
    }
    else {
      forkSensor = getReflectance(FORK_SENSOR_L ,threshold + nightTimeModeTurn);
    }
    // if(forkSensor == 1 && forkPathCrossed == false){
    //     //Serial.println("WE CROSSED");
    //     forkPathCrossed = true;
    // }



    // &&
    int leftSensor = getReflectance(TAPE_FOLLOWER_L,threshold);
    int rightSensor = getReflectance(TAPE_FOLLOWER_R,threshold);

    if(rightSensor ==0 && leftSensor == 0) {
        forkPathCrossed = true;
    }
    #ifdef TESTING_FORK
        Serial.print("fork path crossed:");
        Serial.println(forkPathCrossed);
        Serial.print("right sensor:");
        Serial.println(rightSensor);
        Serial.print("left sensor:");
        Serial.println(leftSensor);
        Serial.print("forkSensor:");
        Serial.println(forkSensor);
    #endif
    if(forkPathCrossed == true && (rightSensor == 1 || leftSensor == 1)){
        //Serial.println("from turn mode back to search mode");
        forkPathCrossed = false;
        return stateBeforeTurn;
    }
    else {
        //Serial.print("turning roboto: ");
        //  if (direction == TURN_L){
        //         Serial.println("LEFT");
        //     } else {
        //         Serial.println("RIGHT");

        //     }
        return direction;
    }




}