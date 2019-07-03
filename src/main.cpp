#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

//TAPE FOLLOWER
#define DETECT_THRESHOLD PA0
#define TAPE_FOLLOWER_L PA5
#define TAPE_FOLLOWER_R PA6

//POST DETECTORS
#define FORK_SENSOR_L PA7
#define FORK_SENSOR_R PA8
#define ECHO_L PB4
#define TRIG_L PB5
#define ECHO_R PB6
#define TRIG_R PB7
#define DISTANCE_THRESH 14 //inches

#define OLED_RESET -1

#define INTERRUPTPIN PA4

int detectDistance();

// defines pins numbers
const int trigPin = TRIG;
const int echoPin = ECHO;

//STATUS
#define ON_TAPE 0
#define OFF_TAPE 1
#define LEFT_OFF_TAPE 2
#define RIGHT_OFF_TAPE 3
#define FORK_ON_LEFT 4
#define FORK_ON_RIGHT 5
#define POST_ON_LEFT 6
#define POST_ON_RIGHT 7

long duration;
int distance_cm;
int distance_in;
volatile int j=0;

volatile float TFL_reflectance, TFR_reflectance, FSL_reflectance, FSR_reflectance, threshold;

Adafruit_SSD1306 display(OLED_RESET);

void setup() {

  Serial.begin(115200);

  //TAPE FOLLOWER
  pinMode(DETECT_THRESHOLD, INPUT);
  pinMode(TAPE_FOLLOWER_L,INPUT);
  pinMode(TAPE_FOLLOWER_R,INPUT);

  //POST DETECTORS
  pinMode(FORK_SENSOR_L, INPUT);
  pinMode(FORK_SENSOR_R, INPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();

  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  if (analogRead(TAPE_FOLLOWER_L) && analogRead(TAPE_FOLLOWER_R)) {

    int STATUS = -1;

    TFL_reflectance = analogRead(TAPE_FOLLOWER_L);
    TFR_reflectance = analogRead(TAPE_FOLLOWER_R);
    FSL_reflectance = analogRead(FORK_SENSOR_L);
    FSR_reflectance = analogRead(FORK_SENSOR_R);
    threshold = analogRead(DETECT_THRESHOLD);

    /*    SSL   FSL   TFL   TFR   FSR   SSR
     *  |     |     |     |     |     |     |
     *  |     |     |     |     |     |     |
     *  |     |     |     |     |     |     |
     * 
     * 
     */

    //Off tape

    if(STATUS == ON_TAPE) {
      
    }
  }
}

// Returns the detected sonar distance in cm
int detectDistance_cm(int trigPin) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance_cm = pulseIn(echoPin, HIGH) * 0.034 / 2;
  return distance_cm;
}

// Returns the detected sonar distance in inches
int detectDistance_in(int trigPin) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance_in = pulseIn(echoPin, HIGH) * 0.034 / 2 * 0.393701;
  return distance_in;
}

//  if( reflectance3 > threshold && reflectance2 > threshold  || reflectance3 > threshold && reflectance1 > threshold ) {
//       int distance = detectDistance();
//         display.setTextSize(1);
//         display.setTextColor(WHITE);
//         display.setCursor(0,15);
//         display.println(distance);
//         display.display();
//         display.clearDisplay();
//       if(distance < DISTANCE_THRESH){
//         display.setTextSize(1);
//         display.setTextColor(WHITE);
//         display.setCursor(0,5);
//         display.println("on fork and detected tower");
//          display.setCursor(0,25);
//         display.println(distance);
//         display.display();
//         display.clearDisplay();
//       }
//       else{
//         display.setTextSize(1);
//         display.setTextColor(WHITE);
//         display.setCursor(0,15);
//         display.println("On fork");
//         display.display();
//         display.clearDisplay();
//       }
//     }
//     else{
//       display.setTextSize(1);
//       display.setTextColor(WHITE);
//       display.setCursor(0,15);
//       display.println("no fork");
//       display.display();
//       display.clearDisplay();
//     }
//   }