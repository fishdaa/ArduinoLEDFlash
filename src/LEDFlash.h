#ifndef LEDFLASH_H
#define LEDFLASH_H

#include <Arduino.h>

class LEDFlash
{
  public:
    LEDFlash(uint8_t pin);
    LEDFlash();

    void begin(uint8_t pin);
    void update();
    void flash();
    void setBrightness(uint16_t brightness);
    uint8_t getBrightness();
    void setDuration(uint8_t duration);
    uint8_t getDuration();
    void on();
    void off();
    bool isOn();

  private:
    uint8_t pin;
    uint16_t brightness;
    uint16_t duration;
    uint32_t offMillis;
    uint16_t delay;
    uint16_t ledOnDelay;
    bool onState = false;
    bool flashState = false;

    void ledOn();
    void ledOff();
};

#endif