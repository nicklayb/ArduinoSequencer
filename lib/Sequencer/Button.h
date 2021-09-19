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
      int buttonState();

    public:
      Button(int pin);
      void read();
      void release();
      bool isPressed();
  };
}

#endif
