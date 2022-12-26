#ifndef _Button2_h_
#define _Button2_h_

#include "Concurrent.h"

/*Button counter class, inherited from Concurrent*/
class Button2 : public Concurrent {
  private:
    /*Defining the different button states, only available for class members*/
    typedef enum
    {
      NOT_PRESSED2,
      PARTIAL_PRESS2,
      DEBOUNCED_PRESS2
    } switch_state_t2;
  
    switch_state_t2    B2_state;
    
  public:
    /*Functions, available globally*/
    void process();
    Button2();
   
    /*Variables, available globally*/
    int selectState;
    bool init_module2_clock;
};

#endif
