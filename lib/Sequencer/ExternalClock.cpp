#include <ExternalClock.h>
#include <Arduino.h>

#define THRESHOLD 500

Sequencer::ExternalClock::ExternalClock(int pin)
{
  this->pin = pin;
};

void Sequencer::ExternalClock::setHandler(Sequencer::ClockHandler *handler)
{
  this->handler = handler;
  this->handler->handleClockStart();
};

void Sequencer::ExternalClock::loop()
{
  if (this->isLow() && this->readsHigh())
  {
    this->setHigh();
  }

  if (this->isHigh() && this->readsLow())
  {
    this->setLow();
  }
};

void Sequencer::ExternalClock::setHigh()
{
  this->state = HIGH;
  this->handler->handleClockTick();
  this->handler->handleClockCycleStop();
  this->handler->handleClockRise();
}

void Sequencer::ExternalClock::setLow()
{
  this->state = LOW;
  this->handler->handleClockTick();
  this->handler->handleClockFall();
  this->handler->handleClockCycleStart();
}

bool Sequencer::ExternalClock::readsHigh()
{
  return analogRead(this->pin) > THRESHOLD;
}

bool Sequencer::ExternalClock::readsLow()
{
  return analogRead(this->pin) <= THRESHOLD;
}

bool Sequencer::ExternalClock::isHigh()
{
  return this->state == HIGH;
}

bool Sequencer::ExternalClock::isLow()
{
  return this->state == LOW;
}

void Sequencer::ExternalClock::setTempo(unsigned long tempo) {}

void Sequencer::ExternalClock::setClockGate(unsigned int clockGate) {}
