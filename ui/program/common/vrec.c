#include "vrec.h"
#include "convert.h"

#define TWO_COMPLEMENT(u8Value) ((~(u8Value)) + 1)

#define BUFFER_TYPE_BIN             0
#define BUFFER_TYPE_HEX_CHAR        1

char   VREC_CommError[][9] =
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

//static INLINE
uint8_t     VREC_CalculateCRC       (const uint8_t  *pBuffer,
                                     size_t         szBytesCount,
                                     uint8_t        u8IsHexChar)
{
    size_t  szCnt;
    uint8_t u8XCode = 0;

    /* Buffer is in binary form */
    if (u8IsHexChar == BUFFER_TYPE_BIN)
    {
        for (szCnt = 0; szCnt < szBytesCount; ++szCnt)
        {
            u8XCode ^= CalculateByteCRC4(pBuffer[szCnt]);

        }
    }
    /* Buffer is in hexadecimal character form */
    else
    {

        for (szCnt = 0; szCnt < szBytesCount; ++szCnt)
        {
            u8XCode ^= CRC4_TABLE[HEX2DEC(pBuffer[szCnt])];
        }
    }
    return u8XCode;
}


void        VREC_DecodeData         (const uint8_t  *pu8Src,
                                     uint8_t        *pu8Dst,
                                     size_t         szLen)
{
    size_t      szCnt;
    for (szCnt = 0; szCnt < szLen; szCnt++)
    {
        pu8Dst[szCnt]   = (HEX2DEC(pu8Src[0])<<4) | HEX2DEC(pu8Src[1]);
        pu8Src         += 2;
    }
    return;
}

uint8_t     VREC_Decode             (const uint8_t  *pVrec,
                                     S_VREC_INFO    *pVrecInfo,
                                     uint32_t         *pszCount,
                                     uint8_t        u8ImageType)
{
    uint8_t     u8CheckSum  = 0;
    uint8_t     u8Temp      = 0;

#if (VREC_ENABLE_ARGUMENT_CHECKING > 0)   /* dev-time error */
    ////printf("\nAllo1\n");
    if ((pVrec      == (uint8_t*)0) ||
        (pVrecInfo  == (S_VREC_INFO*)0) ||
        (pszCount   == (uint32_t*) 0))
    {
        return VREC_ERR_INVALID_PARAMETER;
    }

    if (pVrecInfo->pu8Data == (uint8_t*)0)
    {
        return 0;
    }

    if (pVrec[VREC_PREAMBLE_IDX] != VREC_PREAMBLE)
    {
        return  VREC_ERR_INVALID_FORMAT;
    }
    pVrecInfo->u8Preamble = pVrec[VREC_PREAMBLE_IDX];
#endif
    pVrecInfo->u8DataLength = HexCharToU8(&pVrec[VREC_LENGTH_IDX]);
    u8CheckSum              = HexCharToU8(&pVrec[VREC_DATA_IDX + pVrecInfo->u8DataLength*2]);
//    printf("u8DataLength = %d, u8CheckSum = 0x%2X; = %d\n",pVrecInfo->u8DataLength, u8CheckSum, u8CheckSum);
    pVrecInfo->u8Type       = pVrec[VREC_TYPE_IDX];

    switch (pVrec[VREC_TYPE_IDX])
    {
        case VREC_TYPE_FILE_INFO:
        	////printf("VREC_TYPE_FILE_INFO\n");
            pVrecInfo->sAddress.Value   = HexCharToU16(&pVrec[VREC_DATA_IDX]);    /* ID of Device */
            //pVrecInfo->sAddress.U8[0] = HexCharToU8(&pVrec[VREC_LENGTH_IDX]);
            /* TODO! Store other data here. */

            *pszCount   = 0;
            return VREC_ERR_NONE;
        case VREC_TYPE_FILE_MAP:
        	////printf("VREC_TYPE_FILE_MAP\n");
            pVrecInfo->sAddress.U8[0] = HexCharToU8(&pVrec[VREC_DEV_ID_IDX]);
            pVrecInfo->sAddress.U16[0] = HexCharToU16(&pVrec[VREC_PROG_ID_IDX]);
        	*pszCount = 0;
        	return VREC_ERR_NONE;

        case VREC_TYPE_HEADER:      /* File header */
        	////printf("VREC_TYPE_HEADER\n");
            pVrecInfo->sAddress.Value   = HexCharToU16(&pVrec[VREC_DATA_IDX]);    /* ID of module */

            /* Stored data if Image type is VREC_PACKAGE_FORMAT */
            if (u8ImageType == VREC_PACKAGE_FORMAT)
            {
                pVrecInfo->pu8Data[0]               = pVrec[0];
                pVrecInfo->pu8Data[1]               = pVrec[1];
                pVrecInfo->pu8Data[2]               = pVrecInfo->u8DataLength;
                pVrecInfo->pu8Data[3+pVrecInfo->u8DataLength]   = u8CheckSum;

                VREC_DecodeData(&pVrec[3],
                                &pVrecInfo->pu8Data[3],
                                (size_t)pVrecInfo->u8DataLength);
                ////printf("HEADER A\n");
                *pszCount = (uint32_t)pVrecInfo->u8DataLength + 4;
            }
            else
            {
                *pszCount   = 0;
                //printf("HEADER B\n");
            }
            return VREC_ERR_NONE;


#if (VREC_ENABLE_PARAM_TEST > 0)
        case VREC_TYPE_PARAM_TEST:
        {
            printf("fuck you");
            pVrecInfo->sAddress.Value   =          HexCharToU16(&pVrec[VREC_DATA_IDX]);    /* 16-bit address */

            /* Store the record in VREC-BIN format */
            VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                            &pVrecInfo->pu8Data[0],
                            (size_t)pVrecInfo->u8DataLength);

            *pszCount = (size_t)pVrecInfo->u8DataLength;

            return VREC_ERR_NONE;
        }
#endif //VREC_ENABLE_PARAM_TEST

#if (VREC_ENABLE_MODEL_INFO > 0)
        case VREC_TYPE_MODEL:
        {

            pVrecInfo->sAddress.Value   =          HexCharToU16(&pVrec[VREC_DATA_IDX]);    /* 16-bit address */

            /* Store the record in VREC-BIN format */
            VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                            &pVrecInfo->pu8Data[0],
                            (size_t)pVrecInfo->u8DataLength);

            *pszCount = (size_t)pVrecInfo->u8DataLength;

            return VREC_ERR_NONE;
        }
