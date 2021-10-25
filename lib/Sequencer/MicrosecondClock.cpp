#include <MicrosecondClock.h>
#include <Arduino.h>
#include <Constants.h>

#define CLOCK_MULTIPLIER 50000
#define CLOCK_THRESHOLD 1000
#define RISE_MULTIPLIER 2000
#define FALL_MULTIPLER 500

Sequencer::MicrosecondClock::MicrosecondClock()
{
  this->reference = micros();
  this->current = this->reference;
  this->setTempo(TEMPO_POTENTIOMETER_MIN);
  this->setClockGate(CLOCK_GATE_POTENTIOMETER_MAX);
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
  this->riseThreshold = 10000;
}

void Sequencer::MicrosecondClock::setClockGate(int clockGate)
{
  this->fallThreshold = clockGate;
}

unsigned long Sequencer::MicrosecondClock::clockGateLength()
{
  return ((float)this->fallThreshold / (float)(CLOCK_GATE_POTENTIOMETER_MAX + 1)) * (this->tempo - CLOCK_THRESHOLD);
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
  this->hasRisen = false;
  this->hasFallen = false;
}

void Sequencer::MicrosecondClock::rise()
{
  this->handler->handleClockRise();
  this->hasRisen = true;
}

void Sequencer::MicrosecondClock::fall()
{
  this->handler->handleClockFall();
  this->hasFallen = true;
}

bool Sequencer::MicrosecondClock::isRising()
{
  return !this->hasRisen && this->diff() >= this->riseThreshold;
}

bool Sequencer::MicrosecondClock::isFalling()
{
  return !this->hasFallen && this->diff() >= this->clockGateLength();
}

bool Sequencer::MicrosecondClock::cycleIsStarting()
{
  return this->state == Stopped && this->diff() == 0;
}

bool Sequencer::MicrosecondClock::cycleIsStopping()
{
  return this->state == Started && this->diff() >= this->tempo;
}
