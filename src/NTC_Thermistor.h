/**
	NTC_Thermistor.h - The interface describes a set of methods
	for working with a NTC thermistor and reading
	a temperature in Celsius, Fahrenheit and Kelvin.

	Instantiation, for example, to NTC 3950 thermistor:
	Thermistor* thermistor = new NTC_Thermistor(A1, 8000, 100000, 25, 3950);

	Where,
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

	v.1.1.2:
	- updated conversion from celsius to fahrenheit;
	- added conversion from kelvin to fahrenheit;
	- optimized calls of private methods.

	v.1.1.3:
	- fixed bug in setReadingsNumber() method.

	v.1.1.4:
	- removed deprecated init() method;
	- replaced pinMode from INPUT_PULLUP to INPUT.

	v.2.0.0
	- implemented Thermistor interface;
	- removed methods for averaging result.

	https://github.com/YuriiSalimov/NTC_Thermistor

	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#ifndef NTC_THERMISTOR_H
#define NTC_THERMISTOR_H

#include "Thermistor.h"

// Analog resolution for Arduino board
#define ARDUINO_ADC_RESOLUTION 1023

class NTC_Thermistor : public Thermistor {

	private:
		int pin; // an analog port.
		double referenceResistance;
		double nominalResistance;
		double nominalTemperature; // in Celsius.
		double bValue;
		int adcResolution;

	public:
		/**
			Constructor

			@param pin - an analog port number to be attached to the thermistor
			@param referenceResistance - reference resistance
			@param nominalResistance - nominal resistance
			@param nominalTemperature - nominal temperature in Celsius
			@param bValue - b-value of a thermistor
		*/
		NTC_Thermistor(
			int pin,
			double referenceResistance,
			double nominalResistance,
			double nominalTemperatureCelsius,
			double bValue
		);

		/**
			Constructor

			@param pin - an analog port number to be attached to the thermistor
			@param referenceResistance - reference resistance
			@param nominalResistance - nominal resistance
			@param nominalTemperature - nominal temperature in Celsius
			@param bValue - b-value of a thermistor
			@param adcResolution - ADC resolution (1023, for Arduion)
		*/
		NTC_Thermistor(
			int pin,
			double referenceResistance,
			double nominalResistance,
			double nominalTemperatureCelsius,
			double bValue,
			int adcResolution
		);

		/**
			Reads a temperature in Celsius from the thermistor.

			@return temperature in degree Celsius
		*/
		double readCelsius() override;

		/**
			Reads a temperature in Kelvin from the thermistor.

			@return temperature in degree Kelvin
		*/
		double readKelvin() override;

		/**
			Reads a temperature in Fahrenheit from the thermistor.

			@return temperature in degree Fahrenheit
		*/
		double readFahrenheit() override;

	private:
		/**
			Reads a voltage from the thermistor analog port.

			@return thermistor voltage in analog range (0...1023, for Arduino).
		*/
		inline double readVoltage();

		/**
			Calculates a resistance of the thermistor:
			Converts a value of the thermistor sensor into a resistance.
			R = R0 / (ADC / V - 1);

			@return resistance of the thermistor sensor.
		*/
		inline double readResistance();

		/**
			Resistance to Kelvin conversion:
			1/K = 1/K0 + 1/B * ln(R/R0)

			@param resistance - resistance value to convert
			@return temperature in degree Kelvin
		*/
		inline double resistanceToKelvins(double resistance);

		/**
			Celsius to Kelvin conversion:
			K = C + 273.15

			@param celsius - temperature in degree Celsius to convert
			@return temperature in degree Kelvin
		*/
		inline double celsiusToKelvins(double celsius);

		/**
			Kelvin to Celsius conversion:
			C = K - 273.15

			@param kelvins - temperature in degree Kelvin to convert
			@return temperature in degree Celsius
		*/
		inline double kelvinsToCelsius(double kelvins);

		/**
			Celsius to Fahrenheit conversion:
			F = C * 1.8 + 32

			@param celsius - temperature in degree Celsius to convert
			@return temperature in degree Fahrenheit
		*/
		inline double celsiusToFahrenheit(double celsius);

		/**
			Kelvin to Fahrenheit conversion:
			F = (K - 273.15) * 1.8 + 32

			@param kelvins - temperature in degree Kelvin to convert
			@return temperature in degree Fahrenheit
		*/
		inline double kelvinsToFahrenheit(double kelvins);
};

#endif
