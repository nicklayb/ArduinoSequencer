#include <ButtonSet.h>
#include <Button.h>
#include <Potentiometer.h>
#include <Constants.h>

Sequencer::PotentiometerMap tempoPotentiometerMap{.outMinimum = TEMPO_POTENTIOMETER_MIN, .outMaximum = TEMPO_POTENTIOMETER_MAX};
Sequencer::PotentiometerMap clockGatePotentiometerMap{.outMinimum = CLOCK_GATE_POTENTIOMETER_MIN, .outMaximum = CLOCK_GATE_POTENTIOMETER_MAX};

Sequencer::ButtonSet::ButtonSet(int modeSelectPin, int leftPin, int rightPin, int playPin, int tempoPotentiometerPin, int clockGatePotentiometerPin, int randomPin)
{
  this->modeSelect = new Button(modeSelectPin);
  this->left = new Button(leftPin);
  this->right = new Button(rightPin);
  this->play = new Button(playPin);
  this->random = new Button(randomPin);
  this->tempoPotentiometer = new Sequencer::Potentiometer(tempoPotentiometerPin, tempoPotentiometerMap);
  this->clockGatePotentiometer = new Sequencer::Potentiometer(clockGatePotentiometerPin, clockGatePotentiometerMap);
};

bool Sequencer::ButtonSet::playPressed()
{
  return this->play->isPressed();
};

bool Sequencer::ButtonSet::rightPressed()
{
  return this->right->isPressed();
};

bool Sequencer::ButtonSet::leftPressed()
{
  return this->left->isPressed();
};

bool Sequencer::ButtonSet::randomPressed()
{
  return this->random->isPressed();
};

bool Sequencer::ButtonSet::modeSelectPressed()
{
  return this->modeSelect->isPressed();
};

void Sequencer::ButtonSet::read()
{
  this->modeSelect->read();
  this->play->read();
  this->left->read();
  this->right->read();
};

void Sequencer::ButtonSet::release()
{
  this->modeSelect->release();
  this->play->release();
  this->left->release();
  this->right->release();
};

int Sequencer::ButtonSet::readTempo()
{
  return this->tempoPotentiometer->read();
}

int Sequencer::ButtonSet::readClockGate()
{
  return this->clockGatePotentiometer->read();
}
