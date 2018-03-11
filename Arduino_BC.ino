#include <Wire.h>



#include <LT_SMBus.h>
#include <LT_SMBusPec.h>
#include <LT_SMBusBase.h>
#include <LT_SMBusGroup.h>
#include <LT_SMBusARA.h>
#include <LT_Wire.h>
#include <LT_SMBusNoPec.h>
#include <LT_I2CBus.h>
#include <LT_PMBus.h>
#include <LT_PMBusRail.h>
#include <LT_PMBusDevice.h>
#include <LT_PMBusSpeedTest.h>
#include <LT_FaultLog.h>
#include <LT_PMBusMath.h>
#include <LT_PMBusDetect.h>

#include "BoardCaptain.h"



/* Project: Arduino BC (Board-Captain) 
 * @athor: Nils Minor
 * @date:  20.02.2018
 * 
 * @brief Arduino based processing unit for the following tasks:
 *   - control and monitor ZL2102 DCDC converters via SM BUS
 *
 */




// IO Defines
// HUI (Hardware User Interface)



static LT_SMBus *smbus = new LT_SMBusNoPec(); 
static LT_PMBus *pmbus = new LT_PMBus(smbus);
BoardCaptain BC;

void setup() {
  Serial.begin (115200);
  
}

void loop() {
  
}
