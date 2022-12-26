/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Abstraction Layer (HAL) implementation          */
/* Anish Gautam / P2657398 / 13-10-2022                     */
/************************************************************/

#include "hal.h"

/*Set the data/clock/latch to low by default*/
void HAL_setupGPIO()
{
  DDRB &= ~DATA;
  DDRB &= ~CLOCK;
  DDRB &= ~LATCH;
}

/*Bring the latch high and then low again*/
void HAL_toggleLatch()
{
  PORTB |= LATCH;
  PORTB &= ~LATCH;
}

/*Brings the clock high and then low again*/
void HAL_toggleClock()
{
  PORTB |= CLOCK;
  PORTB &= ~CLOCK;
}

/*Display characters on the 7 segment display*/
void writeToShiftRegister(byte value)
{
  /*Mask to compare and bit bang*/
  byte mask = B10000000;

  /*For each bit, if the mask is the same as the value, pull the data high, otherwise keep low*/
  for (int i = 7; i >= 0; i--)
  {
    if (value & mask)
    {
      PORTB |= DATA;
    }
    else
    {
      PORTB &= ~DATA;
    }
    HAL_toggleClock();
    mask = mask >> 1;             // Move to the next bit
  }
  HAL_toggleLatch();
}
