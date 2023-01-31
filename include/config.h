//DH166D configuration
// #define debug false // false
#define baud_rate 115200

#define moter_pin 0
#define CV_moter 2

//Locomotive Address

#define b2_Digi_Decoder_Address 3 // CV17 & 18 are used Together to program the 4 digit address. Current production Digitrax throttles handle this automatically. See calculator below if separate values are needed by your system for programming 4 digit address
#define b4_Digi_Address_H 33
#define b4_Digi_ADD_L 33
#define b4_Digi_ADD 33

//Locomotive Address CVs

#define CV_b2_Digi_Decoder_Address 1
#define CV_b4_Digi_Address_H 17
#define CV_b4_Digi_ADD_L 18
#define CV_b4_Digi_ADD 119

//Together to program the 4 digit address.
//Current production Digitrax throttles handle this automatically.

//Configuration Register

#define Address_Selection 2            //Address Selection, 2 or 4 digit 2 Digit 2 or 4 Digit
#define NDOT "Fwd"                       // Normal Direction of Travel :: Fwd/Rev
#define Speed_Step_Control 28          //14 or 28 or 28/128 or 128
#define Speed_Table_On_Off false    //Speed Table On or Off
#define Analog_Mode_Conversion true // On or Off

//Configuration Register CV
#define CV_Configuration_Register 29
#define CV_Sub_ADD_S 1     //CV_Address Selection, 2 or 4 digit 2 Digit 2 or 4 Digit
#define CV_Sub_NDOT 2      //CV_Address Normal Direction of Travel :: Fwd/Rev
#define CV_Sub_SSC 3       //CV_Address 14 or 28 or 28/128 or 128
#define CV_Sub_ST_ON_OFF 4 //CV_Address Speed Table On or Off
#define CV_Sub_AD_M_C 5    //CV_Address On or Off

//Locomotion CVs-Control -- Locomotive Motion -- Characteristics

//Acceleration and Deceleration

#define Acceleration 0
#define Deceleration 0

//Three Step Simple Speed Table & Start Voltage
#define Start_Voltage 0     //128 Steps
#define Maximum_Voltage 0   //128 Steps 00, 01 & 255 = max voltage at step 28
#define Mid_Point_Voltage 0 //128 Steps 00 & 01 = straight line curve

//28 Step Speed Tables with 256 Step Resolution
#define Kick_Start_value 0 //128 Step Interpolated
#define Forward_Trim 0     //128 Step Interpolated

//Torque Compensation and Switching Speed
#define Switching_Speed_Torque_Compensation 0
/*FX3 Decoders use CV54 to
control Switching Speed &
Torque Compensation*/

//Functions
#define DC Functions = true; /* Automatic --- DC Functions ON Not Used in FX3 */

//FX3 Functions

#define F0F 0 //forward light effect white
#define F0R 0
#define F1 0
#define F2 0
#define F3 0
#define F4 0
#define F5 0
#define F6 0
#define FX_Rate 0
#define FX_Keep_alive 0
#define Ditch_Light_Blink_hold_time 0
#define Master_Light_Switch true
//CV_CODE

#define CV_F0F 49
#define CV_F0R 50
#define CV_F1 51
#define CV_F2 52
#define CV_F3 113
#define CV_F4 114
#define CV_F5 115
#define CV_F6 116
#define CV_FX_Rate 62
#define CV_FX_Keep_alive 63
#define CV_Ditch_Light_Blink_hold_time 117
#define CV_Master_Light_Switch 118

//Directional Headlights, Transponding, Split Field Motor
#define Directional_Headlight true /*Map F0 Forward & Reverse See CV61 Section  */ /* Not controlled by CV61 in FX3 Decoders */
#define Transponding false
#define Split_Field_Motor false //For AC Motors

//Scaleable Speed Stabilization (Back EMF)
#define Static_Compensation = 128;  //00 to 255
#define Dynamic_Compensation = 48;  //00 to 255
#define Speed_Stabilizer_Droop = 6; //00 to 15

// SuperSonic (Quiet Operation)
#define Motor_Frequency_SuperSonic = 255; //00 to 255 //Default is MAX

//Advanced Consisting
#define Advanced_Consist_Address = 0; //Default is OFF

//Decoder Reset to Default Values
#define Reset_dec_to_fact 128 /*Set to 08 to reset all CV Values. Set to 09 to reset all CV Values except 28 step speed table. */
#define CV_Reset_dec_to_fact 8
#define CV_reboot 2

//Decoder IDs
#define Version ID 64 /* Digitrax Version ID Read Only */        //never set
#define Manufacturer ID 129 /* Digitrax Not affected by reset */ //never set

//Speed Table

int Speed_Table_28[28] = {8, 11, 14, 17, 20, 24, 28, 32, 36, 41, 46, 51, 56, 62, 68, 74, 80, 87, 94, 101, 108, 116, 124, 132, 141, 150, 160, 170};

int Speed_Table_128[128] = {0, 9, 13, 15, 22, 27, 31, 36, 40, 45, 49, 54, 58, 63, 75, 88, 100, 113, 125, 138, 151, 163, 176, 188, 201, 213, 226, 239};


//#define NULL 0
