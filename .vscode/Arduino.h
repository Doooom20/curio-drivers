// Minimal Arduino.h stub for IntelliSense
// This provides basic Arduino types and macros without pulling in ESP-IDF

#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Arduino version
#define ARDUINO 10819

// Basic types
typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

// Boolean
#define HIGH 0x1
#define LOW 0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define INPUT_PULLDOWN 0x3

// Constants
#define true 1
#define false 0

// Min/Max
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define map(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

// Digital/Analog
#define PI 3.14159265358979323846
#define HALF_PI 1.57079632679489661923
#define TWO_PI 6.28318530717958647693
#define DEG_TO_RAD 0.01745329251994329577
#define RAD_TO_DEG 57.29577951308232087679

// PROGMEM
#define PROGMEM
#define PSTR(x) (x)
#define pgm_read_byte(x) (*(x))
#define pgm_read_word(x) (*(x))
#define pgm_read_dword(x) (*(x))
#define pgm_read_float(x) (*(x))
#define pgm_read_ptr(x) (*(x))

// F() macro
#define F(string_literal) (string_literal)

// Flash string helper
class __FlashStringHelper {};

// BitOrder
typedef enum {
    MSBFIRST = 0,
    LSBFIRST = 1
} BitOrder;

// Interrupts
#define noInterrupts() 
#define interrupts()

// Time
unsigned long millis();
unsigned long micros();
void delay(unsigned long);
void delayMicroseconds(unsigned long);

// Yield
#define yield()

// Setup/Loop
void setup();
void loop();

#endif // ARDUINO_H