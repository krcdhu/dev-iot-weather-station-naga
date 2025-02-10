#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_GFX.h>

// Create instances for BMP390 sensor
Adafruit_BMP3XX bmp390;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("BMP390 Pressure Sensor");
  Serial.println("Initializing...");

  // Initialize BMP390 sensor
  if (!bmp390.begin_I2C()) {
    Serial.println("Couldn't find BMP390 sensor :(");
    while (1);
  }
  Serial.println("Found BMP390 sensor :)");
  Serial.println("----------------------------------");

  // Set up oversampling and filter initialization for BMP390
  bmp390.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp390.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp390.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp390.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  // Perform a reading from the BMP390 sensor
  if (!bmp390.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // Display the sensor readings on the serial monitor
  Serial.print("Temperature = ");
  Serial.print(bmp390.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp390.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp390.readAltitude(1013.25)); // Adjust the sea level pressure as needed
  Serial.println(" m");

  delay(5000);
}
