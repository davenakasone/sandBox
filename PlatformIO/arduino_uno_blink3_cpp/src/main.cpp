/*
    C++ blink using other function calls
*/

#include <Arduino.h>

#define DELAY_MS 300
#define DELAY_MULT 10
#define SUB_REPS 5

void blink_LED(int LED, int delay_ms);    // must define before using ... like real life

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);  // LED_BUILTIN expands to 13 ...
}


void loop() 
{
    for (int i = 0; i < SUB_REPS; i++)
    {
        blink_LED(LED_BUILTIN, DELAY_MS);    // short blinks
    }

    for (int i = 0; i < SUB_REPS; i++)
    {
        blink_LED(LED_BUILTIN, DELAY_MULT * DELAY_MS);    // long blinks
    }
}


////~~~~


void blink_LED(int LED, int delay_ms)
{
    digitalWrite(LED, HIGH);    // turn LED on
    delay(delay_ms);            // wait
    digitalWrite(LED, LOW);     // turn LED off
    delay(delay_ms);            // wait
}

////////~~~~~~~~END>  main.cpp
