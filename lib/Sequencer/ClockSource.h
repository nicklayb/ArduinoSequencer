#ifndef SEQUENCER_CLOCK_SOURCE_H
#define SEQUENCER_CLOCK_SOURCE_H

#include <ClockHandler.h>

namespace Sequencer
{
  class ClockSource
  {
  public:
    virtual void setHandler(ClockHandler *handler);
    virtual void loop();
    virtual void setTempo(unsigned long tempo);
    virtual void setClockGate(int clockGate);
  };
}

#endif
