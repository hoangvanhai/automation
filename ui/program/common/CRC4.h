

#ifndef _CRC4_H_
#define _CRC4_H_


#include <stdint.h>
#include <stddef.h>


extern const uint8_t g_aru8CRC4Table[16];

#define CRC4_TABLE    g_aru8CRC4Table



#define CalculateByteCRC4(u8Value)      (CRC4_TABLE[((u8Value) >> 4)] ^ CRC4_TABLE[((u8Value) & 0x0F)])
#define GetCRC4(u8Val)                  CRC4_TABLE[u8Val]

/***********************************************************************************************//**
 * @brief       Calculate CRC4 value of an array
 *
 ***************************************************************************************************
 * @param       pu8Data         Pointer to array of uint8_t values
 * @param       szBytesCount    Number of bytes in array
 *
 * @return      CRC4 value
 *
 * @note        Input uint8_t array is considered as an array of 4-bit elements with 2*length
 **************************************************************************************************/
uint8_t CalculateCRC4           (const uint8_t         *pu8Data,
                                 size_t                 szBytesCount);


#endif	// _CRC4_H_
