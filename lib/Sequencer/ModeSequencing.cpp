#include <ModeSequencing.h>
#include <ModePitching.h>
#include <ModePlay.h>
#include <ModeRandom.h>
#include <Application.h>

Sequencer::ModeSequencing::ModeSequencing() {}

void Sequencer::ModeSequencing::setupMode(Sequencer::Application *application)
{
  this->application = application;
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModeSequencing::handle()
{
  this->application->getLedStrip()->lightUp(this->application->getSequence()->cursorPosition());

  if (this->application->getController()->leftPressed())
  {
    this->application->getSequence()->backward();
  }

  if (this->application->getController()->rightPressed())
  {
    this->application->getSequence()->forward();
  }

  if (this->application->getController()->playPressed())
  {
    return new Sequencer::ModePlay();
  }

  if (this->application->getController()->randomPressed())
  {
    return new Sequencer::ModeRandom();
  }

  if (this->application->getController()->modeSelectPressed())
  {
    if (this->application->getSequence()->hasNote())
    {
      int note = this->application->getSequence()->getNoteIndex();
      return new Sequencer::ModePitching(note);
    }
    else
    {
      return new Sequencer::ModePitching(-1);
    }
  }

  return NULL;
};
