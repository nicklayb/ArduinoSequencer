#include <Arduino.h>
#include <ButtonSet.h>
#include <Cursor.h>
#include <Constants.h>
#include <Pitches.h>
#include <Clock.h>

#define LED_0 2
#define LED_1 3
#define LED_2 4
#define LED_3 5
#define LED_4 6
#define LED_5 7
#define LED_6 8
#define LED_7 9

#define YELLOW_LED 20
#define GREEN_LED 21

#define BUZZ_PIN 1

#define POT_PIN A0

#define RED_BTN 13
#define YELLOW_BTN 12
#define BLUE_BTN 11
#define GREEN_BTN 10

int scale[] = C_MAJOR_SCALE;

Sequencer::ButtonSet *buttons;
Sequencer::Cursor sequenceCursor(0b1);
Sequencer::Cursor cursor(0b1);
Sequencer::Cursor pitchCursor(0b1);
Sequencer::Clock *clock;

void boot()
{
  for (int i = 0; i < 7; i++)
  {
    int note = scale[i];
    tone(BUZZ_PIN, note);
    delay(200);
  }
  noTone(BUZZ_PIN);
}

void setup()
{
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);

  pinMode(BUZZ_PIN, OUTPUT);

  boot();

  clock = new Sequencer::Clock();
  clock->setThreshold(CLOCK_THRESHOLD);
  buttons = new Sequencer::ButtonSet(RED_BTN, YELLOW_BTN, BLUE_BTN, GREEN_BTN);

  //Serial.begin(9600);
}

int mode = MODE_SEQUENCER;

int sequenceIndex = 0;

int pressed = 0;

int sequence = 0b11111111;
int notes[] = {0, 1, 2, 3, 4, 5, 6, 5};

void ledStrip(int highlighted)
{
  if (mode == MODE_PITCH)
  {
    digitalWrite(LED_0, (~highlighted) & 0b1);
    digitalWrite(LED_1, (~highlighted) & 0b10);
    digitalWrite(LED_2, (~highlighted) & 0b100);
    digitalWrite(LED_3, (~highlighted) & 0b1000);
    digitalWrite(LED_4, (~highlighted) & 0b10000);
    digitalWrite(LED_5, (~highlighted) & 0b100000);
    digitalWrite(LED_6, (~highlighted) & 0b1000000);
    digitalWrite(LED_7, (~highlighted) & LAST_BIT);
  }
  else
  {
    digitalWrite(LED_0, highlighted & 0b1);
    digitalWrite(LED_1, highlighted & 0b10);
    digitalWrite(LED_2, highlighted & 0b100);
    digitalWrite(LED_3, highlighted & 0b1000);
    digitalWrite(LED_4, highlighted & 0b10000);
    digitalWrite(LED_5, highlighted & 0b100000);
    digitalWrite(LED_6, highlighted & 0b1000000);
    digitalWrite(LED_7, highlighted & LAST_BIT);
  }
}

int indexFromByte(int byte)
{
  switch (byte)
  {
  case LAST_BIT:
    return 7;
  case 0b1000000:
    return 6;
  case 0b100000:
    return 5;
  case 0b10000:
    return 4;
  case 0b1000:
    return 3;
  case 0b100:
    return 2;
  case 0b10:
    return 1;
  case 0b1:
    return 0;
  default:
    return -1;
  }
}

int shiftLeft(int highlighted)
{
  int newHighlighted = highlighted >> 1;
  if (newHighlighted <= 0)
  {
    return LAST_BIT;
  }
  return newHighlighted;
}

int shiftRight(int highlighted)
{
  int newHighlighted = highlighted << 1;
  if (newHighlighted >= BIT_OVERFLOW)
  {
    return 0b1;
  }
  return newHighlighted;
}

void readTempo()
{
  int maxLength = map(analogRead(POT_PIN), 0, 1024, 3, 20);
  clock->setMaximum(maxLength * CLOCK_MULTIPLIER);
}

void loop()
{
  buttons->read();
  readTempo();

  switch (mode)
  {
  case MODE_SEQUENCER:
    ledStrip(sequenceCursor.getPosition());

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

    break;

  case MODE_PITCH:
    ledStrip(pitchCursor.getPosition());

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
      if (noteIndex >= 0) {
        tone(BUZZ_PIN, scale[noteIndex], 200);
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
    break;

  case MODE_PLAY:
    if (buttons->anyPressed())
    {
      cursor.reset();
      clock->reset();
      mode = MODE_SEQUENCER;
      sequenceCursor.reset();
      noTone(BUZZ_PIN);
    }
    else
    {
      ledStrip(cursor.getPosition() & sequence);
      if (clock->reachedMaximum())
      {
        cursor.forward();
      }

      if (clock->reachedThreshold())
      {
        noTone(BUZZ_PIN);
      }

      if (clock->justStarted())
      {
        if ((cursor.getPosition() & sequence) > 0)
        {
          int noteIndex = notes[indexFromByte(cursor.getPosition())];
          tone(BUZZ_PIN, scale[noteIndex]);
        }
        else
        {
          noTone(BUZZ_PIN);
        }
      }
      clock->tick();
    }
    break;
  }
  buttons->release();
}
