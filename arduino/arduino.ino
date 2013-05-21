/***
 * Galaxie - Interactive Collection of Planets
 * Arduino Interface / MIDI & Sonar Sensor
 *
 * Leo Colombaro - 2013
 ***/

// Libraries
#include <Wire.h>
#include <MIDI.h>
#include <SonarSRF08.h>

// LEDs pins
int LED1 = 6;
int LED2 = 7;
int LED3 = 8;
int ledMidiIn = 9;

// Sonar definition
SonarSRF08 MySonar;
// Sonar parameters
#define CommandRegister 0x00
int New_Address = 248; // 0xF8
#define ResultRegister  0x02
#define GainRegister 0x00 // Setup Analogue Gain -- http://www.robot-electronics.co.uk/htm/srf08tech.html section "Analogue Gain"
#define RangeLocation 0xFF // Setup Range Location -- http://www.robot-electronics.co.uk/htm/srf08tech.html section "Changing the Range"
// Sonar variables
char unit = 'c'; // 'i' for inches, 'c' for centimeters, 'm' for micro-seconds
float sensorReading = 0;
int time = 70;

// Debug Mode
int DEBUG = 0;

// incoming serial byte
int inByte = 0;
int temp = 0;

void setup()
{
  // Initialize each digital pin as an output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(ledMidiIn, OUTPUT);

  // Launch MIDI, by default listening to channel 1, Start serial port at *31250* bps
  //MIDI.begin();
  Serial.begin(9600);

  // Initialize the SRF08 Sonar
  MySonar.connect();  
  MySonar.changeAddress(CommandRegister, New_Address, GainRegister, RangeLocation);
  New_Address += 4; 
  // Offset address not sure why this is but it works for this address
}

void loop()
{
  // If we get a valid byte, read analog ins
  if (Serial.available()) {
    // Get incoming byte
    temp = Serial.read();
    if (temp >= 0) {
      inByte = temp;
    }

    // Allow Debug
    if (DEBUG) {
      Serial.print("Serial Ready for: ");
      Serial.println(inByte);
    }

    // Analyse the request
    switch (inByte) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      // Get note
      getMidi();
      break;

    case 1:
      // Show step 1 is OK
      digitalWrite(LED1, HIGH);
      // Get note
      getMidi();
      break;

    case 2:
      // Show step 2 is OK
      digitalWrite(LED2, HIGH);
      // Get note
      getMidi();
      break;

    case 3:
      // Show all parameters as OK
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);

      /***** SRF08 - Get distance *****/
      // Set units, gain, and range location for reading out distance
      MySonar.setUnit(CommandRegister, New_Address, unit, GainRegister, RangeLocation);
      // Pause
      delay(time);
      // Set register for reading
      MySonar.setRegister(New_Address, ResultRegister);
      // Read data from result register
      sensorReading = MySonar.readData(New_Address, 2);
      // Print out distance
      Serial.println(sensorReading, 0);
      // Pause
      delay(time);
      /*****/
      break;

    default:
      // Request Invalide
      if (DEBUG) {
        Serial.println("Unknow request");
      }
    }
  } 
}

void getMidi () {
  /***** MIDI Input - Receive Message *****/
  // Is there a MIDI message incoming ?
  if (MIDI.read()) {
    // Get the type of the message we caught
    if(MIDI.getType()) {
      // If it is a Program Change
      if(midi::ProgramChange) {
        // Send the data
        Serial.println(MIDI.getData1()); 
      }
    }
  }
  /*****/
}
