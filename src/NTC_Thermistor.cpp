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
) : NTC_Thermistor(
		pin, referenceResistance,
		nominalResistance,
		nominalTemperatureCelsius,
		bValue,
		readingsNumber,
		delayTime,
		NTC_DEFAULT_ENABLE_DELAY
) {
}

NTC_Thermistor::NTC_Thermistor(
	const int pin,
	const double referenceResistance,
	const double nominalResistance,
	const double nominalTemperatureCelsius,
	const double bValue,
	const int readingsNumber,
	const long delayTime,
	const bool useDelay
) {
	this->pin = pin;
	pinMode(this->pin, INPUT_PULLUP);
	this->referenceResistance = referenceResistance;
	this->nominalResistance = nominalResistance;
	this->nominalTemperature = celsiusToKelvins(nominalTemperatureCelsius);
	this->bValue = bValue;
	this->enableRead = false;
	this->analogBuffer = NULL;
	setUseDelay(useDelay);
	setDelayTime(delayTime);
	setReadingsNumber(readingsNumber);
}

/**
	Allocate or reallocate buffer memory
	when delay is disabled.
*/
inline void NTC_Thermistor::initBuffer(){
	if (this->analogBuffer == NULL){
		this->analogBuffer = (double*)malloc(sizeof(double) * this->readingsNumber);
	}else {
		this->analogBuffer = (double*)realloc(this->analogBuffer, sizeof(double) * this->readingsNumber);
	}
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
	return kelvinsToFahrenheit(readKelvin());
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

inline double NTC_Thermistor::resistanceToKelvins(const double resistance) {
	const double inverseKelvin = 1.0 / this->nominalTemperature +
		1.0 / this->bValue * log(resistance / this->nominalResistance);
	return (1.0 / (inverseKelvin));
}

/**
	Calculates a resistance of the thermistor:
	Converts a value of the thermistor sensor into a resistance.
	R = R0 / (ADC / V - 1);
	@return resistance of the thermistor sensor.
*/
inline double NTC_Thermistor::readResistance() {
	return this->referenceResistance / (NTC_THERMISTOR_ADC / readVoltage() - 1);
}

/**
	Reads a voltage from the thermistor analog port.
	Takes READINGS_NUMBER samples in a row,
	with a slight delay.
	@return average thermistor voltage.
*/


inline double NTC_Thermistor::readVoltage() {
	double analogSum = 0;

	//delay enabled
	if (this->useDelay){
		for (unsigned int i = 0; i < this->readingsNumber; i++){
			analogSum += analogRead(this->pin);
			sleep();
		}
		return (analogSum / this->readingsNumber);
	}
	// buffer enabled
	else return this->readBuffer();
}

/**
	Reads voltage readings stored in the buffer.
	@return average thermistor voltage.
*/

inline double NTC_Thermistor::readBuffer() {
	double analogSum = 0;
	for (unsigned int i = 0; i < this->readingsNumber; i++){
		analogSum += this->analogBuffer[i];

		// abort loop if buffer is incomplete
		if (this->isReading() && i == this->bufferId)
			break;
	}

	if (this->isReading()) // return only buffered
		return analogSum / this->bufferId + 1;
	else
		return analogSum / this->readingsNumber;
}

inline void NTC_Thermistor::sleep() {
	delay(this->delayTime);
}

void NTC_Thermistor::setReadingsNumber(const int newReadingsNumber) {
	this->readingsNumber = validate(newReadingsNumber, NTC_DEFAULT_READINGS_NUMBER);

	// delay disabled - set buffer
	if (!this->useDelay){
		initBuffer();
	}
}

void NTC_Thermistor::setDelayTime(const long newDelayTime) {
	this->delayTime = validate(newDelayTime, NTC_DEFAULT_DELAY_TIME);
}


/**
	Enabled/Disable delay interrupts.
	true: enable delay interrupts to readings.
	false: disable delay and enable time based buffer to readings.
*/
void NTC_Thermistor::setUseDelay(bool delayEnable){
	this->useDelay = delayEnable;

	// delay disabled - set buffer
	if (!this->useDelay){
		initBuffer();
	}
}


/**
	Alias to Update(long now)
*/
bool NTC_Thermistor::Update(){
	return Update(millis());
}

/**
	Populate buffer with timed voltage read from the thermistor analog port.
	this->delayTime value is used as interval to read analog port.
	@return
		true: if analog ports is read:
			(enableRead=true and useDelay=false and (now - lastRead) > this->delayTime)
		false: if nothing is executed
			(enableRead=false or useDelay=true or (now - lastRead) < this->delayTime)
*/
bool NTC_Thermistor::Update(long now){
	bool result = false; //default return false

	if (isReading() && !this->useDelay && now - this->lastRead > this->delayTime){

		this->analogBuffer[this->bufferId] = analogRead(this->pin);
		this->lastRead = now;
		this->bufferId++;

		if (this->bufferId >= this->readingsNumber){ //finish read
			this->bufferId = 0; //reset buffer index
			this->enableRead = false; //stop read
		}
		result = true;
	}
	return result;
}

/**
	Start timed based readings when delay is disabled.
	must needs call it before
*/
void NTC_Thermistor::startRead(){
	this->bufferId = 0;
	this->enableRead = true;
	this->lastRead = millis();
}

/**{}
	Returns the data if it is positive,
	otherwise returns alternative data.
*/
template <typename A, typename B>
A NTC_Thermistor::validate(const A data, const B alternative) {
	return (data > 0) ? data : alternative;
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
	C = (K - 273.15) - celsius.
	F = C * 1.8 + 32 - Celsius to Fahrenheit conversion.
	=> Kelvin convert to Celsius, then Celsius to Fahrenheit.
*/
inline double NTC_Thermistor::kelvinsToFahrenheit(const double kelvins) {
	return celsiusToFahrenheit(kelvinsToCelsius(kelvins));
}
