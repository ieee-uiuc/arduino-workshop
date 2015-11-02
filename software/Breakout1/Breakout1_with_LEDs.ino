// This program controls a servo using a Piezo sensor
// If the Arduino detects movement from the Piezo sensor, rotate the servo from 0 to 180.
// Light LEDs based on position

// import the Servo library from Arduino
#include <Servo.h>

// initialize a global variable to track position
int pos;

// initialize a servo object for the code to use
Servo servo;

void setup() {
  // open the serial connection at 9600 BAUD
  Serial.begin(9600);
  
  // tell the servo object what pin to output to
  servo.attach(10);

  // set LED pins at output puns
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
 
 
void loop() {
  // store the value read from pin 0 into a variable
  int sensorValue = analogRead(0);
  Serial.println(sensorValue);
  
  // if the piezo sensor detects a touch, move the servo
  if(sensorValue < 10) {
    //Serial.println(pos);
    
    // start servo at position 0, gradually increase to position 180
    for (pos = 0; pos < 180; ++pos)
    {
      // Turn on/off LEDs based on position
      switch (pos) {
        case 0:
          digitalWrite(7, LOW);
          digitalWrite(2, HIGH);
          break;
        case 30:
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          break;
        case 60:
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          break;
        case 90:
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          break;
        case 120:
          digitalWrite(5, LOW);
          digitalWrite(6, HIGH);
          break;
        case 150:
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          break;
      }
      // Tell servo to move to new position
      servo.write(pos);
      // Sleep for 15 milliseconds
      delay(15);
    }
  }
}
