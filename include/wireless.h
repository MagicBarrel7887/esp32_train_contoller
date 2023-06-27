#pragma once

#ifndef __WIRELESS__H__
#define __WIRELESS__H__

#define debug_wireless true

/*
//#include <RH_NRF24.h>
// Singleton instance of the radio driver
// RH_NRF24 nrf24;
// RH_NRF24 nrf24(4, 5); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini
*/

#include "RF24.h"
#include "engine.h"
#include "config.h"
#include <Wire.h>

engen DT500;

// Set up nRF24L01 radio on SPI bus plus pins 7 & 8

//
// Hardware configuration
//

//nrf_csn:24
//nrf_ce:25

RF24 radio(10,2); // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

//RF24 radio(9, 10); // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

//
// Channel info
//

const uint8_t num_channels = 126;
uint8_t values[num_channels];







struct PayloadStruct
{
    unsigned long Address;
    unsigned long payloadID;
    int b4_Address;
    int cv;
    int R_W;
    int b; // brocast
    int data;
    bool connected;
    bool disconet;
    int C_L_T; // connect to L_Throttle
    int C_R_T;
    int C_R_K;
    int C_L_T_A; //CV L Throttle Address
    int C_R_T_A; // CV R Throttle Address
    int C_S; //CV switch
    int C_P; // CV Power
    int moters;
};
PayloadStruct TX_RX_BC;

class wireless
{

private:
    /* data */
    unsigned long previousMillis1 = 0; //will store last time LED was updated
    unsigned long interval1 = 200;   //interval at which to blink (milliseconds)

    unsigned long previousMillis2 = 0; //will store last time LED was updated
    unsigned long interval2 = 500;    //interval at which to blink (milliseconds)

    unsigned long previousMillis3 = 0; // will store last time LED was updated
    unsigned long interval3 = 10000;      // interval at which to blink (milliseconds)

public:


    int role = 0;   // 0 broadcast 1 LocoNET 3 Advanced Consisting
    int responding; // 0 broadcast 1 TX 2 RX 3 Advanced Consisting

    int recieved(/* args */);
    int setup(/* args */);
    int brodcast(/* args */);
    int Transmit(/* args */);
    int set_PayloadStruct();
    int int_PayloadStruct();
    int isChipConnect();
    int e_db();

};

int wireless::e_db() // engine debug Serial
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis3 > interval3)
        {
            engine_debug(TX_RX_BC.Address, "Address");
            engine_debug(TX_RX_BC.payloadID, "payloadID");

            engine_debug(TX_RX_BC.b4_Address, "b4_Address");
            engine_debug(TX_RX_BC.cv, "cv");
            engine_debug(TX_RX_BC.R_W, "R_W");
            engine_debug(TX_RX_BC.b, "b");
            engine_debug(TX_RX_BC.data, "data");

            engine_debug(TX_RX_BC.connected, "connected");
            engine_debug(TX_RX_BC.disconet, "disconet");

            engine_debug(TX_RX_BC.C_L_T, "C_L_T");
            engine_debug(TX_RX_BC.C_R_T, "C_R_T");

            engine_debug(TX_RX_BC.C_L_T_A, "C_L_T_A");
            engine_debug(TX_RX_BC.C_R_T_A, "C_R_T_A");

            engine_debug(TX_RX_BC.C_S, "C_S");
            engine_debug(TX_RX_BC.C_P, "C_P");

            engine_debug(TX_RX_BC.moters, "moters");

            previousMillis3 = currentMillis; // save the last time I blinked the LED
        }


        return 1;
    }

int nrf24_setup() //! initialize the transceiver
    {
        int f = 0;
        // initialize the transceiver on the SPI bus
        if (!radio.begin())
        {
            DT500.nrf24_error = true;
            Serial.println(F("radio hardware is not responding!!"));

            display.clearDisplay();

            display.setTextSize(1);              // Normal 1:1 pixel scale
            display.setTextColor(SSD1306_WHITE); // Draw white text

            display.setCursor(0, 0);
            display.println(F("radio hardware is not responding!!")); //L Loco Icon
            display.display();
            f = 1;
        }

        radio.setAutoAck(false);

        // Get into standby mode
        radio.startListening();
        radio.stopListening();
        return f;
    }

