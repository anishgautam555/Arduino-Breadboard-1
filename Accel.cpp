#include "Accel.h"
#include "hal.h"
#include <Wire.h>

/*Default constructor*/
Accel::Accel()
{
  isRunning = false;       // The accelerometer code is deactivated by default
  module_delay = 500;      // Delay to start it is 500ms by default
}

void Accel::process()
{
  /*If actionTask is true, run the code*/
  if (actionTask())
  {
    /*Sets up the accelerometer*/
    Wire.beginTransmission(MPU_6050);
    Wire.write(XOUT_High);
    Wire.write(YOUT_High);
    Wire.write(ZOUT_High);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_6050, 6, true);

    /*If 2 or more bytes are available, then run*/
    if (Wire.available() >= 2)
    {
      /*Setting up the X, Y and Z coordinates to read*/
      AccX = Wire.read() << 8;
      AccX |= Wire.read();

      AccY = Wire.read() << 8;
      AccY |= Wire.read();

      AccZ = Wire.read() << 8;
      AccZ |= Wire.read();

      /*Assign the orientations, landscape/upside down*/
      if (abs(AccZ) > abs(AccX) & abs(AccZ) > abs(AccY)) {
        if ( AccX > -200) {
          accelInput = accCharL;     // Orientation is landscape facing the right way round
          lightPriority = 0;         // Doesn't affect lights
        }
        else {
          accelInput = accCharU;     // Board is upside down landscape
          lightPriority = 0;         // Doesn't affect lights
        }
      }

      /*Assigns flat/base up*/
      else if (abs(AccY) > abs(AccX) & abs(AccY) > abs(AccZ)) {
        if (AccX > -500) {
          accelInput = accCharF;     // Board is face up
          lightPriority = 0;         // Doesn't affect lights
        }
        else {
          accelInput = accCharB;     // Board is base up
          lightPriority = 0;         // Doesn't affect lights
        }
      }

      /*Assigns portrait left/right*/
      else if (abs(AccX) > abs(AccY) & abs(AccX) > abs(AccZ)) {
        if (AccX > 10000) {
          accelInput = accRight;     // Board is portrait right
          lightPriority = 2;         // Switches lights to priority state 2
        }
        else {
          accelInput = accLeft;      // Board is portrait left
          lightPriority = 1;         // Switches lights to priority state 1
        }
      }
    }
    module_delay = 333;             // Wait 333ms before checking again
  }
}
