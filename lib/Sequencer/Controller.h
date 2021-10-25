#ifndef SEQUENCER_CONTROLLER_H
#define SEQUENCER_CONTROLLER_H

namespace Sequencer
{
  class Controller
  {
  public:
    virtual bool modeSelectPressed();
    virtual bool leftPressed();
    virtual bool rightPressed();
    virtual bool playPressed();
    virtual bool randomPressed();
    virtual void read();
    virtual void release();
    virtual int readTempo();
    virtual int readClockGate();
  };
}

#endif
