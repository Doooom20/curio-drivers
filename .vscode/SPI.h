// Minimal SPI.h stub for IntelliSense

#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include <stddef.h>
#include "Arduino.h"

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_HALF_SPEED 0
#define SPI_QUARTER_SPEED 1
#define SPI_EIGHTH_SPEED 2
#define SPI_SIXTEENTH_SPEED 3

// MSBFIRST and LSBFIRST are defined in Arduino.h as BitOrder enum values

class SPISettings {
public:
    SPISettings(uint32_t clock = 4000000, BitOrder bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE0) {}
};

class SPIClass {
public:
    void begin() {}
    void end() {}
    void beginTransaction(SPISettings settings) {}
    void endTransaction() {}
    uint8_t transfer(uint8_t data) { return 0; }
    uint16_t transfer16(uint16_t data) { return 0; }
    void transfer(void* buf, size_t count) {}
    void setBitOrder(BitOrder bitOrder) {}
    void setDataMode(uint8_t dataMode) {}
    void setClockDivider(uint8_t clockDiv) {}
    void setFrequency(uint32_t freq) {}
    void setHwCs(uint8_t cs) {}
    void usingInterrupt(uint8_t interruptNumber) {}
    void notUsingInterrupt(uint8_t interruptNumber) {}
    void attachInterrupt() {}
    void detachInterrupt() {}
};

extern SPIClass SPI;

#endif // SPI_H