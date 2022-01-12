/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
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


#include "ff.h"
#include "../mcc.h"
#include "../../mcc_generated_files/sd_spi/sd_spi.h"

static FATFS drive;
static FIL file;

extern float    range_mm_0;                                            // definiert "range_mm_1"       ToF-Sensor 
extern float    range_cm_0;                                            // definiert "range_cm_1"       ToF-Sensor 
extern float    range_mm_45;                                           // definiert "range_mm_2"       ToF-Sensor 
extern float    range_cm_45;                                           // definiert "range_cm_2"       ToF-Sensor 
extern float    range_mm_90;                                           // definiert "range_mm_3"       ToF-Sensor 
extern float    range_cm_90;                                           // definiert "range_cm_3"       ToF-Sensor 
extern float    range_mm_135;                                          // definiert "range_mm_4"       ToF-Sensor 
extern float    range_cm_135;                                          // definiert "range_cm_4"       ToF-Sensor
extern float    range_mm_180;                                          // definiert "range_mm_5"       ToF-Sensor 
extern float    range_cm_180;                                          // definiert "range_cm_5"       ToF-Sensor 
extern float    range_mm_225;                                          // definiert "range_mm_6"       ToF-Sensor 
extern float    range_cm_225;                                          // definiert "range_cm_6"       ToF-Sensor 
extern float    range_mm_270;                                          // definiert "range_mm_7"       ToF-Sensor 
extern float    range_cm_270;                                          // definiert "range_cm_7"       ToF-Sensor 
extern float    range_mm_315;                                          // definiert "range_mm_8"       ToF-Sensor 
extern float    range_cm_315;                                          // definiert "range_cm_8"       ToF-Sensor

void FatFs_Tasks(void){                                                         // "FatFs_Tasks"
    UINT actualLength;                                                          // definiert "actualLength"
    char data[70] = {0};                                                        // definiert "data"
    char datafilename[50] = {0};                                                // definiert "filename"
    char tof_data[500] = {0};                                                    // definiert "tof_data"
    char enter[2] = "\r\n";                                                     // definiert "enter" und schreibt "\r\n" hinein
    
    sprintf(datafilename, "SSLidar MK1 Logdatei.TXT");                          // schreibt "SSLidar MK1 Logdatei.TXT"
    sprintf(tof_data,"ToF:\r\n   0°= %.0fmm\r\n  45°= %.0fmm\r\n  90°= %.0fmm\r\n 135°= %.0fmm\r\n 180°= %.0fmm\r\n 225°= %.0fmm\r\n 270°= %.0fmm\r\n 315°= %.0fmm\r\n",         // 
            range_mm_0,                                                         // 
            range_mm_45,                                                        // 
            range_mm_90,                                                        // 
            range_mm_135,                                                        //
            range_mm_180,                                                       // 
            range_mm_225,                                                       // 
            range_mm_270,                                                       // 
            range_mm_315);                                                      //

    if(SD_SPI_IsMediaPresent() == false){                                       // wenn "SD_SPI_IsMediaPresent" gleich "false"
        LED1_Toggle();                                                          // Blinkt mit LED1
        return;                                                                 // Zurück
    }                                                                           // 
    
    if(f_mount(&drive,"0:",1) == FR_OK){                                        // Wenn Mount von SD-Karte ist gleich "FR_OK"
        if(f_open(&file, datafilename, FA_OPEN_APPEND | FA_READ | FA_WRITE) == FR_OK){ // erzeugt/öffnet "filename"
            f_write(&file, tof_data, sizeof(tof_data)-1, &actualLength );       // schreibt "tof_data" in "file"
            f_write(&file, enter, sizeof(enter)-1, &actualLength );             // schreibt "enter" in "file"
            f_write(&file, enter, sizeof(enter)-1, &actualLength );             // schreibt "enter" in "file"
            f_close(&file);                                                     // schließt Datei "file"
        }                                                                       // 
        f_mount(0,"0:",0);                                                      // Dismount SD-Karte 
    }                                                                           // 
}                                                                               // 