#include <ModePlay.h>
#include <ModeSequencing.h>
#include <MicrosecondClock.h>
#include <MidiClock.h>
#include <Application.h>

Sequencer::ModePlay::ModePlay()
{
  this->clock = new Sequencer::MicrosecondClock(10, CLOCK_THRESHOLD, CLOCK_THRESHOLD);
  // this->clock = new Sequencer::MidiClock(SERIAL_RX);
  this->clock->setHandler(this);
}

void Sequencer::ModePlay::setupMode(Sequencer::Application *application)
{
  this->application = application;
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModePlay::handle()
{
  this->readTempo();

  if (this->application->getController()->modeSelectPressed() || this->application->getController()->playPressed())
  {
    this->application->getSequence()->resetCursor();
    return new ModeSequencing();
  }

  this->clock->loop();

  return NULL;
}

void Sequencer::ModePlay::readTempo()
{
  unsigned long tempo = this->application->getController()->readTempo();
  this->clock->setTempo(tempo);
}

void Sequencer::ModePlay::handleClockStart() {}

void Sequencer::ModePlay::handleClockCycleStart()
{
  if (this->application->getSequence()->sequenceAt(this->cursor) > 0)
  {
    int note = this->application->getNote(this->cursor);
    this->application->getNoiseMaker()->makeNoise(note);
  }
  else
  {
    this->application->getNoiseMaker()->fallThresholdReached();
  }
}

void Sequencer::ModePlay::handleClockCycleStop()
{
  this->cursor.forward();
}

void Sequencer::ModePlay::handleClockRise()
{
  this->application->getNoiseMaker()->riseThresholdReached();
}

void Sequencer::ModePlay::handleClockFall()
{
  this->application->getNoiseMaker()->fallThresholdReached();
}

void Sequencer::ModePlay::handleClockTick()
{
  this->application->getLedStrip()->lightUp(this->cursor.getPosition());
}
