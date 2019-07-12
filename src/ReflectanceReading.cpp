/*
Date: June 13, 2019
Team 3
Reads reflectance from TCRT5000
 */

#include <ReflectanceReading.h>
#include <Arduino.h>

volatile float getReflectance(int Sensor_pin, float threshold){

    if(analogRead(Sensor_pin)>threshold){
        return 1;
    }
    Serial.print("Sensor and threshold:");
    Serial.print(analogRead(Sensor_pin));
    Serial.println(threshold);

    return 0;
}

volatile int getSensorError (int leftSensor, int rightSensor, int leftSensorMemory, int rightSensorMemory) {
      //BOTH ON TAPE
    volatile int error = 0;
    if(rightSensor == 1 && leftSensor == 1){
        error = 0;
    }
    else if (rightSensor ==1 && leftSensor ==0) {
        error = -1;
    }
    else if(rightSensor == 0  && leftSensor == 1){
        error = 1;
    }
    else if(rightSensorMemory == 1){
        error = -5;
    }
    else {
        error = 5;
    }

    return error;
}


