#include <MultiNoiseMaker.h>

Sequencer::MultiNoiseMaker::MultiNoiseMaker(Sequencer::NoiseMaker *left, Sequencer::NoiseMaker *right)
{
  this->left = left;
  this->right = right;
}

void Sequencer::MultiNoiseMaker::makeNoise(int frequency, int duration)
{
  this->left->makeNoise(frequency, duration);
  this->right->makeNoise(frequency, duration);
};

void Sequencer::MultiNoiseMaker::makeNoise(int frequency)
{
  this->left->makeNoise(frequency);
  this->right->makeNoise(frequency);
};

void Sequencer::MultiNoiseMaker::stopNoise()
{
  this->left->stopNoise();
  this->right->stopNoise();
};