int wireless::recieved(/* args */)
{
    unsigned long currentMillis3 = millis();

    if (currentMillis3 - previousMillis2 > interval2)
    {
        previousMillis2 = currentMillis3; // save the last time I blinked the LED

        Serial.print(F("RX "));

        for (uint8_t i = 0; i < 5; ++i)
            radio.openReadingPipe(i, DT500.RX_ADD);

        radio.startListening(); // put radio in RX mode              // end the timer

        Serial.print(F("RX? "));
        uint8_t pipe;
        if (radio.available(&pipe))
        {                                           // is there a payload? get the pipe number that recieved it
            uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
            radio.read(&TX_RX_BC, bytes);           // fetch payload from FIFO
            Serial.print(F("Received "));
            Serial.print(bytes); // print the size of the payload
            Serial.print(F(" bytes on pipe "));
            Serial.print(pipe); // print the pipe number
            Serial.print(F(" from node "));
            Serial.print(TX_RX_BC.Address); // print the payload's origin
            Serial.print(F(". PayloadID: "));
            Serial.println(TX_RX_BC.payloadID); // print the payload's number
        }
    }
    currentMillis3 = millis();

    return 0;
}

int wireless::Transmit(/* args */)
{
    unsigned long currentMillis = millis();
    bool report;

    if (currentMillis - previousMillis1 > interval1)
    {
        radio.stopListening(); // put radio in TX mode
        radio.openWritingPipe(TX_RX_BC.Address);

        // According to the datasheet, the auto-retry features's delay value should
        // be "skewed" to allow the RX node to receive 1 transmission at a time.
        // So, use varying delay between retry attempts and 15 (at most) retry attempts
        radio.setRetries(((role * 3) % 12) + 3, 15); // maximum value is 15 for both args

        previousMillis1 = currentMillis; // save the last time I blinked the LED

        unsigned long start_timer = micros();                       // start the timer
        report = radio.write(&TX_RX_BC, sizeof(TX_RX_BC));          // transmit & save the report
        unsigned long end_timer = micros();                         // end the timer

        if (report)
        {
            // payload was delivered
            #ifdef debug_wireless
            Serial.print(F("Transmission of payloadID "));
            Serial.print(TX_RX_BC.payloadID); // print payloadID
            Serial.print(F(" as Address "));
            Serial.print(TX_RX_BC.Address); // print nodeID
            Serial.print(F(" successful!"));
            Serial.print(F(" Time to transmit: "));
            Serial.print(end_timer - start_timer); // print the timer result
            Serial.println(F(" us"));
            #endif 
          
        }
        else
        {
            Serial.println(F("Transmission failed or timed out")); // payload was not delivered
        }
        TX_RX_BC.payloadID++; // increment payload number
    }
    currentMillis = millis();

    return report;
}

int wireless::setup()
{
    bool report;
    report = nrf24_setup();
    return report;
}

int wireless::brodcast()
{
    unsigned long currentMillis = millis();
    // unsigned long currentMillis3 = millis();

    // int report2 = 0;

    bool report;

    TX_RX_BC.b = 1;

    if (currentMillis - previousMillis1 > interval1)
    {
        radio.stopListening(); // put radio in TX mode
        radio.openWritingPipe(TX_RX_BC.Address);

        // According to the datasheet, the auto-retry features's delay value should
        // be "skewed" to allow the RX node to receive 1 transmission at a time.
        // So, use varying delay between retry attempts and 15 (at most) retry attempts
        radio.setRetries(((role * 3) % 12) + 3, 15); // maximum value is 15 for both args

        previousMillis1 = currentMillis; // save the last time I blinked the LED

        unsigned long start_timer = micros();                 // start the timer
        report = radio.write(&TX_RX_BC, sizeof(TX_RX_BC));    // transmit & save the report
        unsigned long end_timer = micros();                   // end the timer

        if (report)
        {
            // payload was delivered

            Serial.print(F("Transmission of payloadID "));
            Serial.print(TX_RX_BC.payloadID); // print payloadID
            Serial.print(F(" as Address "));
            Serial.print(TX_RX_BC.Address); // print nodeID
            Serial.print(F(" successful!"));
            Serial.print(F(" Time to transmit: "));
            Serial.print(end_timer - start_timer); // print the timer result
            Serial.println(F(" us"));

        }
        else
        {
            Serial.println(F("Transmission failed or timed out")); // payload was not delivered

        }
        TX_RX_BC.payloadID++; // increment payload number
    }
    currentMillis = millis();


    return report;
}

int wireless::set_PayloadStruct()
{
    TX_RX_BC.C_L_T = DT500.analog_joystick_map;
    return 1;
}

int wireless::int_PayloadStruct()
{
    TX_RX_BC.C_L_T = DT500.analog_joystick_map;

    TX_RX_BC.Address = b2_Digi_Decoder_Address;

    TX_RX_BC.b4_Address = b4_Digi_ADD_L + b4_Digi_Address_H ;

    return 1;
}

int wireless::isChipConnect(){
    bool report;

    report = radio.isChipConnected();

    return report;
}

#endif //!__WIRELESS__H__
