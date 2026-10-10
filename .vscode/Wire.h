// Minimal Wire.h stub for IntelliSense

#ifndef WIRE_H
#define WIRE_H

#include <stdint.h>
#include <stddef.h>
#include "Arduino.h"
#include "Stream.h"

class TwoWire : public Stream {
public:
    TwoWire() {}
    void begin() {}
    void begin(int sda, int scl) {}
    void end() {}
    void setClock(uint32_t clock) {}
    uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop = 1) { return 0; }
    uint8_t requestFrom(uint8_t address, uint8_t quantity) { return 0; }
    void beginTransmission(uint8_t address) {}
    uint8_t endTransmission(uint8_t sendStop = 1) { return 0; }
    uint8_t endTransmission() { return 0; }
    size_t write(uint8_t data) { return 1; }
    size_t write(const uint8_t* data, size_t quantity) { return 0; }
    int available() { return 0; }
    int read() { return -1; }
    int peek() { return -1; }
    void flush() {}
    void onReceive(void (*)(int)) {}
    void onRequest(void (*)(void)) {}
};

extern TwoWire Wire;

#endif // WIRE_H