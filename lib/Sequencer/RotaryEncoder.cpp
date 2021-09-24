#include <RotaryEncoder.h>
#include <Arduino.h>

Sequencer::RotaryEncoder::RotaryEncoder(int clkPin, int dtPin)
{
  this->clkPin = clkPin;
  this->dtPin = dtPin;
  pinMode(this->dtPin, INPUT);
  pinMode(this->clkPin, INPUT);
};

void Sequencer::RotaryEncoder::read()
{
  int clkValue = digitalRead(this->clkPin);

  if (clkValue != this->previousClk)
  {
    this->previousInterim = clkValue;
  }
  else
  {
    if (clkValue != this->previousInterim)
    {
      this->previousInterim = clkValue;
      int dtValue = digitalRead(this->dtPin);

      if (clkValue != dtValue)
      {
        this->state = Backward;
      }
      else
      {
        this->state = Forward;
      }

      this->previousClk = clkValue;
    }
  }
};

void Sequencer::RotaryEncoder::release()
{
  this->state = Stale;
}

Sequencer::RotaryEncoderState Sequencer::RotaryEncoder::getState()
{
  return this->state;
}
