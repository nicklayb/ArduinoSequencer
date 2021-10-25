#ifndef SEQUENCER_MIDI_CLOCK_H
#define SEQUENCER_MIDI_CLOCK_H

#include <ClockSource.h>
#include <ClockHandler.h>

namespace Sequencer
{
  class MidiClock : public ClockSource
  {
  private:
    int pin;
    ClockHandler *handler;
    short int pulses;
    bool readMidi();
    bool endOfBeat();
    bool startOfBeat();
    bool isRising();
    bool isFalling();

  public:
    MidiClock(int pin);
    void setHandler(ClockHandler *handler);
    void loop();
    void setTempo(unsigned long tempo);
    void setTempo(int clockGate);
  };
}

#endif
