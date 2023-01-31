 int nrf24_setup()
 {

     Serial.println(F("\n\rRF24/examples/scanner/"));

     //
     // Setup and configure rf radio
     //
     if (!radio.begin())
     {
         Serial.println(F(""));
         Serial.println(F("radio hardware is not responding!!"));
         Serial.println(F(""));
         return 3;
     }
     radio.setAutoAck(false);

     // Get into standby mode
     radio.startListening();
     radio.stopListening();
     radio.printDetails();

     // Print out header, high then low digit
     int i = 0;
     while (i < num_channels)
     {
         Serial.print(i >> 4, HEX);
        ++i;
     }
     Serial.println();
     i = 0;
     while (i < num_channels)
     {
         Serial.print(i & 0xf, HEX);
         ++i;
      }
     Serial.println();
     //delay(1000);

 return 1;
 }