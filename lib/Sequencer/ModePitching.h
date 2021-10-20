#ifndef SEQUENCER_MODE_PITCHING_H
#define SEQUENCER_MODE_PITCHING_H

#include <Mode.h>
#include <Cursor.h>
#include <Application.h>

namespace Sequencer
{
  class ModePitching : public Mode<Application>
  {
  private:
    Cursor cursor = Cursor(0b1);
    Application *application;

  public:
    ModePitching(int note);
    void setupMode(Application *application);
    Mode<Application> *handle();
  };
}

#endif
