#include <Arduino.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

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

#define MODE_SEQUENCER 1
#define MODE_PITCH 2
#define MODE_PLAY 3

#define CLOCK_LENGTH 5000

#define C_MAJOR_SCALE {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5}

int scale[] = C_MAJOR_SCALE;

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
  pinMode(GREEN_BTN, INPUT);
  pinMode(YELLOW_BTN, INPUT);
  pinMode(BLUE_BTN, INPUT);
  pinMode(RED_BTN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  boot();

  //Serial.begin(9600);
}

int red = 0;
int blue = 0;
int yellow = 0;
int green = 0;

int mode = MODE_SEQUENCER;

int sequenceHighlighted = 1;
int sequenceIndex = 0;
int pitchHighlighted = 1;

int pressed = 0;

int sequence = 0b0;//0b01010101;
int notes[] = {0, 0, 0, 0, 0, 0, 0, 0};

int cursor = 0b1;

int clock = 0;

int maxLength = 5;


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
  digitalWrite(LED_7, (~highlighted) & 0b10000000);

  } else {
  digitalWrite(LED_0, highlighted & 0b1);
  digitalWrite(LED_1, highlighted & 0b10);
  digitalWrite(LED_2, highlighted & 0b100);
  digitalWrite(LED_3, highlighted & 0b1000);
  digitalWrite(LED_4, highlighted & 0b10000);
  digitalWrite(LED_5, highlighted & 0b100000);
  digitalWrite(LED_6, highlighted & 0b1000000);
  digitalWrite(LED_7, highlighted & 0b10000000);
  }
}

bool isPressed(int led)
{
  return pressed == 0 && led == HIGH;
}

void release()
{
  if (pressed == 1 && blue == LOW && yellow == LOW && red == LOW and blue == LOW)
  {
    pressed = 0;
  }
}

int indexFromByte(int byte)
{
  switch (byte) {
    case 0b10000000:
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

void loop()
{
  red = digitalRead(RED_BTN);
  blue = digitalRead(BLUE_BTN);
  yellow = digitalRead(YELLOW_BTN);
  green = digitalRead(GREEN_BTN);
  int newMaxLength = map(analogRead(POT_PIN), 0, 1024, 0, 10);
  if (newMaxLength != maxLength) {
    // Serial.print("Tempo changed ");
    // Serial.println(newMaxLength);
    maxLength = newMaxLength;
  }

  switch (mode)
  {
  case MODE_SEQUENCER:
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);

    ledStrip(sequenceHighlighted);

    if (isPressed(red))
    {
      pressed = 1;
      mode = MODE_PITCH;
      sequenceIndex = indexFromByte(sequenceHighlighted);

      if ((sequence & sequenceHighlighted) > 0)
      {
        int note = notes[sequenceIndex];
        pitchHighlighted = 0b10 << note;
      }
      else
      {
        pitchHighlighted = 0b1;
      }
    }

    if (isPressed(blue))
    {
      pressed = 1;
      sequenceHighlighted = sequenceHighlighted << 1;
      if (sequenceHighlighted >= 0b100000000)
      {
        sequenceHighlighted = 0b1;
      }
    }
    if (isPressed(yellow))
    {
      pressed = 1;
      sequenceHighlighted = sequenceHighlighted >> 1;
      if (sequenceHighlighted <= 0)
      {
        sequenceHighlighted = 0b10000000;
      }
    }
    if (isPressed(green))
    {
      pressed = 1;
      mode = MODE_PLAY;
    }

    break;

  case MODE_PITCH:
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    ledStrip(pitchHighlighted);

    if (isPressed(red))
    {
      pressed = 1;
      mode = MODE_SEQUENCER;

      int noteIndex = indexFromByte(pitchHighlighted);

      if (noteIndex > 0)
      {
        sequence = sequence | sequenceHighlighted;
        notes[sequenceIndex] = noteIndex - 1;
      }
      else
      {
        if ((sequence & sequenceHighlighted) > 0)
        {
          sequence = sequence ^ sequenceHighlighted;
          notes[noteIndex] = 0;
        }
      }
    }
    if (isPressed(blue))
    {
      pressed = 1;
      pitchHighlighted = pitchHighlighted << 1;
      if (pitchHighlighted >= 0b100000000)
      {
        pitchHighlighted = 0b1;
      }
    }
    if (isPressed(yellow))
    {
      pressed = 1;
      pitchHighlighted = pitchHighlighted >> 1;
      if (pitchHighlighted <= 0)
      {
        pitchHighlighted = 0b10000000;
      }
    }
    if (isPressed(green))
    {
      pressed = 1;
      mode = MODE_PLAY;
    }
    break;

  case MODE_PLAY:
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    if (isPressed(red))
    {
      pressed = 1;
      cursor = 0b1;
      clock = 0;
      mode = MODE_SEQUENCER;
      noTone(BUZZ_PIN);
    }
    ledStrip(cursor & sequence);
    clock += 1;
    if (clock >= maxLength * 300) {
      clock = 0;
      cursor = cursor << 1;
      if (cursor >= 0b100000000)
      {
        cursor = 0b1;
      }
    }

    if (clock == 0) {
      if ((cursor & sequence) > 0) {
        int noteIndex = notes[indexFromByte(cursor << 1)];
        tone(BUZZ_PIN, scale[noteIndex]);
      } else {
        noTone(BUZZ_PIN);
      }
    }

    break;
  }
  release();
}
