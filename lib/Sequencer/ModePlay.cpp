#include <ModePlay.h>
#include <ModeSequencing.h>
#include <MicrosecondClock.h>
#include <MidiClock.h>
#include <Application.h>

Sequencer::ModePlay::ModePlay() : Sequencer::ModeClocked::ModeClocked() {}

void Sequencer::ModePlay::handleClockCycleStart()
{
  if (this->getApplication()->getSequence()->sequenceAt(this->getCursor()) > 0)
  {
    int note = this->getApplication()->getNote(this->getCursor());
    this->getApplication()->getNoiseMaker()->makeNoise(note);
  }
  else
  {
    this->getApplication()->getNoiseMaker()->fallThresholdReached();
  }
}
