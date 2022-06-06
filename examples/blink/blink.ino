#include <LEDFlash.h>

LEDFlash led(16);

void setup() {
    Serial.begin(115200);
    led.on();
}

void loop() {

    led.on();
    delay(500);
    led.off();
    delay(500);
    
}