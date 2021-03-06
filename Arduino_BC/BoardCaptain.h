
#include "ZL2102.h"             //! Driver for ZL2102 DCDC converter
#include "ntc.h"                //! Small NTC library
#include "BoardCaptainDef.h"    //! Pinout and functionality definitions
#include <FanController.h>

#ifndef _BOARD_CAPTAI_H_
#define _BOARD_CAPTAI_H_


#define BOARD_DATA_ARRAY_SIZE         7
#define BOARD_DATA_POS_VIN            0
#define BOARD_DATA_POS_EN             1
#define BOARD_DATA_POS_TINT           2
#define BOARD_DATA_POS_T1             3
#define BOARD_DATA_POS_T2             4
#define BOARD_DATA_POS_FAN1           5
#define BOARD_DATA_POS_FAN2           6

enum LED_STATE {BC_OK, BC_ERROR};
enum VADJ { V_3V3, V_2V5, V_1V8, V_1V5, V_1V25, V_1V2, V_0V8 };   // selectable voltages for EN531QI
enum PARAMETER { VOLTAGE, CURRENT, POWER}; 

class BoardCaptain {
  public:
    BoardCaptain ();
    void run_system (void);
    void set_vadj (VADJ voltage);
    float get_temp (uint8_t source);
    void state_led (LED_STATE state);
    
    bool setVout (uint8_t psu, float voltage);
    float getVout (uint8_t psu);
    float getVin (uint8_t psu);
    float getIout (uint8_t psu);
    float getPout (uint8_t psu);   
    void  setFanSpeed (uint8_t fan, uint8_t fanspeed);
    
    double getTempIntern (void);
    float getTempFan (uint8_t fan);
    bool turn_on_off (int8_t psu, bool on_off);
    void listParameter (int8_t psu);
    void printAsJSON (void);
  private:
    void search_smbus_devices (void);
    void enable_vadj (bool enable);
    void error_handler (const char *err_msg);
    void vadj_set_outputs (uint8_t VS2, uint8_t VS1, uint8_t VS0);
    bool sense_enable_input (void);
    float sense_input_voltage (void);
    void initTemperatureSensors (void);
    
    float  data_array[BOARD_DATA_ARRAY_SIZE];
    String  data_name[BOARD_DATA_ARRAY_SIZE];

    // Fan controller
    void initFans (void);
    void senseFans (void);
    
    ZL2102 dcdc1;
    ZL2102 dcdc2;
    ZL2102 dcdc3;  
  
    NTC *ntc1;
    NTC *ntc2;
    NTC *ntc_int;
    FanController *fan1;
    FanController *fan2;
    
    bool system_enabled;
    LT_SMBus *smbus;
    LT_PMBus *pmbus;
};

#endif
