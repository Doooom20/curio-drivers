// Minimal Stream.h stub for IntelliSense

#ifndef STREAM_H
#define STREAM_H

#include <stdint.h>
#include <stddef.h>
#include "Print.h"
#include "String.h"

class Stream : public Print {
public:
    int available() { return 0; }
    int read() { return -1; }
    int peek() { return -1; }
    void flush() {}
    size_t readBytes(char* buffer, size_t length) { return 0; }
    size_t readBytes(uint8_t* buffer, size_t length) { return 0; }
    int readBytesUntil(char terminator, char* buffer, size_t length) { return 0; }
    int readBytesUntil(char terminator, uint8_t* buffer, size_t length) { return 0; }
    String readString() { return String(); }
    String readStringUntil(char terminator) { return String(); }
    int find(char* target) { return 0; }
    int find(uint8_t* target) { return 0; }
    int find(const char* target) { return 0; }
    int findUntil(char* target, char* terminator) { return 0; }
    int findUntil(uint8_t* target, uint8_t* terminator) { return 0; }
    int findUntil(const char* target, const char* terminator) { return 0; }
    long parseInt() { return 0; }
    float parseFloat() { return 0; }
    size_t setTimeout(unsigned long timeout) { return 0; }
    unsigned long getTimeout() { return 0; }
};

#endif // STREAM_H