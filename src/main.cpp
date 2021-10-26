#include <Arduino.h>
#include <Rotary.h>
#include <FakeController.h>
#include <Constants.h>
#include <MidiNotes.h>
#include <IndividualLeds.h>
#include <Multiplexed8Bit.h>
#include <Pins.h>
#include <Buzzer.h>
#include <MidiOutput.h>
#include <SerialNoiseMaker.h>
#include <MultiNoiseMaker.h>
#include <ControlVoltage.h>
#include <Controller.h>
#include <Application.h>
#include <ModeKnob.h>

int scale[] = D_MINOR_SCALE_MIDI;
// int leds[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};
int bottomLeds[] = {2, 3, 4};

Sequencer::Application *application;

void setup()
{
  Sequencer::FakeController *controller = new Sequencer::FakeController(TEMPO_POT_PIN, CLOCK_GATE_POT_PIN);
  Sequencer::ControlVoltage *controlVoltage = new Sequencer::ControlVoltage(DIGITAL_ANALOG_CONVERTER_1, TRIG_PIN, GATE_PIN);
  Sequencer::LedStrip *ledStrip = new Sequencer::Multiplexed8Bit(bottomLeds, bottomLeds);
  application = new Sequencer::Application(scale, ledStrip, controller, controlVoltage, new Sequencer::ModeKnob(A0));
}

void loop()
{
  application->loop();
}
