#ifndef SEQUENCER_MODE_PLAY_H
#define SEQUENCER_MODE_PLAY_H

#include <Mode.h>
#include <ClockSource.h>
#include <ClockHandler.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModePlay : public Mode<Application>, public ClockHandler
  {
  private:
    Application *application;
    Cursor cursor = Cursor(0b1);
    ClockSource *clock;
    void readTempo();

  public:
    ModePlay();
    Mode<Application> *handle();
    void setupMode(Application *application);
    void handleClockStart();
    void handleClockCycleStart();
    void handleClockCycleStop();
    void handleClockRise();
    void handleClockFall();
    void handleClockTick();
  };
}

#endif
