#include "LEDFlash.h"

LEDFlash::LEDFlash(uint8_t pin) 
{
  this->brightness = 255;
  this->delay = 0;
  this->duration = 1000;

  #ifdef ARDUINO_ARCH_ESP32
    ledcSetup(0, 5000, 8);
    ledcAttachPin(pin, 0);
  #else
    pinMode(pin, OUTPUT);
  #endif
}

void LEDFlash::on()
{
  this->ledOn();
  this->onState = true;
}

void LEDFlash::off()
{
  this->ledOff();
  this->onState = false;
}

bool LEDFlash::isOn()
{
  return this->onState;
}

void LEDFlash::ledOn()
{
  #ifdef ARDUINO_ARCH_ESP32
    ledcWrite(0, this->brightness);
  #else
    analogWrite(pin, this->brightness);
  #endif
}

void LEDFlash::ledOff()
{
  #ifdef ARDUINO_ARCH_ESP32
    ledcWrite(0, 0);
  #else
    analogWrite(pin, 0);
  #endif
}

void LEDFlash::setBrightness(uint16_t brightness)
{
  if(brightness <= 255 && brightness >= 0 && this->isOn())
  {
    #ifdef ARDUINO_ARCH_ESP32
      ledcWrite(0, brightness);
    #else
      analogWrite(pin, brightness);
    #endif
    this->brightness = brightness;
  }
}

uint8_t LEDFlash::getBrightness()
{
  return this->brightness;
}

void LEDFlash::setDelay(uint16_t delay)
{
  this->delay = delay;
}

uint16_t LEDFlash::getDelay()
{
  return this->delay;
}

void LEDFlash::flash()
{
  this->ledOn();
  this->offMillis = millis() + this->delay;
  this->flashState = true;
}

void LEDFlash::update()
{

  if(this->flashState && this->offMillis < millis())
  {
    this->ledOff();
    this->flashState = false;
  }

  if(!this->flashState && this->onState && this->offMillis + this->ledOnDelay < millis())
  {
    this->ledOn();
  }
}