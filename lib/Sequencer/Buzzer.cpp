#include <Buzzer.h>
#include <Arduino.h>

Sequencer::Buzzer::Buzzer(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
}

void Sequencer::Buzzer::buzz(int frequency)
{
  if (!this->silenced)
    tone(this->pin, frequency);
};

void Sequencer::Buzzer::buzz(int *frequencies, int duration)
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
  if (!this->silenced)
    tone(this->pin, frequency, duration);
};

void Sequencer::Buzzer::stop()
{
  if (!this->silenced)
    noTone(this->pin);
};

void Sequencer::Buzzer::silence()
{
  this->silenced = true;
}

void Sequencer::Buzzer::makeNoise(int frequency)
{
  this->buzz(frequency);
}

void Sequencer::Buzzer::makeNoise(int frequency, int duration)
{
  this->buzz(frequency, duration);
}

void Sequencer::Buzzer::fallThresholdReached()
{
  this->stop();
}

void Sequencer::Buzzer::riseThresholdReached() {}
