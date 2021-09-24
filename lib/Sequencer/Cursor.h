#ifndef SEQUENCER_CURSOR_H
#define SEQUENCER_CURSOR_H

namespace Sequencer
{
  class Cursor
  {
  private:
    int cursor;
    int initial;
    int maxLength;
    void cycle();

  public:
    Cursor(int initialCursor);
    Cursor(int initialCursor, int maxLength);
    void forward();
    void backward();
    int getPosition();
    void reset();
    int bitToIndex();
    void set(int position);
  };
}

#endif
