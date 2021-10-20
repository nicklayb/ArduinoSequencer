#ifndef SEQUENCER_CLOCK_HANDLER_H
#define SEQUENCER_CLOCK_HANDLER_H

namespace Sequencer
{
  class ClockHandler
  {
  public:
    virtual void handleClockStart();
    virtual void handleClockCycleStart();
    virtual void handleClockCycleStop();
    virtual void handleClockRise();
    virtual void handleClockFall();
    virtual void handleClockTick();
  };
}

#endif
