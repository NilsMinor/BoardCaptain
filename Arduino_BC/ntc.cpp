
#include "ntc.h"

NTC::NTC (void) {
  analog_pin = 0;
  bconstant = 0;
  referenceResistance = 0;  
  nominalResistance = 0;  
  nominalTemperature = 0;
  measurmentFrequency = 0;
  measuredTemperatureInCelsius = 0;
}

NTC::NTC (uint8_t pin, float bconst, float refres, float nomres, float nomtemp, uint8_t freq) {
  init (pin, bconst, refres, nomres, nomtemp, freq);
}
void NTC::init (uint8_t pin, float bconst, float refres, float nomres, float nomtemp, uint8_t freq) {
  analog_pin = pin;
  bconstant = bconst;
  referenceResistance = refres;  
  nominalResistance = nomres;  
  nominalTemperature = nomtemp;
  measurmentFrequency = freq;
  measuredTemperatureInCelsius = 0;
  analogReferenceVoltage = 2.5;

  pinMode (analog_pin, INPUT);
}

void NTC::init_103AT2 (uint8_t pin, float refres,  uint8_t freq) {
  init (pin, R103AT2_BC, refres, R103AT2_RES, REF_TEMP, freq);
}
void NTC::init_NCP15XW (uint8_t pin, float refres,  uint8_t freq) {
  init (pin, NCP15XW_BC, refres, NCP15XW_RES, REF_TEMP, freq);
}

static long lastUpdate;
void NTC::measureTemperature (void) {
  
  if (millis() - lastUpdate > (1000/measurmentFrequency) )
  {
      lastUpdate = millis();
      uint16_t raw_value = analogRead (analog_pin);
      double voltage = raw_value * analogReferenceVoltage / 1023;
      
      double vntc = 3.76; // wird noch ein bug sein
      double tempResistance = - (referenceResistance / (1 - vntc/voltage)); 
      
      // Calculation
      // 1/T = 1/ Tn + (1/B * ln(RT/RN) 
      measuredTemperatureInCelsius = KEL_TO_CEL(1.0 / ( (1.0 / (CEL_TO_KEL(nominalTemperature)) + (1.0 / bconstant * log(tempResistance / nominalResistance)))));
  }
}

double NTC::getTemperature (void) {
  return measuredTemperatureInCelsius;
}

