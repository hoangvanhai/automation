#include "convert.h"



uint8_t     HexCharToU8        (const uint8_t  *pHexChar)
{
    return ((uint8_t)(HEX2DEC(pHexChar[0]) << 4) + (uint8_t)HEX2DEC(pHexChar[1]));
}


uint16_t    HexCharToU16       (const uint8_t  *pHexChar)
{
    return (((uint16_t)HEX2DEC(pHexChar[0]) << 12) + ((uint16_t)HEX2DEC(pHexChar[1]) << 8) +
            ((uint16_t)HEX2DEC(pHexChar[2]) <<  4) + ((uint16_t)HEX2DEC(pHexChar[3])     ));
}

uint32_t    HexCharToU24       (const uint8_t  *pHexChar)
{
    return (((uint32_t)HEX2DEC(pHexChar[0]) << 20) + ((uint32_t)HEX2DEC(pHexChar[1]) << 16) +
            ((uint32_t)HEX2DEC(pHexChar[2]) << 12) + ((uint32_t)HEX2DEC(pHexChar[3]) <<  8) +
            ((uint32_t)HEX2DEC(pHexChar[4]) <<  4) + ((uint32_t)HEX2DEC(pHexChar[5])      ));

}

uint32_t    HexCharToU32       (const uint8_t  *pHexChar)
{
    return (((uint32_t)HEX2DEC(pHexChar[0]) << 28) + ((uint32_t)HEX2DEC(pHexChar[1]) << 24) +
            ((uint32_t)HEX2DEC(pHexChar[2]) << 20) + ((uint32_t)HEX2DEC(pHexChar[3]) << 16) +
            ((uint32_t)HEX2DEC(pHexChar[4]) << 12) + ((uint32_t)HEX2DEC(pHexChar[5]) <<  8) +
            ((uint32_t)HEX2DEC(pHexChar[6]) <<  4) + ((uint32_t)HEX2DEC(pHexChar[7])      ));
}

void U8ToHexChar(uint8_t u8Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
    sprintf_safe(tmpStr,"%02X",u8Src);
    memcpy_safe(pu8Dst, tmpStr, 2);
}
void U16ToHexChar(uint16_t u16Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
    sprintf_safe(tmpStr, "%04X", u16Src);
    memcpy_safe(pu8Dst, tmpStr, 4);
}
void U24ToHexChar(uint32_t u24Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
    sprintf_safe(tmpStr, "%06X", u24Src);
    memcpy_safe(pu8Dst, tmpStr, 6);
}
void U32ToHexChar(uint32_t u32Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
    sprintf_safe(tmpStr, "%08X", u32Src);
    memcpy_safe(pu8Dst, tmpStr, 8);
}
