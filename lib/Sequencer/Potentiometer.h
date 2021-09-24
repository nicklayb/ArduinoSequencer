#ifndef SEQUENCER_POTENTIOMETER_H
#define SEQUENCER_POTENTIOMETER_H

namespace Sequencer
{
  struct PotentiometerMap
  {
    int outMinimum;
    int outMaximum;
  };

  class Potentiometer
  {
  private:
    int pin;
    PotentiometerMap mapValues;
    int readRaw();

  public:
    Potentiometer(int pin, PotentiometerMap map);
    int read();
  };
}

#endif
