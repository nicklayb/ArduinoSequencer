#ifndef SEQUENCER_APPLICATION_H
#define SEQUENCER_APPLICATION_H

#include <ButtonSet.h>
#include <Cursor.h>
#include <Constants.h>
#include <Pitches.h>
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
    LedStrip *ledStrip;
    NoiseMaker *noiseMaker;
    Sequence *sequence;
    Mode<Application> *mode;

  public:
    Application(int *scale, LedStrip *ledStrip, Controller *controller, NoiseMaker *noiseMaker);
    Application(int *scale, LedStrip *ledStrip, Controller *controller, NoiseMaker *noiseMaker, Mode<Application> *mode);
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
