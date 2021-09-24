#ifndef SEQUENCER_ROTARY_H
#define SEQUENCER_ROTARY_H
#include <Controller.h>
#include <Button.h>
#include <Potentiometer.h>
#include <RotaryEncoder.h>

namespace Sequencer
{
  class Rotary : public Controller
  {
  private:
    Button *playButton;
    Button *menuButton;
    Potentiometer *tempoPotentiometer;
    RotaryEncoder *rotaryEncoder;

  public:
    Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin, int tempoPotPin);
    bool modeSelectPressed();
    bool leftPressed();
    bool rightPressed();
    bool playPressed();
    void read();
    void release();
    int readTempo();
  };
}

#endif
