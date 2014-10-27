/*
    Racebot

    Arduino race bot designed to follow the left wall of a race course while
    keeping a foot or so away from it. The code should utilize a pwm pin to
    hijack an rc car's antenna for control and use a sonar sensor for left
    wall following.

    Realtek RX2 (RX2B) Control via Arduino code taken from David Bernier:
    https://github.com/monsieurDavid/
    GPL v3 License

    Rules: http://robotics.pjhayward.net/rules/formula-r/

    Author: Robert Whiting
    Email: rswhiting@gmail.com
*/
#include <SoftwareSerial.h>

// Fixed durations as per RX2B datasheet see http://www.datasheetdir.com/RX-2B+download
#define ENDCODE         4
#define FORWARD        10
#define FORWARD_TURBO  16
#define TURBO          22 // not supported, but good to know
#define FORWARD_LEFT   28
#define FORWARD_RIGHT  34
#define BACKWARD       40
#define BACKWARD_RIGHT 46
#define BACKWARD_LEFT  52
#define LEFT           58
#define RIGHT          64

// output pins
#define ANTENNA     9
bool trigger_on = false;

void setup()  
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    pinMode(ANTENNA, OUTPUT);
  
    Serial.println("Connection established");
}

void loop() // run over and over
{
    read();
}

void read(){
    static int v = 0;

    if ( Serial.available()) {
        char ch = Serial.read();

        switch(ch) {
            case 's': // coast
                trigger(ENDCODE);
                trigger_on = false;
                break;
            case 'w': // forward
                break;
            case 'q': // forward-left
                break;
            case 'e': // forward-right
                break;
            case 'x': // backward
                break;
            case 'z': // backward-left
                break;
            case 'c': // backward-right
                break;
        }
    }

    //Send the command, if any, to the toy
    if (trigger_on == true) {
        trigger(mode);
    } 

}


void trigger(int mode) {

    //start code sequence
    for (int w2 = 0; w2 < 4; w2++) {
        currentMicros = micros();
        while (micros() - currentMicros < 1500) {
            digitalWrite(ANTENNA, HIGH);
            digitalWrite(STATUS_LED, HIGH);
        }
        while (micros() - currentMicros < 2000) {
            digitalWrite(ANTENNA, LOW);
            digitalWrite(STATUS_LED, LOW);
        }
    }

    //function code sequence
    for (int w1 = 0; w1 < mode; w1++) {
        currentMicros = micros();
        while (micros() - currentMicros < 500) {
            digitalWrite(ANTENNA, HIGH);
            digitalWrite(STATUS_LED, HIGH);
        }
        while (micros() - currentMicros < 1000) {
            digitalWrite(ANTENNA, LOW);
            digitalWrite(STATUS_LED, LOW);
        }
    }

}

