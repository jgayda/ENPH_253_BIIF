/*
    June 13, 2019
    Sends the required PWM to the motor
 */

#include <Arduino.h>
#include <PWM.h>
#include <sensors.h>

/*
 driveMotor: Uses PWM function to drive one wheel accordingly.
 value: the voltage value mapped to bits to send to the motor to drive the appropriate speed
 forwardDrive: the Pin that makes the wheel drive forwards when at a high value
 backwardDrive: the Pin that makes the wheel turn backwards when at a high value
 (all from the perspective of the robot)
 */
int driveMotor(uint32_t value, PinName forwardDrive, PinName backwardDrive){
    int maxSpeed = SPEED;
    int inputSpeed = (maxSpeed - (value))/2;
    pwm_start(forwardDrive, 100000, maxSpeed, inputSpeed, 1);
    pwm_start(backwardDrive, 100000, maxSpeed, 0, 1);
    return inputSpeed;

}

void stopRobot(){
    driveMotor(SPEED, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD ); //stop the wheel
    driveMotor(SPEED, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD ); // stop the wheel
}

void turnRobot(int direction) {
    if (direction == RIGHT){
        driveMotor(SPEED, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD ); //stop the wheel
    }
    else {
        driveMotor(SPEED, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD ); //stop the wheel
    }
}

