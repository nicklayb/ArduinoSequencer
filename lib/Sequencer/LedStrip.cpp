#include <LedStrip.h>
#include <Arduino.h>

Sequencer::LedStrip::LedStrip(int leds[STRIP_LENGTH])
{
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    this->leds[i] = leds[i];
    pinMode(this->leds[i], OUTPUT);
  }
};

void Sequencer::LedStrip::lightUp(int byte)
{
  this->lightUp(byte, false);
};

void Sequencer::LedStrip::lightUp(int byte, bool inverted)
{
  int compareByte = 0b1;
  byte = inverted ? ~byte : byte;
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    digitalWrite(this->leds[i], byte & compareByte);
    compareByte = compareByte << 1;
  }
}
