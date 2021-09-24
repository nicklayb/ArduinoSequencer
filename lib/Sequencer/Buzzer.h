#ifndef SEQUENCER_BUZZER_H
#define SEQUENCER_BUZZER_H

#include <NoiseMaker.h>

namespace Sequencer
{
  class Buzzer : public NoiseMaker
  {
  private:
    int pin;
    bool silenced = false;

  public:
    Buzzer(int pin);
    void buzz(int frequency);
    void buzz(int frequency, int duration);
    void buzz(int *frequencies, int duration);
    void stop();
    void silence();
    void makeNoise(int frequency);
    void makeNoise(int frequency, int duration);
    void stopNoise();
  };
}

#endif
