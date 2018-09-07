/** @file       BootDef.h
 *  @brief      This file defines const values used throughout project
 *
 *  @authors    LinhBN
 *  @version    1.00
 *  @pre        No precondition
 *
 *  @copyright  All Rights Reserved. This program is the confidential and proprietary product of
 *              ViettelR&D - Vietel Corp. Any unauthorized use, reproduction or transfer of this
 *              program is strictly prohibited.
 *
 *  @note       
 *  @bug        No known bugs.
 *
 *  @par        Modification History
 *
 * Ver   |Who        |Date              |Changes
 * ------|-----------|------------------|---------------------------------------
 * 1.00  | LinhBN    | 9/25/2014        | 
 *
 ****************************************************************************************************/
#ifndef _BOOT_DEF_H
#define _BOOT_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
    



#define BOOT_ERR_NONE                   0x00
#define BOOT_ERR_FORMAT                 0x01
#define BOOT_ERR_CRC                    0x02
#define BOOT_ERR_PARAMETER              0x03
#define BOOT_ERR_NOT_IMPLEMENTED        0x04
#define BOOT_ERR_SERIAL_PARITY          0x05
#define BOOT_ERR_SERIAL_FRAMING         0x06
#define BOOT_ERR_SERIAL_OVERRUN         0x07
#define BOOT_ERR_TIMEOUT                0x08
#define BOOT_ERR_UNKOWN                 0x09

#define BOOT_FULL_VREC_LINE                  0x0A // thinhnt6 recevice full vrec line

#define BOOT_ERR_MAX_VALUE              BOOT_ERR_UNKOWN

#define TIME_OUT_HIGH_WORD              0x02FF
#define TIME_OUT_LOW_WORD               0xFFFF


/**
 * @brief   Register 32-bit structure.
 */
typedef union S_REG32
{
    uint32_t U32;
    struct
    {
        uint16_t    U16L;
        uint16_t    U16H;
    };
    uint8_t U8[4];
}
S_REG32;



#ifdef __cplusplus
}
#endif
#endif  /* _BOOT_DEF_H */


