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

#ifndef _VREC_H
#define _VREC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thinhnt6 Note for VREC
 * 			Truong			So ky tu
 * 	1		Preamble		1
 * 	2		Type			1
 * 	3		Length			2
 * 	4		Data			2n
 * 	5		Checksum		2
 *
 *	if (Type == '0') <==> File Info
 *		!0030002000100
 *		- 03 = length of data (04 is correct)
 *		- 0002 = so luong chuong trinh
 *		- 0001 = version + revision
 *	if (Type == '1') <==> File Map
 *		!10A000700000002000004B100
 *		- 0A = length of data
 *		- 0007 = ID cua thiet bi
 *		- 00000002 = row idx cua chuong trinh con bat dau
 *		- 000004B1 = tong so ban ghi cua chuong trinh con bao gom ca header va end of prog
 *	if (Type == '2') <==> File Header
 *		!20C00071000010001C20014102908
 *		- 0C = length of data
 *		- 0007 = ID cua thiet bi
 *		- 1000010001C200141029 cac thu linh tinh ngay thang nam dek quan tam
 *
 */

//----------Include Files --------------------------------------------------------------------------
#include <stdint.h>

#include "CRC4.h"
#include "BootDef.h"

//----------Constant Definitions -------------------------------------------------------------------
#ifndef INLINE
#define INLINE //inline
#endif

#define VREC_ENABLE_ARGUMENT_CHECKING       1

#define VREC_COMM_ERROR_ACK_IDX 			1

#define VREC_MAX_LENGTH             256
#define VREC_MAX_DATA_BYTES         123
#define VREC_PREAMBLE_IDX           0
#define VREC_TYPE_IDX               1
#define VREC_LENGTH_IDX             2
#define VREC_DATA_IDX               4

#define VREC_NUM_PROG_IDX			2
#define VREC_DEV_ID_IDX				2
#define VREC_PROG_ID_IDX			4
#define VREC_PREAMBLE               ((uint8_t)'!')
#define VREC_IS_PREAMBLE(ch)        (ch == VREC_PREAMBLE)
#define VREC_IS_VALID_CHARACTER(ch) (((ch >= (uint8_t)'0') && (ch <= (uint8_t)'9')) ||\
                                     ((ch >= (uint8_t)'A') && (ch <= (uint8_t)'G')))
//#define HEX2DEC(u8Hex)              (((uint8_t)u8Hex<='9')?((uint8_t)u8Hex -0x30):((uint8_t)u8Hex - 0x37))
//#define HEX2DEC(u8Hex)              (((uint8_t)u8Hex<='9')?((uint8_t)u8Hex -0x30):((((uint8_t)u8Hex<'a')?((uint8_t)u8Hex -0x37):((uint8_t)u8Hex - 0x57))))

//#define DEC2HEX(u8Dec)              (((uint8_t)u8Dec<10)?(0x30+(uint8_t)(u8Dec)):(0x37+(uint8_t)(u8Dec)))

#define VREC_ERR_NONE               BOOT_ERR_NONE        /**< Operation is successful              */
#define VREC_ERR_INVALID_FORMAT     BOOT_ERR_FORMAT        /**< Invalid record format                */
#define VREC_ERR_CHECK_SUM          BOOT_ERR_CRC        /**< Checksum error                       */
#define VREC_ERR_INVALID_PARAMETER  BOOT_ERR_PARAMETER        /**< Input parameter is invalid           */
#define VREC_ERR_NOT_IMPLEMENTED    BOOT_ERR_NOT_IMPLEMENTED        /**< Record type is not implemented       */
#define VREC_ERR_UNKOWN             BOOT_ERR_UNKOWN

#define VREC_RAW_FORMAT             0
#define VREC_PACKAGE_FORMAT         1

#define VREC_ENABLE_CRC_CHECKING    1


#define VREC_TYPE_FILE_INFO         ((uint8_t)'0')
#define VREC_TYPE_FILE_MAP          ((uint8_t)'1')
#define VREC_TYPE_HEADER            ((uint8_t)'2')
#define VREC_TYPE_FILE_DATA16       ((uint8_t)'3')
#define VREC_TYPE_FILE_DATA24       ((uint8_t)'4')
#define VREC_TYPE_FILE_DATA32       ((uint8_t)'5')
#define VREC_TYPE_END_PROGRAM16     ((uint8_t)'6')
#define VREC_TYPE_END_PROGRAM24     ((uint8_t)'7')
#define VREC_TYPE_END_PROGRAM32     ((uint8_t)'8')
#define VREC_TYPE_END_OF_FILE       ((uint8_t)'9')

