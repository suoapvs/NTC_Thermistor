/**
  AverageThermistor - class-wrapper allows to average
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

  v.2.0.2
  - optimized average(*) method;
  - renamed default constants;
  - added default value of constructor parameters;
  - updated documentation.

  https://github.com/YuriiSalimov/NTC_Thermistor

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#ifndef AVERAGE_THERMISTOR_H
#define AVERAGE_THERMISTOR_H

#include "Thermistor.h"

// Default number of average readings.
#define NTC_DEFAULT_AVERAGE_READINGS_NUMBER 10
// Default delay time of average readings.
#define NTC_DEFAULT_AVERAGE_DELAY_TIME 1

class AverageThermistor final : public Thermistor {

  private:
    Thermistor* origin;
    int readingsNumber;
    int delayTime;

  public:
    /**
      Constructor

      @param origin - origin Thermistor instance (not NULL)
      @param readingsNumber - average readings number (default, 10)
      @param delayTimeInMillis - average delay time in milliseconds (default, 1 ms)
    */
    AverageThermistor(
      Thermistor* origin,
      int readingsNumber = NTC_DEFAULT_AVERAGE_READINGS_NUMBER,
      int delayTimeInMillis = NTC_DEFAULT_AVERAGE_DELAY_TIME
    );

    /**
      Destructor
      Deletes the origin Thermistor instance.
    */
    ~AverageThermistor();

    /**
      Reads a temperature in Celsius from the thermistor.

      @return average temperature in degree Celsius
    */
    double readCelsius() override;

    /**
      Reads a temperature in Kelvin from the thermistor.

      @return average temperature in degree Kelvin
    */
    double readKelvin() override;

    /**
      Reads a temperature in Fahrenheit from the thermistor.

      @return average temperature in degree Fahrenheit
    */
    double readFahrenheit() override;

  private:
    /**
      Reads the temperature from the "*read()" method
      "readingsNumber" times with delay "delayTimeInMillis".
      Returns the average value.

      @param *read - origin method that return temperature (not NULL)
      @return average temperature from the input *read() method
    */
    inline double average(double (Thermistor::*read)());

    /**
      For delay between readings.
    */
    inline void sleep();

    /**
      Validates the input data.

      @param data - value to validate
      @param alternative - alternative value to return
      @returns the data if it is valid (> 0),
      otherwise returns alternative data.
    */
    template <typename A, typename B>
    inline A validate(A data, B alternative);
};

#endif
