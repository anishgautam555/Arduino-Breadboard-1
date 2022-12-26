#ifndef _Button1_h_
#define _Button1_h_

#include "Concurrent.h"
#include "hal.h"
#include <Arduino.h>

/*Button counter class, inherited from Concurrent*/
class Button1 : public Concurrent {
  private:
    /*Defining the different button states, only available for class members*/
    typedef enum
    {
      NOT_PRESSED,
      PARTIAL_PRESS,
      DEBOUNCED_PRESS
    } switch_state_t;
    
    switch_state_t    B1_state;
  
  public:
    /*Functions, available globally*/
    void process();
    Button1();

    /*Variables, available globally*/
    int buttonPresses;                   // Counts how many times the button has been pressed
    bool init_module1_clock;
};

#endif
