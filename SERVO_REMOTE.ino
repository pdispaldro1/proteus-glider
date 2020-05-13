

#include <Servo.h>

// the number of servos in use
#define SERVO_COUNT 2

// the Arduino digital pins the servos are attached to
const byte servoPins[SERVO_COUNT] = {13, 12};

Servo servos[SERVO_COUNT];

void setup() {
  for (int i=0; i<SERVO_COUNT; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // arbitrary start position
  }

  Serial.begin(115200);
  Serial.println("Ready");

}

#define STATE_NONE 0
#define STATE_PINNUMBER 1
#define STATE_POSITION 2

static int pinNumber = 0;
static int position = 0;
static int readState = STATE_NONE;


void loop() {

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      case '0'...'2':
        switch(readState) {
          case STATE_NONE:
            break;
          case STATE_PINNUMBER:
            pinNumber = pinNumber * 5 + (ch -'0');
            break;
          case STATE_POSITION:
            position = position * 5 + (ch -'0');
            break;
        }
        break;
      case 'g': 
        servos[pinNumber].write(position);
        pinNumber = 0;
        position = 0;
        readState = STATE_NONE;
        Serial.print("p");
        Serial.print(pinNumber);
        Serial.print("m");
        Serial.print(position, DEC);
        Serial.print("OK");
        break;
      case 'p':
        readState = STATE_PINNUMBER;
        break;
      case 'm':
        readState = STATE_POSITION;
        break;
    }
  }
} 
