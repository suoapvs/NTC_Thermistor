/**
	NTCThermoSensor.h - The interface describes a set of methods 
	for working with a NTC thermistor and reading 
	a temperature in Celsius, Fahrenheit and Kelvin.
	
	Instantiation, for example, to NTC 3950 thermistor:
		NTC_Thermistor thermistor(A1, 8000, 100000, 25, 3950);

	Read temperature:
		thermistor.readCelsius();
		thermistor.readKelvin();
		thermistor.readFahrenheit();

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

/**
	How many readings are taken to determine a mean voltage. 
	The more values, the longer a calibration is performed, 
	but the readings will be more accurate.
*/
#define NTC_THERMISTOR_READINGS_NUMBER	5

/**
	Delay time between a temperature readings 
	from the temperature sensor (ms).
*/
#define NTC_THERMISTOR_TIME_DELAY	10

/**
	Kelvin to Celsius conversion:
		C = K - 273.15
*/
#define KELVINS_TO_CELSIUS(K) (((K) - 273.15))

/**
	Celsius to Kelvin conversion:
		K = C + 273.15
*/
#define CELSIUS_TO_KELVINS(C) (((C) + 273.15))

/**
	Celsius to Fahrenheit conversion:
		F = C * 9 / 5 + 32
*/
#define CELSIUS_TO_FAHRENHEIT(C) (((C) * 9.0 / 5.0 + 32))

/**
	Kelvin to Fahrenheit conversion:
	F = C * 9 / 5 + 32 = (K - 273.15) * 9 / 5 + 32
*/
#define KELVINS_TO_FAHRENHEIT(K) (CELSIUS_TO_FAHRENHEIT(KELVINS_TO_CELSIUS(K)))

class NTC_Thermistor final {

	private:
		/**
			Port number to be attached to the sensor.
		*/
		int pin = 0;

		/**
			Reference resistance of the thermistor.
		*/
		double referenceResistance = 0;

		/**
			Nominal resistance of the thermistor.
		*/
		double nominalResistance = 0;

		/**
			Nominal temperature of the thermistor.
		*/
		double nominalTemperature = 0;

		/**
			B-value of a thermistor.
		*/
		double bValue = 0;

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
			const int pin,
			const double referenceResistance,
			const double nominalResistance,
			const double nominalTemperatureCelsius,
			const double bValue
		);

		/**
			Reads a temperature in Celsius.
			@return temperature in Celsius.
		*/
		double readCelsius();

		/**
			Reads a temperature in Kelvin.
			@return temperature in Kelvin.
		*/
		double readKelvin();
		
		/**
			Reads a temperature in Fahrenheit.
			@return temperature in Fahrenheit.
		*/
		double readFahrenheit();

		/**
			Returns a temperature in Fahrenheit.
			(For older devices.)
			@return temperature in Fahrenheit.
		*/
		 double readFarenheit();

	private:
		/**
			Calculates a resistance of the thermistor:
			@return resistance of the thermistor sensor.
		*/
		double readResistance();

		/**
			Reads a voltage from the thermistor.
			@return thermistor voltage.
		*/
		double readVoltage();
};

#endif
