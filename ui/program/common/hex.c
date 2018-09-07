#include "hex.h"
#include "convert.h"

char   HEX_CommError[][9] =
{
    "!A01000E",     // NACK
    "!A01010D",     // ACK
    "!A010208",     // Format error
    "!A01030B",     // Wrong CRC
    "!A010402",     // Not applicable
    "!A010501",     // Timeout
    "!A010604",     // Parity error
    "!A010707",     // Framing error
    "!A010805",     // Overrun error
    "!A010906"      // Unkown error
};


uint8_t DecodeHexLine 		(	const uint8_t  *pHexLine,
                                        IntelHexLineInfoTypeDef    *pHexLineInfo,
                                        uint32_t         *pszCount)
{
    uint8_t i;
    pHexLineInfo->u8DataLength = HexCharToU8(&pHexLine[HEX_LENGTH_IDX]);

    pHexLineInfo->u8Type       = HexCharToU8(&pHexLine[HEX_TYPE_IDX]);

    pHexLineInfo->u16Address   = HexCharToU16(&pHexLine[HEX_ADDR_IDX]);

    for(i = 0; i < pHexLineInfo->u8DataLength; i ++)
    {
        pHexLineInfo->pu8Data[i] = HexCharToU8(&pHexLine[HEX_DATA_IDX + i*2]);
    }
    switch (pHexLineInfo->u8Type)
    {
        case HEX_TYPE_EXT_LINEAR_ADDRESS:
        case HEX_TYPE_DATA:
        case HEX_TYPE_END_OF_FILE:
        case HEX_TYPE_UNKNOWN:
            return INTEL_HEX_ERR_NONE;
        default:
            return INTEL_HEX_ERR_UNKOWN;
    }
}

