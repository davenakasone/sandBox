/*
    C code to blink LED
    just for familiarizaiton
        looks good...
*/

#include <Arduino.h>

#define DELAY_MS 4000

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);    // initialize LED as output
}

void loop() 
{
    digitalWrite(LED_BUILTIN, HIGH);    // turn LED on
    delay(DELAY_MS);                    // wait
    digitalWrite(LED_BUILTIN, LOW);     // turn LED off
    delay(DELAY_MS);                    // wait ...repeats
}

////////~~~~~~~~END>  main.c
