/* The MIT License (MIT)
 *
 * Copyright (c) 2014 to nils minor (contact nilsminor@web.de)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 25.05.2018 Nils Minor
 *  
 *  This library acts as a lightweight class to read averaged 
 * temperature values from an NTC. It is reduced im memory and
 * it is possible to change the reference voltage. It is also a non
 * blocking version, it does not use any delay.
 *
 *  Vx
 *  |
 * | |
 * | | REF
 * | |
 *  |_______ ADC
 *  |
 * | |
 * | | NTC
 * | |
 *  |
 * Gnd
 * 
 * TODO:
 *  - implement smoothing / averaging 
 *  - implment callibration function
 *  - rework analog reference / also adc circuit
 *  - implement commutativity of NTC and reference resistor
 */

#ifndef _NTC_H_
#define _NTC_H_

#include "Arduino.h"
// //23368 Bytes (81%) > 21978 Bytes (76%)
#define NCP15XW_BC          3950    // B constant
#define NCP15XW_RES         15000   // Resistance 15k @ 25 °C
#define R103AT2_BC          3435    // 10k @ 25 °C
#define R103AT2_RES         10000   // Resistance 10k @ 25 °C
#define REF_RES             10000   // Reference resistance
#define REF_TEMP            25      // Nominal temperature
#define RES_FREQ            10      // Measurment Frequency

#define CEL_TO_KEL(c) (double)(c+273.15)
#define KEL_TO_CEL(c) (double)(c-273.15)

class NTC {
  public:
    NTC (void);
    NTC (uint8_t pin, float bconst, float refres, float nomres, float nomtemp, uint8_t freq);
    void init (uint8_t pin, float bconst, float refres, float nomres, float nomtemp, uint8_t freq);
    void init_103AT2 (uint8_t pin, float refres,  uint8_t freq);
    void init_NCP15XW (uint8_t pin, float refres,  uint8_t freq);

    double getTemperature (void);
    void measureTemperature (void);
  private:
    uint8_t   analog_pin;
    float     bconstant;
    float     referenceResistance;  
    float     nominalResistance;  
    float     nominalTemperature;
    uint8_t   measurmentFrequency;
    float     analogReferenceVoltage;
    double     measuredTemperatureInCelsius;
  
};





#endif
