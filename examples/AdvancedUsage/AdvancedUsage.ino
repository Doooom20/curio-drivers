/*
  CurioDrivers Advanced Usage Example
  
  This example demonstrates advanced features of the CurioDrivers library
  including direct access to native Adafruit objects for custom functionality.
*/

#include <CurioDrivers.h>

using namespace CurioDrivers;

// Create instances
SSD1306Display* display = nullptr;
Seesaw* seesaw = nullptr;
NeoPixel* neopixel = nullptr;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("CurioDrivers Advanced Usage Example");
  
  // Initialize SSD1306 display with custom I2C address
  display = new SSD1306Display(128, 64, &Wire, -1);
  display->begin();
  
  // Access native Adafruit_SSD1306 for advanced features
  Adafruit_SSD1306* nativeDisplay = display->getNativeDisplay();
  nativeDisplay->setRotation(0);
  nativeDisplay->dim(false);
  nativeDisplay->invertDisplay(false);
  
  // Initialize Seesaw
  seesaw = createSeesaw();
  if (seesaw->begin()) {
    Serial.print("Seesaw found! Version: 0x");
    Serial.println(seesaw->getVersion(), HEX);
    
    // Access native Adafruit_seesaw for advanced features
    Adafruit_seesaw* nativeSeesaw = seesaw->getNativeSeesaw();
    
    // Configure Seesaw GPIO pins
    nativeSeesaw->pinMode(0, INPUT_PULLUP);  // Button input
    nativeSeesaw->pinMode(1, OUTPUT);        // LED output
    nativeSeesaw->pinMode(2, INPUT);         // Analog input
    
    // Enable PWM on pin 1
    nativeSeesaw->analogWrite(1, 128);  // 50% duty cycle
  }
  
  // Initialize NeoPixel with custom type (RGBW)
  neopixel = new NeoPixel(16, 6, NEO_GRBW + NEO_KHZ800);
  neopixel->begin();
  neopixel->setBrightness(100);
  
  // Access native Adafruit_NeoPixel for advanced features
  Adafruit_NeoPixel* nativeStrip = neopixel->getNativeStrip();
  
  // Show startup animation
  startupAnimation();
  
  Serial.println("Advanced setup complete!");
}

void loop() {
  // Read button from Seesaw
  if (seesaw) {
    uint8_t buttonState = seesaw->digitalRead(0);
    
    // Control LED on Seesaw based on button
    seesaw->digitalWrite(1, buttonState ? HIGH : LOW);
    
    // Read analog value
    uint16_t analogVal = seesaw->analogRead(2);
    
    // Map analog value to NeoPixel brightness
    uint8_t brightness = map(analogVal, 0, 1023, 0, 255);
    neopixel->setBrightness(brightness);
    
    // Display info on screen
    display->clear();
    display->setCursor(0, 0);
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->println("Advanced Demo");
    display->print("Button: ");
    display->println(buttonState ? "PRESSED" : "RELEASED");
    display->print("Analog: ");
    display->println(analogVal);
    display->print("Brightness: ");
    display->println(brightness);
    display->display();
  }
  
  // Rainbow cycle with brightness control
  static uint16_t hue = 0;
  for (int i = 0; i < neopixel->numPixels(); i++) {
    uint32_t color = NeoPixel::ColorHSV(hue + (i * 65536 / neopixel->numPixels()));
    neopixel->setPixelColor(i, color);
  }
  neopixel->show();
  hue += 128;
  
  delay(20);
}

void startupAnimation() {
  // Theater chase animation
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < neopixel->numPixels(); i += 3) {
        neopixel->setPixelColor(i + q, NeoPixel::Color(255, 255, 255));
      }
      neopixel->show();
      delay(50);
      for (int i = 0; i < neopixel->numPixels(); i += 3) {
        neopixel->setPixelColor(i + q, 0);
      }
    }
  }
  
  // Color wipe
  uint32_t colors[] = {
    NeoPixel::Color(255, 0, 0),
    NeoPixel::Color(0, 255, 0),
    NeoPixel::Color(0, 0, 255),
    NeoPixel::Color(255, 255, 0),
    NeoPixel::Color(0, 255, 255),
    NeoPixel::Color(255, 0, 255)
  };
  
  for (uint32_t color : colors) {
    for (int i = 0; i < neopixel->numPixels(); i++) {
      neopixel->setPixelColor(i, color);
      neopixel->show();
      delay(20);
    }
  }
  
  neopixel->clear();
  neopixel->show();
}