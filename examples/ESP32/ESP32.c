/*
  NTC Thermistor for ESP32 higher accuracy results

  Reads a temperature from the NTC 3950 thermistor and displays
  it in the default Serial.

  ESP32 devices are 12-bit ADC devices so the defuault is 4095 here.

  https://github.com/bobwolff68/NTC_Thermistor

  Created by Bob Wolff from Yuri's original - 2024
  Released into the public domain.
*/
#include <Thermistor.h>
#include <NTC_Thermistor.h>

#define SENSOR_PIN              3
#define REFERENCE_RESISTANCE    10000
#define NOMINAL_RESISTANCE      10000
#define NOMINAL_TEMPERATURE     25
#define B_VALUE                 3950
#define ESP32_ANALOG_RESOLUTION 4095
#define ESP32_ADC_VREF_MV       3300

Thermistor* thermistor;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  thermistor = new NTC_Thermistor_ESP32(
    SENSOR_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
    ESP32_ADC_VREF_MV,
    ESP32_ANALOG_RESOLUTION
  );
}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  const double celsius = thermistor->readCelsius();
  const double kelvin = thermistor->readKelvin();
  const double fahrenheit = thermistor->readFahrenheit();

  // Output of information
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(kelvin);
  Serial.print(" K, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  delay(500); // optionally, only to delay the output of information in the example.
}
