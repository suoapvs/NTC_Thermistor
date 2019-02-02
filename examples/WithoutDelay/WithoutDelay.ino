#include <Arduino.h>

/*
  Thermistor.

  Reads a temperature from the NTC 3950 thermistor and displays
  it in the default Serial.

  https://github.com/YuriiSalimov/NTC_Thermistor

  Created by Oséias Ferreira, January, 2019
  based on code written by Yuri Shalimov, April, 2018.
  Released into the public domain.
*/
#include <NTC_Thermistor.h>

#define SENSOR_PIN             A1
#define REFERENCE_RESISTANCE   8000
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

/**
   How many readings are taken to determine a mean temperature.
   The more values, the longer a calibration is performed,
   but the readings will be more accurate.
*/
#define READINGS_NUMBER 10

/**
   Delay time between a temperature readings
   from the temperature sensor (ms).
*/
#define DELAY_TIME 20

#define DELAY_ENABLE false

const int printInterval = 2000; //sec
long lastPrint = 0;

uint8_t numRead = 10;

NTC_Thermistor* thermistor = NULL;

void setup() {
  Serial.begin(9600);
  Serial.println("NTC_Thermistor Disable Delay example.");
  thermistor = new NTC_Thermistor(
    SENSOR_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
    READINGS_NUMBER,
    DELAY_TIME,
    DELAY_ENABLE
  );
  /* or
    thermistor = new NTC_Thermistor(
      SENSOR_PIN,
      REFERENCE_RESISTANCE,
      NOMINAL_RESISTANCE,
      NOMINAL_TEMPERATURE,
      B_VALUE
    );
    thermistor->setReadingsNumber(READINGS_NUMBER);
    thermistor->setDelayTime(DELAY_TIME);
    thermistor->setUseDelay(DELAY_ENABLE);
  */

  // start first read
  thermistor->startRead();
}

void loop() {
  unsigned long now = millis(); // to control Serial.print
  unsigned long now_us = 0;     // to measure spent time

  if (thermistor->isReading()){
    now_us = micros();
    if (thermistor->Update(now)) {
      unsigned long updateTime = micros() - now_us;
      Serial.print("updateTime: ");
      Serial.println(String(updateTime) + " us");
    }
  }
  else{ //read is finished
    if (now - lastPrint > printInterval){ // print only after wait printInterval

      now_us = micros(); // reset

      double celsius = thermistor->readCelsius();
      double kelvin = thermistor->readKelvin();
      double fahrenheit = thermistor->readFahrenheit();

      unsigned long readTime = micros() - now_us;

      Serial.print("NoDelay\t");
      Serial.print("Temperature: ");
      Serial.print(String(celsius) + " C, ");
      Serial.print(String(kelvin) + " K, ");
      Serial.print(String(fahrenheit) + " F ");
      Serial.print("readTime: ");
      Serial.println(String(readTime) + " us ");

      //enable delay
      thermistor->setUseDelay(true);

      now_us = micros(); // reset

      celsius = thermistor->readCelsius();
      kelvin = thermistor->readKelvin();
      fahrenheit = thermistor->readFahrenheit();

      readTime = micros() - now_us;

      Serial.print("Delay\t");
      Serial.print("Temperature: ");
      Serial.print(String(celsius) + " C, ");
      Serial.print(String(kelvin) + " K, ");
      Serial.print(String(fahrenheit) + " F ");
      Serial.print("ReadTime: ");
      Serial.println(String(readTime) + " us ");

      //disable delay
      thermistor->setUseDelay(false);
      numRead++;
      thermistor->setReadingsNumber(numRead);
      if (numRead == 20) numRead=5;


      lastPrint = now;

      // read again
      thermistor->startRead();
    }
  }
}
