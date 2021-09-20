#include <Rotary.h>
#include <Arduino.h>

Sequencer::Rotary::Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin)
{
  this->playButton = new Button(playButtonPin);
  this->menuButton = new Button(clickPin, INPUT_PULLUP);
  this->clkPin = clkPin;
  this->dtPin = dtPin;

  pinMode(this->clkPin, INPUT);
  pinMode(this->dtPin, INPUT);
}

bool Sequencer::Rotary::modeSelectPressed()
{
  return this->menuButton->isPressed();
};

bool Sequencer::Rotary::leftPressed()
{
  return this->rotaryState == FORWARD;
};

bool Sequencer::Rotary::rightPressed()
{
  return this->rotaryState == BACKWARD;
};

bool Sequencer::Rotary::playPressed()
{
  return this->playButton->isPressed();
};

void Sequencer::Rotary::read()
{
  this->playButton->read();
  this->menuButton->read();

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
        this->rotaryState = BACKWARD;
      }
      else
      {
        this->rotaryState = FORWARD;
      }

      this->previousClk = clkValue;
    }
  }
};

void Sequencer::Rotary::release()
{
  this->playButton->release();
  this->menuButton->release();
  this->rotaryState = STALE;
};
