#include <Arduino.h>
#include <Rotary.h>
#include <Constants.h>
#include <MidiNotes.h>
#include <IndividualLeds.h>
#include <Pins.h>
#include <Buzzer.h>
#include <MidiOutput.h>
#include <MultiNoiseMaker.h>
#include <ControlVoltage.h>
#include <Controller.h>
#include <Application.h>

int scale[] = C_MAJOR_SCALE_MIDI;
int leds[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

Sequencer::Application *application;

void setup()
{
  Sequencer::Controller *controller = new Sequencer::Rotary(PLAY_PIN, CLK_PIN, DT_PIN, MODE_SELECT_PIN, POT_PIN);
  Sequencer::IndividualLeds *ledStrip = new Sequencer::IndividualLeds(leds);
  Sequencer::MidiOutput *midiOut = new Sequencer::MidiOutput(SERIAL_TX);
  Sequencer::ControlVoltage *controlVoltage = new Sequencer::ControlVoltage(DIGITAL_ANALOG_CONVERTER_1, TRIG_PIN, GATE_PIN);
  Sequencer::MultiNoiseMaker *noiseMaker = new Sequencer::MultiNoiseMaker(midiOut, controlVoltage);
  application = new Sequencer::Application(scale, ledStrip, controller, noiseMaker);
}

void loop()
{
  application->loop();
}
