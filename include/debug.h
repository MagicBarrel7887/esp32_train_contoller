#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "engine.h"



class debug
{
private:
    /* data */
    unsigned long loopCount = 0;
    unsigned long timer = 0;


public:
    debug(/* args */);
    int IO(/* args */);
    int nrf24error();
    int display_time_DEBUG();
    int serial_debug();

    ~debug();
    int display_Function_DEBUG = 0;
};

debug::debug(/* args */)
{
}

debug::~debug()
{
    display.clearDisplay();

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(F("!_DEBUG_!"));

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println(3.141592);

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("0x"));
    display.println(0xDEADBEEF, HEX);

    display.display();

    return;
}

int debug::display_time_DEBUG()
{
    if ((millis() - timer) > 500)
    {
        digitalWrite(32, 100);



        switch (display_Function_DEBUG)
        {
        case 1:
            debug();
            break;
        case 2:
            IO();
            break;
        case 3:
            nrf24error();
            break;
        case 4:
            serial_debug();
            break;
        case 5:
            display_Function_DEBUG = 3;
            break;

        default:
            break;
        }

        display_Function_DEBUG ++;

        loopCount = 0;
        timer = millis();

        digitalWrite(32, 0);
    }
    loopCount++;



    return 0;
}

int debug::IO()
{
    display.clearDisplay();

    display.setTextSize(0.5);            // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text

    display.setCursor(1, 0);  // Start at top-left corner
    display.println(DT500.display_Function); //L Semaphore

    display.setCursor(115, 0);
    display.println(DT500.RX_ADD); //R Semaphore

    display.setCursor(40, 10); // Start at top-left corner
    display.println(F("IO DEBUG"));

    display.setCursor(0, 15);
    display.println(DT500.RX_ADD); //L Loco Icon

    display.setCursor(109, 15);
    display.println(DT500.temp_code); //R Loco Icon

    display.setCursor(27, 25);
    display.println(F("lta")); //L Throttle Address

    display.setCursor(75, 25);
    display.println(F("rta")); //R Throttle Address

    display.setCursor(55, 25);
    display.println(F("fn")); //Mode Indicator

    display.display();

    return 0;
}

int debug::nrf24error()
{


    display.clearDisplay();

    display.setTextSize(0.5);            // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text

    display.setCursor(1, 0);  // Start at top-left corner
    display.println(F("nrf24_error ")); //L Semaphore
    display.println(DT500.nrf24_error); //L Semaphore

    display.setCursor(115, 0);
    display.println(F("sr")); //R Semaphore

    display.setCursor(40, 10); // Start at top-left corner
    display.println(F("messages"));

    display.setCursor(0, 15);
    display.println(F("lli")); //L Loco Icon

    display.setCursor(109, 15);
    display.println(F("rli")); //R Loco Icon

    display.setCursor(27, 25);
    display.println(F("lta")); //L Throttle Address

    display.setCursor(75, 25);
    display.println(F("rta")); //R Throttle Address

    display.setCursor(55, 25);
    display.println(F("fn")); //Mode Indicator

    display.display();

    return 0;
}

int debug::serial_debug()
{
    Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    DT500.e_db();

    return 0;
}

#endif // __DEBUG_H_

