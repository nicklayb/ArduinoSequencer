#include <MicrosecondClock.h>
#include <Arduino.h>
#include <Constants.h>

Sequencer::MicrosecondClock::MicrosecondClock(unsigned long tempo, unsigned int riseThreshold, unsigned int fallThreshold)
{
  this->reference = micros();
  this->current = this->reference;
  this->riseThreshold = riseThreshold;
  this->fallThreshold = fallThreshold;
  this->setTempo(tempo);
}

void Sequencer::MicrosecondClock::setHandler(ClockHandler *handler)
{
  this->handler = handler;
  this->handler->handleClockStart();
}

void Sequencer::MicrosecondClock::loop()
{
  this->handler->handleClockTick();

  if (this->cycleIsStopping())
  {
    this->cycleStop();
  }
  else
  {
    if (this->cycleIsStarting())
    {
      this->cycleStart();
    }
    else if (this->isFalling())
    {
      this->fall();
    }
    else if (this->isRising())
    {
      this->rise();
    }
    this->current = micros();
  }
}

void Sequencer::MicrosecondClock::setTempo(unsigned long tempo)
{
  this->tempo = tempo * CLOCK_MULTIPLIER;
  this->riseThreshold = 2000 * tempo;
  this->fallThreshold = 1000 * tempo;
}

unsigned long Sequencer::MicrosecondClock::diff()
{
  return this->current - this->reference;
}

void Sequencer::MicrosecondClock::cycleStart()
{
  this->handler->handleClockCycleStart();
  this->state = Started;
}

void Sequencer::MicrosecondClock::cycleStop()
{
  this->handler->handleClockCycleStop();
  this->state = Stopped;
  this->reference = micros();
  this->current = this->reference;
}

void Sequencer::MicrosecondClock::rise()
{
  this->handler->handleClockRise();
  this->state = Risen;
}

void Sequencer::MicrosecondClock::fall()
{
  this->handler->handleClockFall();
  this->state = Fallen;
}

bool Sequencer::MicrosecondClock::isRising()
{
  return this->state == Started && this->diff() >= this->riseThreshold;
}

bool Sequencer::MicrosecondClock::isFalling()
{
  return this->state == Risen && this->diff() >= this->tempo - this->fallThreshold;
}

bool Sequencer::MicrosecondClock::cycleIsStarting()
{
  return this->state == Stopped && this->diff() == 0;
}

bool Sequencer::MicrosecondClock::cycleIsStopping()
{
  return this->state == Fallen && this->diff() >= this->tempo;
}
