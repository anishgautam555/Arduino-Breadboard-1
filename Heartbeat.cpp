#include "Heartbeat.h"
#include "hal.h"

/*Default constructor*/
Heartbeat::Heartbeat()
{
  isRunning = false;      // Heartbeat isn't running by default
  module_delay = 500;     // Default module delay is 500ms
  state = 0;              // Default state is 0
}

void Heartbeat::process()
{
  /*When running, switch on/off repeatedly*/
  if (actionTask())
  {
    switch (state) {
      case 0:
        heartbeatInput = dot;    // Displays the dot on the 7 segment display
        module_delay = 270;      // Waits 270ms
        state = 1;               // Change to state 1
        break;
      case 1:
        heartbeatInput = B00000000;       // Extinguishes the dot
        module_delay = 270;               // Waits 270ms
        state = 0;                        // Returns to state 0
        break;
      default:
        state = 0;                        // Defaults state to 0
        heartbeatInput = B00000000;       // Defaults the shift register input to empty
    }
  }
}
