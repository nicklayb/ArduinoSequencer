#include <Cursor.h>
#include <Constants.h>

Sequencer::Cursor::Cursor(int initialCursor) : Sequencer::Cursor::Cursor(initialCursor, 0b10000000){};

Sequencer::Cursor::Cursor(int initialCursor, int maxLength)
{
  this->cursor = initialCursor;
  this->initial = initialCursor;
  this->maxLength = maxLength;
};

void Sequencer::Cursor::forward()
{
  this->cursor = this->cursor << 1;
  this->cycle();
};

void Sequencer::Cursor::backward()
{
  this->cursor = this->cursor >> 1;
  this->cycle();
};

int Sequencer::Cursor::getPosition()
{
  return this->cursor;
};

void Sequencer::Cursor::cycle()
{
  if (this->cursor > this->maxLength)
  {
    this->cursor = 0b1;
  }
  if (this->cursor < 0b1)
  {
    this->cursor = this->maxLength;
  }
};

void Sequencer::Cursor::reset()
{
  this->cursor = this->initial;
}

int Sequencer::Cursor::bitToIndex()
{
  switch (this->getPosition())
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

void Sequencer::Cursor::set(int position)
{
  this->cursor = position;
}
