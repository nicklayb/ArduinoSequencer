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

  public:
    ModePitching(int note);
    Mode<Application> *handle(Application *application);
  };
}

#endif
