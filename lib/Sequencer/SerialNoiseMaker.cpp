#include <SerialNoiseMaker.h>
#include <Arduino.h>

Sequencer::SerialNoiseMaker::SerialNoiseMaker()
{
  Serial.begin(9600);
};

void Sequencer::SerialNoiseMaker::makeNoise(int midiNote)
{
  Serial.print("makeNoise: ");
  Serial.println(midiNote);
};

void Sequencer::SerialNoiseMaker::makeNoise(int midiNote, int duration)
{
  Serial.print("makeNoise: ");
  Serial.print(midiNote);
  Serial.print(" - ");
  Serial.println(duration);
};

void Sequencer::SerialNoiseMaker::fallThresholdReached()
{
  Serial.println("fallThresholdReached");
}

void Sequencer::SerialNoiseMaker::riseThresholdReached()
{
  Serial.println("riseThresholdReached");
}
