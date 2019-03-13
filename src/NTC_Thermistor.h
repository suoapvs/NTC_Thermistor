/**
	NTC_Thermistor.h - The interface describes a set of methods
	for working with a NTC thermistor and reading
	a temperature in Celsius, Fahrenheit and Kelvin.

	Instantiation, for example, to NTC 3950 thermistor:
		NTC_Thermistor thermistor(A1, 8000, 100000, 25, 3950);
		or
		NTC_Thermistor thermistor(
			A1, 8000, 100000, 25, 3950,
			READINGS_NUMBER, DELAY_TIME
		);

		Where,
		READINGS_NUMBER - How many readings are taken
		to determine a mean temperature. The more values,
		the longer a calibration is performed, but the readings
		will be more accurate.

		DELAY_TIME - Delay time between a temperature readings
		from the temperature sensor (ms).

	Read temperature:
		double celsius = thermocouple.readCelsius();
		double kelvin = thermocouple.readKelvin();
		double fahrenheit = thermocouple.readFahrenheit();

	v.1.1.2:
	- updated conversion from celsius to fahrenheit;
	- added conversion from kelvin to fahrenheit;
	- optimized calls of private methods.

	v.1.1.3:
	- Fixed bug in setReadingsNumber() method.

	v.1.1.4:
	- Removed deprecated init() method;
	- Replaced pinMode from INPUT_PULLUP to INPUT.

	https://github.com/YuriiSalimov/NTC_Thermistor

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#if defined(ARDUINO) && (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

/**
	Min value of Arduino ADC.
*/
#define NTC_THERMISTOR_ADC_MIN	0

/**
	Max value of Arduino ADC.
*/
#define NTC_THERMISTOR_ADC_MAX	1023

/**
	Values diapason of Arduino ADC
*/
#define NTC_THERMISTOR_ADC	((NTC_THERMISTOR_ADC_MAX) - (NTC_THERMISTOR_ADC_MIN))

#define NTC_DEFAULT_READINGS_NUMBER	5
#define NTC_DEFAULT_DELAY_TIME	10

class NTC_Thermistor final {

	private:
		int pin; // an analog port.
		double referenceResistance;
		double nominalResistance;
		double nominalTemperature; // in Celsius.
		double bValue;
		int readingsNumber;
		long delayTime;

	public:
		/**
			Constructor.
			@param pin - an analog port number to be attached
				to the thermistor.
			@param referenceResistance - reference resistance.
			@param nominalResistance - nominal resistance.
			@param nominalTemperature - nominal temperature in Celsius.
			@param bValue - b-value of a thermistor.
		*/
		NTC_Thermistor(
			int pin,
			double referenceResistance,
			double nominalResistance,
			double nominalTemperatureCelsius,
			double bValue
		);

		/**
			Constructor.
			@param pin - an analog port number to be attached
				to the thermistor.
			@param referenceResistance - reference resistance.
			@param nominalResistance - nominal resistance.
			@param nominalTemperature - nominal temperature in Celsius.
			@param bValue - b-value of a thermistor.
			@param readingsNumber - how many readings are
				taken to determine a mean temperature.
			@param delayTime - delay time between
				a temperature readings (ms).
		*/
		NTC_Thermistor(
			int pin,
			double referenceResistance,
			double nominalResistance,
			double nominalTemperatureCelsius,
			double bValue,
			int readingsNumber,
			long delayTime
		);

		/**
			Reads and returns a temperature in Celsius
			from the thermocouple.
		*/
		double readCelsius();

		/**
			Returns a temperature in Kelvin.
		*/
		double readKelvin();

		/**
			Returns a temperature in Fahrenheit.
		*/
		double readFahrenheit();

		/**
			Returns a temperature in Fahrenheit
			(For older devices).
		*/
		double readFarenheit();

		/**
			Sets a new readings number.
		*/
		void setReadingsNumber(int newReadingsNumber);

		/**
			Sets a new delay time.
		*/
		void setDelayTime(long newDelayTime);

	private:
		/**
			Calculates a resistance of the thermistor:
		*/
		inline double readResistance();

		/**
			Reads a voltage from the thermistor.
		*/
		inline double readVoltage();

		/**
			Resistance to Kelvin conversion:
			1/K = 1/K0 + 1/B * ln(R/R0)
		*/
		inline double resistanceToKelvins(double resistance);

		/**
			Celsius to Kelvin conversion:
			K = C + 273.15
		*/
		inline double celsiusToKelvins(double celsius);

		/**
			Kelvin to Celsius conversion:
			C = K - 273.15
		*/
		inline double kelvinsToCelsius(double kelvins);

		/**
			Celsius to Fahrenheit conversion:
			F = C * 1.8 + 32
		*/
		inline double celsiusToFahrenheit(double celsius);

		/**
			Kelvin to Fahrenheit conversion:
			F = (K - 273.15) * 1.8 + 32
		*/
		inline double kelvinsToFahrenheit(double kelvins);

		inline void sleep();

		/**
			Returns the data if it is valid,
			otherwise returns alternative data.
		*/
		template <typename A, typename B> A validate(A data, B alternative);
};

#endif
