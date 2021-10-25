#ifndef SEQUENCER_MODE_RANDOM_H
#define SEQUENCER_MODE_RANDOM_H

#include <ModeClocked.h>
#include <ClockSource.h>
#include <ClockHandler.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModeRandom : public ModeClocked
  {
  private:
    int randomIndex();

  public:
    ModeRandom();
    void handleClockCycleStart();
  };
}

#endif
