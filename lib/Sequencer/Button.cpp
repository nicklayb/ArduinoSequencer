#include <Button.h>
#include <Arduino.h>

Sequencer::Button::Button(int pin) : Sequencer::Button::Button(pin, INPUT) {}
Sequencer::Button::Button(int pin, int inputType)
{
  this->pin = pin;
  this->inputType = inputType;
  pinMode(this->pin, this->inputType);
};

int Sequencer::Button::buttonState()
{
  return digitalRead(this->pin);
}

void Sequencer::Button::read()
{
  this->buttonValue = this->buttonState();
};

void Sequencer::Button::release()
{
  if (this->pressed && this->buttonValue == this->unpressedState())
  {
    this->pressed = false;
  }
};

bool Sequencer::Button::isPressed()
{
  if (!this->pressed && this->buttonValue == this->pressedState()) {
    this->pressed = true;
    return true;
  }
  return false;
}

int Sequencer::Button::pressedState()
{
  if (this->inputType == INPUT_PULLUP)
  {
    return LOW;
  }
  return HIGH;
}

int Sequencer::Button::unpressedState()
{
  if (this->inputType == INPUT_PULLUP)
  {
    return HIGH;
  }
  return LOW;
}
