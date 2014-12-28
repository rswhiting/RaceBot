#ifndef CAR_H_
#define CAR_H_

#include <Arduino.h>
#include <AFMotor.h>
#include <NewPing.h>
#define FROZEN 0

class Car {
    public:
        Car();
        double leftDist();
        double frontDist();
        void goForward();
        void goBack();
        void goLeft();
        void goRight();
        void stop();
        void print();
    private:
	double left = 0;
	double front = 0;
	String action = "";

        // Sonar
        const int MAX_PING = 200;
        const int LEFT_TRIGGER_PIN = 17;
        const int LEFT_ECHO_PIN = 18;
        const int FORWARD_TRIGGER_PIN = 14;
        const int FORWARD_ECHO_PIN = 15;
        NewPing leftSonarSensor;
        NewPing forwardSonarSensor;

        // Motors
        AF_DCMotor forwardMotor;
        AF_DCMotor turnMotor;
        const int MOTOR_SPEED = 255;
};

#endif
