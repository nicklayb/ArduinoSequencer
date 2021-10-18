#ifndef SEQUENCER_LED_STRIP_H
#define SEQUENCER_LED_STRIP_H

namespace Sequencer
{
  class LedStrip
  {
  public:
    virtual void lightUp(int byte);
    virtual void lightUp(int byte, bool inverted);
  };
}

#endif
