#include <followTape.h>
#include <sensors.h>

volatile float left_reflect=0, right_reflect=0, threshold=0;
volatile int error=0;
unsigned long start_time=0;
unsigned long dt=0;
unsigned long deltaError=0;
volatile float PIDValue=0;
volatile float left_reflect_memory=0, right_reflect_memory=0;

const int speed = SPEED;

int motorVal_L=0;
int motorVal_R=0;

int nightTimeMode = 50;

/* startDriving()
 *
 * Starts driving the robot by writing max speed (SPEED) to both of the motors
 */
void startDriving () {
// Set initial reflectance memory to initial reflectance value for first loop comparison
  threshold = analogRead(DETECT_THRESHOLD);
  left_reflect_memory = getReflectance(TAPE_FOLLOWER_L, threshold);
  right_reflect_memory = getReflectance(TAPE_FOLLOWER_R, threshold);
  driveMotor(0, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
  driveMotor(0, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
}



/* followTape()
 *
 * Follows the tape, computes the position error of the robot relative to the tape, and makes
 * necessary corrections to its motor values using PID to ensure that the robot remains on the tape
 *    Robot Position State: LAST ON RIGHT  |  OFF ON LEFT  |  ON TAPE  |  OFF ON RIGHT  |  LAST ON LEFT
 *    Error Value:               -5                -1            0              1                5
 * @returns error - the integer value corresponding to the relative error of the robot's position
 */
int followTape() {
  threshold = analogRead(DETECT_THRESHOLD);
  left_reflect = getReflectance(TAPE_FOLLOWER_L, threshold);
  right_reflect = getReflectance(TAPE_FOLLOWER_R, threshold);
  error = getSensorError(left_reflect, right_reflect, left_reflect_memory, right_reflect_memory);

  unsigned long currentTime = millis();

  if(error != previousDiffError) {
    dt = currentTime - start_prev_error;
  }

  if(error != previousError){
    start_prev_error = start_curr_error;
    start_curr_error = currentTime;
    previousDiffError = previousError;
  }

  PIDValue = PID_compute(error, previousDiffError, dt);


  //BOTH ON TAPE
  if(error == 0){
    motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
   }
  //RIGHT ON TAPE, LEFT OFF TAPE --> TURN RIGHT
  else if(error == -1){
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
    motorVal_L = driveMotorIncrease(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
  }
  //LEFT ON TAPE, RIGHT OFF TAPE --> TURN LEFT
  else if(error == 1){
    motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
    motorVal_R = driveMotorIncrease(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
  }
  //LAST KNOWN LOCATION ON RIGHT --> TURN LEFT
  else if(error == -5){
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
    motorVal_L = driveMotorIncrease(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
  }
  //LAST KNOWN LOCATION ON LEFT --> TURN RIGHT
  else if (error == 5){
      motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
      motorVal_R = driveMotorIncrease(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
  }
  else{
    // Serial.println("No valid error detected");
  }

  #ifdef TESTING
    //if(millis() % 1000 == 0){
      printMotorVal(error); //DEBUG
    //}
  #endif



  //update sensor memory
  if(left_reflect == 1 || right_reflect == 1 ){
      left_reflect_memory = left_reflect;
      right_reflect_memory = right_reflect;
  }

  //update previous error
    previousError = error;
    return error;
}

void printMotorVal (int error) {
  Serial.print("PID Value: ");
  Serial.print(PIDValue);
    //BOTH ON TAPE
  if(error == 0){
    Serial.print("BOTH ON | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
   }
  //RIGHT ON TAPE, LEFT OFF TAPE --> TURN RIGHT
  else if(error == -1){
    Serial.print("LEFT OFF | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LEFT ON TAPE, RIGHT OFF TAPE --> TURN LEFT
  else if(error == 1){
    Serial.print("RIGHT OFF | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LAST KNOWN LOCATION ON RIGHT --> TURN LEFT
  else if(error == -5){
    Serial.print("LAST ON RIGHT | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LAST KNOWN LOCATION ON LEFT --> TURN RIGHT
  else if (error == 5){
      Serial.print("LAST ON LEFT | MotorVal_L: ");
      Serial.print(motorVal_L);
      Serial.print(" MotorVal_R: ");
      Serial.println(motorVal_R);
  }

}


/* detectFork()
 *
 * Checks to see if there is a fork on either side of the robot BUT ONLY if the robot
 * has an error of 0 to ensure our confidence on whether or not the robot actually sees a fork
 * @return : FORK_STATUS - Can be:
 *                      (0) NO_FORK
 *                      (1) FORK_ON_LEFT
 *                      (2) FORK_ON_RIGHT
 */
int detectFork () {

  int FSL_reflectance = getReflectance(FORK_SENSOR_L,threshold + nightTimeMode);
  int FSR_reflectance = getReflectance(FORK_SENSOR_R,threshold  + nightTimeMode);

  #ifdef TESTING
  Serial.print("Left Fork Sensor: ");
  Serial.print(analogRead(FSL_reflectance));
  Serial.print (" Right Fork Sensor: ");
  Serial.println(analogRead(FSR_reflectance));
  #endif

  if (FSL_reflectance == 1) {
    return FORK_ON_LEFT;
  }
  else if (FSR_reflectance == 1){
    return FORK_ON_RIGHT;
  }
  else {
    return NO_FORK;
  }
}