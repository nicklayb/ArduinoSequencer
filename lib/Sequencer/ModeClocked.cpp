#include <ModeClocked.h>
#include <ModeSequencing.h>
#include <MicrosecondClock.h>
#include <MidiClock.h>
#include <Application.h>

Sequencer::ModeClocked::ModeClocked()
{
  this->clock = new Sequencer::MicrosecondClock();
  this->clock->setHandler(this);
}

void Sequencer::ModeClocked::setupMode(Sequencer::Application *application)
{
  this->application = application;
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModeClocked::handle()
{
  this->readTempo();
  this->readClockGate();

  if (this->application->getController()->modeSelectPressed() || this->application->getController()->playPressed())
  {
    this->application->getSequence()->resetCursor();
    return new ModeSequencing();
  }

  this->clock->loop();

  return NULL;
}

void Sequencer::ModeClocked::readTempo()
{
  this->clock->setTempo(4);
  return;
  unsigned long tempo = this->application->getController()->readTempo();
  this->clock->setTempo(tempo);
}

void Sequencer::ModeClocked::readClockGate()
{
  this->clock->setClockGate(4);
  return;
  unsigned int clockGate = this->application->getController()->readClockGate();
  this->clock->setClockGate(clockGate);
}

void Sequencer::ModeClocked::handleClockStart() {}

void Sequencer::ModeClocked::handleClockCycleStart() {}

void Sequencer::ModeClocked::handleClockCycleStop()
{
  this->cursor.forward();
  this->application->getLedStrip()->lightUp(this->cursor.getPosition());
}

void Sequencer::ModeClocked::handleClockRise()
{
  this->application->getNoiseMaker()->riseThresholdReached();
}

void Sequencer::ModeClocked::handleClockFall()
{
  this->application->getNoiseMaker()->fallThresholdReached();
}

void Sequencer::ModeClocked::handleClockTick()
{
}

Sequencer::ClockSource *Sequencer::ModeClocked::getClock()
{
  return this->clock;
}

Sequencer::Application *Sequencer::ModeClocked::getApplication()
{
  return this->application;
}

Sequencer::Cursor Sequencer::ModeClocked::getCursor()
{
  return this->cursor;
}
