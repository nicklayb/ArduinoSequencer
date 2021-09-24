#ifndef SEQUENCER_MODE_PLAY_H
#define SEQUENCER_MODE_PLAY_H

#include <Mode.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModePlay : public Mode<Application>
  {
  private:
    Cursor cursor = Cursor(0b1);
    Clock *clock;
    void readTempo(Controller *controller);

  public:
    ModePlay();
    Mode<Application> *handle(Application *application);
  };
}

#endif
