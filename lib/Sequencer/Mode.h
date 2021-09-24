#ifndef SEQUENCER_MODE_H
#define SEQUENCER_MODE_H

namespace Sequencer
{
  template <class T>
  class Mode
  {
  public:
    virtual Mode<T> *handle(T *application);
  };
}

#endif
