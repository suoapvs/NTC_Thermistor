#include "AverageThermistor.h"

AverageThermistor::AverageThermistor(
  Thermistor* origin,
  const int readingsNumber,
  const int delayTimeInMillis
) {
  this->origin = origin;
  this->readingsNumber = validate(readingsNumber, NTC_AVERAGE_READINGS_NUMBER);
  this->delayTime = validate(timeoutInMillis, NTC_AVERAGE_DELAY_TIME);
}

AverageThermistor::~AverageThermistor() {
  delete this->origin;
}

double AverageThermistor::readCelsius() {
  return average(&Thermistor::readCelsius, this->origin);
}

double AverageThermistor::readKelvin() {
  return average(&Thermistor::readKelvin, this->origin);
}

double AverageThermistor::readFahrenheit() {
  return average(&Thermistor::readFahrenheit, this->origin);
}

double AverageThermistor::average(
  double (Thermistor::*read)(),
  Thermistor* thermistor
) {
  double sum = 0;
  for (int i = 0; i < this->readingsNumber; i++) {
    sum += (thermistor->*read)();
    sleep();
  }
  return (sum / this->readingsNumber);
}

inline void AverageThermistor::sleep() {
  delay(this->delayTime);
}

template <typename A, typename B>
A AverageThermistor::validate(A data, B alternative) {
  return (data > 0) ? data : alternative;
}