#define VREC_TYPE_ACK               ((uint8_t)'A')
#define VREC_TYPE_BOOT_HOOK         ((uint8_t)'B')
#define VREC_TYPE_SELECT_NODE       ((uint8_t)'C')
#define VREC_TYPE_GET               ((uint8_t)'D')

#define VREC_TYPE_SI3               VREC_TYPE_FILE_DATA24 //((uint8_t)'F')


//thinhnt6 supplementary for param test
// Set of command
//#define VREC_ENABLE_PARAM_TEST                      1
//#define VREC_ENABLE_MODEL_INFO                      1

//#define VREC_TYPE_PARAM_TEST_READ_CMD                    0
//#define VREC_TYPE_PARAM_TEST_WRITE_CMD                   1
//#define VREC_TYPE_PARAM_TEST_FLASH_WRITE_CMD             2 // after write value to PIC's RAM, write to FLASH
//#define VREC_TYPE_TEST_CODEC_CMD                    3
//#define VREC_TYPE_RETEST_CODEC_CMD                  4
//#define VREC_TYPE_TEST_SPI_FLASH_CMD                5
//#define VREC_TYPE_RETEST_SPI_FLASH_CMD              6
//#define VREC_TYPE_TEST_DSP_CMD                      7
//#define VREC_TYPE_RETEST_DSP_CMD                    8
//#define VREC_TYPE_TEST_TRANSA1_CMD                  9
//#define VREC_TYPE_RETEST_TRANSA1_CMD                10

//#define VREC_TYPE_PARAM_ERR                         0xFF


// Set of SUB_TYPE for CMD READ, WRITE
#define VREC_TYPE_PARAM_SUBCMD_DEFAULT             0 // unused
#define VREC_TYPE_PARAM_SUBCMD_CODEC_LEFT_DVOL     1
#define VREC_TYPE_PARAM_SUBCMD_CODEC_RIGHT_DVOL    2


// VREC Model CMD definition
#define VREC_MODEL_CMD_READ 0x00  // read command
#define VREC_MODEL_CMD_WRITE 0x01 // write command
#define VREC_MODEL_CMD_ERASE 0x03 // erase command


// VREC Model SUBCMD definition
#define VREC_MODEL_SUBCMD_HW 0x00 // Hardware number subcmd
#define VREC_MODEL_SUBCMD_BN 0x01 // Board number subcmd

#define VREC_MODEL_SUBCMD_ERR	0xFFFF	// Error subcmd

#define VREC_ERR_UNKOWN             BOOT_ERR_UNKOWN


#define VREC_COMM_NACK_IDX 0
#define VREC_COMM_ACK_IDX 1

//----------Type Definitions -----------------------------------------------------------------------
typedef union S_U32_tag
{
    uint8_t         U8[4];
    uint16_t        U16[2];
    uint32_t        Value;
}
S_U32;

typedef struct S_VREC_INFO_tag
{
    uint8_t         u8Preamble;
    uint8_t         u8Type;
    uint8_t         u8DataLength;
    S_U32           sAddress;
    uint8_t        *pu8Data;
}
S_VREC_INFO;

//----------Macros Definitions ---------------------------------------------------------------------


//----------Function Prototypes --------------------------------------------------------------------


/***********************************************************************************************//**
 * @brief       Decode a VREC record to binary form.
 ***************************************************************************************************
 * @param       pVrecBuff   Pointer to a VREC record
 * @param       pVrecInfo   Pointer to output vrec info
 * @param       pszCount    Pointer to a variable to store actual number of bytes has been written
 *                          to data field of vrec info.
 * @return	    Status of operation
 * @retval      VREC_ERR_NONE               Operation is successful.
 * @retval      VREC_ERR_INVALID_FORMAT     pVrec does not point to a valid record.
 * @retval      VREC_ERR_CHECK_SUM          Record checksum is wrong.
 * @retval      VREC_ERR_INVALID_PARAMETER  Argument(s) is NULL (available when 
 *                                          VREC_ENABLE_ARGUMENT_CHECKING > 0).
 * @note        Constraints
 *              +   Data buffer size must be large enough store the binary data.
 *              +   Data and source VREC buffers should not overlap.
 *
 **************************************************************************************************/
uint8_t     VREC_Decode             (const uint8_t  *pVrec,
                                     S_VREC_INFO    *pVrecInfo,
                                     uint32_t         *pszCount,
                                     uint8_t        u8ImageType);

void        VREC_DecodeData         (const uint8_t  *pu8Src,
                                     uint8_t        *pu8Dst,
                                     size_t         szLen);

uint8_t     VREC_CalculateCRC     (const uint8_t  *pBuffer,
                                     size_t         szBytesCount,
                                     uint8_t        u8IsHexChar);

extern char VREC_CommError[][9];


#ifdef __cplusplus
}
#endif
#endif  /* _VREC_H */
