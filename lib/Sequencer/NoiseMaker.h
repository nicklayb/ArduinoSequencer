#ifndef SEQUENCER_NOISE_MAKER_H
#define SEQUENCER_NOISE_MAKER_H

namespace Sequencer
{
  class NoiseMaker
  {
  public:
    virtual void makeNoise(int frequency, int duration);
    virtual void makeNoise(int frequency);
    virtual void stopNoise();
  };
}

#endif
