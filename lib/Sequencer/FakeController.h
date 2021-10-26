#ifndef SEQUENCER_FAKE_CONTROLLER_H
#define SEQUENCER_FAKE_CONTROLLER_H

#include <Controller.h>
#include <Potentiometer.h>

namespace Sequencer
{
  class FakeController : public Controller
  {
  private:
    Potentiometer *tempoPotentiometer;
    Potentiometer *clockGatePotentiometer;

  public:
    FakeController(int tempoPotentiometerPin, int clockGatePotentiometerPin);
    bool playPressed();
    bool rightPressed();
    bool leftPressed();
    bool modeSelectPressed();
    bool randomPressed();
    void read();
    void release();
    int readTempo();
    int readClockGate();
  };
}

#endif
