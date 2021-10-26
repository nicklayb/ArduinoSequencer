#ifndef SEQUENCER_MULTIPLEXED_8_BIT_H
#define SEQUENCER_MULTIPLEXED_8_BIT_H

#include <LedStrip.h>

#define INPUT_BITS 3
#define STRIP_LENGTH 8

namespace Sequencer
{
  class Multiplexed8Bit : public LedStrip
  {
  private:
    int topRow[INPUT_BITS];
    int bottomRow[INPUT_BITS];
    int *getRow(bool inverted);

  public:
    Multiplexed8Bit(int topRow[INPUT_BITS], int bottomRow[INPUT_BITS]);
    void lightUp(int byte);
    void lightUp(int byte, bool inverted);
  };
}

#endif
