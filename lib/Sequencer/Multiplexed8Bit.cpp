#include <Multiplexed8Bit.h>
#include <Arduino.h>

Sequencer::Multiplexed8Bit::Multiplexed8Bit(int topRow[INPUT_BITS], int bottomRow[INPUT_BITS])
{
  for (int i = 0; i < INPUT_BITS; i++)
  {
    this->topRow[i] = topRow[i];
    this->bottomRow[i] = bottomRow[i];
    pinMode(this->topRow[i], OUTPUT);
    pinMode(this->bottomRow[i], OUTPUT);
    digitalWrite(this->topRow[i], LOW);
    digitalWrite(this->bottomRow[i], LOW);
  }
};

void Sequencer::Multiplexed8Bit::lightUp(int byte)
{
  this->lightUp(byte, false);
};

void Sequencer::Multiplexed8Bit::lightUp(int byte, bool inverted)
{
  int *row = this->getRow(inverted);
  int multiplexerBits = this->inputByteToMultiplexerBits(byte);
  int checkByte = 0b1;

  for (int i = 0; i < INPUT_BITS; i++)
  {
    int signal = ((multiplexerBits & checkByte) > 0) ? HIGH : LOW;
    digitalWrite(row[i], signal);

    checkByte = checkByte << 1;
  }
}

int *Sequencer::Multiplexed8Bit::getRow(bool inverted)
{
  if (inverted)
  {
    return this->bottomRow;
  }
  return this->topRow;
}

int Sequencer::Multiplexed8Bit::inputByteToMultiplexerBits(int byte)
{
  int checkByte = 0b1;
  for (int i = 1; i <= STRIP_LENGTH; i++)
  {
    if ((byte & checkByte) > 0)
    {
      return i;
    }
    checkByte = checkByte << 1;
  }
  return 0;
}
