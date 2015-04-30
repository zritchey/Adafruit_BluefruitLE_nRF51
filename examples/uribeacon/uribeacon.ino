/**************************************************************************/
/*!
    @file     uribeacon.ino
    @author   hathach, ktown (Adafruit Industries)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2015, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include <string.h>
#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BLE_HWSPI.h"
#include "Adafruit_BLE_SWUART.h"

//=======================================================================
// HARDWARE SETTING
//=======================================================================

//------------- Hardware SPI Module -------------//
#define BLUEFRUIT_SPI_RST_PIN       (9)

#define BLUEFRUIT_SPI_IRQ_PIN       (3)  // MUST be an interrupt pin (pin 2 or 3 on an Uno)!
#define BLUEFRUIT_SPI_CS_PIN        (10)

// Use hardware SPI for the remaining pins:
// On an UNO: SCK = 13, MISO = 12, and MOSI = 11

//------------- Software UART Module -------------//
#define BLUEFRUIT_UART_MODE_PIN      (12)

#define BLUEFRUIT_UART_RXD_PIN       (8)
#define BLUEFRUIT_UART_TXD_PIN       (9)
#define BLUEFRUIT_UART_CTS_PIN       (10)
#define BLUEFRUIT_UART_RTS_PIN       (11)

//Adafruit_BLE_HWSPI ble(BLUEFRUIT_SPI_CS_PIN, BLUEFRUIT_SPI_IRQ_PIN /*, BLUEFRUIT_SPI_RST_PIN */);
Adafruit_BLE_SWUART ble(BLUEFRUIT_UART_RXD_PIN, BLUEFRUIT_UART_TXD_PIN,
                        BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN, BLUEFRUIT_UART_MODE_PIN);

//=======================================================================
// APPLICATION SETTING
//=======================================================================
#define BUFSIZE                    128

// URL that is advertised, it must not longer than 17 (omitted http:// and www.)
#define URL                 "http://www.adafruit.com"


/**************************************************************************/
/*!
    @brief  Helper MACROS to check command execution. Print 'FAILED!' or 'OK!',
            loop forever if failed
*/
/**************************************************************************/
#define EXECUTE(command)\
  do{\
    if ( !(command) ) { Serial.println( F("FAILED!") ); while(1){} }\
    Serial.println( F("OK!") );\
  }while(0)

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("BLE URI BEACON EXAMPLE"));
  Serial.println(F("----------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin() )
  {
    Serial.println( F("FAILED! (Check your wiring?)") );
    while(1){}
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.print(F("Performing a factory reset: "));
  EXECUTE( ble.factoryReset() );

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  /* Set ble command verbose */
  ble.verbose(false);

  /* Print Bluefruit information */
  ble.info();

  /* Set URI beacon data */
  Serial.print(F("Setting uri beacon to Adafruit website: "));
  ble.println("AT+BLEURIBEACON=" URL);
  EXECUTE( ble.waitForOK() );

  Serial.println();
  Serial.println(F("Please use Google Physical Web application to test"));
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
}
