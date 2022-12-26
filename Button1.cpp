#include "Button1.h"
#include "hal.h"
#include "Concurrent.h"

#define debounce    300

/*Default constructor*/
Button1::Button1()
{
  isRunning = false; // The button counter is deactivated by default
}

void Button1::process()
{
  static unsigned long debounce_count;
  
  static switch_state_t state;

  {
    /*While clock is on, the delay is 15ms, the default is not pressed and the clock turns off*/
    if (init_module1_clock) {
      module_delay = 15;
      module_time = millis();
      module_doStep = false;
      init_module1_clock = false;
      state = NOT_PRESSED;
    }
    
    /*After this, if the button is held for longer than the module time, there is a step taken*/
    else {
      unsigned long m = millis();
      if ( ( (long)(m - module_time) ) > module_delay ) {
        module_time = m; module_doStep = true;
      }
      else module_doStep = false;
    }

    /*Debounce setup*/
    if (module_doStep) {
      switch (state) {
        case NOT_PRESSED:
          if (button1Released) state = NOT_PRESSED;
          else {
            debounce_count = millis();
            state = PARTIAL_PRESS;
          }
          break;
        case PARTIAL_PRESS:
          if (button1Released) state = NOT_PRESSED;
          else if ((millis() - debounce_count) < debounce) state = PARTIAL_PRESS;
          else state = DEBOUNCED_PRESS;
          break;
        case DEBOUNCED_PRESS:
          if (button1Released) state = NOT_PRESSED;
          else state = DEBOUNCED_PRESS;
          break;

        default:
          state = NOT_PRESSED;
          break;
      }
      B1_state = state;
    }
    {
      static switch_state_t   old;
      if (old != B1_state)
      {
        old = B1_state;
        /*When the button passes the debounce time, add a press to the counter*/
        switch (old)
        {
          case DEBOUNCED_PRESS:
            buttonPresses++;
            if (buttonPresses > 15) buttonPresses = 0;        // Return to 0 when end of array is reached
            break;
          case PARTIAL_PRESS:                                 // Do nothing if the press is partial
            break;
        }
      }
    }
  }
}
