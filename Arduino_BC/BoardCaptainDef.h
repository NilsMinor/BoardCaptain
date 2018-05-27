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

 /*! \file BoardCaptainDef.h
  * Contains most of the board related definitions like pinout and predefined values.
  * Should serve as one file where the values can be easily changed. 
  * 
  */
/*!  IO definitions ***************************************************************************************** */
/*!  Analog Inputs  ***************************************************************************************** */
#define ADC_12V_INPUT       A0    // Pin 
#define ADC_VADJ            A1    // Pin
#define ADC_TEMP_1          A3    // Pin
#define ADC_TEMP_2          A4    // Pin
#define ADC_TEMP_INTERN     A5    // Pin
#define ADC_REF_VOLTAGE     2.5
// A2 is N.C. 
/*!  Digital Outputs ***************************************************************************************** */
#define OUT_nLED_RG         4     // Pin 25       // LOW = red, HIGH = green      
#define OUT_SET_VADJ_VS0    11    // MISO Pin 11
#define OUT_SET_VADJ_VS1    6     // SCK Pin 9
#define OUT_SET_VADJ_VS2    33    // MOSI Pin 10
#define OUT_EN_VADJ_1       7     // Pin
// D5 is N.C.
/*!  PWM Poutputs   ***************************************************************************************** */
#define FAN_DRIVE_1         9     // Pin 29       // PWM Drive for fan 1
#define FAN_DRIVE_2         10    // Pin 30       // PWM Drive for fan 2
/*!  Digital Inputs ***************************************************************************************** */     
#define FAN_TACH_1          1     // Pin          // Tacho input for fan 1
#define FAN_TACH_2          8     // Pin 28       // Tacho input for fan 2
#define SYSTEM_EN           13    // Pin 32       // Enable system, active low pulled down on module
/*!  Communication  ***************************************************************************************** */
#define SMBUS_SDA           19    // Pin 19
#define SMBUS_SCL           18    // Pin 18
#define UART_TX             1     // Pin 21
#define UART_RX             0     // Pin 20   
/*****************************************************************
******************************************* */
/*!  Functionality  ***************************************************************************************** */

#define SENSOR_THRESHOLD    10000
