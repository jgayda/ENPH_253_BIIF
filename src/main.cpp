#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

//TAPE FOLLOWER
#define TAPE_FOLLOWER_L PA5
#define TAPE_FOLLOWER_R PA6

//POST DETECTORS
#define FORK_SENSOR_L PA7
#define FORK_SENSOR_R PA8
#define SONAR_L PA10
#define SONAL_R PA11
#define ECHO PB4
#define TRIG PB5

#define DETECT_THRESHOLD PA0
#define OLED_RESET -1

#define DISTANCE_THRESH 14 //inches

int detectDistance();

// defines pins numbers
const int trigPin = TRIG;
const int echoPin = ECHO;

long duration;
int distance;
int distance_in;

volatile int j=0;
#define INTERRUPTPIN PA4

volatile float reflectance1, reflectance2, reflectance3, threshold;

Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(115200);
  pinMode(OBJECT_SENSOR_1,INPUT);
  pinMode(OBJECT_SENSOR_2,INPUT);
  pinMode(DETECT_THRESHOLD, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // display.setFont(&FreeMono9pt7b);
  display.display();

  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  if (analogRead(OBJECT_SENSOR_1) && analogRead(OBJECT_SENSOR_2)){
    reflectance1 = analogRead(OBJECT_SENSOR_1);
    reflectance2 = analogRead(OBJECT_SENSOR_2);
    reflectance3 = analogRead(OBJECT_SENSOR_3);
    threshold = analogRead(DETECT_THRESHOLD);


    if( reflectance3 > threshold && reflectance2 > threshold  || reflectance3 > threshold && reflectance1 > threshold ) {
      int distance = detectDistance();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,15);
        display.println(distance);
        display.display();
        display.clearDisplay();
      if(distance < DISTANCE_THRESH){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,5);
        display.println("on fork and detected tower");
         display.setCursor(0,25);
        display.println(distance);
        display.display();
        display.clearDisplay();
      }
      else{
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,15);
        display.println("On fork");
        display.display();
        display.clearDisplay();
      }
    }
    else{
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,15);
      display.println("no fork");
      display.display();
      display.clearDisplay();
    }
  }
}

//returns distance to the sonar in inches
int detectDistance(){
  // display.setFont(&FreeMono9pt7b);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  distance_in = distance * 0.393701;
  return distance_in;
}

