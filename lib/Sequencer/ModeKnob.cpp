#include <ModeKnob.h>
#include <Potentiometer.h>
#include <MicrosecondClock.h>
#include <MidiClock.h>
#include <Application.h>
#include <Binary.h>
#include <MidiNotes.h>

#define INPUT_BITS 3

#define ALL_NOTES                                                                                                                                                               \
  {                                                                                                                                                                             \
    NOTE_MIDI_C5, NOTE_MIDI_CS5, NOTE_MIDI_D5, NOTE_MIDI_DS5, NOTE_MIDI_E5, NOTE_MIDI_F5, NOTE_MIDI_FS5, NOTE_MIDI_G5, NOTE_MIDI_GS5, NOTE_MIDI_A5, NOTE_MIDI_AS5, NOTE_MIDI_B5 \
  }

int allNotes[] = ALL_NOTES;

Sequencer::PotentiometerMap notePotentiometer{.outMinimum = 0, .outMaximum = 12};

Sequencer::ModeKnob::ModeKnob(int inputPin) : Sequencer::ModeClocked::ModeClocked()
{
  this->potentiometer = new Sequencer::Potentiometer(inputPin, notePotentiometer);
}

void Sequencer::ModeKnob::handleClockCycleStart()
{
  int value = this->potentiometer->read();
  if (value > 0)
  {
    int note = allNotes[value - 2];
    this->getApplication()->getNoiseMaker()->makeNoise(note);
  }
}
