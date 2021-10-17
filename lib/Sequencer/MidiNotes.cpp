#include <MidiNotes.h>

int notes[] = NOTES;

int frequencyToMidiNote(int frequency)
{
  for (int i = 0; i < KEY_COUNT; i++)
  {
    if (notes[i] == frequency)
    {
      return i + BASE_NOTE;
    }
  }
  return NOTE_UNDEFINED;
}
