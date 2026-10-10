#ifndef CURIO_DRIVERS_H
#define CURIO_DRIVERS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_seesaw.h>
#include <Adafruit_NeoPixel.h>

namespace CurioDrivers {

// Display abstraction
class Display {
public:
    virtual ~Display() = default;
    virtual void begin() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void setTextColor(uint16_t color) = 0;
    virtual void setTextSize(uint8_t size) = 0;
    virtual void print(const char* str) = 0;
    virtual void println(const char* str) = 0;
    virtual int16_t width() = 0;
    virtual int16_t height() = 0;
};

// SSD1306 Display implementation
class SSD1306Display : public Display {
private:
    Adafruit_SSD1306* _display;
    int16_t _width;
    int16_t _height;

public:
    SSD1306Display(int16_t width, int16_t height, TwoWire* wire = &Wire, int8_t rst_pin = -1);
    ~SSD1306Display() override;

    void begin() override;
    void clear() override;
    void display() override;
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) override;
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void setCursor(int16_t x, int16_t y) override;
    void setTextColor(uint16_t color) override;
    void setTextSize(uint8_t size) override;
    void print(const char* str) override;
    void println(const char* str) override;
    int16_t width() override;
    int16_t height() override;
    Adafruit_SSD1306* getNativeDisplay();
};

// Seesaw abstraction
class Seesaw {
private:
    Adafruit_seesaw* _seesaw;

public:
    explicit Seesaw(TwoWire* wire = &Wire);
    ~Seesaw();

    bool begin(uint8_t addr = 0x36);
    uint16_t getVersion();
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t value);
    uint8_t digitalRead(uint8_t pin);
    uint16_t analogRead(uint8_t pin);
    void analogWrite(uint8_t pin, uint16_t value);
    Adafruit_seesaw* getNativeSeesaw();
};

// NeoPixel abstraction
class NeoPixel {
private:
    Adafruit_NeoPixel* _strip;

public:
    NeoPixel(uint16_t n, uint8_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800);
    ~NeoPixel();

    void begin();
    void setPixelColor(uint16_t n, uint32_t color);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    uint32_t getPixelColor(uint16_t n);
    void show();
    void clear();
    uint16_t numPixels();
    void setBrightness(uint8_t brightness);
    uint8_t getBrightness();
    Adafruit_NeoPixel* getNativeStrip();

    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255);
};

// Factory functions
Display* createSSD1306Display(int16_t width, int16_t height, TwoWire* wire = &Wire, int8_t rst_pin = -1);
Seesaw* createSeesaw(TwoWire* wire = &Wire);
NeoPixel* createNeoPixel(uint16_t n, uint8_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800);

} // namespace CurioDrivers

#endif // CURIO_DRIVERS_H
