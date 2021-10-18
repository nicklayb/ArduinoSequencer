#include <MultiNoiseMaker.h>

Sequencer::MultiNoiseMaker::MultiNoiseMaker(Sequencer::NoiseMaker *left, Sequencer::NoiseMaker *right)
{
  this->left = left;
  this->right = right;
}

void Sequencer::MultiNoiseMaker::makeNoise(int midiNote, int duration)
{
  this->left->makeNoise(midiNote, duration);
  this->right->makeNoise(midiNote, duration);
};

void Sequencer::MultiNoiseMaker::makeNoise(int midiNote)
{
  this->left->makeNoise(midiNote);
  this->right->makeNoise(midiNote);
};

void Sequencer::MultiNoiseMaker::fallThresholdReached()
{
  this->left->fallThresholdReached();
  this->right->fallThresholdReached();
};

void Sequencer::MultiNoiseMaker::riseThresholdReached()
{
  this->left->riseThresholdReached();
  this->right->riseThresholdReached();
};
