/*
 * File:   command.c
 * Author: Torben
 *
 * Created on October 6, 2020, 9:35 AM
 */

/** Includes **************************************************/
#define FCY 32000000UL

#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <stdio.h>
#include "command.h"
#include "vl53l0x.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

#define VL53L0X_Add_01      0x11                                        // ToF-Sensor 
#define VL53L0X_Add_02      0x12                                        // ToF-Sensor 
#define VL53L0X_Add_03      0x13                                        // ToF-Sensor 
#define VL53L0X_Add_04      0x14                                        // ToF-Sensor 
#define VL53L0X_Add_05      0x15                                        // ToF-Sensor 
#define VL53L0X_Add_06      0x16                                        // ToF-Sensor 
#define VL53L0X_Add_07      0x17                                        // ToF-Sensor 
#define VL53L0X_Add_08      0x18                                        // ToF-Sensor 
#define VL53L0X_Add_09      0x19                                        // ToF-Sensor 
#define VL53L0X_Add_10      0x1A                                        // ToF-Sensor 
#define VL53L0X_Add_11      0x1B                                        // ToF-Sensor 
#define VL53L0X_Add_12      0x1C                                        // ToF-Sensor 

extern float    range_mm_0;                                            // definiert "range_mm_1"       ToF-Sensor 
extern float    range_cm_0;                                            // definiert "range_cm_1"       ToF-Sensor 
extern float    range_mm_30;                                           // definiert "range_mm_2"       ToF-Sensor 
extern float    range_cm_30;                                           // definiert "range_cm_2"       ToF-Sensor 
extern float    range_mm_60;                                           // definiert "range_mm_3"       ToF-Sensor 
extern float    range_cm_60;                                           // definiert "range_cm_3"       ToF-Sensor 
extern float    range_mm_90;                                           // definiert "range_mm_4"       ToF-Sensor 
extern float    range_cm_90;                                           // definiert "range_cm_4"       ToF-Sensor
extern float    range_mm_120;                                          // definiert "range_mm_5"       ToF-Sensor 
extern float    range_cm_120;                                          // definiert "range_cm_5"       ToF-Sensor 
extern float    range_mm_150;                                          // definiert "range_mm_6"       ToF-Sensor 
extern float    range_cm_150;                                          // definiert "range_cm_6"       ToF-Sensor 
extern float    range_mm_180;                                          // definiert "range_mm_7"       ToF-Sensor 
extern float    range_cm_180;                                          // definiert "range_cm_7"       ToF-Sensor 
extern float    range_mm_210;                                          // definiert "range_mm_8"       ToF-Sensor 
extern float    range_cm_210;                                          // definiert "range_cm_8"       ToF-Sensor
extern float    range_mm_240;                                          // definiert "range_mm_9"       ToF-Sensor 
extern float    range_cm_240;                                          // definiert "range_cm_9"       ToF-Sensor 
extern float    range_mm_270;                                          // definiert "range_mm_10"      ToF-Sensor 
extern float    range_cm_270;                                          // definiert "range_cm_10"      ToF-Sensor 
extern float    range_mm_300;                                          // definiert "range_mm_11"      ToF-Sensor 
extern float    range_cm_300;                                          // definiert "range_cm_11"      ToF-Sensor 
extern float    range_mm_330;                                          // definiert "range_mm_12"      ToF-Sensor 
extern float    range_cm_330;                                          // definiert "range_cm_12"      ToF-Sensor

I2C1_MESSAGE_STATUS status;                                             // 

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[2] = {0x00, 0x00};                                  // definiert "readBuffer" 

uint8_t Slave_Address;                                                  // definiert "Slave_Address" 

uint16_t retryTimeOut1;                                                  // definiert "retryTimeOut1" 
uint16_t retryTimeOut2;                                                  // definiert "retryTimeOut2" 

/** Programm **************************************************/

