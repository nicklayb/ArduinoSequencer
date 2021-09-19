#include <Button.h>
#include <Arduino.h>

Sequencer::Button::Button(int pin)
{
  this->pin = pin;
  pinMode(this->pin, INPUT);
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
  if (this->pressed && this->buttonValue == LOW)
  {
    this->pressed = false;
  }
};

bool Sequencer::Button::isPressed()
{
  if (!this->pressed && this->buttonValue == HIGH) {
    this->pressed = true;
    return true;
  }
  return false;
}
