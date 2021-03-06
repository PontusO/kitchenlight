/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * The LED driver we use in this example is connected to pin 6
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */
#include <TimerOne.h>
 
#include "pt.h"
#include "ptfactory.h"
#include "types.h"
#include "swtimers.h"
#include "pir.h"
#include "ramp.h"

int ledPin = 6;    // LED light connected to digital pin 6
int ledPin1 = 5;    // LED light connected to digital pin 6
int ledPin2 = 6;    // LED light connected to digital pin 6

/*
 * Pins that are connected to the PIR sensors.
 *
 * Pir 1 is considered the room sensor. It will detect if a person
 * has entered the room and gently light the light.
 *
 * Pir 2 is the close proximity sensor, it shall be set to the minimum
 * sensitivity and placed downwards where you want to have the activation
 * area.
 */
int pin_pir1 = 8;
int pin_pir2 = 7;

/* Protothread instances */
pt_pir_t pir_1;
pt_pir_t pir_2;
pt_ramp ramp;

void setup()  {
  Serial.begin(9600);
  pinMode (ledPin, OUTPUT);
  analogWrite (ledPin, 100);
  // Framework initialization
  init_swtimers();
  // Initilize protothreads
  pir_init(&pir_1, 0, pin_pir1);
  pir_init(&pir_2, 1, pin_pir2);
  init_ramp(&ramp);
  Serial.println ("Initialization done !");
}

void loop()  {
  handle_pir (&pir_1);
  handle_pir (&pir_2);
  thread_ramp (&ramp);
}
