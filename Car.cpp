#include "Car.h"

Car::Car() :
    leftSonarSensor(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_PING),
    forwardSonarSensor(FORWARD_TRIGGER_PIN, FORWARD_ECHO_PIN, MAX_PING),
    forwardMotor(4),
    turnMotor(3)
    {
    // init motors
    forwardMotor.setSpeed(MOTOR_SPEED);
    forwardMotor.run(RELEASE);
    turnMotor.setSpeed(MOTOR_SPEED);
    turnMotor.run(RELEASE);
    Serial.println("Motors initialized");
}

double Car::leftDist(){
    double distance = distance = leftSonarSensor.ping() / US_ROUNDTRIP_CM;
    // get rid of interference
    left = distance > MAX_PING ? 0 : distance;
    return left;
}

double Car::frontDist(){
    double distance = distance = forwardSonarSensor.ping() / US_ROUNDTRIP_CM;
    // get rid of interference
    front = distance > MAX_PING ? 0 : distance;
    return front;
}

void Car::goBack(){
    if(!FROZEN){
        forwardMotor.run(FORWARD);
        turnMotor.run(RELEASE);
    }
    action = "Back";
}

void Car::goForward(){
    if(!FROZEN){
        forwardMotor.run(BACKWARD);
        turnMotor.run(RELEASE);
    }
    action = "Forward";
}

void Car::goLeft(){
    if(!FROZEN){
        turnMotor.run(FORWARD);
    }
    action = "Left";
}

void Car::goRight(){
    if(!FROZEN){
        turnMotor.run(BACKWARD);
    }
    action = "Right";
}

void Car::stop(){
    if(!FROZEN){
        forwardMotor.run(RELEASE);
        turnMotor.run(RELEASE);
    }
    action = "Stop";
}

void Car::print(){
    Serial.print("left ");
    if(front == 0)
      Serial.print("----");
    else
      Serial.print(left);
    Serial.print(" front ");
    if(front == 0)
      Serial.print("----");
    else
      Serial.print(front);
    Serial.print(" action ");
    Serial.print(action);
    Serial.print("\n");
}

