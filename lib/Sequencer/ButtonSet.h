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
    Potentiometer *tempoPotentiometer;

  public:
    ButtonSet(int modeSelectPin, int leftPin, int rightPin, int playPin, int tempoPotPin);
    bool playPressed();
    bool rightPressed();
    bool leftPressed();
    bool modeSelectPressed();
    void read();
    void release();
    int readTempo();
  };
}

#endif
