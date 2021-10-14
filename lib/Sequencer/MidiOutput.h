#ifndef SEQUENCER_MIDI_OUTPUT_H
#define SEQUENCER_MIDI_OUTPUT_H

#include <NoiseMaker.h>

namespace Sequencer
{
  class MidiOutput : public NoiseMaker
  {
  private:
    int lastNote = -1;
    int messagePin;
    void sendNotePressed(int note);
    void sendNoteReleased(int note);
    void sendMessage(int command, int firstParameter, int secondParameter);

  public:
    MidiOutput(int messagePin);
    void makeNoise(int frequency, int duration);
    void makeNoise(int frequency);
    void stopNoise();
  };
}

#endif
