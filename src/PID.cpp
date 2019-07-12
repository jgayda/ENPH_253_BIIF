#include <Arduino.h>

#include <sensors.h>

/*
*June 13th 2019
*Krysten Zissos
*This function takes a float error value, a float previous error value, and a float change in time value (time since error last changed).
*It outputs an int, g, as a value scaled by PID control
*/
//Values to tune for PID control
int maxSpeed = SPEED;
float k_p = 0.1 * maxSpeed;
float k_d=100 * maxSpeed;

float PID_compute (float error, float prevError, float dTime){
    float d = 0.0;
    if(dTime == 0){
        k_d = 0;
    }
    else{
        d=k_d*(error-prevError)/dTime;
    }
    Serial.print("prevError: ");
    Serial.print(prevError);
    Serial.print(" dTime: ");
    Serial.print(dTime);
    Serial.print(" ");
    float p=error*k_p;
    float g=abs(p+d);

    // clamps the PID so we won't explode
    if(g > maxSpeed){
        g = maxSpeed;
    }
    //scales g value to an integer from 1-250, was 500 originally in h bridge lab
   // g = 20 * g;
    return g;
}