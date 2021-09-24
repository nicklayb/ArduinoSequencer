#include <Arduino.h>
#include <Rotary.h>
#include <Constants.h>
#include <Pitches.h>
#include <LedStrip.h>
#include <Pins.h>
#include <Buzzer.h>
#include <Controller.h>
#include <Application.h>

int scale[] = F_MAJOR_SCALE;
int leds[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

Sequencer::Application *application;

void setup()
{
  Sequencer::Controller *controller = new Sequencer::Rotary(GREEN_BTN, CLK_PIN, DT_PIN, RED_BTN, POT_PIN);
  Sequencer::LedStrip *ledStrip = new Sequencer::LedStrip(leds);
  Sequencer::Buzzer *buzzer = new Sequencer::Buzzer(BUZZ_PIN);
  application = new Sequencer::Application(scale, ledStrip, controller, buzzer);
}

void loop()
{
  application->loop();
}
