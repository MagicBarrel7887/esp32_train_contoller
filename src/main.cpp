#include "Arduino.h"
#include "SPI.h"
#include <Wire.h>
#include "Adafruit_Keypad.h"

#include <TTP229.h>

#include "RF24.h"
#include "printf.h"

#include "DT500-MID.h"
#include <engine.h>
#include <wireless.h>
#include <debug.h>


wireless DH500_radio;

debug DEBUG;

int role = 0;   // 0 connect 1 LocoNET 3 Advanced Consisting
int responding; // 0 broadcast 1 TX 2 RX 3 Advanced Consisting




// #include "DT500-Os.h"

void setup() {
  Serial.begin(baud_rate);

  // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    SPI.begin(14, 12, 13, 15);

    digitalWrite(LED_BUILTIN, 255);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

// Show initial display buffer contents on the screen --
// the library initializes this with an Adafruit splash screen.
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(LED_BUILTIN, 255);

    if (nrf24_setup() == 1)
    {
      digitalWrite(LED_BUILTIN, 255);
    }else
    {
      digitalWrite(LED_BUILTIN, 0);
    }

    

    DH500_radio.int_PayloadStruct();

      
    DT500.Arduino_digital_analog_int();

    delay(500);

    // Clear the buffer
    display.clearDisplay();


   
    radio.printDetails();

    delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  DT500.lastDebounceTime = millis();

  DT500.loopCount++;

  DT500.get_count();

  DT500.error = DT500.push_buttons_joystick();

  DH500_radio.set_PayloadStruct();

  // DEBUG.display_time_DEBUG();

  DH500_radio.e_db();

  DH500_radio.Transmit();

  
}
