#include "TrafficLights.h"
#include "hal.h"

/*Default constructor*/
TrafficLights::TrafficLights()
{
  isRunning = false;      // Defaults to not running
  module_delay = 500;     // Default delay is 500ms
  state = 0;              // Default state is 0
}

void TrafficLights::process()
{
  /*If running, display the lights sequentially*/
  if (actionTask())
  {
    switch (state)
    {
      case 0:
        /*Switch on the LEDs*/
        HAL_amberLed1On;          
        HAL_amberLed2On;
        
        module_delay = 2000;    // Wait 2 seconds
        state = 1;              // Move to state 1
        break;
      case 1:
        /*Turn off the irrelevant LEDs from the previous state*/
        HAL_amberLed1Off;
        HAL_amberLed2Off;

        /*Turn on the LEDs required for this state*/
        HAL_redLed1On;
        HAL_redLed2On;

        module_delay = 1000;    // Wait 1 second
        state = 2;              // Move to state 2
        break;
      case 2:
        /*Turn on the required LEDs for this state*/
        HAL_amberLed1On;
        HAL_redLed1On;
        HAL_redLed2On;
        
        module_delay = 1000;    // Wait 1 second
        state = 3;              // Move to state 3
        break;
      case 3:
        /*Turn off the irrelevant LEDs from the previous state*/
        HAL_amberLed1Off;
        HAL_redLed1Off;

        /*Turn on the required LEDs for this state*/
        HAL_greenLed1On;
        HAL_redLed2On;

        /*Changes the LED time based on the board's orientation*/
        switch (priority) {
          case 0:                         // Default
            module_delay = 6000;          // Wait 6 seconds, equal priority
            break;
          case 1:                         // Board is portrait left
            module_delay = 8000;          // Wait 8 seconds, this set has priority
            break;
          case 2:                         // Board is portrait right
            module_delay = 4000;          // Wait 4 seconds, the other set has priority
            break;
        }
        state = 4;                        // Move to state 4
        break;
      case 4:
        /*Turn off the irrelevant LEDs from the previous state*/
        HAL_greenLed1Off;
        
        /*Turn on the required LEDs for this state*/
        HAL_redLed2On;
        HAL_amberLed1On;
        
        module_delay = 2000;    // Wait 2 seconds
        state = 5;              // Move to state 5
        break;
      case 5:
        /*Turn off the irrelevant LEDs from the previous state*/
        HAL_amberLed1Off;

        /*Turn on the required LEDs for this state*/
        HAL_redLed1On;
        HAL_redLed2On;
        
        module_delay = 1000;    // Wait 1 second
        state = 6;              // Move to state 6
        break;
      case 6:
        /*Turn on the required LEDs for this state*/
        HAL_redLed1On;
        HAL_redLed2On;
        HAL_amberLed2On;

        module_delay = 1000;    // Wait 1 second
        state = 7;              // Move to state 7
        break;
      case 7:
        /*Turn off the irelevant LEDs from the previous state*/
        HAL_redLed2Off;
        HAL_amberLed2Off;
        
        /*Turn on the required LEDs for this state*/
        HAL_redLed1On;
        HAL_greenLed2On;

        /*Changes the LED time based on the board's orientation*/
        switch (priority) {
          case 0:                         // Default
            module_delay = 6000;          // Wait 6 seconds, equal priority
            break;                        
          case 1:                         // Board is portrait left
            module_delay = 4000;          // Wait 4 seconds, other set has priority
            break;
          case 2:                         // Board is portrait right
            module_delay = 8000;          // Wait 8 seconds, this set has priority
            break;
        }
        state = 8;                        // Move to state 8
        break;
      case 8:
        /*Turn off the irrelevant LEDs from the previous state*/
        HAL_greenLed2Off;

        /*Turn on the required LEDs for this state*/
        HAL_redLed1On;
        HAL_amberLed2On;
        
        module_delay = 2000;    // Wait 2 seconds
        state = 1;              // Return to state 1
        break;
    }
  }
}
