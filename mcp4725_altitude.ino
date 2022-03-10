/*  Altimeter with DC output
    William E Webb 03-10-2022
    based on the work of:

      AUTHOR: Rob Tillaart
      URL: https://github.com/RobTillaart/MCP4725

      http://www.adafruit.com/products/2650
*/

#include "Wire.h"
#include "MCP4725.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

MCP4725 MCP(0x62);  // 0x62 or 0x63

#define DATE "03/10/2022"
#define SEALEVELPRESSURE_HPA (1013.25)

float altitude_f;

Adafruit_BME280 bme; // I2C

void setup()
{
  Serial.begin(115200);

  Serial.print("MCP4725 Altitude output program: ");
  Serial.print(" MCP_BMP.ino dated: "); Serial.print(DATE);
  Serial.println(MCP4725_VERSION);

  MCP.begin();
  unsigned status;

  // default settings
  status = bme.begin();
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
}

void loop()
{
  altitude_f = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print("Approx. Altitude = "); Serial.print(altitude_f); Serial.println(" m");
  MCP.setValue(int(altitude_f));
  delay (100);
}
