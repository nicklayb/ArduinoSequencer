#include <ModePitching.h>
#include <ModeSequencing.h>
#include <Application.h>

Sequencer::ModePitching::ModePitching(int note)
{
  if (note >= 0)
  {
    this->cursor.set(0b10 << note);
  }
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModePitching::handle(Sequencer::Application *application)
{
  application->getLedStrip()->lightUp(this->cursor.getPosition(), true);

  if (application->getController()->leftPressed())
  {
    this->cursor.backward();
  }

  if (application->getController()->rightPressed())
  {
    this->cursor.forward();
  }

  if (application->getController()->modeSelectPressed())
  {
    byte noteIndex = this->cursor.bitToIndex();

    if (noteIndex > 0)
    {
      application->getSequence()->setNote(noteIndex - 1);
    }
    else
    {
      if (application->getSequence()->hasNote())
      {
        application->getSequence()->clearNote();
      }
    }

    return new Sequencer::ModeSequencing();
  }

  if (application->getController()->playPressed())
  {
    byte noteIndex = this->cursor.bitToIndex() - 1;
    if (noteIndex >= 0)
    {
      application->getNoiseMaker()->makeNoise(application->getNote(noteIndex), 200);
    }
  }

  return NULL;
};
