/**
 * 
 * @file 		VrecEncode.h 
 * @date 		Mar 19, 2015
 * @author 		Nguyen Tien Thinh (thinhnt6)
 */

#ifndef VRECENCODE_H_
#define VRECENCODE_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------Include Files --------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "vrec.h"

void VREC_U8ToHexChar(uint8_t u8Src, uint8_t* pu8Dst);
void VREC_U16ToHexChar(uint16_t u8Src, uint8_t* pu8Dst);
void VREC_U24ToHexChar(uint32_t u8Src, uint8_t* pu8Dst);
void VREC_U32ToHexChar(uint32_t u8Src, uint8_t* pu8Dst);
/**
 * Create a VREC LINE of type PARAM TEST
 * example: !F06000100020003xx
 * F: type VREC_TYPE_PARAM_TEST
 * 06: len
 * 0001: 2 bytes command (in hex string)
 * 0002: 2 bytes sub command (in hex string)
 * 0003: 2 bytes value (in hex string)
 * @param pu8Dst
 * @param u16CMD
 * @param u16SubCMD
 * @param u16Val
 */
void VREC_Param_Test_Gen(uint8_t* pu8Dst, uint16_t u16CMD, uint16_t u16SubCMD, uint16_t u16Val);
/**
 * Generate a Vrec line to pu8Dst
 * @param pu8Dst
 * @param u16CMD
 * @param u16SubCMD
 * @param u8Len 	len of data (for example 3 bytes for HW version) 10 bytes for Serial  number
 * @param pu8Data	data of
 */
void VREC_Model_Gen(uint8_t *pu8Dst, uint8_t u8Len, uint8_t u8CMD, uint8_t *pu8Data);

#ifdef __cplusplus
}
#endif

#endif /* VRECENCODE_H_ */
