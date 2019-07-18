#include <Arduino.h>
#include <sensors.h>

//Values to tune for PID control
float k_p = 0.13 * SPEED;
float k_d= 4 * SPEED;

void PID_debugger(float error, float prevError, float dTime, float propor, float deriv);



/* PID_compute()
 * Takes in an error value, the previous DIFFERENT error value, and the difference in time between the current error and the timestamp
 * since the most previous CHANGE in error.
 * @param : error - the CURRENT measured error
 *          prevError - the previous DIFFERENT error value
 *          dTime - the difference in time between error and prevError
 * @return : PID_value - the calculated PID value which can either be:
 *                         (1) if PID_value > Maxiumum Robot Speed --> PID_value will be SPEED
 *                         (2) else the PID_value will be derivative + proportional
 */
float PID_compute (float error, float prevError, float dTime){

    float deriv = 0.0;
    if(dTime != 0){
        deriv = k_d * (error - prevError) / (dTime);
    }

    float propor = error * k_p;
    //Uncomment the next line for debugging purposes
    //PID_debugger(error, prevError, dTime, propor, deriv);
    return (abs(propor + deriv) < SPEED) ? abs(propor + deriv) : SPEED;
}



/* PID_debugger()
 * 
 * Prints out all of our error values, and the calculated needed PID values
 * For debugging purposes only :) 
 * @param : error - the CURRENT measured error
 *          prevError - the previous DIFFERENT error value
 *          dTime - the difference in time between error and prevError
 *          propor - the calculated proportional PID value
 *          deriv - the calculated derivative PID value
 */
void PID_debugger(float error, float prevError, float dTime, float propor, float deriv) {
  Serial.print("Current Error: ");
  Serial.print(error);
  Serial.print(" | Previous Error: ");
  Serial.print(prevError);
  Serial.print(" | dTime: ");
  Serial.print(dTime);
  Serial.print(" | Proportional Control: ");
  Serial.print(propor);
  Serial.print(" | Derivative Control: ");
  Serial.print(deriv);
  Serial.print(" | PID Value Written: ");
  Serial.println(abs(propor+deriv));
}