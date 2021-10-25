#ifndef SEQUENCER_BUTTON_SET_H
#define SEQUENCER_BUTTON_SET_H

#include <Button.h>
#include <Controller.h>
#include <Potentiometer.h>

namespace Sequencer
{
  class ButtonSet : public Controller
  {
  private:
    Button *modeSelect;
    Button *right;
    Button *left;
    Button *play;
    Button *random;
    Potentiometer *tempoPotentiometer;
    Potentiometer *clockGatePotentiometer;

  public:
    ButtonSet(int modeSelectPin, int leftPin, int rightPin, int playPin, int tempoPotentiometerPin, int clockGatePotentiometerPin, int randomPin);
    bool playPressed();
    bool rightPressed();
    bool leftPressed();
    bool modeSelectPressed();
    bool randomPressed();
    void read();
    void release();
    int readTempo();
    int readClockGate();
  };
}

#endif
