#include <LEDFlash.h>

#define LED_PIN 16

LEDFlash led(LED_PIN);

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