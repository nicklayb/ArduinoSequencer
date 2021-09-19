#include <Arduino.h>
#include <ButtonSet.h>
#include <Cursor.h>
#include <Constants.h>
#include <Pitches.h>
#include <Clock.h>
#include <LedStrip.h>
#include <Pins.h>
#include <Buzzer.h>

int scale[] = C_MAJOR_SCALE;
int leds[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

Sequencer::ButtonSet *buttons;
Sequencer::Cursor sequenceCursor(0b1);
Sequencer::Cursor cursor(0b1);
Sequencer::Cursor pitchCursor(0b1);
Sequencer::Clock *clock;
Sequencer::LedStrip *ledStrip;
Sequencer::Buzzer* buzzer;

int mode = MODE_SEQUENCER;

int sequenceIndex = 0;

int pressed = 0;

int sequence = 0b11111111;
int notes[] = {0, 1, 2, 3, 4, 5, 6, 5};

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
  buttons = new Sequencer::ButtonSet(RED_BTN, YELLOW_BTN, BLUE_BTN, GREEN_BTN);
  ledStrip = new Sequencer::LedStrip(leds);
  buzzer = new Sequencer::Buzzer(BUZZ_PIN);

  buzzer->buzz(scale, 200);
}

void handleSequencer()
{

  ledStrip->lightUp(sequenceCursor.getPosition());

  if (buttons->modeSelectPressed())
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

  if (buttons->rightPressed())
  {
    sequenceCursor.forward();
  }
  if (buttons->leftPressed())
  {
    sequenceCursor.backward();
  }
  if (buttons->playPressed())
  {
    mode = MODE_PLAY;
  }
}

void handlePitch()
{

  ledStrip->lightUp(pitchCursor.getPosition(), true);

  if (buttons->modeSelectPressed())
  {
    mode = MODE_SEQUENCER;

    int noteIndex = pitchCursor.bitToIndex();

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

  if (buttons->playPressed())
  {
    int noteIndex = pitchCursor.bitToIndex() - 1;
    if (noteIndex >= 0)
    {
      buzzer->buzz(scale[noteIndex], 200);
    }
  }
  if (buttons->rightPressed())
  {
    pitchCursor.forward();
  }
  if (buttons->leftPressed())
  {
    pitchCursor.backward();
  }
}

void handlePlay()
{
  if (buttons->anyPressed())
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
  buttons->read();
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
  buttons->release();
}
