/**
  AverageThermistor.h - class-wrapper allows to average
  the temperature value of origin Thermistor instance.

  Instantiation:
  Thermistor* thermistor = new AverageThermistor(
    THERMISTOR, READINGS_NUMBER, DELAY_TIME
  );

  Where,
  THERMISTOR - origin Thermistor instance.

  READINGS_NUMBER - How many readings are taken
  to determine a mean temperature. The more values,
  the longer a calibration is performed, but the readings
  will be more accurate.

  DELAY_TIME - Delay time between a temperature readings
  from the temperature sensor (ms).

  Read temperature:
  double celsius = thermistor->readCelsius();
  double kelvin = thermistor->readKelvin();
  double fahrenheit = thermistor->readFahrenheit();

  v.2.0.0
  - created

  https://github.com/YuriiSalimov/NTC_Thermistor

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#ifndef AVERAGE_THERMISTOR_H
#define AVERAGE_THERMISTOR_H

#include "Thermistor.h"

// Default number of average readings.
#define NTC_AVERAGE_READINGS_NUMBER	5
// Default delay time of average readings.
#define NTC_AVERAGE_DELAY_TIME	10

class AverageThermistor final : public Thermistor {

  private:
    Thermistor* origin;
    int readingsNumber;
    int delayTime;

  public:
    /**
      Constructor

      @param origin - origin Thermistor instance.
      @param readingsNumber - average readings number
      @param delayTimeInMillis - average delay time (in milliseconds)
    */
    AverageThermistor(
      Thermistor* origin,
      int readingsNumber,
      int delayTimeInMillis
    );

    /**
      Destructor
      Deletes the origin Thermistor instance.
    */
    ~AverageThermistor();

    /**
      Returns an average temperature in Celsius.
    */
    double readCelsius() override;

    /**
      Returns an average temperature in Kelvin.
    */
    double readKelvin() override;

    /**
      Returns an average temperature in Fahrenheit.
    */
    double readFahrenheit() override;

  private:
    double average(
      double (Thermistor::*read)(),
      Thermistor* thermistor
    );

    /**
      For delay between readings.
    */
    inline void sleep();

    /**
      Returns the data if it is valid,
      otherwise returns alternative data.
    */
    template <typename A, typename B> A validate(A data, B alternative);
};

#endif
