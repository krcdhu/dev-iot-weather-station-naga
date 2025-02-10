#include <Wire.h>
#include "Adafruit_SHT4x.h"
#include "Adafruit_BMP3XX.h"

// Create instances for both sensors
Adafruit_SHT4x sht45 = Adafruit_SHT4x();
Adafruit_BMP3XX bmp390;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial port to connect

  Serial.println("Initializing sensors...");

  // Initialize the SHT45 sensor
  if (!sht45.begin()) {
    Serial.println("Couldn't find SHT45 sensor :(");
    while (1) delay(1);
  }
  Serial.println("Found SHT45 sensor :)");

  // Set SHT45 precision to high and disable heater
  sht45.setPrecision(SHT4X_HIGH_PRECISION);
  sht45.setHeater(SHT4X_NO_HEATER);

  // Initialize the BMP390 sensor
  if (!bmp390.begin_I2C()) {
    Serial.println("Couldn't find BMP390 sensor :(");
    while (1) delay(1);
  }
  Serial.println("Found BMP390 sensor :)");

  // Set up BMP390 oversampling and filter initialization
  bmp390.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp390.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp390.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp390.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  // Declare sensor event objects for SHT45
  sensors_event_t humidity, temp;
  sht45.getEvent(&humidity, &temp);

  // Read temperature from SHT45
  Serial.print("SHT45 Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  // Read humidity from SHT45
  Serial.print("SHT45 Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  // Read temperature and pressure from BMP390
  if (!bmp390.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("BMP390 Temperature: ");
  Serial.print(bmp390.temperature);
  Serial.println(" °C");

  Serial.print("BMP390 Pressure: ");
  Serial.print(bmp390.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("BMP390 Approx. Altitude: ");
  Serial.print(bmp390.readAltitude(1013.25)); // Adjust the sea level pressure as needed
  Serial.println(" m");

  Serial.println();
  delay(5000); // Delay between readings
}
