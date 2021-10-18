#ifndef SEQUENCER_INDIVIDUAL_LEDS_H
#define SEQUENCER_INDIVIDUAL_LEDS_H

#include <LedStrip.h>

#define STRIP_LENGTH 8

namespace Sequencer
{
  class IndividualLeds : public LedStrip
  {
  private:
    int leds[STRIP_LENGTH];

  public:
    IndividualLeds(int leds[STRIP_LENGTH]);
    void lightUp(int byte);
    void lightUp(int byte, bool inverted);
  };
}

#endif
