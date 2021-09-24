#ifndef SEQUENCER_SEQUENCE_H
#define SEQUENCER_SEQUENCE_H

#define MAX_NOTES 16
#define SILENCE -1

#include <Cursor.h>

namespace Sequencer
{
  class Sequence
  {
  private:
    int index = 0;
    int length;
    int sequence = 0b1;
    Cursor *cursor;
    void updateIndex();
    int notes[MAX_NOTES];
    void initialize();

  public:
    Sequence(int length);
    void forward();
    void backward();
    int getIndex();
    void setNote(int note);
    void clearNote();
    int getNoteIndex();
    int getNoteIndex(Cursor cursor);
    bool hasNote();
    void resetCursor();
    int sequenceAt(Cursor cursor);
    int cursorPosition();
  };
}

#endif
