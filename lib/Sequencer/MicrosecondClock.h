#ifndef SEQUENCER_MILLISECOND_CLOCK_H
#define SEQUENCER_MILLISECOND_CLOCK_H

#include <ClockSource.h>
#include <ClockHandler.h>

namespace Sequencer
{
  enum MicrosecondClockState
  {
    Started,
    Risen,
    Fallen,
    Stopped
  };
  class MicrosecondClock : public ClockSource
  {
  private:
    ClockHandler *handler;
    unsigned long reference;
    unsigned long current = 0;
    unsigned int riseThreshold;
    unsigned int fallThreshold;
    unsigned long tempo;
    MicrosecondClockState state = Stopped;
    unsigned long diff();
    void cycleStart();
    void cycleStop();
    void rise();
    void fall();
    bool isRising();
    bool isFalling();
    bool cycleIsStarting();
    bool cycleIsStopping();

  public:
    MicrosecondClock(unsigned long tempo, unsigned int riseThreshold, unsigned int fallThreshold);
    void setHandler(ClockHandler *handler);
    void loop();
    void setTempo(unsigned long tempo);
  };
}

#endif
