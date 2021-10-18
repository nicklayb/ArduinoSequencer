#ifndef SEQUENCER_NOISE_MAKER_H
#define SEQUENCER_NOISE_MAKER_H

namespace Sequencer
{
  class NoiseMaker
  {
  public:
    virtual void makeNoise(int midiNote, int duration);
    virtual void makeNoise(int midiNote);
    virtual void fallThresholdReached();
    virtual void riseThresholdReached();
  };
}

#endif
