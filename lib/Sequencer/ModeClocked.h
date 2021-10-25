#ifndef SEQUENCER_MODE_CLOCKED_H
#define SEQUENCER_MODE_CLOCKED_H

#include <Mode.h>
#include <ClockSource.h>
#include <ClockHandler.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModeClocked : public Mode<Application>, public ClockHandler
  {
  private:
    Application *application;
    Cursor cursor = Cursor(0b1);
    ClockSource *clock;
    void readTempo();
    void readClockGate();

  protected:
    Application *getApplication();
    Cursor getCursor();
    ClockSource *getClock();

  public:
    ModeClocked();
    Mode<Application> *handle();
    void setupMode(Application *application);
    virtual void handleClockStart();
    virtual void handleClockCycleStart();
    virtual void handleClockCycleStop();
    virtual void handleClockRise();
    virtual void handleClockFall();
    virtual void handleClockTick();
  };
}

#endif
