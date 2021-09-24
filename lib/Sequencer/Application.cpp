#include <Application.h>
#include <ButtonSet.h>
#include <Cursor.h>
#include <NoiseMaker.h>
#include <Constants.h>
#include <Pitches.h>
#include <Clock.h>
#include <LedStrip.h>
#include <Pins.h>
#include <Controller.h>
#include <Sequence.h>
#include <ModeSequencing.h>

using namespace Sequencer;

Application::Application(int *scale, LedStrip *ledStrip, Controller *controller, NoiseMaker *noiseMaker)
{
  this->scale = scale;
  this->ledStrip = ledStrip;
  this->controller = controller;
  this->sequence = new Sequence(8);
  this->noiseMaker = noiseMaker;
  this->mode = new ModeSequencing();
}

void Application::loop()
{
  this->controller->read();

  Mode<Application> *newMode = this->mode->handle(this);

  if (newMode != NULL)
  {
    this->mode = newMode;
    this->noiseMaker->stopNoise();
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