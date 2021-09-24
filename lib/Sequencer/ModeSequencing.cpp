#include <ModeSequencing.h>
#include <ModePitching.h>
#include <ModePlay.h>
#include <Application.h>

Sequencer::ModeSequencing::ModeSequencing() {}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModeSequencing::handle(Sequencer::Application *application)
{
  application->getLedStrip()->lightUp(application->getSequence()->cursorPosition());

  if (application->getController()->leftPressed())
  {
    application->getSequence()->backward();
  }

  if (application->getController()->rightPressed())
  {
    application->getSequence()->forward();
  }

  if (application->getController()->playPressed())
  {
    return new Sequencer::ModePlay();
  }

  if (application->getController()->modeSelectPressed())
  {
    if (application->getSequence()->hasNote())
    {
      int note = application->getSequence()->getNoteIndex();
      return new Sequencer::ModePitching(note);
    }
    else
    {
      return new Sequencer::ModePitching(-1);
    }
  }

  return NULL;
};
