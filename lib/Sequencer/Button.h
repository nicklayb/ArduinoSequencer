#ifndef SEQUENCER_BUTTON_H
#define SEQUENCER_BUTTON_H
#include <Arduino.h>

namespace Sequencer
{
  class Button
  {
  private:
    bool pressed = false;
    int buttonValue = LOW;
    int pin;
    int inputType;
    int buttonState();
    int pressedState();
    int unpressedState();

  public:
    Button(int pin);
    Button(int pin, int inputType);
    void read();
    void release();
    bool isPressed();
  };
}

#endif
