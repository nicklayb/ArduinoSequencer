#ifndef SEQUENCER_ROTARY_H
#define SEQUENCER_ROTARY_H
#include <Controller.h>
#include <Button.h>
#include <Encoder.h>

#define STALE 2;
#define FORWARD 1;
#define BACKWARD 0;

namespace Sequencer
{
  class Rotary : public Controller
  {
    private:
      Button* playButton;
      Button* menuButton;
      Encoder* encoder;
      int clkPin;
      int dtPin;
      int clickPin;
      int rotaryState = STALE;
      int previousClk = 0;
      int previousInterim = 0;
      void decodeValues(int clkValue, int dtValue);

    public:
      Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin);
      bool modeSelectPressed();
      bool leftPressed();
      bool rightPressed();
      bool playPressed();
      void read();
      void release();
  };
}

#endif
