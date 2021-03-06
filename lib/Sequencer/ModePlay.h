#ifndef SEQUENCER_MODE_PLAY_H
#define SEQUENCER_MODE_PLAY_H

#include <ModeClocked.h>
#include <ClockSource.h>
#include <ClockHandler.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModePlay : public ModeClocked
  {
  public:
    ModePlay();
    void handleClockCycleStart();
  };
}

#endif
