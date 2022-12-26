#ifndef _Heartbeat_h_
#define _Heartbeat_h_

#include "Concurrent.h"
#include <Arduino.h>

/*Heartbeat class, inherits from Concurrent*/
class Heartbeat : public Concurrent {
  private:
    int state;              // Gets the state of the heartbeat, only accessible by class members
  public:
    /*Functions, accessible globally*/
    void process();
    Heartbeat();
    
    byte heartbeatInput;    // Gets the heartbeat input to put onto the 7 segment display
};

#endif
