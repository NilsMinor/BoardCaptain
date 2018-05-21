



#ifndef _BOARD_CAPTAI_H_
#define _BOARD_CAPTAI_H_

#include "Arduino.h"
#include "ZL2102.h"
#include <CLI.h>


// IO definitions

// Analog inputs
#define ADC_12V_INPUT       AIN0
#define ADC_VADJ            AIN1
//#define ADC???              AIN2
#define ADC_TEMP_1          AIN3
#define ADC_TEMP_2          AIN4
#define ADC_TEMP_INTERN     AIN5    

      

// Outputs
#define OUT_nLED_RG         4    // LOW = red, HIGH = green      
#define OUT_SET_VADJ_VS0    1    //
#define OUT_SET_VADJ_VS1    6    // 
#define OUT_SET_VADJ_VS2    33   //
#define OUT_EN_VADJ_1       26   //


// Communication
// TX       D1
// RX       D0
// USB+     USB_P (Pin 4)
// USB-     USB_N (Pin 3)

#define SMBUS_SDA           19
#define SMBUS_SCL           18


#define TEMP_INT            0
#define TEMP_EXT1           1
#define TEMP_EXT2           2


enum LED_STATE {BC_OK, BC_ERROR};
enum VADJ { V_3V3, V_2V5, V_1V8, V_1V5, V_1V25, V_1V2, V_0V8 }; // selectable voltages for EN5312QI
enum PARAMETER { VOLTAGE, CURRENT, POWER}; 


class BoardCaptain {
  public:
    BoardCaptain ();
    void  set_vadj (VADJ voltage);
    float get_temp (uint8_t source);
    float get_parameter (uint8_t psu, PARAMETER parameter);
    void  state_led (LED_STATE state);
    void smbus_test (void);

    void search_smbus_devices (void);
    
  private:
    void enable_vadj (bool enable);
    void error_handler (const char *err_msg);
    void vadj_set_outputs (uint8_t VS2, uint8_t VS1, uint8_t VS0);
    ZL2102 dcdc1;
    ZL2102 dcdc2;
    ZL2102 dcdc3;
    

    LT_SMBus *smbus;
    LT_PMBus *pmbus;
};

#endif
