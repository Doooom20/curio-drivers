// Minimal Print.h stub for IntelliSense

#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stddef.h>

class Print {
public:
    virtual size_t write(uint8_t) = 0;
    
    size_t print(const char* str) { return 0; }
    size_t print(char c) { return 0; }
    size_t print(unsigned char b, int base = 10) { return 0; }
    size_t print(int n, int base = 10) { return 0; }
    size_t print(unsigned int n, int base = 10) { return 0; }
    size_t print(long n, int base = 10) { return 0; }
    size_t print(unsigned long n, int base = 10) { return 0; }
    size_t print(double n, int digits = 2) { return 0; }
    
    size_t println(const char* str) { return 0; }
    size_t println(char c) { return 0; }
    size_t println(unsigned char b, int base = 10) { return 0; }
    size_t println(int n, int base = 10) { return 0; }
    size_t println(unsigned int n, int base = 10) { return 0; }
    size_t println(long n, int base = 10) { return 0; }
    size_t println(unsigned long n, int base = 10) { return 0; }
    size_t println(double n, int digits = 2) { return 0; }
    size_t println() { return 0; }
    
    size_t printf(const char* format, ...) { return 0; }
};

#endif // PRINT_H