/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GB204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#define FCY 32000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/fatfs/fatfs.h"
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

int      i;                                                     // definiert "i"
float    range_mm_0;                                            // definiert "range_mm_1"       ToF-Sensor 
float    range_cm_0;                                            // definiert "range_cm_1"       ToF-Sensor 
float    range_mm_45;                                           // definiert "range_mm_2"       ToF-Sensor 
float    range_cm_45;                                           // definiert "range_cm_2"       ToF-Sensor 
float    range_mm_90;                                           // definiert "range_mm_3"       ToF-Sensor 
float    range_cm_90;                                           // definiert "range_cm_3"       ToF-Sensor 
float    range_mm_135;                                          // definiert "range_mm_4"       ToF-Sensor 
float    range_cm_135;                                          // definiert "range_cm_4"       ToF-Sensor
float    range_mm_180;                                          // definiert "range_mm_5"       ToF-Sensor 
float    range_cm_180;                                          // definiert "range_cm_5"       ToF-Sensor 
float    range_mm_225;                                          // definiert "range_mm_6"       ToF-Sensor 
float    range_cm_225;                                          // definiert "range_cm_6"       ToF-Sensor 
float    range_mm_270;                                          // definiert "range_mm_7"       ToF-Sensor 
float    range_cm_270;                                          // definiert "range_cm_7"       ToF-Sensor 
float    range_mm_315;                                          // definiert "range_mm_8"       ToF-Sensor 
float    range_cm_315;                                          // definiert "range_cm_8"       ToF-Sensor
char     buffer;                                                // defeniert "buffer"

/*
                         Main application
 */
int main(void){                                                 // "main"
    SYSTEM_Initialize();                                        // initialize the device
    Sensor_01_SetLow();                                         // setzt "Sensor_01" auf 0
    Sensor_02_SetLow();                                         // setzt "Sensor_02" auf 0
    Sensor_03_SetLow();                                         // setzt "Sensor_03" auf 0
    Sensor_04_SetLow();                                         // setzt "Sensor_04" auf 0
    Sensor_05_SetLow();                                         // setzt "Sensor_05" auf 0
    Sensor_06_SetLow();                                         // setzt "Sensor_06" auf 0
    Sensor_07_SetLow();                                         // setzt "Sensor_07" auf 0
    Sensor_08_SetLow();                                         // setzt "Sensor_08" auf 0
    __delay_ms(500);                                            // warte 500ms
    ToF_Init();                                                 // ruft "ToF_Init" auf

    while(1){                                                   // Endlosschleife
        range_mm_0   = VL53L0X_Millimeter_GetValue(VL53L0X_Add_01);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_01"
        range_mm_45  = VL53L0X_Millimeter_GetValue(VL53L0X_Add_02);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_02"
        range_mm_90  = VL53L0X_Millimeter_GetValue(VL53L0X_Add_03);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_03"
        range_mm_135 = VL53L0X_Millimeter_GetValue(VL53L0X_Add_04);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_04"
        range_mm_180 = VL53L0X_Millimeter_GetValue(VL53L0X_Add_05);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_05"
        range_mm_225 = VL53L0X_Millimeter_GetValue(VL53L0X_Add_06);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_06"
        range_mm_270 = VL53L0X_Millimeter_GetValue(VL53L0X_Add_07);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_07"
        range_mm_315 = VL53L0X_Millimeter_GetValue(VL53L0X_Add_08);// schreibt ergebnis von "VL53L0X_Millimeter_GetValue" in "range_mm_08"
        
        Wert_korrektur();                                       // ruft "Wert_korrektur" auf
        FatFs_Tasks();                                          // ruft "FatFs_Tasks" auf
        
        printf(" W0=   %.0fmm\r\n W45=  %.0fmm\r\n W90=  %.0fmm\r\n W135= %.0fmm\r\n W180= %.0fmm\r\n W225= %.0fmm\r\n W270= %.0fmm\r\n W315= %.0fmm\r\n\r\n",         // 
            range_mm_0,                                         // 
            range_mm_45,                                        // 
            range_mm_90,                                        // 
            range_mm_135,                                       //
            range_mm_180,                                       // 
            range_mm_225,                                       // 
            range_mm_270,                                       // 
            range_mm_315);                                      // 

        __delay_ms(50);                                         // warte 50ms 
    }                                                           // 
    return 1;                                                   // 
}                                                               // 
/**
 End of File
*/

