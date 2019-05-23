/**
	Thermistor.h - interface describes a set of methods
	for working with a thermistor sensor and reading
	a temperature in Celsius, Fahrenheit and Kelvin.

	v.2.0.0
	- created

	https://github.com/YuriiSalimov/NTC_Thermistor

	Created by Yurii Salimov, May, 2019.
	Released into the public domain.
*/
#ifndef THERMISTOR_H
#define THERMISTOR_H

#if defined(ARDUINO) && (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

class Thermistor {

	public:
		/**
			Reads and returns a temperature in Celsius
			from the thermocouple.
		*/
		virtual double readCelsius() = 0;

		/**
			Returns a temperature in Kelvin.
		*/
		virtual double readKelvin() = 0;

		/**
			Returns a temperature in Fahrenheit.
		*/
		virtual double readFahrenheit() = 0;
};

#endif
