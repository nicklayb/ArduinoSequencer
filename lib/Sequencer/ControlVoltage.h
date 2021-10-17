#ifndef SEQUENCE_CONTROL_VOLTAGE_H
#define SEQUENCE_CONTROL_VOLTAGE_H

#include <NoiseMaker.h>

namespace Sequencer
{
  class ControlVoltage : public NoiseMaker
  {
  private:
    int digitalAnalogPin;
    int triggerPin;
    int gatePin;
    void setVoltage(bool channel, bool boostGain, unsigned int milliVolt);
    void writeDigitalAnalogPin(int value);
    void setVelocity(unsigned int milliVolt);
    void setNote(int midiMessage);
    unsigned int midiMessageToMilliVolt(int midiMessage);

  public:
    ControlVoltage(int digitalAnalogPin, int triggerPin, int gatePin);
    void makeNoise(int frequency, int duration);
    void makeNoise(int frequency);
    void stopNoise();
  };
}

#endif
