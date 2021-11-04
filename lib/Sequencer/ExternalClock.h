#ifndef SEQUENCER_EXTERNAL_CLOCK_H
#define SEQUENCER_EXTERNAL_CLOCK_H

#include <Arduino.h>
#include <ClockSource.h>
#include <ClockHandler.h>

namespace Sequencer
{
  class ExternalClock : public ClockSource
  {
  private:
    ClockHandler *handler;
    bool state = LOW;
    int pin;
    bool readsHigh();
    bool readsLow();
    bool isHigh();
    bool isLow();
    void setLow();
    void setHigh();

  public:
    ExternalClock(int pin);
    void setHandler(ClockHandler *handler);
    void loop();
    void setTempo(unsigned long tempo);
    void setClockGate(unsigned int clockGate);
  };
}

#endif
