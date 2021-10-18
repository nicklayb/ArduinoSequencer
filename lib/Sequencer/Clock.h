#ifndef SEQUENCER_CLOCK_H
#define SEQUENCER_CLOCK_H

namespace Sequencer
{
  class Clock
  {
  private:
    int clock = 0;
    int maximum;
    int threshold;

  public:
    Clock();
    void setMaximum(int maximum);
    void setThreshold(int threshold);
    void tick();
    bool reachedMaximum();
    bool reachedFallThreshold();
    bool reachedRiseThreshold();
    void reset();
    bool justStarted();
  };
}

#endif
