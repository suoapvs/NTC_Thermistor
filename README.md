# NTC Thermistor Library

For Arduino boards.
The Library implements a set of methods for working with a NTC thermistor.
Provides a temperature reading in Celsius, Fahrenheit and Kelvin.

## Installation

1. [Download](https://github.com/YuriiSalimov/NTC_Thermistor/releases) the Latest release from gitHub.
2. Unzip and modify the Folder name to "NTC_Thermistor" (Remove the '-version')
3. Paste the modified folder on your Library folder (On your `libraries` folder inside Sketchbooks or Arduino software).
4. Restart the Arduino IDE.

## Circuit Diagram

Connect to the analog side of an Arduino Uno. Run 5V through the thermistor, then a pull-down resistor (R0), and into ground. To measure the temperature pull a line off the junction of the thermistor and the resistor, and into an analog pin (A1 here).

![Diagram](Diagram.png)

## Methods

```cpp
    // Instantiation:
    /**
        pin - an analog port number to be attached to the thermistor.
        R0 - reference resistance.
        Rn - nominal resistance.
        Tn - nominal temperature in Celsius.
        B - b-value of a thermistor.
    */
    NTC_Thermistor thermistor(pin, R0, Rn, Tn, B);

    // or
    /**
    	READINGS_NUMBER - How many readings are taken to determine
        a mean temperature. The more values, the longer a calibration
        is performed, but the readings will be more accurate.
    	DELAY_TIME - Delay time between a temperature readings (ms).
    */
    NTC_Thermistor thermistor(
		pin, R0, Rn, Tn, B,
		READINGS_NUMBER, DELAY_TIME
	);

    // Read a temperature in Celsius.
    double celsius = thermistor.readCelsius();
    // Read a temperature in Kelvin.
    double Kelvin = thermistor.readKelvin();
    // Read a temperature in Fahrenheit.
    double fahrenheit = thermistor.readFahrenheit();
    // For older devices.
    double farenheit = thermistor.readFarenheit();

    // Sets a new readings number.
    thermistor.setReadingsNumber(READINGS_NUMBER);
    // Sets a new delay time.
    thermistor.setDelayTime(DELAY_TIME);

```

Created by [Yurii Salimov](mailto:yuriy.alex.salimov@gmail.com).

