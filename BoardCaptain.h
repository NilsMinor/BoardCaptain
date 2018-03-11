
#ifndef _BOARD_CAPTAI_H_
#define _BOARD_CAPTAI_H_

#include "Arduino.h"



// IO definitions

// Analog inputs
#define ADC_12V_INPUT       AIN0
#define ADC_VADJ            AIN1
//#define ADC???              AIN2
#define ADC_TEMP_1          AIN3
#define ADC_TEMP_2          AIN4
#define ADC_TEMP_INTERN     AIN5    

      

// Outputs
#define OUT_nLED_RG         0    // LOW = red, HIGH = green      
#define OUT_SET_VADJ_VS0    1    //
#define OUT_SET_VADJ_VS1    6    // 
#define OUT_SET_VADJ_VS2    33   //
#define OUT_EN_VADJ_1       26  //


// Communication
// TX       D1
// RX       D0
// USB+     USB_P (Pin 4)
// USB-     USB_N (Pin 3)

#define SMBUS_SDA           19
#define SMBUS_SCL           18


enum VADJ { V_3V3, V_2V5, V_1V8, V_1V5, V_1V25, V_1V2, V_0V8 }; // selectable voltages for EN5312QI


class BoardCaptain {
  public:
    BoardCaptain ();
  private:
    void set_vadj (VADJ voltage);
  
  
};






#endif
