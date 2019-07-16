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

void startDriving () {
// Set initial reflectance memory to initial reflectance value for first loop comparison
  threshold = analogRead(DETECT_THRESHOLD);
  left_reflect_memory = getReflectance(TAPE_FOLLOWER_L, threshold);
  right_reflect_memory = getReflectance(TAPE_FOLLOWER_R, threshold);
}


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
  Serial.print("PID Value: ");
  Serial.print(PIDValue);

  //BOTH ON TAPE
  if(error == 0){
    motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
    Serial.print("BOTH ON | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
   }
  //RIGHT ON TAPE, LEFT OFF TAPE --> TURN RIGHT
  else if(error == -1){
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
    Serial.print("LEFT OFF | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LEFT ON TAPE, RIGHT OFF TAPE --> TURN LEFT
  else if(error == 1){
    motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
    Serial.print("RIGHT OFF | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LAST KNOWN LOCATION ON RIGHT --> TURN LEFT
  else if(error == -5){
    motorVal_R = driveMotor(PIDValue, RIGHT_WHEEL_FWD, RIGHT_WHEEL_BKWD);
    Serial.print("LAST ON RIGHT | MotorVal_L: ");
    Serial.print(motorVal_L);
    Serial.print(" MotorVal_R: ");
    Serial.println(motorVal_R);
  }
  //LAST KNOWN LOCATION ON LEFT --> TURN RIGHT
  else if (error == 5){
      motorVal_L = driveMotor(PIDValue, LEFT_WHEEL_FWD, LEFT_WHEEL_BKWD);
      Serial.print("LAST ON LEFT | MotorVal_L: ");
      Serial.print(motorVal_L);
      Serial.print(" MotorVal_R: ");
      Serial.println(motorVal_R);
  }
  else{
    Serial.println("No valid error detected");
  }
  //update sensor memory
  if(left_reflect == 1 || right_reflect == 1 ){
      left_reflect_memory = left_reflect;
      right_reflect_memory = right_reflect;
  }

  //update previous error
    previousError = error;
    return error;
}


int detectFork () {
  Serial.print("Left Fork Sensor: ");
  int FSL_reflectance = getReflectance(FORK_SENSOR_L,threshold);
  Serial.print("Right Fork Sensor: ");
  int FSR_reflectance = getReflectance(FORK_SENSOR_R,threshold);

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