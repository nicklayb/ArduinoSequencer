#include <Arduino.h>
#include <MidiClock.h>
#include <ClockHandler.h>

#define CLOCK_COMMAND 0b11111000
#define PULSES_PER_QUARTER_NOTE 24
#define RISE_THRESHOLD 2
#define FALL_THRESHOLD 2

Sequencer::MidiClock::MidiClock(int pin)
{
  this->pin = pin;
  Serial.begin(31250);
}

void Sequencer::MidiClock::setHandler(ClockHandler *handler)
{
  this->handler = handler;
  this->handler->handleClockStart();
}

void Sequencer::MidiClock::setTempo(unsigned long tempo) {}

void Sequencer::MidiClock::setTempo(int clockGate) {}

void Sequencer::MidiClock::loop()
{
  if (this->startOfBeat())
  {
    this->handler->handleClockCycleStart();
  }

  if (this->endOfBeat())
  {
    this->handler->handleClockCycleStop();
  }

  if (this->isRising())
  {
    this->handler->handleClockRise();
  }

  if (this->isFalling())
  {
    this->handler->handleClockFall();
  }

  if (this->readMidi())
  {
    this->handler->handleClockTick();
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }
}

bool Sequencer::MidiClock::readMidi()
{
  digitalWrite(4, HIGH);
  byte command;
  if (Serial.available())
  {
    command = Serial.read();

    if (command == CLOCK_COMMAND)
    {
      this->pulses += 1;
      return true;
    }
  }
  digitalWrite(4, LOW);
  delay(1000);
  return false;
}

bool Sequencer::MidiClock::startOfBeat()
{
  return this->pulses == 0;
}

bool Sequencer::MidiClock::endOfBeat()
{
  return this->pulses == PULSES_PER_QUARTER_NOTE;
}

bool Sequencer::MidiClock::isFalling()
{
  return this->pulses == PULSES_PER_QUARTER_NOTE - FALL_THRESHOLD;
}

bool Sequencer::MidiClock::isRising()
{
  return this->pulses == RISE_THRESHOLD;
}
