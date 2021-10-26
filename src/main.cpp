#include <Arduino.h>
#include <Rotary.h>
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
int bottomLeds[] = {MUX_1_1, MUX_1_2, MUX_1_3};
int topLeds[] = {MUX_2_1, MUX_2_2, MUX_2_3};

Sequencer::Application *application;

void setup()
{
  Sequencer::Controller *controller = new Sequencer::Rotary(PLAY_PIN, CLK_PIN, DT_PIN, MODE_SELECT_PIN, TEMPO_POT_PIN, CLOCK_GATE_POT_PIN, RANDOM_PIN);
  //Sequencer::IndividualLeds *ledStrip = new Sequencer::IndividualLeds(leds);
  Sequencer::Multiplexed8Bit *ledStrip = new Sequencer::Multiplexed8Bit(topLeds, bottomLeds);
  Sequencer::MidiOutput *midiOut = new Sequencer::MidiOutput(SERIAL_TX);
  Sequencer::ControlVoltage *controlVoltage = new Sequencer::ControlVoltage(DIGITAL_ANALOG_CONVERTER_1, TRIG_PIN, GATE_PIN);
  Sequencer::MultiNoiseMaker *noiseMaker = new Sequencer::MultiNoiseMaker(midiOut, controlVoltage);
  //Sequencer::SerialNoiseMaker *serial = new Sequencer::SerialNoiseMaker();
  //Sequencer::MultiNoiseMaker *noiseMaker = new Sequencer::MultiNoiseMaker(serial, controlVoltage);
  application = new Sequencer::Application(scale, ledStrip, controller, noiseMaker, new ModeKnob(A0));
}

void loop()
{
  application->loop();
}
