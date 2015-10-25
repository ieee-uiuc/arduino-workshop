// This program controls a servo using a Piezo sensor
// If the Arduino detects movement from the Piezo sensor, rotate the servo
// If the servo hits its maximum position (360ish), reset the servo position to 0 and continue onwards

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
  //Serial.println(sensorValue);
  
  // if the piezo sensor detects a touch, move the servo
  if(sensorValue < 10) {
    //Serial.println(pos);
    
    // if the servo position is already at its maximum, reset the servo's position
    for (pos = 0; pos < 360; ++pos)
    {
      pos++;
      servo.write(pos);
      delay(15);
    }
  }
}
