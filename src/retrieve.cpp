/* RETRIEVE MODE
 *
 * STATUS : Robot has approached the infinity stone post such that it is aligned with the post and ready to begin
 *          to try and retrieve the stone.
 *
 * PROTOCOL : Ensure that the arm starts at 3" off of the ground (the lowest point where a midway tape marker can be located) and move up until
 *            the tape has been detected.
 *
 * POSSIBLE PREVIOUS MODES : Approach Mode
 *
 * POSSIBLE NEXT MODES : Pathfinder Mode
 *
 */

//Describes the maximum amount of times the robot will try to pick up the claw before giving up.

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

#include <sensors.h>
#include <strategy.h>
#include <search.h>
#include <time.h>
#include <math.h>

int slaveCommTimeout = 20000;

byte masterRequest();
void masterTransmit(byte buffer [3]);

//TODO: DISABLE INTERRUPTS

int retrieveMode(int direction) {
  byte slaveResponse = 200;
    //CHANGE
  byte slaveAction = PICKUP;
  byte slaveDirection = (currentPostMap[2] == LEFT) ? SLAVE_LEFT : SLAVE_RIGHT; //CHANGE;
  //byte slaveDirection = (direction == LEFT) ? SLAVE_LEFT:SLAVE_RIGHT;
  byte slaveDistance = (slaveDirection == LEFT) ? detectDistance_cm(TRIG_L,ECHO_L):detectDistance_cm(TRIG_R,ECHO_R);
  //byte slaveDistance = (direction == LEFT) ? detectDistance_cm(TRIG_L,ECHO_L):detectDistance_cm(TRIG_R,ECHO_R);



    #ifdef SLAVE_TESTING
        Serial.print("SLAVE DISTANCE: ");
        Serial.print(slaveDistance);
        Serial.print(" | SLAVE DIRECTION: ");
        Serial.println(slaveDirection);
    #endif

  byte buffer [] = {slaveAction,slaveDirection,slaveDistance};

  #ifdef SLAVE_TESTING
    Serial.print(buffer[0]);
    Serial.print(buffer[1]);
    Serial.println(buffer[2]);
#endif

  volatile byte a = 1;

  int transmisstionTimer = millis();

    #ifdef SLAVE_TESTING
        Serial.println("started transmitting");
    #endif

  for (int i = 0; i < 3 ; i++) {
    Serial3.write(buffer[i]);
  }

  int complete = 1;
  int unable = 2;


  while (Serial3.available() <= 0 || (Serial3.peek() != byte(complete) && Serial3.peek() != byte(unable))) {
    if(Serial3.peek() > 50) {
      Serial3.read();
    }
    #ifdef SERIAL_TESTING
      Serial.print("NO RESPONSE | peek --> ");
      Serial.println(Serial3.peek());
    #endif
    //if(millis() - transmisstionTimer > slaveCommTimeout) return RESET;
    //if(millis() - transmisstionTimer > slaveCommTimeout) return RESET;
  }
  // while (Serial3.available() > 0) {
  // // while (Serial3.available() > 0 && (Serial3.peek() == COMPLETE || Serial3.peek() == UNABLE))
  //   slaveResponse = Serial3.read();
  //   // if(slaveResponse == 255){
  //   //   while (Serial3.available() > 0){
  //   //     slaveResponse = Serial3.read();
  //   //   }
  //   // }
  // }

  // while (Serial3.available()<=0){
  //   //Serial.println("No response from slave...");
  // }
  slaveResponse = Serial3.read();


    #ifdef SERIAL_TESTING
      Serial.print("got something from slave: ");
      Serial.println(slaveResponse);
    #endif
    return (int(slaveResponse) == int(COMPLETE)) ? RETURN : RESET;
  }
  // while (slaveResponse != COMPLETE || slaveResponse != UNABLE) {
  //     while (Serial3.available() <= 0 ) {
  //     #ifdef SERIAL_TESTING
  //       Serial.println("NO RESPONSE");
  //     #endif
  //     if(millis() - transmisstionTimer > slaveCommTimeout) return RESET;
  //     }
  //     while (Serial3.available() > 0){

  //     }

  // }


//   while(int(masterResponse) == int(IN_PROGRESS)) {
//     #ifdef SLAVE_TESTING
//         Serial.println("arm picking up");
//       #endif
//     masterResponse = masterRequest();
//
//   }
//   #ifdef SLAVE_TESTING
//     Serial.println("OUT OF THE LOOP");
//     Serial.println(masterResponse);
//     #endif
//     pwm_start(LEFT_WHEEL_FWD, 100000, SPEED, 0, 1);
//     pwm_start(LEFT_WHEEL_BKWD, 100000, SPEED, 0, 1);
//     pwm_start(RIGHT_WHEEL_BKWD, 100000, SPEED, 0, 1);
//     pwm_start(RIGHT_WHEEL_FWD, 100000, SPEED, 0, 1);
//  return (int(masterResponse) == int(COMPLETE)) ? RETURN : RESET;




byte masterRequest() {
    delay(500);
  byte reply = Wire.requestFrom(SLAVE_ADDRESS,1);
  byte a = 200;
  delay(500);
  while (Wire.available()) {
    a = Wire.read();
    #ifdef SLAVE_TESTING
        Serial.println(a);
    #endif
  }
  return a;
}



void masterTransmit(byte buffer[3]) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(buffer,3);
  Wire.endTransmission();
  #ifdef SLAVE_TESTING
    Serial.println("Done transmission");
    #endif
    delay(1000);
}