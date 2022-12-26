#ifndef _Accel_h_
#define _Accel_h_

#include "Concurrent.h"

/*Accelerometer class, inherits from Concurrent*/
class Accel : public Concurrent {
  private:
    /*Orientation variables, only accessible in class*/
    int AccX;
    int AccY;
    int AccZ;
  public:
    /*Functions, accessible globally*/
    void process();
    Accel();

    /*Public variables, so they can be accessed globally*/
    int lightPriority;     // Used to change priority of traffic lights
    byte accelInput;       // Used to display the orientation with the heartbeat on the 7 segment display
};

#endif
