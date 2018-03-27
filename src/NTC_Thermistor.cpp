/**
	The class implements a set of methods of the NTC_Thermistor.h 
	interface for working with a NTC thermistor and reading 
	a temperature in Celsius, Fahrenheit and Kelvin.

	https://github.com/YuriiSalimov/NTC_Thermistor
	
	Created by Yurii Salimov, February, 2018.
	Released into the public domain.
*/
#include "NTC_Thermistor.h"

NTC_Thermistor::NTC_Thermistor(
	const int pin,
	const double referenceResistance,
	const double nominalResistance,
	const double nominalTemperatureCelsius,
	const double bValue
) {
	this->pin = pin;
	this->referenceResistance = referenceResistance;
	this->nominalResistance = nominalResistance;
	this->nominalTemperature = CELSIUS_TO_KELVINS(nominalTemperatureCelsius);
	this->bValue = bValue;
	pinMode(this->pin, INPUT_PULLUP);
}

/**
	Reads and returns a temperature in Celsius.
	Reads the temperature in Kelvin, 
	converts in Celsius and return it.
	@return temperature in Celsius.
*/
double NTC_Thermistor::readCelsius() {
	const double kelvin = readKelvin();
	return KELVINS_TO_CELSIUS(kelvin);
}

/**
	Returns a temperature in Fahrenheit.
	Reads a temperature in Kelvin, 
	converts in Fahrenheit and return it.
	@return temperature in Fahrenheit.
*/
double NTC_Thermistor::readFahrenheit() {
	const double kelvin = readKelvin();
	return KELVINS_TO_FAHRENHEIT(kelvin);
}

double NTC_Thermistor::readFarenheit() {
	return readFahrenheit();
}

/**
	Returns a temperature in Kelvin.
	Reads the thermistor resistance, 
	converts in Kelvin and return it:
	1/K = 1/K0 + 1/B * ln(R/R0)
	@return temperature in Kelvin.
*/
double NTC_Thermistor::readKelvin() {
	const double resistance = readResistance();
	const double inverseKelvin = 1.0 / this->nominalTemperature +
		1.0 / this->bValue * log(resistance / this->nominalResistance);
	return (1.0 / inverseKelvin);
}

/**
	Calculates a resistance of the thermistor:
	Converts a value of the thermistor sensor into a resistance.
	R = R0 / (ADC / V - 1);
	@return resistance of the thermistor sensor.
*/
double NTC_Thermistor::readResistance() {
	const double voltage = readVoltage();
	return this->referenceResistance / (NTC_THERMISTOR_ADC / voltage - 1);
}

/**
	Reads a voltage from the thermistor analog port.
	Takes READINGS_NUMBER samples in a row, 
	with a slight delay.
	@return average thermistor voltage.
*/
double NTC_Thermistor::readVoltage() {
	double average = 0;
	for (int i = 0; i < NTC_THERMISTOR_READINGS_NUMBER; i++) {
		average += analogRead(this->pin);
		delay(NTC_THERMISTOR_TIME_DELAY);
	}
	return (average / NTC_THERMISTOR_READINGS_NUMBER);
}
