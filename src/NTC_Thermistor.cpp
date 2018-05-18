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
) : NTC_Thermistor(
		pin, referenceResistance,
		nominalResistance,
		nominalTemperatureCelsius,
		bValue,
		NTC_DEFAULT_READINGS_NUMBER,
		NTC_DEFAULT_DELAY_TIME
) {
}

NTC_Thermistor::NTC_Thermistor(
	const int pin,
	const double referenceResistance,
	const double nominalResistance,
	const double nominalTemperatureCelsius,
	const double bValue,
	const int readingsNumber,
	const long delayTime
) {
	this->pin = pin;
	this->referenceResistance = referenceResistance;
	this->nominalResistance = nominalResistance;
	this->nominalTemperature = celsiusToKelvins(nominalTemperatureCelsius);
	this->bValue = bValue;
	setReadingsNumber(readingsNumber);
	setDelayTime(delayTime);
	init();
}

void NTC_Thermistor::init() {
	pinMode(this->pin, INPUT_PULLUP);
}

/**
	Reads and returns a temperature in Celsius.
	Reads the temperature in Kelvin,
	converts in Celsius and return it.
	@return temperature in Celsius.
*/
double NTC_Thermistor::readCelsius() {
	return kelvinsToCelsius(readKelvin());
}

/**
	Returns a temperature in Fahrenheit.
	Reads a temperature in Celsius,
	converts in Fahrenheit and return it.
	@return temperature in Fahrenheit.
*/
double NTC_Thermistor::readFahrenheit() {
	return celsiusToFahrenheit(readCelsius());
}

double NTC_Thermistor::readFarenheit() {
	return readFahrenheit();
}

/**
	Returns a temperature in Kelvin.
	Reads the thermistor resistance,
	converts in Kelvin and return it.
	@return temperature in Kelvin.
*/
double NTC_Thermistor::readKelvin() {
	return resistanceToKelvins(readResistance());
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
	double analogSum = 0;
	for (int i = 0; i < this->readingsNumber; i++) {
		analogSum += analogRead(this->pin);
		sleep();
	}
	return (analogSum / this->readingsNumber);
}

void NTC_Thermistor::sleep() {
	delay(this->delayTime);
}

void NTC_Thermistor::setReadingsNumber(const int newReadingsNumber) {
	this->readingsNumber = validate(readingsNumber, NTC_DEFAULT_READINGS_NUMBER);
}

void NTC_Thermistor::setDelayTime(const long newDelayTime) {
	this->delayTime = validate(newDelayTime, NTC_DEFAULT_DELAY_TIME);
}

template <typename A, typename B>
A NTC_Thermistor::validate(const A data, const B min) {
	return (data > 0) ? data : min;
}

double NTC_Thermistor::resistanceToKelvins(const double resistance) {
	const double inverseKelvin = 1.0 / this->nominalTemperature +
		1.0 / this->bValue * log(resistance / this->nominalResistance);
	return (1.0 / inverseKelvin);
}

double NTC_Thermistor::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

double NTC_Thermistor::kelvinsToCelsius(const double kelvins) {
	return (kelvins - 273.15);
}

double NTC_Thermistor::celsiusToFahrenheit(const double celsius) {
	return (celsius * 9.0 / 5.0 + 32);
}
