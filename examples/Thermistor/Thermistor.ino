/*
  Thermistor.

  Reads a temperature from the NTC 3950 thermistor and displays
  it in the default Serial.

  https://github.com/YuriiSalimov/NTC_Thermistor

  Created by Yurii Salimov, February, 2018.
  Released into the public domain.
*/
#include <NTC_Thermistor.h>

#define SENSOR_PIN             A1
#define REFERENCE_RESISTANCE   8000
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

NTC_Thermistor* thermistor = NULL;

void setup() {
  Serial.begin(9600);
  thermistor = new NTC_Thermistor(
    SENSOR_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE
  );
}

void loop() {
  const double celsius = thermistor->readCelsius();
  const double kelvin = thermistor->readKelvin();
  const double fahrenheit = thermistor->readFahrenheit();
  Serial.print("Temperature: ");
  Serial.print(String(celsius) + " C, ");
  Serial.print(String(kelvin) + " K, ");
  Serial.println(String(fahrenheit) + " F");
  delay(500);
}

