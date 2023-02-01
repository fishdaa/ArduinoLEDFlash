#include <LEDFlash.h>
#include <EasyButton.h>

#define BUTTON_PIN 25
#define LED_PIN 16

LEDFlash led(LED_PIN);

EasyButton button1(BUTTON_PIN);

void setup()
{
  Serial.begin(115200);
  button1.begin();
  button1.onPressed(onBtnPress);
}

void loop()
{
  led.update();
  button1.read();
}

void onBtnPress()
{
  Serial.println("Button Pressed");
  led.flash();
}