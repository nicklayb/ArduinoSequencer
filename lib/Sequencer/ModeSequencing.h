#ifndef SEQUENCER_MODE_SEQUENCING_H
#define SEQUENCER_MODE_SEQUENCING_H

#include <Mode.h>
#include <Application.h>

namespace Sequencer
{
  class ModeSequencing : public Mode<Application>
  {
  public:
    ModeSequencing();
    Mode<Application> *handle(Application *application);
  };
}

#endif