#endif //VREC_ENABLE_PARAM_TEST

        case VREC_TYPE_FILE_DATA16: /* Program data 16 bit */
        	//printf("TYPE_FILE_DATA16\n");
            pVrecInfo->sAddress.Value   = HexCharToU16(&pVrec[VREC_DATA_IDX]);    /* 16-bit address */

            if (u8ImageType == VREC_PACKAGE_FORMAT)
            {
                /* Store the record in VREC-BIN format */
                pVrecInfo->pu8Data[0]               = pVrec[VREC_PREAMBLE_IDX];
                pVrecInfo->pu8Data[1]               = pVrec[VREC_TYPE_IDX];
                pVrecInfo->pu8Data[2]               = pVrecInfo->u8DataLength;
                pVrecInfo->pu8Data[3+pVrecInfo->u8DataLength]   = u8CheckSum;

                VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                                &pVrecInfo->pu8Data[4],
                                (size_t)pVrecInfo->u8DataLength);

                *pszCount = (uint32_t)pVrecInfo->u8DataLength + 4;
            }
            else
            {
                /* Store program data only */
                VREC_DecodeData(&pVrec[VREC_DATA_IDX + 4],         /* Program data offset of 4 */
                                 pVrecInfo->pu8Data,
                                 (size_t)(pVrecInfo->u8DataLength - 2));

                *pszCount       = (uint32_t)(pVrecInfo->u8DataLength - 2);
            }
            return VREC_ERR_NONE;

        case VREC_TYPE_FILE_DATA24: /* Program data 24 bit */
        	//printf("VREC_TYPE_FILE_DATA24\n");
            pVrecInfo->sAddress.Value   = HexCharToU24(&pVrec[4]);    /* 24-bit address */

            if (u8ImageType == VREC_PACKAGE_FORMAT)
            {
                /* Store the record in VREC-BIN format */
                pVrecInfo->pu8Data[0]               = pVrec[VREC_PREAMBLE_IDX];
                pVrecInfo->pu8Data[1]               = pVrec[VREC_TYPE_IDX];
                pVrecInfo->pu8Data[2]               = pVrecInfo->u8DataLength;
                pVrecInfo->pu8Data[3+pVrecInfo->u8DataLength]   = u8CheckSum;

                VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                                &pVrecInfo->pu8Data[4],
                                (size_t)pVrecInfo->u8DataLength);

                *pszCount = (uint32_t)pVrecInfo->u8DataLength + 4;
            }
            else
            {
                /* Store program data only */
                VREC_DecodeData(&pVrec[VREC_DATA_IDX + 6],         /* Program data offset of 6 */
                                pVrecInfo->pu8Data,
                                (size_t)(pVrecInfo->u8DataLength - 3));

                *pszCount       = (uint32_t)(pVrecInfo->u8DataLength - 3);
            }

            return VREC_ERR_NONE;

        case VREC_TYPE_FILE_DATA32: /* Program data 32 bit */
        	//printf("VREC_TYPE_FILE_DATA32\n");
            pVrecInfo->sAddress.Value   = HexCharToU32(&pVrec[4]);    /* 24-bit address */

            if (u8ImageType == VREC_PACKAGE_FORMAT)
            {
                /* Store the record in VREC-BIN format */
                pVrecInfo->pu8Data[0]               = pVrec[VREC_PREAMBLE_IDX];
                pVrecInfo->pu8Data[1]               = pVrec[VREC_TYPE_IDX];
                pVrecInfo->pu8Data[2]               = pVrecInfo->u8DataLength;
                pVrecInfo->pu8Data[3+pVrecInfo->u8DataLength]   = u8CheckSum;

                VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                                &pVrecInfo->pu8Data[3],
                                (size_t)pVrecInfo->u8DataLength);

                *pszCount  = (uint32_t)pVrecInfo->u8DataLength + 4;
            }
            else
            {
                /* Store program data only */
                VREC_DecodeData(&pVrec[VREC_DATA_IDX + 8],
                                pVrecInfo->pu8Data,
                                (size_t)(pVrecInfo->u8DataLength - 4));

                *pszCount       = (uint32_t)(pVrecInfo->u8DataLength - 4);
            }
            return VREC_ERR_NONE;

        case VREC_TYPE_END_PROGRAM16:
        case VREC_TYPE_END_PROGRAM24:       /* End of program 24 bit */
        case VREC_TYPE_END_PROGRAM32:
        	//printf("VREC_TYPE_END_PROGRAM\n");
            pVrecInfo->sAddress.Value   = HexCharToU24(&pVrec[4]);    /* 24-bit address */
            if (u8ImageType == VREC_PACKAGE_FORMAT)
            {
                /* Store the record in VREC-BIN format */
                pVrecInfo->pu8Data[0]               = pVrec[VREC_PREAMBLE_IDX];
                pVrecInfo->pu8Data[1]               = pVrec[VREC_TYPE_IDX];
                pVrecInfo->pu8Data[2]               = pVrecInfo->u8DataLength;
                pVrecInfo->pu8Data[3+pVrecInfo->u8DataLength]   = u8CheckSum;

                VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                                &pVrecInfo->pu8Data[3],
                                (size_t)pVrecInfo->u8DataLength);

                *pszCount  = (uint32_t)pVrecInfo->u8DataLength + 4;

                return VREC_ERR_NONE;
            }
            else
            {
                /* Store program data only */
            	//printf("Store program data only\n");
                VREC_DecodeData(&pVrec[VREC_DATA_IDX],
                                pVrecInfo->pu8Data,
                                (size_t)pVrecInfo->u8DataLength);

                *pszCount       = (uint32_t)(pVrecInfo->u8DataLength-4);

                return VREC_ERR_NONE;
            }
            break;

        case VREC_TYPE_END_OF_FILE:
        	*pszCount = 0;
            return VREC_ERR_NONE;

        default:
        	*pszCount = 0;
            return VREC_ERR_INVALID_FORMAT;
    }
    //printf("\nAllo3\n");

    return VREC_ERR_UNKOWN;
}

