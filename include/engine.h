#pragma once

#ifndef __ENGEN__H__
#define __ENGEN__H__


#define ttp229_statue false
#define DeBUG false


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>

#if ttp229_statue == true

#include <TTP229.h>

#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//#include "wireless.h"
#if ttp229_statue == true

TTP229 ttp229;

#endif

unsigned long previousMillis1 = 0; //will store last time LED was updated
unsigned long interval1 = 10000;   //interval at which to blink (milliseconds)

unsigned long previousMillis2 = 0; //will store last time LED was updated
unsigned long interval2 = 5000;    //interval at which to blink (milliseconds)

int but_1_pin = 2; // Boton Amarillo - A
int but_2_pin = 4; // Boton Amarillo - C
int but_3_pin = 5; // Boton Azul     - D
int but_4_pin = 3; // Boton Azul     - B
int but_5_pin = 6; // Boton F
int but_6_pin = 7; // Boton E
int but_7_pin = 8; // analog_button

int analogPin_joy_x = A0;


unsigned int dot_duration = 200;

class engen
{
private:
    

    int R_Reverse_Key;
    int L_Reverse_Key;

    int DISP_Key;
    int FUNC_Key;

    

    int FUNC_data[9];
    int LOCO;

    int EMERGENCY_STOP_Key;
    int error_number;

   

    

    int analogPin_joy = A3;
    int analog_joystick;
    

    int but_1;
    int but_2;
    int but_3;
    int but_4;
    int but_5;

   unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers



public:

   unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
   int e_db();

   int Function(/* args */);
   int Arduino_digital_analog_int(/* args */);
   int Loco_Selection(/* args */);
   int MU(/* args */);
   int Switch(/* args */);
   int Power(/* args */);

   int Status_Edit(/* args */);
   int Programming_Paged(/* args */);
   int Programming_Physical(/* args */);
   int Programming_Direct(/* args */);
   int Programming_Operations_Mode(/* args */);
   int Recall(/* args */);
   int Find(/* args */);
   int display_8();
   int push_buttons_joystick();

   bool nrf24_error = false;

   int RX_ADD;

   int error;

   int display_Function = 0;
   int temp_code;
   int cv_code;
   int lts; // L Throttle speed
   int data_io;

   int L_Throttle;
   int R_Throttle;

   bool sitch;
   bool Powr;

   int lta; //L Throttle Address
   int rta; //R Throttle Address

   int analog_joystick_map;

   //** @brief code loop counter -- Average loops per second @return 1
   unsigned long loopCount;
   unsigned long startTime;
   
   int get_count();

    #if ttp229_statue == true

    int ttp229_get_states();

    int ttp229_get_any_Pressed();

    /// Return true if key is pressed
    /// \param key Number of key
    /// \return True if key is pressed
    int ttp229_get_Pressed();

    /// Return true if key is pressed
    /// \param key Number of key
    /// \return True if key is pressed
    int ttp229_is_Key_Press(int key);

    #define enable_TTP229 false

    int engine_debug();

    #endif

    int analog_joystick_x;
};

int engen::Arduino_digital_analog_int(){

  pinMode(analogPin_joy_x, INPUT);

  pinMode(but_1_pin, INPUT_PULLUP);
  pinMode(but_2_pin, INPUT_PULLUP);
  pinMode(but_3_pin, INPUT_PULLUP);
  pinMode(but_4_pin, INPUT_PULLUP);
  pinMode(but_5_pin, INPUT_PULLUP);
  pinMode(but_6_pin, INPUT_PULLUP);
  pinMode(but_7_pin, INPUT_PULLUP);


  return 0;
}
//** @brief check buttons and Debounce @return 0 good, 1 error, 2 not at debouncing timer delay set

int engen::push_buttons_joystick(){




   analog_joystick_x = analogRead(analogPin_joy_x);
   analog_joystick_map = analogRead(analogPin_joy);

   if(analog_joystick_map >= 0){
      analog_joystick_map = map(analog_joystick_map, 0, 1023, 0, 255);
   }
   if(analog_joystick_map <= 0){
      analog_joystick_map = map(analog_joystick_map, -1023, 0, -255, 0);
   }


   but_1 = digitalRead(but_1_pin);
   but_2 = digitalRead(but_2_pin);
   but_3 = digitalRead(but_3_pin);
   but_4 = digitalRead(but_4_pin);
   but_5 = digitalRead(but_5_pin);
   return 0;
   }



//** @brief train controller functions @return null

 int engen::Function(/* args */)
 {
    for (int i = 0; i < 9; ++i) {

    }

    return 0;
 }

 int engen::Loco_Selection(/* args */)
 {
  // lcd.home();
  //  lcd.clear();
  //  lcd.print(Lo);
    return 0;
 }

 int engen::MU(/* args */)
 {
  //  lcd.home();
  //  lcd.clear();
  //  lcd.print(Mu);
    return 0;
 }

 int engen::Switch(/* args */)
 {
  //  lcd.home();
  // lcd.clear();
  // lcd.print(Sw);
    return 0;
 }

 int engen::Power(/* args */)
 {
  //  lcd.home();
  //  lcd.clear();
  //  lcd.print(Pw);
    return 0;
 }

 int engen::Status_Edit(/* args */)
 {
    return 0;
 }

 int engen::Programming_Paged(/* args */)
 {
    return 0;
 }

 int engen::Programming_Physical(/* args */)
 {
    return 0;
 }

 int engen::Programming_Direct(/* args */)
 {
    return 0;
 }

 int engen::Programming_Operations_Mode(/* args */)
 {
    return 0;
 }

 int engen::Recall(/* args */)
 {
    return 0;
 }

 int engen::Find(/* args */)
 {
    return 0;
 }





