#define FCY 32000000UL

#include "xc.h"
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"
#include "command.h"
#include "sht40.h"

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

#define SHT40_ADDR    0x44

extern I2C1_MESSAGE_STATUS status;                                      // 
extern uint8_t Slave_Address;                                           // definiert "Slave_Address" 
extern uint8_t writeBuffer[3];                                          // definiert "writeBuffer"
extern uint8_t readBuffer[2];                                           // definiert "readBuffer"

void SHT40_Init(void){                                                  // "SHT40_Init"
    Slave_Address = SHT40_ADDR;                                         // schreibt "SHT40_ADDR" in "Slave_Address"    
  
    writeBuffer[0] = 0xFD;                                              // schreibt "0xFD" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    __delay_ms(10);                                                     // warte 10ms
}                                                                       // 

void SHT40_Read(void){                                                  // "SHT40_Read"
    Slave_Address = SHT40_ADDR;                                         // schreibt "SHT40_ADDR" in "Slave_Address"    
  
    writeBuffer[0] = 0xFD;                                              // schreibt "0xFD" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf   
    __delay_ms(10);                                                     // warte 10ms
    I2C1_MasterRead(&readBuffer[0], 6, Slave_Address, &status);         // liest von I2C1 in 6 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
}                                                                       // 


float SHT40_temp_GetValue(void){                                        // "SHT40_temp_GetValue"  
    float    tempDataAnz;                                               // definiert "tempDataAnz"
    uint16_t buffer;                                                    // definiert "buffer"
    
    SHT40_Read();                                                       // ruft "SHT40_Read" auf
    buffer = readBuffer[0] * 256 + readBuffer[1];                       // 
    tempDataAnz = buffer;                                               // schreibt inhalt von "buffer" in "tempDataAnz"
    tempDataAnz = -45 + 175 * tempDataAnz/65535;                        // 
    
    return tempDataAnz;                                                 // gibt "tempDataAnz" zur�ck     
}                                                                       // 

float SHT40_humy_GetValue(void){                                        // "SHT40_humy_GetValue" 
    float    pressDataAnz;                                              // definiert "pressDataAnz"
    uint16_t buffer;                                                    // definiert "buffer"
    
    SHT40_Read();                                                       // ruft "SHT40_Read" auf
    buffer = readBuffer[3] * 256 + readBuffer[4];                       // 
    pressDataAnz = buffer;                                              // schreibt inhalt von "buffer" in "pressDataAnz"
    pressDataAnz = -6 + 125 * pressDataAnz/65535;                       // 
    
    if(pressDataAnz > 100){                                             // wenn "pressDataAnz" gr��er als "100" ist
        pressDataAnz = 100;                                             // "pressDataAnz" gleich 100
    }                                                                   // 
    if (pressDataAnz < 0){                                              // wenn "pressDataAnz" kleiner als "100" ist
        pressDataAnz = 0;                                               // "pressDataAnz" gleich 0
    }                                                                   // 
    
    return pressDataAnz;                                                // gibt "pressDataAnz" zur�ck     
}                                                                       // 
