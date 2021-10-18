#include <ControlVoltage.h>
#include <Arduino.h>
#include <MidiNotes.h>

#define NOTE_CHANNEL 0
#define VELOCITY_CHANNEL 1
#define VELOCITY 10
#define NULL_VELOCITY 0

#define NOTE_SF 47.069f

Sequencer::ControlVoltage::ControlVoltage(int digitalAnalogPin, int triggerPin, int gatePin)
{
  this->triggerPin = triggerPin;
  this->gatePin = gatePin;
  this->initDac(digitalAnalogPin);
  this->setGate(LOW);
  this->setTrigger(LOW);
}

void Sequencer::ControlVoltage::initDac(int digitalAnalogPin)
{
  this->dac = new MCP4822(digitalAnalogPin);
  this->dac->init();
  this->dac->turnOnChannelA();
  this->dac->turnOnChannelB();
  this->dac->setGainA(MCP4822::High);
  this->dac->setGainB(MCP4822::High);
}

void Sequencer::ControlVoltage::makeNoise(int midiNote, int duration)
{
  this->makeNoise(midiNote);
  delay(duration);
  this->fallThresholdReached();
};

void Sequencer::ControlVoltage::makeNoise(int midiNote)
{
  this->setNote(midiNote);
  this->setVelocity(VELOCITY);
  this->setGate(HIGH);
  this->setTrigger(HIGH);
};

void Sequencer::ControlVoltage::fallThresholdReached()
{
  this->setGate(LOW);
  this->setVelocity(NULL_VELOCITY);
};

void Sequencer::ControlVoltage::riseThresholdReached()
{
  this->setTrigger(LOW);
}

void Sequencer::ControlVoltage::setNote(int midiNote)
{
  this->setVoltage(NOTE_CHANNEL, midiNoteToVoltage(midiNote));
}

void Sequencer::ControlVoltage::setVelocity(unsigned int milliVolt)
{
  this->setVoltage(VELOCITY_CHANNEL, milliVolt << 5);
}

void Sequencer::ControlVoltage::setTrigger(int value)
{
  digitalWrite(this->triggerPin, value);
}

void Sequencer::ControlVoltage::setGate(int value)
{
  digitalWrite(this->gatePin, value);
}

void Sequencer::ControlVoltage::setVoltage(bool channel, unsigned int millivolt)
{
  if (channel)
  {
    dac->setVoltageA(millivolt);
  }
  else
  {
    dac->setVoltageB(millivolt);
  }
  dac->updateDAC();
}
