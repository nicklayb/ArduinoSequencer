#include <Rotary.h>
#include <Arduino.h>
#include <Potentiometer.h>
#include <Constants.h>

Sequencer::PotentiometerMap tempoPotentiometerMap{.outMinimum = TEMPO_POTENTIOMETER_MIN, .outMaximum = TEMPO_POTENTIOMETER_MAX};
Sequencer::PotentiometerMap clockGatePotentiometerMap{.outMinimum = CLOCK_GATE_POTENTIOMETER_MIN, .outMaximum = CLOCK_GATE_POTENTIOMETER_MAX};

Sequencer::Rotary::Rotary(int playButtonPin, int clkPin, int dtPin, int clickPin, int tempoPotentiometerPin, int clockGatePotentiometerPin, int randomPin)
{
  this->playButton = new Button(playButtonPin);
  this->randomButton = new Button(randomPin);
  this->menuButton = new Button(clickPin, INPUT_PULLUP);
  this->rotaryEncoder = new RotaryEncoder(clkPin, dtPin);
  this->tempoPotentiometer = new Potentiometer(tempoPotentiometerPin, tempoPotentiometerMap);
  this->clockGatePotentiometer = new Potentiometer(clockGatePotentiometerPin, clockGatePotentiometerMap);
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

bool Sequencer::Rotary::randomPressed()
{
  return this->randomButton->isPressed();
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

int Sequencer::Rotary::readClockGate()
{
  return this->clockGatePotentiometer->read();
}

int Sequencer::Rotary::readTempo()
{
  return this->tempoPotentiometer->read();
}
