#include <SoftwareSerial.h>
#include "DriveMotors.h"
#include "HCSR04.h"
#include "Mallet.h"
#include "Pins.h"
#include <Servo.h>

HCSR04 pingFront(PING_FRONT_TRIG, PING_FRONT_ECHO);
HCSR04 pingLeft(PING_LEFT_TRIG, PING_LEFT_ECHO);
HCSR04 pingRight(PING_RIGHT_TRIG, PING_RIGHT_ECHO);
SoftwareSerial xbeeComm(XBEE_DOUT, XBEE_DIN);
DriveMotors myMotors(MOTOR_LEFT_CH0, MOTOR_LEFT_CH1,
                    MOTOR_RIGHT_CH0, MOTOR_RIGHT_CH1);
Servo mallet;
//Mallet myMallet(&mallet);

byte newByte;

void setup() {
  Serial.begin(9600);
  xbeeComm.begin(9600);
  mallet.attach(MALLET_PIN);
  mallet.write(MALLET_RETRACT_POS);

  pingFront.update();
  pingLeft.update();
  pingRight.update();
  
  while (!xbeeComm.available()) {
    // Just wait until something is received
    Serial.println("Waiting for a command...");
  }
}

void loop() {
  newByte = xbeeComm.read();

  pingFront.update();
  pingLeft.update();
  pingRight.update();

  if (newByte != -1) {
    switch (newByte) {
      case '\r':
      case '\n':
      case 255:
        break;
        
      case 's':
        Serial.println("Stop command");
        myMotors.driveStop();
        break;

      case 'w':
        Serial.println("Drive forward");
        myMotors.driveForward(DRIVE_SPEED_CRUISE);
        break;

      case 'a':
        Serial.println("Turn left");
        myMotors.turnLeft(TURN_SPEED);
        break;

      case 'd':
        Serial.println("Turn right");
        myMotors.turnRight(TURN_SPEED);
        break;

      case 'q':
        Serial.println("Pivot left");
        myMotors.pivotLeft(TURN_SPEED);
        break;

      case 'e':
        Serial.println("Pivot right");
        myMotors.pivotRight(TURN_SPEED);
        break;

      case 'x':
        Serial.println("Drive reverse");
        myMotors.driveReverse(DRIVE_REVERSE_SPEED);
        break;

      case 'm':
        Serial.println("Measurement");
        byte distances[3];
        distances[0] = (byte) pingFront.getDistanceInCm();
        distances[1] = (byte) pingLeft.getDistanceInCm();
        distances[2] = (byte) pingRight.getDistanceInCm();
        
        xbeeComm.write(distances, sizeof(distances)/sizeof(byte));

        break;

      case 'p':
      case ' ':
        Serial.println("Attack!");
        mallet.write(MALLET_EXTEND_POS);
        delay(MALLET_SNAP_DURATION);
        mallet.write(MALLET_SNAP_POS);
        mallet.write(MALLET_RETRACT_POS);
        delay(MALLET_RETRACT_DURATION);
        //myMallet.swing();
        //myMallet.retract();
        break;

      default:
        Serial.print("Unknown command: ");
        Serial.println(newByte);
    }
  }
}