void ToF_Init(void){                                                    // "ToF_Init"
    Sensor_01_SetLow();                                                 // setzt "Sensor_01" auf 0
    Sensor_02_SetLow();                                                 // setzt "Sensor_02" auf 0
    Sensor_03_SetLow();                                                 // setzt "Sensor_03" auf 0
    Sensor_04_SetLow();                                                 // setzt "Sensor_04" auf 0
    Sensor_05_SetLow();                                                 // setzt "Sensor_05" auf 0
    Sensor_06_SetLow();                                                 // setzt "Sensor_06" auf 0
    Sensor_07_SetLow();                                                 // setzt "Sensor_07" auf 0
    Sensor_08_SetLow();                                                 // setzt "Sensor_08" auf 0
    Sensor_09_SetLow();                                                 // setzt "Sensor_09" auf 0
    Sensor_10_SetLow();                                                 // setzt "Sensor_10" auf 0
    Sensor_11_SetLow();                                                 // setzt "Sensor_11" auf 0
    Sensor_12_SetLow();                                                 // setzt "Sensor_12" auf 0
    __delay_ms(500);                                                    // warte 500ms
    
    Sensor_01_SetHigh();                                                // setzt "Sensor_01" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_01);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_01" auf  

    Sensor_02_SetHigh();                                                // setzt "Sensor_02" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_02);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_02" auf 
    
    Sensor_03_SetHigh();                                                // setzt "Sensor_03" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_03);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_03" auf  
    
    Sensor_04_SetHigh();                                                // setzt "Sensor_04" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_04);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_04" auf  
    
    Sensor_05_SetHigh();                                                // setzt "Sensor_05" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_05);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_05" auf  

    Sensor_06_SetHigh();                                                // setzt "Sensor_06" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_06);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_06" auf 
    
    Sensor_07_SetHigh();                                                // setzt "Sensor_07" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_07);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_07" auf  
    
    Sensor_08_SetHigh();                                                // setzt "Sensor_08" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_08);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_08" auf  
    
    Sensor_09_SetHigh();                                                // setzt "Sensor_09" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_09);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_09" auf  

    Sensor_10_SetHigh();                                                // setzt "Sensor_10" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_10);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_10" auf 
    
    Sensor_11_SetHigh();                                                // setzt "Sensor_11" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_11);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_11" auf  
    
    Sensor_12_SetHigh();                                                // setzt "Sensor_12" auf 1
    __delay_ms(150);                                                    // warte 150ms
    VL53L0X_Init();                                                     // initialisierung des Sensors
    __delay_ms(100);                                                    // warte 100ms
    VL53L0X_SetAdd(VL53L0X_Add_12);                                     // ruft "VL53L0X_SetAdd" mit "VL53L0X_Add_12" auf  
    __delay_ms(500);                                                    // warte 500ms
}                                                                       //

void Wert_korrektur(void){                                              // "Wert_korrektur"
    if(range_mm_0 > 5000){                                              // fragt "range_mm_0" ab ob größer als 5000
        range_mm_0 = 2000;                                              // schreibt "2000" in "range_mm_0"
    }                                                                   // 
    if(range_mm_30 > 5000){                                             // fragt "range_mm_30" ab ob größer als 5000
        range_mm_30 = 2000;                                             // schreibt "2000" in "range_mm_30"
    }                                                                   // 
    if(range_mm_60 > 5000){                                             // fragt "range_mm_60" ab ob größer als 5000
        range_mm_60 = 2000;                                             // schreibt "2000" in "range_mm_60"
    }                                                                   // 
    if(range_mm_90 > 5000){                                             // fragt "range_mm_90" ab ob größer als 5000
        range_mm_90 = 2000;                                             // schreibt "2000" in "range_mm_90"
    }                                                                   // 
    if(range_mm_120 > 5000){                                            // fragt "range_mm_120" ab ob größer als 5000
        range_mm_120 = 2000;                                            // schreibt "2000" in "range_mm_120"
    }                                                                   // 
    if(range_mm_150 > 5000){                                            // fragt "range_mm_150" ab ob größer als 5000
        range_mm_150 = 2000;                                            // schreibt "2000" in "range_mm_150"
    }                                                                   // 
    if(range_mm_180 > 5000){                                            // fragt "range_mm_180" ab ob größer als 5000
        range_mm_180 = 2000;                                            // schreibt "2000" in "range_mm_180"
    }                                                                   // 
    if(range_mm_210 > 5000){                                            // fragt "range_mm_210" ab ob größer als 5000
        range_mm_210 = 2000;                                            // schreibt "2000" in "range_mm_210"
    }                                                                   // 
    if(range_mm_240 > 5000){                                            // fragt "range_mm_240" ab ob größer als 5000
        range_mm_240 = 2000;                                            // schreibt "2000" in "range_mm_240"
    }                                                                   // 
    if(range_mm_270 > 5000){                                            // fragt "range_mm_270" ab ob größer als 5000
        range_mm_270 = 2000;                                            // schreibt "2000" in "range_mm_270"
    }                                                                   // 
    if(range_mm_300 > 5000){                                            // fragt "range_mm_300" ab ob größer als 5000
        range_mm_300 = 2000;                                            // schreibt "2000" in "range_mm_300"
    }                                                                   // 
    if(range_mm_330 > 5000){                                            // fragt "range_mm_330" ab ob größer als 5000
        range_mm_330 = 2000;                                            // schreibt "2000" in "range_mm_330"
    }                                                                   // 
}                                                                       // 

void i2c1_message_pending_100(void){                                    // "i2c1_message_pending_100"
    retryTimeOut1 = 0;                                                  // setzt "retryTimeOut1" auf 0
    retryTimeOut2 = 0;                                                  // setzt "retryTimeOut2" auf 0
    while(status == I2C1_MESSAGE_PENDING){                              // solange "status" gleich "I2C1_MESSAGE_PENDING" ist
        if (retryTimeOut2 == 500){                                      // wenn "retryTimeOut2" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut2++;                                            // "retryTimeOut2" +1
        }                                                               // 
    }                                                                   // 
    while(status != I2C1_MESSAGE_FAIL){                                 // solange "status" nicht gleich "I2C1_MESSAGE_FAIL" ist
        if (retryTimeOut1 == 500){                                      // wenn "retryTimeOut1" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut1++;                                            // "retryTimeOut1" +1
        }                                                               // 
    }                                                                   // 
    //I2C1_LOST_STATE
}                                                                       // 