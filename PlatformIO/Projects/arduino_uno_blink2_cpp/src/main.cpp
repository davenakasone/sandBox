/*
    C++ blink with some enhancements
    some LEDs on different boards are oppisite... HIGH = off
*/

#include <Arduino.h>

#define DELAY_MS 4000

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}


void loop() 
{
    digitalWrite(LED_BUILTIN, HIGH);    // turn LED on
    Serial.println("HIGH");             // display "HIGH"
    delay(DELAY_MS);                    // wait

    digitalWrite(LED_BUILTIN, LOW);     // turn LED off
    Serial.println("LOW");              // display "LOW"
    delay(DELAY_MS);                    // wait 
}

////////~~~~~~~~END>  main.cpp
