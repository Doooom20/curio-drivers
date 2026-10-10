// Minimal String.h stub for IntelliSense

#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

class String {
public:
    String() : _buffer(nullptr), _length(0), _capacity(0) {}
    String(const char* cstr) : _buffer(nullptr), _length(0), _capacity(0) {
        if (cstr) {
            _length = strlen(cstr);
            _capacity = _length + 1;
            _buffer = new char[_capacity];
            strcpy(_buffer, cstr);
        }
    }
    String(const String& other) : _buffer(nullptr), _length(0), _capacity(0) {
        if (other._buffer) {
            _length = other._length;
            _capacity = other._capacity;
            _buffer = new char[_capacity];
            strcpy(_buffer, other._buffer);
        }
    }
    ~String() {
        delete[] _buffer;
    }
    
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] _buffer;
            _length = other._length;
            _capacity = other._capacity;
            if (other._buffer) {
                _buffer = new char[_capacity];
                strcpy(_buffer, other._buffer);
            } else {
                _buffer = nullptr;
            }
        }
        return *this;
    }
    
    char charAt(unsigned int index) const { return _buffer ? _buffer[index] : 0; }
    int length() const { return _length; }
    bool operator==(const String& other) const { return _length == other._length && strcmp(_buffer, other._buffer) == 0; }
    const char* c_str() const { return _buffer ? _buffer : ""; }
    
private:
    char* _buffer;
    int _length;
    int _capacity;
};

#endif // STRING_H