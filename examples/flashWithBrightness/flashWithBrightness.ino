#include <LEDFlash.h>
#include <EasyButton.h>

#define LED_PIN 16
#define BUTTON_PIN 25
#define BR_UP 26
#define BR_DOWN 27

EasyButton button1(BUTTON_PIN);
EasyButton button2(BR_UP);
EasyButton button3(BR_DOWN);

LEDFlash led(LED_PIN);

void setup() {
  Serial.begin(115200);

  button1.begin();
  button2.begin();
  button3.begin();

  button1.onPressed(onBtnPress);
  button2.onPressed(onBtnPressUp);
  button3.onPressed(onBtnPressDown);
}

void loop() {
  /* Always call this function in the loop for LEDFlash to work. */
  led.update();
  
  button1.read();
  button2.read();
  button3.read();
}

void onBtnPress() {
  Serial.println("Button Pressed");
  led.flash();
}

void onBtnPressUp() {
  Serial.println("The BR UP is pressed");
  led.setBrightness(led.getBrightness() + 10);
  Serial.println(led.getBrightness());
}

void onBtnPressDown() {
  Serial.println("The BR DOWN is pressed");
  led.setBrightness(led.getBrightness() - 10);
  Serial.println(led.getBrightness());
}