#include <ModeRandom.h>
#include <ModeSequencing.h>
#include <MicrosecondClock.h>
#include <MidiClock.h>
#include <Application.h>

#define SCALE_LENGTH 7

Sequencer::ModeRandom::ModeRandom() : Sequencer::ModeClocked::ModeClocked() {}

void Sequencer::ModeRandom::handleClockCycleStart()
{
  int noteIndex = this->randomIndex();
  int note = this->getApplication()->getNote(noteIndex);
  this->getApplication()->getNoiseMaker()->makeNoise(note);
}

int Sequencer::ModeRandom::randomIndex()
{
  return rand() % SCALE_LENGTH;
}
