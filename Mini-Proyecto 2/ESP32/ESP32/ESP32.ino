
// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int temp = 0;
String leds;
int entrada = 0;

// set up the 'counter' feed
AdafruitIO_Feed *mini2 = io.feed("mini2");
AdafruitIO_Feed *Rojo = io.feed("Rojo");
AdafruitIO_Feed *Verde = io.feed("Verde");

void handleMessage(AdafruitIO_Data *data){
  leds = data ->value();
}

void setup() {
  
  // start the serial connection
  Serial.begin(9600);
  pinMode(3, OUTPUT);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();
  Rojo -> onMessage(handleMessage);
  Verde -> onMessage(handleMessage);
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    digitalWrite(3, HIGH);
    delay(500);
  }
  digitalWrite(3, LOW);

  Rojo -> get();
  Verde -> get();

  
  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();


  if (Serial.available() > 0) {
    entrada = Serial.read();
    mini2->save ((entrada,DEC));
  }

  switch (leds.toInt()){
    case 00:
    Serial.write (0x10);
    break;

    case 01:
    Serial.write (0x20);
    break;

    case 10:
    Serial.write (0x30);
    break;

    case 11:
    Serial.write (0x40);
    break;

    default:
      break;
  }


  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}
