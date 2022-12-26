#ifndef _TrafficLights_h_
#define _TrafficLights_h_

#include "Concurrent.h"

/*Traffic lights class, inherits from Concurrent*/
class TrafficLights : public Concurrent {
  private:
    int state;              // Declares the state of the traffic lights, only accessible by class members
  public:
    /*Functions, accessible globally*/
    void process(); 
    TrafficLights();
    
    int priority;           // Finds the priority based on orientation and determines the time LEDs stay on
};

#endif
