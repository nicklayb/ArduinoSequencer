#include <Arduino.h>
#include <MidiOutput.h>
#include <MidiNotes.h>

#define MIDI_BAUD_RATE 31250
#define MIDI_NOTE_ON 0x90
#define MIDI_NOTE_OFF 0x80
#define VELOCITY 0x6A

Sequencer::MidiOutput::MidiOutput(int messagePin)
{
  this->messagePin = messagePin;
  Serial.begin(MIDI_BAUD_RATE);
};

void Sequencer::MidiOutput::makeNoise(int midiNote)
{
  this->lastNote = midiNote;
  this->sendNotePressed(this->lastNote);
};

void Sequencer::MidiOutput::makeNoise(int midiNote, int duration)
{
  this->makeNoise(midiNote);
  delay(duration);
  this->sendNoteReleased(this->lastNote);
};

void Sequencer::MidiOutput::fallThresholdReached()
{
  if (this->lastNote != NOTE_UNDEFINED)
  {
    this->sendNoteReleased(this->lastNote);
  }
  this->lastNote = NOTE_UNDEFINED;
}

void Sequencer::MidiOutput::riseThresholdReached() {}

void Sequencer::MidiOutput::sendNotePressed(int note)
{
  this->sendMessage(MIDI_NOTE_ON, note, VELOCITY);
}
void Sequencer::MidiOutput::sendNoteReleased(int note)
{
  this->sendMessage(MIDI_NOTE_OFF, note, VELOCITY);
}

void Sequencer::MidiOutput::sendMessage(int command, int firstParameter, int secondParameter)
{
  Serial.write(command);
  Serial.write(firstParameter);
  Serial.write(secondParameter);
}
