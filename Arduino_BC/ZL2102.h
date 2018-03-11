
/* Library for Renesas ZL2102 6A Digital Integrated Synchronous Step-Down DC/DC
   https://www.intersil.com/content/dam/Intersil/documents/zl21/zl2102.pdf

   Nils Minor 11.03.2018
*/

#ifndef _ZL2102_H_
#define _ZL2102_H_

#include <LT_PMBus.h>       // Include for PM-Bus relevant codes



 

//   Definition                           Code
#define ZL2102_OPERATION                  OPERATION         // LT_BMBus
#define ZL2102_ON_OFF_CFG                 ON_OFF_CONFIG     // LT_BMBus
#define ZL2102_CLEAR_FAULT                CLEAR_FAULTS      // LT_BMBus
#define ZL2102_VOUT_MODE                  VOUT_MODE         // LT_BMBus 
#define ZL2102_VOUT_COMMAND               VOUT_COMMAND      // LT_BMBus
#define ZL2102_VOUT_MAX                   VOUT_MAX          // LT_BMBus
#define ZL2102_VOUT_OV_FAULT_LIMIT        VOUT_OV_FAULT_LIMIT         // 0x40   L16u
#define ZL2102_VOUT_OV_FAULT_RESPONSE     VOUT_OV_FAULT_RESPONSE      // 0x41   BIT
#define ZL2102_VOUT_UV_FAULT_LIMIT        VOUT_UV_FAULT_LIMIT         // 0x44   L16U
#define ZL2102_VOUT_UV_FAULT_RESPONSE     VOUT_UV_FAULT_RESPONSE      // 0x45   BIT
#define ZL2102_IOUT_OC_FAULT_LIMIT        IOUT_OC_FAULT_LIMIT         // 0x46   L11
#define ZL2102_IOUT_UC_FAULT_LIMIT        0x47                        // L11
#define ZL2102_OT_FAULT_LIMIT             OT_FAULT_LIMIT              // 0x4F   L11 +125
#define ZL2102_OT_FAULT_RESPONSE          0x50                        // BIT
#define ZL2102_OT_WARN_LIMIT              OT_WARN_LIMIT               // 0x51   L11 +110
#define ZL2102_UT_WARN_LIMIT              UT_WARN_LIMIT               // 0x52   L11 -50
#define ZL2102_UT_FAULT_LIMIT             UT_FAULT_LIMIT              // 0x53   L11 -55
#define ZL2102_UT_FAULT_RESPONSE          0x54                        //        L11 BIT
#define ZL2102_POWER_GOOD_ON              0x5E                        // 0x54   L16
#define ZL2102_STATUS_WORD                STATUS_WORD                 // 0x79   2b
#define ZL2102_READ_VIN                   READ_VIN                    // 0x88   L11
#define ZL2102_READ_VOUT                  READ_VOUT                   // 0x8B   L16u
#define ZL2102_READ_IOUT                  READ_IOUT                   // 0x8C   L11
#define ZL2102_READ_TEMP                  READ_OTEMP                  // 0x8D   L11
#define ZL2102_FREQUENCY                  0x95                        //        L11
#define ZL2102_USER_CONFIG                MFR_CONFIG_ALL              //
#define ZL2102_DDC_CONFIG                 0xD3                        //  
#define ZL2102_STORE_USER_ALL             STORE_USER_ALL              // 0x15   
#define ZL2102_RESTORE_USER_ALL           RESTORE_USER_ALL            // 0x16
#define ZL2102_RESTORE_FACTORY            0xF4
#define ZL2102_BLANK_PARAMS               0xEB                        // 0x10
#define ZL2102_MFR_IOUT_OC_FAULT_RESPONSE 0xE5

#define ZL2102_VOUT_MODE_VALUE            -13                         // linear mode Exponent = -13
#define ZL2102_COMMAND_SPACING            2                           // 2ms between consecutive commands
#define ZL2102_CLOCK_RATE                 100000






#endif