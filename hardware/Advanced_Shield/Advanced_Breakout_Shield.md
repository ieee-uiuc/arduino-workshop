# Breakout Two Shield
Arduino shield for the Baseline Arduino workshop.
  * 3.5 mm audio jacks in and out, with leads (and associated circuitry) to analog in pins for reading the audio into the arduino.
    * Note: Audio jacks are stereo, but signal chain is mono.
  * Analog Potentiometers read by the arduino as inputs
  * In series, two second order filters; one high pass, one low pass, with tunable digital resistors.
  * 2 Buttons (IEEE Logos)
  * Other used pins go out to headers

## Rework Instructions 
Unfortunately, we didn't get the PCB entirely right on the first go. There's two reworks that need to happen
  * Arduino GND needs to be shorted to shield ground. We can recommend using the ground's by LPF1, a small wire will fix this.
  * Potentiometers are wired backwards. In the PCB, the wiper terminally was mislabled. To fix this, you have to manually rewire the "W" and "B" terminals to swap them. Leaving the pots out doesn't affect the board overall. 