#include <IndividualLeds.h>
#include <Arduino.h>

Sequencer::IndividualLeds::IndividualLeds(int leds[STRIP_LENGTH])
{
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    this->leds[i] = leds[i];
    pinMode(this->leds[i], OUTPUT);
    digitalWrite(this->leds[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    digitalWrite(this->leds[i], LOW);
  }
};

void Sequencer::IndividualLeds::lightUp(int byte)
{
  this->lightUp(byte, false);
};

void Sequencer::IndividualLeds::lightUp(int byte, bool inverted)
{
  int compareByte = 0b1;
  byte = inverted ? ~byte : byte;
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    digitalWrite(this->leds[i], byte & compareByte);
    compareByte = compareByte << 1;
  }
}
