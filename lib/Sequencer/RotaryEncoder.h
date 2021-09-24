#ifndef SEQUENCER_ROTARY_ENCODER_H
#define SEQUENCER_ROTARY_ENCODER_H

namespace Sequencer
{
  enum RotaryEncoderState
  {
    Forward,
    Stale,
    Backward
  };
  class RotaryEncoder
  {
  private:
    int clkPin;
    int dtPin;
    int previousInterim = 0;
    int previousClk = 0;
    RotaryEncoderState state = Stale;

  public:
    RotaryEncoder(int clkPin, int dtPin);
    void read();
    void release();
    RotaryEncoderState getState();
  };
}

#endif
