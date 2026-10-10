#include "curio-drivers.h"

namespace CurioDrivers {

// SSD1306 Display implementation
SSD1306Display::SSD1306Display(int16_t width, int16_t height, TwoWire* wire, int8_t rst_pin)
    : _display(new Adafruit_SSD1306(width, height, wire, rst_pin)),
      _width(width), _height(height) {}

SSD1306Display::~SSD1306Display() {
    delete _display;
}

void SSD1306Display::begin() {
    _display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    _display->clearDisplay();
    _display->display();
}
void SSD1306Display::clear() { _display->clearDisplay(); }
void SSD1306Display::display() { _display->display(); }
void SSD1306Display::drawPixel(int16_t x, int16_t y, uint16_t color) { _display->drawPixel(x, y, color); }
void SSD1306Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) { _display->drawLine(x0, y0, x1, y1, color); }
void SSD1306Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { _display->drawRect(x, y, w, h, color); }
void SSD1306Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { _display->fillRect(x, y, w, h, color); }
void SSD1306Display::setCursor(int16_t x, int16_t y) { _display->setCursor(x, y); }
void SSD1306Display::setTextColor(uint16_t color) { _display->setTextColor(color); }
void SSD1306Display::setTextSize(uint8_t size) { _display->setTextSize(size); }
void SSD1306Display::print(const char* str) { _display->print(str); }
void SSD1306Display::println(const char* str) { _display->println(str); }
int16_t SSD1306Display::width() { return _width; }
int16_t SSD1306Display::height() { return _height; }
Adafruit_SSD1306* SSD1306Display::getNativeDisplay() { return _display; }

// Seesaw abstraction
Seesaw::Seesaw(TwoWire* wire) : _seesaw(new Adafruit_seesaw(wire)) {}
Seesaw::~Seesaw() { delete _seesaw; }
bool Seesaw::begin(uint8_t addr) { return _seesaw->begin(addr); }
uint16_t Seesaw::getVersion() { return _seesaw->getVersion(); }
void Seesaw::pinMode(uint8_t pin, uint8_t mode) { _seesaw->pinMode(pin, mode); }
void Seesaw::digitalWrite(uint8_t pin, uint8_t value) { _seesaw->digitalWrite(pin, value); }
uint8_t Seesaw::digitalRead(uint8_t pin) { return _seesaw->digitalRead(pin); }
uint16_t Seesaw::analogRead(uint8_t pin) { return _seesaw->analogRead(pin); }
void Seesaw::analogWrite(uint8_t pin, uint16_t value) { _seesaw->analogWrite(pin, value); }
Adafruit_seesaw* Seesaw::getNativeSeesaw() { return _seesaw; }

// NeoPixel abstraction
NeoPixel::NeoPixel(uint16_t n, uint8_t pin, neoPixelType type)
    : _strip(new Adafruit_NeoPixel(n, pin, type)) {}
NeoPixel::~NeoPixel() { delete _strip; }
void NeoPixel::begin() { _strip->begin(); _strip->show(); }
void NeoPixel::setPixelColor(uint16_t n, uint32_t color) { _strip->setPixelColor(n, color); }
void NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) { _strip->setPixelColor(n, r, g, b); }
void NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) { _strip->setPixelColor(n, r, g, b, w); }
uint32_t NeoPixel::getPixelColor(uint16_t n) { return _strip->getPixelColor(n); }
void NeoPixel::show() { _strip->show(); }
void NeoPixel::clear() { _strip->clear(); }
uint16_t NeoPixel::numPixels() { return _strip->numPixels(); }
void NeoPixel::setBrightness(uint8_t brightness) { _strip->setBrightness(brightness); }
uint8_t NeoPixel::getBrightness() { return _strip->getBrightness(); }
Adafruit_NeoPixel* NeoPixel::getNativeStrip() { return _strip; }
uint32_t NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b) { return Adafruit_NeoPixel::Color(r, g, b); }
uint32_t NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) { return Adafruit_NeoPixel::Color(r, g, b, w); }
uint32_t NeoPixel::ColorHSV(uint16_t hue, uint8_t sat, uint8_t val) { return Adafruit_NeoPixel::ColorHSV(hue, sat, val); }

// Factory functions
Display* createSSD1306Display(int16_t width, int16_t height, TwoWire* wire, int8_t rst_pin) {
    return new SSD1306Display(width, height, wire, rst_pin);
}
Seesaw* createSeesaw(TwoWire* wire) { return new Seesaw(wire); }
NeoPixel* createNeoPixel(uint16_t n, uint8_t pin, neoPixelType type) {
    return new NeoPixel(n, pin, type);
}

} // namespace CurioDrivers
