

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
AdafruitIO_Feed *rojo = io.feed("rojo");
AdafruitIO_Feed *verde = io.feed("verde");


void handleMessage(AdafruitIO_Data *data){
  leds = data ->value();
}

void setup() {
  
  // start the serial connection
  Serial.begin(9600);
  pinMode(2, OUTPUT);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();
  rojo -> onMessage(handleMessage);
  verde -> onMessage(handleMessage);
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print("Esperando");
    digitalWrite(2, HIGH);
    delay(500);
  }
  digitalWrite(2, LOW);

  rojo -> get();
  verde -> get();

  
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
    case 1:
    Serial.write (1);
    Serial.print(1);
    break;

    case 2:
    Serial.write (2);
    Serial.print(2);
    break;

    case 3:
    Serial.write (3);
    Serial.print(3);
    break;

    case 4:
    Serial.write (4);
    Serial.print(4);
    break;

    default:
      break;
  }


  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(1000);

}
