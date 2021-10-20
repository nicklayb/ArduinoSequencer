#include <Rotary.h>
#include <Arduino.h>
#include <Potentiometer.h>

Sequencer::PotentiometerMap potMap{.outMinimum = 1, .outMaximum = 10};

Sequencer::Rotary::Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin, int tempoPotPin)
{
  this->playButton = new Button(playButtonPin);
  this->menuButton = new Button(clickPin, INPUT_PULLUP);
  this->rotaryEncoder = new RotaryEncoder(clkPin, dtPin);
  this->tempoPotentiometer = new Potentiometer(tempoPotPin, potMap);
}

bool Sequencer::Rotary::modeSelectPressed()
{
  return this->menuButton->isPressed();
};

bool Sequencer::Rotary::leftPressed()
{
  return this->rotaryEncoder->getState() == Forward;
};

bool Sequencer::Rotary::rightPressed()
{
  return this->rotaryEncoder->getState() == Backward;
};

bool Sequencer::Rotary::playPressed()
{
  return this->playButton->isPressed();
};

void Sequencer::Rotary::read()
{
  this->playButton->read();
  this->menuButton->read();
  this->rotaryEncoder->read();
};

void Sequencer::Rotary::release()
{
  this->playButton->release();
  this->menuButton->release();
  this->rotaryEncoder->release();
};

int Sequencer::Rotary::readTempo()
{
  return this->tempoPotentiometer->read();
}
