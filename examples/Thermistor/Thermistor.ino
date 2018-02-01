/*
  Thermistor.

  Reads a temperature from the NTC 3950 thermistor and displays
  it in the default Serial.

  Yurii Salimov (yuriy.alex.salimov@gmail.com)
*/
#include <NTC_Thermistor.h>

#define SENSOR_PIN             A1
#define REFERENCE_RESISTANCE   8000
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

NTC_Thermistor* thermistor;

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
  Serial.print("Temperature: ");
  Serial.print(String(thermistor->readCelsius()) + " C, ");
  Serial.print(String(thermistor->readFahrenheit()) + " F, ");
  Serial.println(String(thermistor->readKelvin()) + " K");
}

