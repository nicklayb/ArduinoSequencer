#ifndef SEQUENCER_MODE_KNOB_H
#define SEQUENCER_MODE_KNOB_H

#include <ModeClocked.h>
#include <ClockSource.h>
#include <ClockHandler.h>
#include <Cursor.h>
#include <Potentiometer.h>
#include <Application.h>

namespace Sequencer
{
  class ModeKnob : public ModeClocked
  {
  private:
    Potentiometer *potentiometer;

  public:
    ModeKnob(int inputPin);
    void handleClockCycleStart();
  };
}

#endif
