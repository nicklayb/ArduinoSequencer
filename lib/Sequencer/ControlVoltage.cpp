#include <ControlVoltage.h>
#include <Arduino.h>
#include <SPI.h>
#include <MidiNotes.h>

#define NOTE_CHANNEL 0
#define VELOCITY_CHANNEL 1
#define VELOCITY 10
#define NULL_VELOCITY 0

#define NOTE_SF 47.069f

Sequencer::ControlVoltage::ControlVoltage(int digitalAnalogPin, int triggerPin, int gatePin)
{
  this->digitalAnalogPin = digitalAnalogPin;
  this->triggerPin = triggerPin;
  this->gatePin = gatePin;
  pinMode(this->digitalAnalogPin, OUTPUT);
  this->writeDigitalAnalogPin(HIGH);
  SPI.begin();
}

void Sequencer::ControlVoltage::makeNoise(int frequency, int duration)
{
  this->makeNoise(frequency);
  delay(duration);
  this->stopNoise();
};

void Sequencer::ControlVoltage::makeNoise(int frequency)
{
  int midiMessage = frequencyToMidiNote(frequency);
  this->setNote(midiMessage);
  this->setVelocity(VELOCITY);
};

void Sequencer::ControlVoltage::stopNoise()
{
  this->setVelocity(NULL_VELOCITY);
};

void Sequencer::ControlVoltage::setNote(int midiMessage)
{
  this->setVoltage(NOTE_CHANNEL, true, this->midiMessageToMilliVolt(midiMessage));
}

void Sequencer::ControlVoltage::setVelocity(unsigned int milliVolt)
{
  this->setVoltage(VELOCITY_CHANNEL, true, milliVolt << 5);
}

void Sequencer::ControlVoltage::writeDigitalAnalogPin(int value)
{
  digitalWrite(this->digitalAnalogPin, value);
}

// https://github.com/elkayem/midi2cv/blob/1626113092650d5b7fb3bcff1e6b570a65b09d46/midi2cv.ino#L243
void Sequencer::ControlVoltage::setVoltage(bool channel, bool boostGain, unsigned int milliVolt)
{
  unsigned int command = channel ? 0x9000 : 0x1000;

  command |= boostGain ? 0x0000 : 0x2000;
  command |= (milliVolt & 0x0FFF);

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  this->writeDigitalAnalogPin(LOW);
  SPI.transfer(command >> 8);
  SPI.transfer(command & 0xFF);
  this->writeDigitalAnalogPin(HIGH);
  SPI.endTransaction();
}

// https://github.com/elkayem/midi2cv/blob/1626113092650d5b7fb3bcff1e6b570a65b09d46/midi2cv.ino#L232
unsigned int Sequencer::ControlVoltage::midiMessageToMilliVolt(int midiMessage)
{
  return (unsigned int)((float)midiMessage * NOTE_SF + 0.5);
}
