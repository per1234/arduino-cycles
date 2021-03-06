/*
  Fade
  Fades on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

#include <Cycles.h>
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
unsigned long time;
SineWave wave(500, 255);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
  Serial.begin(9600); 
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

// the loop routine runs over and over again forever:
void loop() {
  time = millis();
  analogWrite(led, wave.value(time));
  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  if (stringComplete) {
    Serial.println(inputString);
    wave.setAmplitude(time, inputString.toInt(), 1000);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
