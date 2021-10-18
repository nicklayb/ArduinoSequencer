#include <MidiNotes.h>

int notes[] = NOTES;

int frequencyToMidiNote(int frequency)
{
  for (int i = 0; i < FREQ_KEY_COUNT; i++)
  {
    if (notes[i] == frequency)
    {
      return i + BASE_NOTE;
    }
  }
  return NOTE_UNDEFINED;
}

#define BASE_VOLTAGE 1000
#define BASE_MIDI_NOTE 71
#define OCTAVE_LENGTH 12

unsigned int midiNoteToVoltage(int midiNote)
{
  int note = midiNote - BASE_MIDI_NOTE;
  float ratio = ((float)note / (float)OCTAVE_LENGTH);

  return (int)(BASE_VOLTAGE + ratio * 1000);
}
