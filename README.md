# NTC Thermistor Library

For Arduino, ESP32 and STM32 boards.

Enhanced in 2024 by Bob Wolff to support more accurate NTC results
on ESP32 devices. Some of the ESP32 devices like the ESP32-C3 have
the ADC raw count values as "uncalibrated" results while the
millivolt reading from analogReadMillivolts() are calibrated and
are quite a bit more accurate. Instantiating NTC_Thermistor_ESP32
and passing in the voltage reference in millivoltes (likely 3300),
this derived class will give more accurate results for temperatures.

The Library implements a set of methods for working with a NTC thermistor.
Provides a temperature reading in Celsius, Fahrenheit and Kelvin.

## Installation

1. [Download](https://github.com/bobwolff68/NTC_Thermistor/releases) the Latest release from gitHub.
2. Unzip and modify the Folder name to "NTC_Thermistor" (Remove the '-version')
3. Paste the modified folder on your Library folder (On your `libraries` folder inside Sketchbooks or Arduino software).
4. Restart the Arduino IDE.

## Circuit Diagram

Connect to the analog side of an Arduino Uno. Run GND through the thermistor, then a pull-down resistor (R0), and into reference voltage. To measure the temperature pull a line off the junction of the thermistor and the resistor, and into an analog pin (A1 here).

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

    // Read a temperature in Celsius.
    double celsius = thermistor.readCelsius();
    // Read a temperature in Kelvin.
    double Kelvin = thermistor.readKelvin();
    // Read a temperature in Fahrenheit.
    double fahrenheit = thermistor.readFahrenheit();
    // For older devices.
    double farenheit = thermistor.readFarenheit();
```

### Examples

[Serial Reading](/examples/SerialReading/SerialReading.ino)

[Average Measurement](/examples/AverageMeasurement/AverageMeasurement.ino)

[Smooth Measurement](/examples/SmoothMeasurement/SmoothMeasurement.ino)

[STM32...](/examples/STM32/STM32.ino)

[All examples...](/examples)

Created by Yurii Salimov.
