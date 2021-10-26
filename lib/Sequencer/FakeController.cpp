#include <FakeController.h>
#include <Button.h>
#include <Potentiometer.h>
#include <Constants.h>

Sequencer::PotentiometerMap tempoPotentiometerMap{.outMinimum = TEMPO_POTENTIOMETER_MIN, .outMaximum = TEMPO_POTENTIOMETER_MAX};
Sequencer::PotentiometerMap clockGatePotentiometerMap{.outMinimum = CLOCK_GATE_POTENTIOMETER_MIN, .outMaximum = CLOCK_GATE_POTENTIOMETER_MAX};

Sequencer::FakeController::FakeController(int tempoPotentiometerPin, int clockGatePotentiometerPin)
{
  this->tempoPotentiometer = new Sequencer::Potentiometer(tempoPotentiometerPin, tempoPotentiometerMap);
  this->clockGatePotentiometer = new Sequencer::Potentiometer(clockGatePotentiometerPin, clockGatePotentiometerMap);
};

bool Sequencer::FakeController::playPressed()
{
  return false;
};

bool Sequencer::FakeController::rightPressed()
{
  return false;
};

bool Sequencer::FakeController::leftPressed()
{
  return false;
};

bool Sequencer::FakeController::randomPressed()
{
  return false;
};

bool Sequencer::FakeController::modeSelectPressed()
{
  return false;
};

void Sequencer::FakeController::read(){};

void Sequencer::FakeController::release(){};

int Sequencer::FakeController::readTempo()
{
  return this->tempoPotentiometer->read();
}

int Sequencer::FakeController::readClockGate()
{
  return this->clockGatePotentiometer->read();
}
