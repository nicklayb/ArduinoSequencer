#ifndef SEQUENCER_SERIAL_NOISE_MAKER_H
#define SEQUENCER_SERIAL_NOISE_MAKER_H

#include <NoiseMaker.h>

namespace Sequencer
{
  class SerialNoiseMaker : public NoiseMaker
  {
  public:
    SerialNoiseMaker();
    void makeNoise(int midiNote, int duration);
    void makeNoise(int midiNote);
    void fallThresholdReached();
    void riseThresholdReached();
  };
}

#endif
