#include "DriveMotors.h"

//#define MOTOR_LEFT_CH0 3
//#define MOTOR_LEFT_CH1 11
//#define MOTOR_RIGHT_CH0  10
//#define MOTOR_RIGHT_CH1  9
#define MOTOR_LEFT_CH0 5
#define MOTOR_LEFT_CH1 6
#define MOTOR_RIGHT_CH0  11
#define MOTOR_RIGHT_CH1  3

DriveMotors myMotors(MOTOR_LEFT_CH0, MOTOR_LEFT_CH1,
                    MOTOR_RIGHT_CH0, MOTOR_RIGHT_CH1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  myMotors.driveForward(128);
  //myMotors.driveReverse(128);
  //myMotors.pivotLeft(128);
  //myMotors.pivotRight(128);
  //myMotors.turnLeft(128);
  //myMotors.turnRight(128);
}
