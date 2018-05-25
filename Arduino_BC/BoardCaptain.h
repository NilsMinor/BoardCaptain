
#ifndef _BOARD_CAPTAI_H_
#define _BOARD_CAPTAI_H_

#include "Arduino.h"
#include "ZL2102.h"
#include "CLI.h"
#include <NTC_Thermistor.h>


// IO definitions

// Analog inputs
#define ADC_12V_INPUT       A0    // Pin 
#define ADC_VADJ            A1    // Pin
#define ADC_TEMP_1          A3    // Pin
#define ADC_TEMP_2          A4    // Pin
#define ADC_TEMP_INTERN     A5    // Pin
// A2 is N.C. 
// Outputs  ////////////////////////////
#define OUT_nLED_RG         4     // Pin 25    // LOW = red, HIGH = green      
#define OUT_SET_VADJ_VS0    11    // MISO Pin 11
#define OUT_SET_VADJ_VS1    6     // SCK Pin 9
#define OUT_SET_VADJ_VS2    33    // MOSI Pin 10
#define OUT_EN_VADJ_1       7     // Pin
 // D5 is N.C.
 
#define FAN_DRIVE_1         9     // Pin 29   // PWM Drive for fan 1
#define FAN_DRIVE_2         10    // Pin 30   // PWM Drive for fan 2

// Inputs         
#define FAN_TACH_1          1     // Pin      // Tacho input for fan 1
#define FAN_TACH_2          8     // Pin 28   // Tacho input for fan 2
#define SYSTEM_EN           13    // Pin 32   // Enable system, active low pulled down on module

// Communication
// TX       D1
// RX       D0
// USB+     USB_P (Pin 4)
// USB-     USB_N (Pin 3)
#define SMBUS_SDA           19
#define SMBUS_SCL           18    
#define UART_TX             1     // Pin 21
#define UART_RX             0     // Pin 20   

enum LED_STATE {BC_OK, BC_ERROR};
enum VADJ { V_3V3, V_2V5, V_1V8, V_1V5, V_1V25, V_1V2, V_0V8 };   // selectable voltages for EN531QI
enum PARAMETER { VOLTAGE, CURRENT, POWER}; 

class BC_CLI; // forward declaration

class BoardCaptain {
  public:
    BoardCaptain ();
    void run_system (void);
    void set_vadj (VADJ voltage);
    float get_temp (uint8_t source);
    void state_led (LED_STATE state);
    void search_smbus_devices (void);

    double getTempIntern (void);
  private:
    void enable_vadj (bool enable);
    void error_handler (const char *err_msg);
    void vadj_set_outputs (uint8_t VS2, uint8_t VS1, uint8_t VS0);
    bool sense_enable_input (void);

    BC_CLI *bc_cli;
    ZL2102 dcdc1;
    ZL2102 dcdc2;
    ZL2102 dcdc3;
    NTC_Thermistor* temp_internal;
    
    bool system_enabled;
    LT_SMBus *smbus;
    LT_PMBus *pmbus;
};

#endif
