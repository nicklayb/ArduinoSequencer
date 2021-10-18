#ifndef SEQUENCER_MULTI_NOISE_MAKER_H
#define SEQUENCER_MULTI_NOISE_MAKER_H

#include <NoiseMaker.h>

namespace Sequencer
{
  class MultiNoiseMaker : public NoiseMaker
  {
  private:
    NoiseMaker *left;
    NoiseMaker *right;

  public:
    MultiNoiseMaker(NoiseMaker *left, NoiseMaker *right);
    void makeNoise(int midiNote, int duration);
    void makeNoise(int midiNote);
    void fallThresholdReached();
    void riseThresholdReached();
  };
}

#endif
