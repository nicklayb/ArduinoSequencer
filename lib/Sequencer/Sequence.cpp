#include <Sequence.h>
#include <Pitches.h>

Sequencer::Sequence::Sequence(int length)
{
  this->length = length;
  this->initialize();
};

void Sequencer::Sequence::initialize()
{
  int currentPosition = 0b1;
  int currentLength = 0b1;
  for (int i = 0; i < this->length - 1; i++)
  {
    currentLength = currentLength << 1;
  }
  this->cursor = new Sequencer::Cursor(0b1, currentLength);
  for (int i = 0; i < this->length; i++)
  {
    this->sequence = this->sequence | currentPosition;
    currentPosition = currentPosition << 1;
  }
  for (int i = 0; i < MAX_NOTES; i++)
  {
    this->notes[i] = NOTE_C1;
  }
}

void Sequencer::Sequence::backward()
{
  this->cursor->backward();
  this->updateIndex();
};

void Sequencer::Sequence::forward()
{
  this->cursor->forward();
  this->updateIndex();
};

void Sequencer::Sequence::updateIndex()
{
  this->index = this->cursor->bitToIndex();
};

bool Sequencer::Sequence::hasNote()
{
  return (this->sequence & this->cursor->getPosition()) > 0;
};

int Sequencer::Sequence::getIndex()
{
  return this->index;
};

void Sequencer::Sequence::setNote(int note)
{
  this->notes[this->getIndex()] = note;
  this->sequence = this->sequence | this->cursor->getPosition();
};

void Sequencer::Sequence::clearNote()
{
  this->notes[this->getIndex()] = 0;
  this->sequence = this->sequence ^ this->cursor->getPosition();
};

int Sequencer::Sequence::getNoteIndex()
{
  return this->notes[this->getIndex()];
};

int Sequencer::Sequence::getNoteIndex(Cursor cursor)
{
  if ((this->sequenceAt(cursor)) > 0)
  {
    return this->notes[cursor.bitToIndex()];
  }
  return SILENCE;
};

void Sequencer::Sequence::resetCursor()
{
  this->cursor->reset();
  this->updateIndex();
};

int Sequencer::Sequence::sequenceAt(Cursor cursor)
{
  return this->sequence & cursor.getPosition();
};

int Sequencer::Sequence::cursorPosition()
{
  return this->cursor->getPosition();
}
