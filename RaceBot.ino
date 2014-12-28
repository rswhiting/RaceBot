/*
   RaceBot

   Arduino race bot designed to follow the left wall of a race course while
   keeping a foot or so away from it. 

Rules: http://robotics.pjhayward.net/rules/formula-r/

Author: Robert Whiting
Email: rswhiting@gmail.com
*/  
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <NewPing.h>
#include "Car.h"

// Car object
Car car;

// Timing & distances
#define FRONT_MIN         40
#define SIDE_MIN          15
#define SIDE_MAX          25
#define POST_ENABLED      0

void post(){
  // power on self test
  car.goForward();
  delay(3000);
  car.stop();
  delay(3000);
  car.goBack();
  delay(3000);
  car.stop();
  delay(3000);
  car.goRight();
  delay(3000);
  car.stop();
  delay(3000);
  car.goLeft();
  delay(3000);
  car.stop();
  delay(3000);
}


// SETUP #######################################################################
void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    Serial.println("Connection established");
    if(POST_ENABLED){
      Serial.println("POST start");
      post();
      Serial.println("POST complete");
    }
    // TODO: countdown?
    car.goForward();
}


// MAIN LOOP ###################################################################
void loop()
{
    // check side (turn left and adjust to wall)
    double leftDist = car.leftDist();
    if (leftDist != 0 && leftDist > SIDE_MAX){
       car.goLeft();
    }else if (leftDist != 0 && leftDist < SIDE_MIN){
      car.goRight();
    }else{
      // check forward (avoid hitting things and right turns)
      double frontDist = car.frontDist();
      if (frontDist != 0 && frontDist < FRONT_MIN){
        car.goRight();
      }else{
        car.goForward();
      }
    }
    car.print();
}


