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
    void makeNoise(int frequency, int duration);
    void makeNoise(int frequency);
    void stopNoise();
  };
}

#endif
