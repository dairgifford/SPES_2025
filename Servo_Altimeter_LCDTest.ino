/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

// portable display code
#include <LiquidCrystal.h>

        //          BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/* servo stuff
#include <Servo.h> 
 
Servo myservo; 

int closed = 0;
int open = 180;
int servopin = 5 */


Adafruit_BMP280 bmp; // I2C

double pressure_abs, pressure_baseline;

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  //status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //pressure_baseline = bmp.readpressure(); 

  lcd.begin(16, 2);
  
  //myservo.attach(servopin);
  //myservo.write(closed)
}

void loop() {

  pressure_abs = bmp.readPressure();
  //altitude_delta = altitude(paToMbar(pressure_abs), paToMbar(pressure_baseline));

    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.print("Altitude change (m) = ");
    //Serial.println(altitude_delta);

    Serial.println();

    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(bmp.readTemperature());
    lcd.setCursor(0,1);
    lcd.print("Altitude = ");
    lcd.print(bmp.readAltitude(1013.25));

    delay(2000);

    /*
    if (altitude_delta > 10){
      myservo.write(open);
    }
    else if(altitude_delta < 10){
      myservo.write(cllosed);
    }
    */
}

double altitude(double P, double P0)
// Given a pressure measurement P (mbar) and the pressure at a baseline P0 (mbar),
// return altitude (meters) above baseline.
{
  return (44330.0 * (1 - pow(P / P0, 1 / 5.255)));
}

double paToMbar(double pressurePa) {
  return(pressurePa/100);
}
