#include "Arduino.h"
#include "Adafruit_SHT4x.h"
#include <Wire.h>

Adafruit_SHT4x sht45;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial port to connect

  Serial.println("Adafruit SHT45 Temp and Hum Sensor");
  Serial.println("Initializing...");

  // Initialize the SHT4x sensor
  if (!sht45.begin()) {
    Serial.println("Couldn't find SHT45 sensor :(");
    while (1) delay(1);
  }
  Serial.println("Found SHT45 sensor :)");
  Serial.println("----------------------------------");

  // Set precision to high
  sht45.setPrecision(SHT4X_HIGH_PRECISION);
  // Disable heater
  sht45.setHeater(SHT4X_NO_HEATER);
}

void loop() {
  // Declare sensor event objects
  sensors_event_t humidity, temp;
  sht45.getEvent(&humidity, &temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(5000);
}
