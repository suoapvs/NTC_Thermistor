#include "SmoothThermistor.h"

SmoothThermistor::SmoothThermistor(
  Thermistor* origin,
  const int factor
) {
  this->origin = origin;
  this->factor = factor;
}

SmoothThermistor::~SmoothThermistor() {
  delete this->origin;
}

double SmoothThermistor::readCelsius() {
  return this->celsius = smoothe(
    this->origin->readCelsius(),
    this->celsius
  );
}

double SmoothThermistor::readKelvin() {
  return this->kelvin = smoothe(
    this->origin->readKelvin(),
    this->kelvin
  );
}

double SmoothThermistor::readFahrenheit() {
  return this->fahrenheit = smoothe(
    this->origin->readFahrenheit(),
    this->fahrenheit
  );
}

double SmoothThermistor::smoothe(
  const double input,
  const double data
) {
  return (this->factor > 1) ?
    (data * (this->factor - 1) + input) / this->factor :
    input;
}
