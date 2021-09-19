#include <Buzzer.h>
#include <Arduino.h>

Sequencer::Buzzer::Buzzer(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
}

void Sequencer::Buzzer::buzz(int frequency)
{
  tone(this->pin, frequency);
};

void Sequencer::Buzzer::buzz(int* frequencies, int duration)
{
  for (int i = 0; frequencies[i] != NULL; i++)
  {
    buzz(frequencies[i]);
    delay(duration);
    stop();
  }
}

void Sequencer::Buzzer::buzz(int frequency, int duration)
{
  tone(this->pin, frequency, duration);
};

void Sequencer::Buzzer::stop()
{
  noTone(this->pin);
};
