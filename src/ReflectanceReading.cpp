#include <ReflectanceReading.h>
#include <Arduino.h>

/* getReflectance()
 * Returns 
 */
volatile float getReflectance(int Sensor_pin, float threshold){
//   if(analogRead(Sensor_pin)>threshold){
//     return 1;
//   }
//   return 0;
  return (analogRead(Sensor_pin) > threshold) ? 1 : 0;
}

/* getSensorError
 */
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


