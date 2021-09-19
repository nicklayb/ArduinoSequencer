#ifndef SEQUENCER_BUTTON_SET_H
#define SEQUENCER_BUTTON_SET_H

#include <Button.h>

namespace Sequencer
{
  class ButtonSet
  {
    private:
      Button* modeSelect;
      Button* right;
      Button* left;
      Button* play;

    public:
      ButtonSet(int modeSelectPin, int leftPin, int rightPin, int playPin);
      bool playPressed();
      bool rightPressed();
      bool leftPressed();
      bool modeSelectPressed();
      bool anyPressed();
      void read();
      void release();
  };
}

#endif
