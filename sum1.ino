#include "hal.h"
#include "Concurrent.h"
#include "TrafficLights.h"
#include "Heartbeat.h"
#include "Button1.h"
#include "Button2.h"
#include "Accel.h"

#include <Wire.h>
#include <Arduino.h>

/*Class member creation*/
TrafficLights Lights;
Heartbeat Heartbeat;
Button1 LeftButton;
Button2 RightButton;
Accel Gyro;

unsigned charArray[] = {char0, char1, char2, char3, char4, char5, char6, char7, char8, char9, charA, charB, charC, charD, charE, charF};

void setup() {
  /*Sets the pins to be input or outputs, read or write*/
  DDRD |= 0b11111100;
  DDRB |= 0b00110001;
  PORTC |= 0b00000011;
  DDRC &= 0b00110000;

  LeftButton.init_module1_clock = true;
  RightButton.init_module2_clock = true;

  /*Activates serial monitor*/
  Serial.begin(9600);

  /*Start running the classes*/
  Lights.setRunning(true);
  Heartbeat.setRunning(true);
  LeftButton.setRunning(true);
  RightButton.setRunning(true);
  Gyro.setRunning(true);

  /*Sets up the accelerometer*/
  Wire.begin();
  Wire.beginTransmission(MPU_6050);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  {
    /*Ties the accelerometer input and traffic light priority together*/
    Lights.priority = Gyro.lightPriority;

    /*These are always running so turn them on outside the switch*/
    RightButton.process();
    Heartbeat.process();

    /*Determines the different modes*/
    switch(RightButton.selectState) {
      case 0:                                                                                             // State 1
        Lights.process();                                                                                 // Turn the lights on
        writeToShiftRegister(Heartbeat.heartbeatInput | charT);                                           // Display "t" and the heartbeat on the 7 segment display
        break;
      case 1:                                                                                             // State 2
        LeftButton.process();                                                                             // Turn the left button on
        writeToShiftRegister (Heartbeat.heartbeatInput | charArray[LeftButton.buttonPresses]);            // Display the heartbeat and the character array on the 7 segment display
        break;
      case 2:                                                                                             // State 3
        Gyro.process();                                                                                   // Turn on the accelerometer gyroscope
        writeToShiftRegister (Heartbeat.heartbeatInput | Gyro.accelInput);                                // Display the heartbeat and orientation on the 7 segment display
        break;
      case 3:                                                                                             // State 4
        Lights.process();                                                                                 // Turn on the lights
        LeftButton.process();                                                                             // Turn on the left button
        writeToShiftRegister(Heartbeat.heartbeatInput | charArray[LeftButton.buttonPresses]);             // Display the character array and heartbeat on the 7 segment display
        break;
      case 4:                                                                                             // State 5
        Lights.process();                                                                                 // Turn on the lights
        Gyro.process();                                                                                   // Turn on the accelerometer gyroscope
        writeToShiftRegister(Heartbeat.heartbeatInput | Gyro.accelInput);                                 // Display the heartbeat and orientation on the 7 segment display
        break;
    }
  }
}
