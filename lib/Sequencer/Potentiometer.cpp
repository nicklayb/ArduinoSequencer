#include <Potentiometer.h>
#include <Arduino.h>

Sequencer::Potentiometer::Potentiometer(int pin, Sequencer::PotentiometerMap mapValues)
{
  this->pin = pin;
  this->mapValues = mapValues;
  pinMode(this->pin, INPUT);
};

int Sequencer::Potentiometer::read()
{
  return map(this->readRaw(), 0, 1023, this->mapValues.outMinimum, this->mapValues.outMaximum);
}

int Sequencer::Potentiometer::readRaw()
{
  return analogRead(this->pin);
}
