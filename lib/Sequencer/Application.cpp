#include <Application.h>
#include <ButtonSet.h>
#include <Cursor.h>
#include <NoiseMaker.h>
#include <Constants.h>
#include <Pitches.h>
#include <LedStrip.h>
#include <Pins.h>
#include <Controller.h>
#include <Sequence.h>
#include <ModeSequencing.h>
#include <ModePlay.h>
#include <ModeRandom.h>

using namespace Sequencer;

Application::Application(int *scale, LedStrip *ledStrip, Controller *controller, NoiseMaker *noiseMaker)
{
  this->scale = scale;
  this->ledStrip = ledStrip;
  this->controller = controller;
  this->sequence = new Sequence(8);
  this->noiseMaker = noiseMaker;
  this->mode = new ModeRandom();
  this->mode->setupMode(this);
}

void Application::loop()
{
  this->controller->read();

  Mode<Application> *newMode = this->mode->handle();

  if (newMode != NULL)
  {
    this->mode = newMode;
    this->mode->setupMode(this);
    this->noiseMaker->fallThresholdReached();
  }

  this->controller->release();
}

Sequence *Application::getSequence()
{
  return this->sequence;
}

LedStrip *Application::getLedStrip()
{
  return this->ledStrip;
}

Controller *Application::getController()
{
  return this->controller;
}

NoiseMaker *Application::getNoiseMaker()
{
  return this->noiseMaker;
}

int Application::getNote(Cursor cursor)
{
  return this->scale[this->getSequence()->getNoteIndex(cursor)];
}

int Application::getNote(int noteIndex)
{
  return this->scale[noteIndex];
}
