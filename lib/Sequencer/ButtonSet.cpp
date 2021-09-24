#include <ButtonSet.h>
#include <Button.h>
#include <Potentiometer.h>

Sequencer::PotentiometerMap potMap{.outMinimum = 3, .outMaximum = 20};

Sequencer::ButtonSet::ButtonSet(int modeSelectPin, int leftPin, int rightPin, int playPin, int tempoPotPin)
{
  this->modeSelect = new Button(modeSelectPin);
  this->left = new Button(leftPin);
  this->right = new Button(rightPin);
  this->play = new Button(playPin);
  this->tempoPotentiometer = new Sequencer::Potentiometer(tempoPotPin, potMap);
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
