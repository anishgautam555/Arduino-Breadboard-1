#include "Button2.h"
#include "hal.h"
#include "Concurrent.h"

#define debounce    300

/*Default constructor*/
Button2::Button2()
{
  isRunning = false; // The button counter is deactivated by default
  selectState = 0;   // The default state is 0;
}

void Button2::process()
{
  static unsigned long debounce_count;
  static switch_state_t2 state;

  /*Inititalisation before the clock is turned off, defaults to not pressed*/
  if (init_module2_clock) {
      module_delay = 15;
      module_time=millis();
      module_doStep=false;
      init_module2_clock=false;
      state= NOT_PRESSED2;
    }
    /*If it is pressed with the clock off, a step is taken*/
    else {
      unsigned long m=millis();
      if ( ( (long)(m - module_time) ) > module_delay ) {
        module_time = m; module_doStep = true;
      }
      else module_doStep = false;
    }
    
    /*Debounce setup*/
    if (module_doStep) {
      switch(state){
          case NOT_PRESSED2: 
            if (button2Released) state= NOT_PRESSED2;
            else {
              debounce_count = millis();
              state= PARTIAL_PRESS2;
            }
            break;
          case PARTIAL_PRESS2: 
            if (button2Released) state= NOT_PRESSED2;
            else if ((millis()-debounce_count) < debounce) state= PARTIAL_PRESS2;
            else state= DEBOUNCED_PRESS2;
            break;
          case DEBOUNCED_PRESS2: 
            if (button2Released) state= NOT_PRESSED2;
            else state= DEBOUNCED_PRESS2;
            break;
          
          default: 
            state= NOT_PRESSED2; 
            break;
      }  
      B2_state = state;
    }
  
    
  {
    static switch_state_t2   old;
    if (old != B2_state)
    {
      old = B2_state;
      
      /*If the press passes the debounce time, the state is changed*/
      switch(old)
      {
      case DEBOUNCED_PRESS2:
        selectState++;
        if (selectState > 4) selectState = 0;     // Return to 0 after the final state
        Serial.print("The current state is ");
        Serial.println(selectState);
        break;
      case PARTIAL_PRESS2:                        // Do nothing if the press is partial
        break;
      }
      }
    }
 }
