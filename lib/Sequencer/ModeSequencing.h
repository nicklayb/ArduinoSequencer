#ifndef SEQUENCER_MODE_SEQUENCING_H
#define SEQUENCER_MODE_SEQUENCING_H

#include <Mode.h>
#include <Application.h>

namespace Sequencer
{
  class ModeSequencing : public Mode<Application>
  {
  private:
    Application *application;

  public:
    ModeSequencing();
    Mode<Application> *handle();
    void setupMode(Application *application);
  };
}

#endif
