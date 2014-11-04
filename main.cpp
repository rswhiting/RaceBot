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

// Sonar
#define MAX_DISTANCE      200
#define LEFT_TRIGGER_PIN  12
#define LEFT_ECHO_PIN     11
NewPing leftSonarSensor(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE);
//#define FORWAARD_TRIGGER_PIN  12
//#define FORWARD_ECHO_PIN     11
//NewPing forwardSonarSensor(FORWARD_TRIGGER_PIN, FORWARD_ECHO_PIN, MAX_DISTANCE);

// Motors
AF_DCMotor forwardMotor(4); // pin 6
AF_DCMotor turnMotor(3);    // pin 5
#define MOTOR_SPEED       255

// Timing & distances
#define SIDE_MIN          10 // cm
#define SIDE_MAX          15 // cm

// FUNCTIONS ###################################################################

double leftPing() {
    double distance = distance = leftSonarSensor.ping() / US_ROUNDTRIP_CM;
        Serial.print("Left Ping: ");
        Serial.print(distance);
        Serial.println("cm");
    return distance;
}

double forwardPing() {
    //    double distance = distance = forwardSonarSensor.ping() / US_ROUNDTRIP_CM;
    //    Serial.print("Left Ping: ");
    //    Serial.print(distance);
    //    Serial.println("cm");
    //    return distance;
    return MAX_DISTANCE;
}

void forward() {
    forwardMotor.run(FORWARD);
    turnMotor.run(RELEASE);
    Serial.println("Onward!");
}

void forwardRight() {
    forwardMotor.run(FORWARD);
    turnMotor.run(FORWARD);
    Serial.println("Right!");
}

void forwardLeft() {
    forwardMotor.run(FORWARD);
    turnMotor.run(BACKWARD);
    Serial.println("Left!");
}

void stop() {
    forwardMotor.run(RELEASE);
    turnMotor.run(RELEASE);
    Serial.println("Stop!");
}

void backward() {
    forwardMotor.run(BACKWARD);
    turnMotor.run(RELEASE);
    Serial.println("Back!");
}

// SETUP #######################################################################

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("Connection established");
    // init motors
    forwardMotor.setSpeed(MOTOR_SPEED);
    forwardMotor.run(RELEASE);
    turnMotor.setSpeed(MOTOR_SPEED);
    turnMotor.run(RELEASE);
}

// MAIN LOOP ###################################################################

void loop() {
    // check forward (avoid hitting things and right turns)
    // TODO

    // check side (turn left and adjust to wall)
    double leftDist = leftPing();
    if (leftDist > SIDE_MAX)
        forwardRight();
    else if (leftDist < SIDE_MIN)
        forwardLeft();
    else
        forward();
}
