#include <ModePlay.h>
#include <ModeSequencing.h>
#include <Application.h>

Sequencer::ModePlay::ModePlay()
{
  this->clock = new Clock();
  this->clock->setThreshold(CLOCK_THRESHOLD);
}

Sequencer::Mode<Sequencer::Application> *Sequencer::ModePlay::handle(Sequencer::Application *application)
{
  this->readTempo(application->getController());

  if (application->getController()->modeSelectPressed() || application->getController()->playPressed())
  {
    application->getSequence()->resetCursor();
    return new ModeSequencing();
  }
  else
  {
    application->getLedStrip()->lightUp(this->cursor.getPosition());

    if (this->clock->reachedMaximum())
    {
      this->cursor.forward();
    }

    if (this->clock->reachedRiseThreshold())
    {
      application->getNoiseMaker()->riseThresholdReached();
    }

    if (this->clock->reachedFallThreshold())
    {
      application->getNoiseMaker()->fallThresholdReached();
    }

    if (this->clock->justStarted())
    {
      if (application->getSequence()->sequenceAt(this->cursor) > 0)
      {
        int note = application->getNote(this->cursor);
        application->getNoiseMaker()->makeNoise(note);
      }
      else
      {
        application->getNoiseMaker()->fallThresholdReached();
      }
    }

    this->clock->tick();
  }

  return NULL;
};

void Sequencer::ModePlay::readTempo(Sequencer::Controller *controller)
{
  int maxLength = controller->readTempo();
  this->clock->setMaximum(maxLength * CLOCK_MULTIPLIER);
}
