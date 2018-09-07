/**
 * 
 * @file 		VrecEncode.c 
 * @date 		Mar 19, 2015
 * @author 		Nguyen Tien Thinh (thinhnt6)
 */

#include "VrecEncode.h"

void VREC_U8ToHexChar(uint8_t u8Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
	sprintf_safe(tmpStr,"%02X",u8Src);
	memcpy_safe(pu8Dst, tmpStr, 2);
}
void VREC_U16ToHexChar(uint16_t u16Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
	sprintf_safe(tmpStr, "%04X", u16Src);
	memcpy_safe(pu8Dst, tmpStr, 4);
}
void VREC_U24ToHexChar(uint32_t u24Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
	sprintf_safe(tmpStr, "%06X", u24Src);
	memcpy_safe(pu8Dst, tmpStr, 6);
}
void VREC_U32ToHexChar(uint32_t u32Src, uint8_t* pu8Dst)
{
    char_safe tmpStr[32];
	sprintf_safe(tmpStr, "%08X", u32Src);
	memcpy_safe(pu8Dst, tmpStr, 8);
}


//void VREC_Param_Test_Gen(uint8_t *pu8Dst, uint16_t u16CMD, uint16_t u16SubCMD, uint16_t u16Val)
//{
//    uint8_t u8CRC;
//    pu8Dst[VREC_PREAMBLE_IDX] = VREC_PREAMBLE;
//    pu8Dst[VREC_TYPE_IDX] = VREC_TYPE_PARAM_TEST;
//    VREC_U8ToHexChar(6, &pu8Dst[VREC_LENGTH_IDX]);
//    VREC_U16ToHexChar(u16CMD, &pu8Dst[4]);
//    VREC_U16ToHexChar(u16SubCMD, &pu8Dst[8]);
//    VREC_U16ToHexChar(u16Val, &pu8Dst[12]);
//    u8CRC = VREC_CalculateCRC(&pu8Dst[1], 6*2+3,1);
//    VREC_U8ToHexChar(u8CRC, &pu8Dst[4+6*2]);
//    pu8Dst[4+6*2+2] = '\0';
//}


//void VREC_Model_Gen(uint8_t *pu8Dst, uint8_t u8Len, uint8_t u8CMD, uint8_t *pu8Data)
//{
//    uint8_t u8CRC;
//    uint8_t u8DataLen = 2+u8Len;
//    int i;
//    pu8Dst[VREC_PREAMBLE_IDX] = VREC_PREAMBLE;
//    pu8Dst[VREC_TYPE_IDX] = VREC_TYPE_MODEL;
//    VREC_U8ToHexChar(u8DataLen, &pu8Dst[VREC_LENGTH_IDX]);
//    VREC_U8ToHexChar(u8Len, &pu8Dst[4]);
//    VREC_U8ToHexChar(u8CMD, &pu8Dst[6]);
//    for (i = 0; i < u8Len; i++)
//    {
//        VREC_U8ToHexChar(pu8Data[i], &pu8Dst[8+2*i]);
//    }
//    u8CRC = VREC_CalculateCRC(&pu8Dst[1], u8DataLen*2+3, 1);
//    VREC_U8ToHexChar(u8CRC, &pu8Dst[4+u8DataLen*2]);
//    pu8Dst[4+u8DataLen*2+2] = '\0';
//    //pu8Dst[4+u8DataLen*2+3] = '\0';
//}
