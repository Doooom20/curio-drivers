/*
  CurioDrivers Basic Usage Example
  
  This example demonstrates how to use the CurioDrivers library
  to control an SSD1306 display, Seesaw device, and NeoPixel strip.
*/

#include <CurioDrivers.h>

using namespace CurioDrivers;

// Create instances
Display* display = nullptr;
Seesaw* seesaw = nullptr;
NeoPixel* neopixel = nullptr;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("CurioDrivers Basic Usage Example");
  
  // Initialize SSD1306 display (128x64)
  display = createSSD1306Display(128, 64);
  display->begin();
  display->clear();
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);
  display->println("CurioDrivers Ready!");
  display->display();
  
  // Initialize Seesaw
  seesaw = createSeesaw();
  if (seesaw->begin()) {
    Serial.print("Seesaw found! Version: 0x");
    Serial.println(seesaw->getVersion(), HEX);
    display->println("Seesaw: OK");
  } else {
    Serial.println("Seesaw not found!");
    display->println("Seesaw: NOT FOUND");
  }
  display->display();
  
  // Initialize NeoPixel (8 pixels on pin 6)
  neopixel = createNeoPixel(8, 6);
  neopixel->begin();
  neopixel->setBrightness(50);
  
  // Test NeoPixel
  for (int i = 0; i < neopixel->numPixels(); i++) {
    neopixel->setPixelColor(i, NeoPixel::Color(255, 0, 0)); // Red
  }
  neopixel->show();
  delay(500);
  
  for (int i = 0; i < neopixel->numPixels(); i++) {
    neopixel->setPixelColor(i, NeoPixel::Color(0, 255, 0)); // Green
  }
  neopixel->show();
  delay(500);
  
  for (int i = 0; i < neopixel->numPixels(); i++) {
    neopixel->setPixelColor(i, NeoPixel::Color(0, 0, 255)); // Blue
  }
  neopixel->show();
  delay(500);
  
  neopixel->clear();
  neopixel->show();
  
  display->println("NeoPixel: OK");
  display->display();
  
  Serial.println("Setup complete!");
}

void loop() {
  // Demo: Rainbow cycle on NeoPixel
  static uint16_t hue = 0;
  
  for (int i = 0; i < neopixel->numPixels(); i++) {
    uint32_t color = NeoPixel::ColorHSV(hue + (i * 65536 / neopixel->numPixels()));
    neopixel->setPixelColor(i, color);
  }
  neopixel->show();
  
  hue += 256;
  
  // Read from Seesaw if available
  if (seesaw) {
    // Example: Read analog value from pin 0
    uint16_t analogVal = seesaw->analogRead(0);
    
    // Display on screen
    display->clear();
    display->setCursor(0, 0);
    display->println("CurioDrivers Demo");
    display->print("Seesaw A0: ");
    display->println(analogVal);
    display->print("Hue: ");
    display->println(hue);
    display->display();
  }
  
  delay(50);
}