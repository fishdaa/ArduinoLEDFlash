#include <LEDFlash.h>

LEDFlash led(16);

#define BUTTON_PIN 26

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
	/* Always call this function in the loop for LEDFlash to work. */
	led.update();

    /* Check if the button is pressed. */
    if (digitalRead(BUTTON_PIN) == LOW) 
    {
        if (!led.isOn()) led.on();
        else led.off();
    }

}
