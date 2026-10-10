
#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>
#include "curio-drivers.h"

using namespace CurioDrivers;

// Hardware configuration
constexpr int16_t SCREEN_WIDTH  = 128;
constexpr int16_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_RESET     = -1;
constexpr uint8_t CALCULATOR_SEESAW_ADDRESS = 0x50;
constexpr uint8_t CLEAR_PIN = 0;

// Seesaw button pins
constexpr uint8_t BUTTON_X      = 6;
constexpr uint8_t BUTTON_Y      = 2;
constexpr uint8_t BUTTON_A      = 5;
constexpr uint8_t BUTTON_B      = 1;
constexpr uint8_t BUTTON_SELECT = 0;
constexpr uint8_t BUTTON_START  = 16;

// Hardware abstraction
Display* display = nullptr;
Seesaw* controls = nullptr;

// Calculator state
double inputOne = 0;
double inputTwo = 0;
double output = 0;

uint8_t operation = 0;
int selectedInput = 0;

constexpr uint16_t STACK_SIZE = 256;
double stack[STACK_SIZE];
uint16_t stackPointer = 0;

const char operationCharacters[] = {'+', '-', 'x', '/'};

constexpr uint8_t BUTTON_PINS[] = {
    BUTTON_X,
    BUTTON_Y,
    BUTTON_A,
    BUTTON_B,
    BUTTON_SELECT,
    BUTTON_START
};

// Stack operations
bool push(double value) {
    if (stackPointer >= STACK_SIZE) {
        return false;
    }

    stack[stackPointer++] = value;
    return true;
}

bool pop(double& value) {
    if (stackPointer == 0) {
        return false;
    }

    value = stack[--stackPointer];
    return true;
}

// Input handling
bool pressed(uint8_t pin) {
    return controls->digitalRead(pin) == LOW;
}

void resetCalculator() {
    inputOne = 0;
    inputTwo = 0;
    output = 0;
    operation = 0;
    selectedInput = 0;
    stackPointer = 0;
}

void handleInput() {
    if (pressed(BUTTON_A)) {
        selectedInput = (selectedInput + 1) % 3;
        delay(180);
    }

    if (pressed(BUTTON_Y)) {
        selectedInput = (selectedInput + 2) % 3;
        delay(180);
    }

    if (pressed(BUTTON_B)) {
        switch (selectedInput) {
            case 0:
                inputOne--;
                break;

            case 1:
                operation = (operation + 3) % 4;
                break;

            case 2:
                inputTwo--;
                break;
        }

        delay(100);
    }

    if (pressed(BUTTON_X)) {
        switch (selectedInput) {
            case 0:
                inputOne++;
                break;

            case 1:
                operation = (operation + 1) % 4;
                break;

            case 2:
                inputTwo++;
                break;
        }

        delay(100);
    }

    if (pressed(BUTTON_SELECT)) {
        push(output);
        delay(180);
    }

    if (pressed(BUTTON_START)) {
        double value;

        if (pop(value)) {
            switch (selectedInput) {
                case 0:
                    inputOne = value;
                    break;

                case 2:
                    inputTwo = value;
                    break;
            }
        }

        delay(180);
    }
}

// Calculator logic
void calculate() {
    switch (operation) {
        case 0:
            output = inputOne + inputTwo;
            break;

        case 1:
            output = inputOne - inputTwo;
            break;

        case 2:
            output = inputOne * inputTwo;
            break;

        case 3:
            output = (inputTwo != 0)
                ? inputOne / inputTwo
                : NAN;
            break;
    }
}

// Display helpers
void printNumber(double value, uint8_t decimals = 0) {
    char buffer[32];

    if (isnan(value)) {
        display->print("Undefined");
        return;
    }

    if (isinf(value)) {
        display->print(value < 0 ? "-Infinity" : "Infinity");
        return;
    }

    snprintf(buffer, sizeof(buffer), "%.*f", decimals, value);
    display->print(buffer);
}

void drawCalculator() {
    display->clear();
    display->setTextColor(1);

    // Expression
    display->setTextSize(2);
    display->setCursor(0, 2);
    printNumber(inputOne);

    display->setCursor(30, 2);
    char op[2] = {operationCharacters[operation], '\0'};
    display->print(op);

    display->setCursor(60, 2);
    printNumber(inputTwo);

    display->setCursor(90, 2);
    display->print("=");

    // Selected operand indicator
    const int16_t positions[] = {0, 30, 60};
    display->fillRect(0, 16, 128, 5, 0);
    display->fillRect(positions[selectedInput], 16, 10, 5, 1);

    // Result
    display->setCursor(0, 24);

    if (isnan(output) || isinf(output)) {
        printNumber(output);
    } else if (fabs(output - round(output)) < 0.000000001) {
        printNumber(output, 0);
    } else {
        printNumber(output, 3);
    }

    // Stack status
    display->setTextSize(1);
    display->setCursor(0, 40);

    char status[32];
    snprintf(
        status,
        sizeof(status),
        "Stack: %u/%u",
        static_cast<unsigned>(stackPointer),
        static_cast<unsigned>(STACK_SIZE)
    );
    display->println(status);

    display->display();
}

// Initialization
void setup() {
    Serial.begin(9600);
    Wire.begin();

    pinMode(CLEAR_PIN, INPUT_PULLUP);

    display = createSSD1306Display(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        &Wire,
        OLED_RESET
    );

    controls = createSeesaw(&Wire);

    display->begin();

    if (!controls->begin(CALCULATOR_SEESAW_ADDRESS)) {
        Serial.println("Seesaw initialization failed.");

        while (true) {
            delay(100);
        }
    }

    for (uint8_t pin : BUTTON_PINS) {
        controls->pinMode(pin, INPUT_PULLUP);
    }

    display->setTextSize(2);
    display->setTextColor(1);
    display->setCursor(0, 20);
    display->println("Calculator");
    display->display();

    delay(500);
}

// Main application loop
void loop() {
    if (digitalRead(CLEAR_PIN) == LOW) {
        resetCalculator();
        delay(180);
    }

    handleInput();
    calculate();
    drawCalculator();
}
