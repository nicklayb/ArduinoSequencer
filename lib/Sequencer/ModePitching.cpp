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

void Sequencer::ModePitching::setupMode(Sequencer::Application *application)
{
  this->application = application;
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModePitching::handle()
{
  this->application->getLedStrip()->lightUp(this->cursor.getPosition(), true);

  if (this->application->getController()->leftPressed())
  {
    this->cursor.backward();
  }

  if (this->application->getController()->rightPressed())
  {
    this->cursor.forward();
  }

  if (this->application->getController()->modeSelectPressed())
  {
    byte noteIndex = this->cursor.bitToIndex();

    if (noteIndex > 0)
    {
      this->application->getSequence()->setNote(noteIndex - 1);
    }
    else
    {
      if (this->application->getSequence()->hasNote())
      {
        this->application->getSequence()->clearNote();
      }
    }

    return new Sequencer::ModeSequencing();
  }

  if (this->application->getController()->playPressed())
  {
    byte noteIndex = this->cursor.bitToIndex() - 1;
    if (noteIndex >= 0)
    {
      this->application->getNoiseMaker()->makeNoise(this->application->getNote(noteIndex), 200);
    }
  }

  return NULL;
};
