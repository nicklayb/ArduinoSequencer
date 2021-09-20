#include <Arduino.h>
#include <ButtonSet.h>
#include <Rotary.h>
#include <Cursor.h>
#include <Constants.h>
#include <Pitches.h>
#include <Clock.h>
#include <LedStrip.h>
#include <Pins.h>
#include <Buzzer.h>
#include <Controller.h>

int scale[] = C_MAJOR_SCALE;
int leds[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

Sequencer::Controller *controller;
Sequencer::Cursor sequenceCursor(0b1);
Sequencer::Cursor cursor(0b1);
Sequencer::Cursor pitchCursor(0b1);
Sequencer::Clock *clock;
Sequencer::LedStrip *ledStrip;
Sequencer::Buzzer *buzzer;

byte mode = MODE_SEQUENCER;

byte sequenceIndex = 0;

byte sequence = 0b11111111;
byte notes[] = {0, 1, 2, 3, 4, 5, 6, 5};

void readTempo()
{
  int maxLength = map(analogRead(POT_PIN), 0, 1024, 3, 20);
  clock->setMaximum(maxLength * CLOCK_MULTIPLIER);
}

void setup()
{
  pinMode(BUZZ_PIN, OUTPUT);

  clock = new Sequencer::Clock();
  clock->setThreshold(CLOCK_THRESHOLD);
  controller = new Sequencer::Rotary(GREEN_BTN, CLK_PIN, DT_PIN, RED_BTN);

  ledStrip = new Sequencer::LedStrip(leds);
  buzzer = new Sequencer::Buzzer(BUZZ_PIN);
  buzzer->buzz(scale, 200);
}

void handleSequencer()
{

  ledStrip->lightUp(sequenceCursor.getPosition());

  if (controller->modeSelectPressed())
  {
    mode = MODE_PITCH;
    sequenceIndex = sequenceCursor.bitToIndex();

    if ((sequence & sequenceCursor.getPosition()) > 0)
    {
      int note = notes[sequenceIndex];
      pitchCursor.set(0b10 << note);
    }
    else
    {
      pitchCursor.reset();
    }
  }

  if (controller->rightPressed())
  {
    sequenceCursor.forward();
  }
  if (controller->leftPressed())
  {
    sequenceCursor.backward();
  }
  if (controller->playPressed())
  {
    mode = MODE_PLAY;
  }
}

void handlePitch()
{

  ledStrip->lightUp(pitchCursor.getPosition(), true);

  if (controller->modeSelectPressed())
  {
    mode = MODE_SEQUENCER;

    byte noteIndex = pitchCursor.bitToIndex();

    if (noteIndex > 0)
    {
      sequence = sequence | sequenceCursor.getPosition();
      notes[sequenceIndex] = noteIndex - 1;
    }
    else
    {
      if ((sequence & sequenceCursor.getPosition()) > 0)
      {
        sequence = sequence ^ sequenceCursor.getPosition();
        notes[noteIndex] = 0;
      }
    }
  }

  if (controller->playPressed())
  {
    byte noteIndex = pitchCursor.bitToIndex() - 1;
    if (noteIndex >= 0)
    {
      buzzer->buzz(scale[noteIndex], 200);
    }
  }
  if (controller->rightPressed())
  {
    pitchCursor.forward();
  }
  if (controller->leftPressed())
  {
    pitchCursor.backward();
  }
}

void handlePlay()
{
  if (controller->modeSelectPressed() || controller->playPressed())
  {
    cursor.reset();
    clock->reset();
    mode = MODE_SEQUENCER;
    sequenceCursor.reset();
    buzzer->stop();
  }
  else
  {
    ledStrip->lightUp(cursor.getPosition() & sequence);
    if (clock->reachedMaximum())
    {
      cursor.forward();
    }

    if (clock->reachedThreshold())
    {
      buzzer->stop();
    }

    if (clock->justStarted())
    {
      if ((cursor.getPosition() & sequence) > 0)
      {
        int noteIndex = notes[cursor.bitToIndex()];
        buzzer->buzz(scale[noteIndex]);
      }
      else
      {
        buzzer->stop();
      }
    }
    clock->tick();
  }
}

void loop()
{
  controller->read();
  readTempo();

  switch (mode)
  {
  case MODE_SEQUENCER:
    handleSequencer();
    break;

  case MODE_PITCH:
    handlePitch();
    break;

  case MODE_PLAY:
    handlePlay();
    break;
  }
  controller->release();
}
