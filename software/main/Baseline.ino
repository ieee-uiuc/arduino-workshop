// This simple tutorial turns on an LED when a button (located in pin 9) is "pressed"
// It first initializes variables to hold the data for us to use
// Then in the initial setup, it initializes the two pins we are going to be using as
// input and output. Finally, in the loop method, it reads the value from the button
// and writes that value (either HIGH or LOW) to the LED

// initialize what LED we want to turn on + what pin the "button" is hooked up to
int ledPin = 5;
int inPin = 9;
int val = 0;

void setup() {
  // set up pin mode
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT); 
}

void loop() {
  // use digitalRead (returns either HIGH (1) or LOW (0) as it is digital)
  val = digitalRead(inPin);
  
  // use digitalWrite (accepts either a HIGH (1) or LOW (0) value) to write the value
  // of the button to the LED's pin
  digitalWrite(ledPin, val);
}
