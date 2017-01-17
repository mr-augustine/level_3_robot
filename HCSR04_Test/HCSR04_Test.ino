#include "HCSR04.h"

HCSR04 myPingSensor(A0,A1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  myPingSensor.update();
  Serial.print(myPingSensor.getDistanceInCm());
  Serial.println(" cm");
  delay(500);
}
