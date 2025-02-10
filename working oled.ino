#include <Wire.h>
#include "HT_SSD1306Wire.h"

// Initialize the display with the I2C address and pins
static SSD1306Wire  display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Power on the OLED display
  VextON();
  delay(100);

  // Initialize the display
  display.init();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  // Clear the display
  display.clear();

  // Set text alignment to the left
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Display "Hello world" in different font sizes
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "SHT45");

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 25, "Temperature: ");

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 43, "Humidity: ");

  // Write the buffer to the display
  display.display();

  // Add a short delay before the next update
  delay(1000);
}

// Function to power on the OLED display
void VextON() {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

// Function to power off the OLED display
void VextOFF() {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);
}
