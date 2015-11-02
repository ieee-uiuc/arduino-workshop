// This program controls a servo using a Piezo sensor
// If the Arduino detects movement from the Piezo sensor, rotate the servo from 0 to 180.

// import the Servo library from Arduino
#include <Servo.h>

// initialize a global variable to track position
int pos = 0;

// initialize a servo object for the code to use
Servo servo;

void setup() {
  // open the serial connection at 9600 BAUD
  Serial.begin(9600);
  
  // tell the servo object what pin to output to
  servo.attach(10);
}
 
 
void loop() {
  // store the value read from pin 0 into a variable
  int sensorValue = analogRead(0);
  // Serial.println(sensorValue);
  
  // if the piezo sensor detects a touch, move the servo
  if(sensorValue < 10) {
    // Serial.println(pos);
    
    // gradually move servo from position 0 to position 180
    for (pos = 0; pos < 180; ++pos)
    {
      servo.write(pos);
      delay(15);
    }
  }
}
