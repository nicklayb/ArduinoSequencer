#ifndef SEQUENCER_BUZZER_H
#define SEQUENCER_BUZZER_H

namespace Sequencer
{
  class Buzzer
  {
    private:
      int pin;
      bool silenced = false;

    public:
      Buzzer(int pin);
      void buzz(int frequency);
      void buzz(int frequency, int duration);
      void buzz(int* frequencies, int duration);
      void stop();
      void silence();
  };
}

#endif
