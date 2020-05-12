#include <Adafruit_Sensor.h>

#include <bmp3.h>
#include <Adafruit_BMP3XX.h>
#include <bmp3_defs.h>

#include <SPI.h>

#include <SD.h>

#include <EepromAT24C32.h>
#include <ThreeWire.h>
#include <RtcUtility.h>
#include <RtcTemperature.h>
#include <RtcDS3231.h>
#include <RtcDS1307.h>
#include <RtcDS1302.h>
#include <RtcDateTime.h>
#include <RtcDS3234.h>

#include <Wire.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP3XX bmp; // I2C
//Adafruit_BMP3XX bmp(BMP_CS); // hardware SPI
//Adafruit_BMP3XX bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
 
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("BMP388 test");
 
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
 
  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  //bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}
 
void loop() {
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");
 
  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");
 
  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
 
  Serial.println();
  delay(2000);
}
