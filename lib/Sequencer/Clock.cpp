#include <Clock.h>

Sequencer::Clock::Clock() {}

void Sequencer::Clock::setMaximum(int maximum)
{
  this->maximum = maximum;
}

void Sequencer::Clock::setThreshold(int threshold)
{
  this->threshold = threshold;
}

void Sequencer::Clock::tick()
{
  this->clock += 1;

  if (this->clock > this->maximum)
  {
    this->reset();
  }
}

bool Sequencer::Clock::reachedMaximum()
{
  return this->clock >= this->maximum;
}

bool Sequencer::Clock::reachedThreshold()
{
  return this->clock >= (this->maximum - this->threshold);
}

void Sequencer::Clock::reset()
{
  this->clock = 0;
}

bool Sequencer::Clock::justStarted()
{
  return this->clock == 0;
}
