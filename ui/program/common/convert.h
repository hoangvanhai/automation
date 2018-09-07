
#ifndef __CONVERT_H__
#define __CONVERT_H__

#ifdef __cplusplus
extern "C" {
#endif


//----------Include Files --------------------------------------------------------------------------
#include <stdint.h>

#define HEX2DEC(u8Hex)              (((uint8_t)u8Hex<='9')?((uint8_t)u8Hex -0x30):((((uint8_t)u8Hex<'a')?((uint8_t)u8Hex -0x37):((uint8_t)u8Hex - 0x57))))

#define DEC2HEX(u8Dec)              (((uint8_t)u8Dec<10)?(0x30+(uint8_t)(u8Dec)):(0x37+(uint8_t)(u8Dec)))


uint8_t     HexCharToU8        (const uint8_t  *pHexChar);


uint16_t    HexCharToU16       (const uint8_t  *pHexChar);


uint32_t    HexCharToU24       (const uint8_t  *pHexChar);


uint32_t    HexCharToU32       (const uint8_t  *pHexChar);

void U8ToHexChar(uint8_t u8Src, uint8_t* pu8Dst);
void U16ToHexChar(uint16_t u8Src, uint8_t* pu8Dst);
void U24ToHexChar(uint32_t u8Src, uint8_t* pu8Dst);
void U32ToHexChar(uint32_t u8Src, uint8_t* pu8Dst);
#ifdef __cplusplus
}
#endif
#endif  /* _H */
