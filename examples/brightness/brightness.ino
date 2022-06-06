#include <LEDFlash.h>

LEDFlash led(16);

#define BUTTON_PIN 25
#define BR_UP 26
#define BR_DOWN 27

bool lastButtonState = false;
bool currentButtonState = false;

bool BRUPstate = false;
bool BRUPCRstate = false;

bool BRDOWNstate = false;
bool BRDOWNCRstate = false;

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BR_UP, INPUT_PULLUP);
    pinMode(BR_DOWN, INPUT_PULLUP);
    led.setBrightness(250);
    led.on();
}

void loop() {
  /* Always call this function in the loop for LEDFlash to work. */
  led.update();

  lastButtonState = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  BRUPstate = BRUPCRstate;      // save the last state
  BRUPCRstate = digitalRead(BR_UP); // read new state

  BRDOWNstate = BRDOWNCRstate;      // save the last state
  BRDOWNCRstate = digitalRead(BR_DOWN); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");

    if(!led.isOn()) led.on();
    else led.off();
  }

  if(BRUPstate == HIGH && BRUPCRstate == LOW) {
    Serial.println("The BR UP is pressed");
    led.setBrightness(led.getBrightness() + 10);
    Serial.println(led.getBrightness());
  }

  if(BRDOWNstate == HIGH && BRDOWNCRstate == LOW) {
    Serial.println("The BR DOWN is pressed");
    led.setBrightness(led.getBrightness() - 10);
    Serial.println(led.getBrightness());
  }
}