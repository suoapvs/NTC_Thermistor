/**
	Created by Yurii Salimov, February, 2018.
	Released into the public domain.

	Modified by Bob Wolff - 2024 - adding in a derived class for
	ESP32 which utilizes the ADC reading of millivolts instead of
	raw ADC count values. This is because in some of the ESP32
	chips, only the millivolt reading is a calibrated result.
	To do this, the user's Vref much be input in the constructor.
*/
#include "NTC_Thermistor.h"

NTC_Thermistor::NTC_Thermistor(
	const int pin,
	const double referenceResistance,
	const double nominalResistance,
	const double nominalTemperatureCelsius,
	const double bValue,
	const int adcResolution
) {
	pinMode(this->pin = pin, INPUT);
	this->referenceResistance = referenceResistance;
	this->nominalResistance = nominalResistance;
	this->nominalTemperature = celsiusToKelvins(nominalTemperatureCelsius);
	this->bValue = bValue;
	this->adcResolution = max(adcResolution, 0);
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
	Reads a temperature in Kelvin,
	converts in Fahrenheit and return it.

	@return temperature in Fahrenheit.
*/
double NTC_Thermistor::readFahrenheit() {
	return kelvinsToFahrenheit(readKelvin());
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

inline double NTC_Thermistor::resistanceToKelvins(const double resistance) {
	const double inverseKelvin = 1.0 / this->nominalTemperature +
		log(resistance / this->nominalResistance) / this->bValue;
	return (1.0 / inverseKelvin);
}

inline double NTC_Thermistor::readResistance() {
	return this->referenceResistance / (this->adcResolution / readVoltage() - 1);
}

inline double NTC_Thermistor::readVoltage() {
	return analogRead(this->pin);
}

inline double NTC_Thermistor::celsiusToKelvins(const double celsius) {
	return (celsius + 273.15);
}

inline double NTC_Thermistor::kelvinsToCelsius(const double kelvins) {
	return (kelvins - 273.15);
}

inline double NTC_Thermistor::celsiusToFahrenheit(const double celsius) {
	return (celsius * 1.8 + 32);
}

/**
	Kelvin to Fahrenheit conversion:
	F = (K - 273.15) * 1.8 + 32
	Where C = (K - 273.15) is Kelvins To Celsius conversion.
	Then F = C * 1.8 + 32 is Celsius to Fahrenheit conversion.
	=> Kelvin convert to Celsius, then Celsius to Fahrenheit.
*/
inline double NTC_Thermistor::kelvinsToFahrenheit(const double kelvins) {
	return celsiusToFahrenheit(kelvinsToCelsius(kelvins));
}

/***
 * @brief Slight derivation which reads the 'voltage' (which is
 * really in raw ADC count values) indirectly through reading
 * the ADC's millivolt reading. This is due to a calibration
 * which happens for the millivolt reading that gives a much
 * more accurate reading than raw 'analogRead()'
 */
NTC_Thermistor_ESP32::NTC_Thermistor_ESP32(
	const int pin,
	const double referenceResistance,
	const double nominalResistance,
	const double nominalTemperatureCelsius,
	const double bValue,
	const uint16_t adcVref,
	const int adcResolution
) : NTC_Thermistor(pin, referenceResistance, nominalResistance, nominalTemperatureCelsius, bValue, adcResolution)
{
	this->vref_mv = adcVref;
}

/***
 * @brief read the calibrated version of the ADC count value indirectly
 * by reading the millivolts value (which is calibrated by Espressif)
 * and back-calculating the raw ADC count value.
 */
double NTC_Thermistor_ESP32::readVoltage() {
	return (double)analogReadMilliVolts(this->pin) / (double)this->vref_mv * this->adcResolution;
}
