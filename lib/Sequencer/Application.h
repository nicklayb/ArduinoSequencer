#ifndef SEQUENCER_APPLICATION_H
#define SEQUENCER_APPLICATION_H

#include <ButtonSet.h>
#include <Cursor.h>
#include <Constants.h>
#include <Pitches.h>
#include <Clock.h>
#include <LedStrip.h>
#include <Pins.h>
#include <NoiseMaker.h>
#include <Controller.h>
#include <Sequence.h>
#include <Mode.h>

namespace Sequencer
{
  class Application
  {
  private:
    int *scale;
    Controller *controller;
    Cursor cursor = Cursor(0b1);
    LedStrip *ledStrip;
    NoiseMaker *noiseMaker;
    Sequence *sequence;
    Mode<Application> *mode;

  public:
    Application(int *scale, LedStrip *ledStrip, Controller *controller, NoiseMaker *noiseMaker);
    void loop();
    Sequence *getSequence();
    LedStrip *getLedStrip();
    Controller *getController();
    NoiseMaker *getNoiseMaker();
    int getNote(Cursor cursor);
    int getNote(int noteIndex);
  };
}

#endif
