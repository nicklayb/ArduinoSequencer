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
    Button *randomButton;
    Potentiometer *tempoPotentiometer;
    Potentiometer *clockGatePotentiometer;
    RotaryEncoder *rotaryEncoder;

  public:
    Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin, int tempoPotentiometerPin, int clockGatePotentiometerPin, int randomPin);
    bool modeSelectPressed();
    bool leftPressed();
    bool rightPressed();
    bool playPressed();
    bool randomPressed();
    void read();
    void release();
    int readTempo();
    int readClockGate();
  };
}

#endif
