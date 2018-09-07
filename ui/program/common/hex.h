/** @file       vrec.h
 *  @brief      This file provides API for VREC record manipulation.
 *
 *  @authors    LinhBN
 *  @author     Thinhnt6
 *  @pre        No precondition
 *
 *  @copyright  All Rights Reserved. This program is the confidential and proprietary product of
 *              ViettelR&D - Vietel Corp. Any unauthorized use, reproduction or transfer of this
 *              program is strictly prohibited.
 *
 *  @note       No Note at the moment
 *  @bug        No known bugs.
 *
 *  @par        Modification History
 *
 * Ver   |Who        |Date              |Changes
 * ------|-----------|------------------|---------------------------------------
 * 1.00  | LinhBN    | 9/25/2014        |
 *
 ****************************************************************************************************/

#ifndef _HEX_H
#define _HEX_H

#ifdef __cplusplus
extern "C" {
#endif


//----------Include Files --------------------------------------------------------------------------
#include <stdint.h>
#include "vrec.h"
#include "CRC4.h"
#include "BootDef.h"

//----------Constant Definitions -------------------------------------------------------------------
#define VREC_ERR_NONE               BOOT_ERR_NONE        /**< Operation is successful              */
#define VREC_ERR_INVALID_FORMAT     BOOT_ERR_FORMAT        /**< Invalid record format                */
#define VREC_ERR_CHECK_SUM          BOOT_ERR_CRC        /**< Checksum error                       */
#define VREC_ERR_INVALID_PARAMETER  BOOT_ERR_PARAMETER        /**< Input parameter is invalid           */
#define VREC_ERR_NOT_IMPLEMENTED    BOOT_ERR_NOT_IMPLEMENTED        /**< Record type is not implemented       */
#define VREC_ERR_UNKOWN             BOOT_ERR_UNKOWN

#define HEX_PREAMBLE               ((uint8_t)':')
#define HEX_IS_PREAMBLE(ch)        (ch == HEX_PREAMBLE)
#define HEX_IS_VALID_CHARACTER(ch) (((ch >= (uint8_t)'0') && (ch <= (uint8_t)'9')) ||\
                                     ((ch >= (uint8_t)'A') && (ch <= (uint8_t)'G')))
//----------Type Definitions -----------------------------------------------------------------------

typedef struct S_HEX_INFO_tag
{
    uint8_t         u8Preamble;
    uint8_t         u8Type;
    uint8_t         u8DataLength;
    S_U32           sAddress;
    uint8_t        *pu8Data;
}
S_HEX_INFO;

//----------Macros Definitions ---------------------------------------------------------------------

//manhbt Intel Hex Format

typedef enum _ERRCODE_DEFINED
{
    INTEL_HEX_ERR_NONE = 0,
    INTEL_HEX_ERR_UNKOWN
}E_INTEL_HEX_ERR_CODE;

typedef struct S_HEX_INFO_
{
    uint8_t         u8Preamble;
    uint8_t         u8DataLength;
    uint16_t		u16Address;
    uint8_t 		u8Type;
    uint8_t        *pu8Data;
}
IntelHexLineInfoTypeDef;

//Intel hex record type
//00 - data record
//01 - end-of-file record
//02 - extended segment address record
//04 - extended linear address record
//05 - start linear address record (MDK-ARM only)

#define HEX_TYPE_DATA        		  	0x00
#define HEX_TYPE_END_OF_FILE       	  	0x01
#define HEX_TYPE_EXT_SEGMENT          	0x02
#define HEX_TYPE_EXT_LINEAR_ADDRESS   	0x04
#define HEX_TYPE_UNKNOWN           		0x05


#define HEX_TYPE_ACK					0x10
#define HEX_TYPE_NACK					0x11
#define HEX_TYPE_BOOT_HOOK				0x12
// manhbt defined type for custom bootloader
//:10 0000 00 7804002045010008152500080D0A0008 A5
//: - preamble
//10 - datalen
//0000 - offset address
//00 - type 0 (data record)
//7804002045010008152500080D0A0008 - data
//A5 - checksum
//:00 0000 10 F0 - ACK message
#define HEX_TYPE_ERASE_SECTOR       	0x13
#define HEX_TYPE_ERASE_BANK       		0x14
#define HEX_TYPE_JUMP	       			0x15
#define HEX_TYPE_REBOOT     			0x16

#define HEX_LENGTH_IDX		1
#define HEX_TYPE_IDX		7
#define HEX_ADDR_IDX		3
#define HEX_DATA_IDX		9

#define HEX_MSG_ACK         ":00000010F0"
#define HEX_MSG_NACK        ":00000011EF"
#define HEX_MSG_BOOTHOOK    ":00000012EE"
#define HEX_MSG_JUMP        ":00000015EB"
#define HEX_MSG_REBOOT      ":00000016EA"

//----------Function Prototypes --------------------------------------------------------------------

uint8_t DecodeHexLine 		(	const uint8_t  *pHexLine,
                                IntelHexLineInfoTypeDef    *pHexLineInfo,
                                uint32_t         *pszCount);

#ifdef __cplusplus
}
#endif
#endif  /* _HEX_H */
