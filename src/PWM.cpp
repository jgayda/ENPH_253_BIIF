#include <Arduino.h>
#include <PWM.h>
#include <sensors.h>



/* driveMotor()
 *
 * Generates a P M function to drive a motor using a forward motor pin and a backward motor pin.
 * For the sake of the wheel motor, this function directly interfaces with the rear H-Bridge.
 * @param : value - the voltage value mapped to bits to send to the motor to drive the appropriate speed
 *          forwardDrive - the pin that makes the wheel drive forwards when at a high value
 *          backwardDrive - the pin that makes the wheel drive backwards when at a high value
 * @returns : inputSpeed - the speed that is being written to the motor
 */
int driveMotor(uint32_t value, PinName forwardDrive, PinName backwardDrive){
  int inputSpeed = (SPEED - (value)) * speedFactor;
  pwm_start(forwardDrive, 100000, SPEED, inputSpeed, 0);
  pwm_start(backwardDrive, 100000, SPEED, 0, 0);
  return inputSpeed;
}

int driveMotorIncrease(uint32_t value, PinName forwardDrive, PinName backwardDrive) {
  int inputSpeed = (SPEED + value) * speedFactor;
  pwm_start(forwardDrive, 100000, SPEED, inputSpeed, 0);
  pwm_start(backwardDrive, 100000, SPEED, 0, 0);
  return inputSpeed;
}



/* stopRobot()
 *
 * Completely stops the robot by writing a value of 0 to both motors
 */
void stopRobot(){
  driveMotor(SPEED, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD ); //stop the wheel
  driveMotor(SPEED, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD ); // stop the wheel
}



/* turnRobot()
 *
 * Takes a direction as a variable and stops the correct side's motor so that the robot
 * turns in one direction
 * @param : direction - the direction to turn the motor
 */
void turnRobot(int direction) {
  if (direction == TURN_R){
    driveMotor(0,LEFT_WHEEL_FWD,LEFT_WHEEL_BKWD);
    //driveMotor(SPEED, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD ); //stop the wheel
    driveMotor(0,RIGHT_WHEEL_BKWD,RIGHT_WHEEL_FWD);
  }
  else {
    driveMotor(0,RIGHT_WHEEL_FWD,RIGHT_WHEEL_BKWD);
    //driveMotor(SPEED, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD ); //stop the wheel
    driveMotor(0,LEFT_WHEEL_BKWD,LEFT_WHEEL_FWD);
  }
}

void spinRobot180(int direction) {
  if (direction == TURN_R){
    driveMotor(0,LEFT_WHEEL_FWD,LEFT_WHEEL_BKWD);
    driveMotor(0, RIGHT_WHEEL_BKWD, RIGHT_WHEEL_FWD ); //stop the wheel
  }
  else {
    driveMotor(0, LEFT_WHEEL_BKWD, LEFT_WHEEL_FWD ); //stop the wheel
    driveMotor(0,RIGHT_WHEEL_FWD,RIGHT_WHEEL_BKWD);
  }
}


