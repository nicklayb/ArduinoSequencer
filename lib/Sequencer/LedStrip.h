#ifndef SEQUENCER_LED_STRIP_H
#define SEQUENCER_LED_STRIP_H

#define STRIP_LENGTH 8

namespace Sequencer
{
  class LedStrip
  {
    private:
      int leds[STRIP_LENGTH];

    public:
      LedStrip(int leds[STRIP_LENGTH]);
      void lightUp(int byte);
      void lightUp(int byte, bool inverted);
  };
}

#endif
