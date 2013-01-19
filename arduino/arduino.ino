#include <Wire.h>
#include <MIDI.h>
#include <SonarSRF08.h>

int LED1 = 6;
int LED2 = 7;
int LED3 = 8;
int ledMidiIn = 9;

SonarSRF08 MySonar;

#define CommandRegister 0x00
int New_Address = 248; // 0xF8
#define ResultRegister  0x02
#define GainRegister 0x00 // Setup Analogue Gain -- http://www.robot-electronics.co.uk/htm/srf08tech.html section "Analogue Gain"
#define RangeLocation 0xFF // Setup Range Location -- http://www.robot-electronics.co.uk/htm/srf08tech.html section "Changing the Range"

int DEBUG = 1;
char unit = 'c'; // 'i' for inches, 'c' for centimeters, 'm' for micro-seconds
float sensorReading = 0;
int time = 70;

void setup()
{
  // initialize the digital pin as an output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(ledMidiIn, OUTPUT);

  // Launch MIDI, by default listening to channel 1
  MIDI.begin();

  // initialize the SRF08 Sonar
  MySonar.connect();  
  MySonar.changeAddress(CommandRegister, New_Address, GainRegister, RangeLocation);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  New_Address += 4; 
  // offset address not sure why this is but it works for this address
}

void loop()
{
  char inByte = 0;
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();

    switch (inByte) {
    case 1:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);

      getMidi();
      break;

    case 2:
      // Show Step 1 is OK
      digitalWrite(LED1, HIGH);
      getMidi();
      break;

    case 3:
      // Show Step 2 is OK
      digitalWrite(LED2, HIGH);
      getMidi();
      break;

    case 4:
      // Show all parametres OK
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);

      /***** SRF08 - Get distance *****/
      // set units, gain, and range location for reading out distance
      MySonar.setUnit(CommandRegister, New_Address, unit, GainRegister, RangeLocation);
      // pause
      delay(time);
      // set register for reading
      MySonar.setRegister(New_Address, ResultRegister);
      // read data from result register
      sensorReading = MySonar.readData(New_Address, 2);
      // print out distance
      Serial.print(sensorReading);
      Serial.println();
      // pause
      delay(time);
      break;

    default:
      // No Signal
      Serial.print("no");
      Serial.println();
    }
  }
}

void getMidi () {
  /***** MIDI Message *****/
  // Is there a MIDI message incoming ?
  if (MIDI.read()) {
    // Get the type of the message we caught
    if(MIDI.getType()) {
      // If it is a Program Change
      if(midi::ProgramChange) {
        // Send the data
        Serial.print(MIDI.getData1()); 
        Serial.println();
      }
    }
  }
}

