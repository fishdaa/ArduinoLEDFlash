#include "LEDFlash.h"

LEDFlash::LEDFlash(uint8_t pin) 
{
  begin(pin);
}

LEDFlash::LEDFlash() {}

void LEDFlash::begin(uint8_t pin) 
{
  this->pin = pin;
  this->brightness = 255;
  this->duration = 5;
  this->ledOnDelay = 50;
  this->onState = false;

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
  if(brightness <= 255 && brightness >= 1)
  {
    if(this->onState)
    {
      #ifdef ARDUINO_ARCH_ESP32
        ledcWrite(0, brightness);
      #else
        analogWrite(pin, brightness);
      #endif
    }

    this->brightness = brightness;
  }
}

uint8_t LEDFlash::getBrightness()
{
  return this->brightness;
}

void LEDFlash::setDuration(uint8_t duration)
{
  this->duration = duration;
}

uint8_t LEDFlash::getDuration()
{
  return this->duration;
}

void LEDFlash::flash()
{
  this->offMillis = millis() + (this->duration * 1000);
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

  if(this->flashState && this->onState && (this->offMillis - (this->duration * 1000)) + this->ledOnDelay > millis())
  {
    this->ledOff();
  }

  if(this->flashState && (this->offMillis - (this->duration * 1000)) + this->ledOnDelay < millis())
  {
    this->ledOn();
  }
}