//** @brief code loop counter -- Average loops per second @return 1
 int engen::get_count()
 {
    if ((millis() - startTime) > 5000)
    {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount / 5);
        startTime = millis();
        loopCount = 0;
    }

    return 1; // or some valid int
 }


//** @brief display_8 defalt display mode @return int
 int engen::display_8()
 {
    if (display_Function == 0)
    {

        display.clearDisplay();

        display.setTextSize(0.5);            // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text

        display.setCursor(1, 0);  // Start at top-left corner
        display.println(F("sl")); //L Semaphore

        display.setCursor(115, 0);
        display.println(F("sr")); //R Semaphore

        display.setCursor(40, 10); // Start at top-left corner
        display.println(F("messages"));

        display.setCursor(0, 15);
        display.println(lts); //L Loco Icon

        display.setCursor(109, 15);
        display.println(F("rli")); //R Loco Icon

        display.setCursor(27, 25);
        display.println(F("lta")); //L Throttle Address

        display.setCursor(75, 25);
        display.println(F("rta")); //R Throttle Address

        display.setCursor(55, 25);
        display.println(temp_code); //Mode Indicator

        display.display();
    }

    if (display_Function == 1){
        display.clearDisplay();

        display.setTextSize(1);              // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE); // Draw white text

        display.setCursor(0, 10);
        display.println(F("enter Fn_code:")); //L Loco Icon

        display.setCursor(55, 20);
        display.println(temp_code); //Mode Indicator

        display.display();
    }

        return 0;
 }

//** @brief ttp229_statue defalt set to false ttp229 not use @return bool false
    #if ttp229_statue == true

        int engen::ttp229_get_states(){
        ttp229.readKeys();

        Serial.print("Key states: ");
        for (int i = 0; i < 16; ++i) {
        if (ttp229.isKeyPress(i)) {
            Serial.print("1 ");
            } else {
            Serial.print("0 ");
            }
     }
     return 0;
     }

     int engen::ttp229_get_Pressed(){

     ttp229.readKeys();

     int key = ttp229.getKey(); // gets Pressed key out put int
     Serial.print("Pressed key: ");
     Serial.print(key);

     Serial.print("   ");
     if (ttp229.isKeyDown(0)) {

        Serial.print("Key 0 is down");
     } else if (ttp229.isKeyUp(0)) {

        Serial.print("Key 0 is up");
     }

     return key;
     }


     int engen::ttp229_is_Key_Press(int key){
     ttp229.readKeys();

     // int keys = ttp229.getKey(); // gets Pressed key out put int
     int keys = ttp229.isKeyDown(key);


     return keys;
     }


     int engen::ttp229_get_any_Pressed(){

     ttp229.readKeys();
     bool gb;
     int key = ttp229.getKey(); // gets Pressed key out put int
     Serial.print("Pressed key: ");
     Serial.print(key);

     for(int g = 0; g < 16; g++){
     bool ga = ttp229.isKeyDown(g);

     if(!ga){
        gb = false;
         break;
       }

     if (ga) {
        gb = true;
     }
     }


     Serial.print("   ");
     if (ttp229.isKeyDown(0)) {

        Serial.print("Key 0 is down");
     } else if (ttp229.isKeyUp(0)) {

        Serial.print("Key 0 is up");
     }

        return gb;
     }
#endif

 int engine_debug(int a, String b){

    const char *c = b.c_str();

    Serial.print(c);   // inputstring
    Serial.print(" ");   // space
    Serial.println(a); // payload was not delivered

    return 1;
 }

 int engen::e_db() // engine debug Serial
 {
    engine_debug(L_Throttle, "L_Throttle");
    engine_debug(R_Throttle, "R_Throttle");
    engine_debug(R_Reverse_Key, "R_Reverse_Key");
    engine_debug(L_Reverse_Key, "L_Reverse_Key");

    engine_debug(DISP_Key, "DISP_Key");
    engine_debug(FUNC_Key, "FUNC_Key");

    engine_debug(sitch, "sitch");
    engine_debug(Powr, "Powr");

    engine_debug(0, "FUNC_data unavalbel");
    engine_debug(LOCO, "LOCO");

    engine_debug(EMERGENCY_STOP_Key, "EMERGENCY_STOP_Key");
    engine_debug(error_number, "error_number");

    engine_debug(lta, "lta");
    engine_debug(lta, "rta");

    engine_debug(analog_joystick_map, "analog_joystick");

    engine_debug(but_1, "but_1");
    engine_debug(but_2, "but_2");
    engine_debug(but_3, "but_3");
    engine_debug(but_4, "but_4");
    engine_debug(but_5, "but_5");
    
    engine_debug(error, "error");
  

    return 1;
 }

 int db(int a, String b){

    const char *c = b.c_str();

    Serial.print(c); // inputstring
    Serial.println(a); // payload was not delivered

    return 1;
 }


#endif //!__ENGEN__H__
