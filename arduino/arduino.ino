#include <MIDI.h>
#include <SonarSRF08.h>

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

void loop()
{
  char inByte = 0;
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    // byte read, send three characters
    Serial.print("$");
    Serial.print("$");
    Serial.print("$");
        
  }
}
