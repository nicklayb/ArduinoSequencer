#ifndef SEQUENCE_CONTROL_VOLTAGE_H
#define SEQUENCE_CONTROL_VOLTAGE_H

#include <MCP48xx.h>
#include <NoiseMaker.h>

namespace Sequencer
{
  class ControlVoltage : public NoiseMaker
  {
  private:
    MCP4822 *dac;
    int triggerPin;
    int gatePin;
    void setVoltage(bool channel, unsigned int milliVolt);
    void setVelocity(unsigned int milliVolt);
    void setNote(int midiMessage);
    void initDac(int digitalAnalogPin);
    void setGate(int value);
    void setTrigger(int value);

  public:
    ControlVoltage(int digitalAnalogPin, int triggerPin, int gatePin);
    void makeNoise(int midiNote, int duration);
    void makeNoise(int midiNote);
    void fallThresholdReached();
    void riseThresholdReached();
  };
}

#endif
