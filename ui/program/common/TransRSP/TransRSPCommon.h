#ifndef TRANSRSPCOMMON_H
#define TRANSRSPCOMMON_H

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 	File name	:	TransRSPL2.h
// 	Brief 		: 	The second layer of RSP communication protocol. This layer has responsibilities
//					of packing / unpacking RSP frame, event processing
//
//	Author 		: 	manhbt
//  Note 		:
/// RSP Protocol Detail: /////////////////////////////////////////////////////////////////////////////
//
//      0       1        2      3      4      5      6       7
//  |-------------------------------------------------------------------------|
//  | Header| ScrADD | DstADD | SEQ | CTRL | DLEN | CRC_D | CRC_H | DATA_0_...|
//  |-------------------------------------------------------------------------|
//	CTRL detail:
//		- bit 7: 	1	- ACK request, 0 - Not ACK request
//		- bit 6-5:	00	- FRM_CMD
//					01	- FRM_DATA
//					10	- FRM_DEBUG
//	    - bit 4-0:	CMD_TYPE, DATA_TYPE, DEBUG_TYPE
//////////////////////////////////////////////////////////////////////////////////////////////////////
// 	MODIFICATION HISTORY:
//
// 	Ver  	Author 		Date       	Changes
// 	----- 	-------- 	---------- 	------------------------------------------------------------------
// 	1.00  	MANHBT  	06-04-2017 	Create Framework
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////// Include Files /////////////////////////////////////////////

#define 	ENABLE_CHECK_DUPLICATED_SEQ_NUMBER		1

///////////////////////////////////// Constant Definitions ///////////////////////////////////////////
#define IS_DATA_FRM(fk)					((fk & RSP_FRM_TYPE_MASK) ? FALSE : TRUE)
#define IS_CMD_FRM(fk)					((fk & RSP_FRM_TYPE_MASK) ? TRUE : FALSE)

#define IS_ACK_FRAME(f)                 (((f & ~RSP_FRM_CTRL_MASK) == RSP_CMD_ACK ) ? TRUE : FALSE)
#define IS_NACK_FRAME(f)                (((f & ~RSP_FRM_CTRL_MASK) == RSP_CMD_NACK ) ? TRUE : FALSE)

#define RETURN_PACKAGE					TRUE	// use for ACK/NACK/NOTDONE frame
#define SEND_PACKAGE					FALSE

#define RSP_ADDR_BROADCAST				0xFFFF
#define RSP_ADDR_PC						0x0001
#define RSP_ADDR_USBCANCONV				0x0002

// Frame structure and macros
#define RSP_FRM_IDX_SOF					0		// Start of Frame - 2 bytes - must be 0x5555 in RSP protocol
#define RSP_FRM_IDX_DLEN				2		// Data_len - 2 bytes
#define RSP_FRM_IDX_FLAGS				4		// Flags - 1 bytes
#define RSP_FRM_IDX_DSTADDR				5		// Dest. Address - 2 bytes
#define RSP_FRM_IDX_SRCADDR				7		// Src. Address - 2 bytes
#define RSP_FRM_IDX_CRCH				9		// CRC-8 of RSP Header
#define RSP_FRM_IDX_DATA0				10		// Data payload - DLEN*sizeof(uint8_t) bytes



#define RSP_SOF_PREAMBLE				0x55
#define RSP_SOF_VALUE					0x5555
#define RSP_FRM_DATA_MAX_SIZE                           0x400	// 1024 bytes max
#define RSP_FRM_HDR_SIZE				10
#define	RSP_FRM_MAX_SIZE				(RSP_FRM_HDR_SIZE + RSP_FRM_DATA_MAX_SIZE + 2)



//#define FORM_CTRL(ACKReq, FrmTpy)		(((ACKReq) ? 0x80 : 0x00) | (FrmTpy & 0x7F))
#define IS_ACK_REQ(flags)				((flags) & RSP_FRM_ACKREQ_MASK ? TRUE : FALSE)
//#define GET_FRM_TYPE(ctrl)				((ctrl) & 0x7F)


#define RSP_FRM_TYPE_MASK				0x80	// Bit 7-6: type cmd or data frame
#define RSP_FRM_TYPE_DATA				0x00	// Bit 7: 0 - Data frame
#define RSP_FRM_TYPE_CMD				0x80	// Bit 7: 1 - Command Frame

#define RSP_FRM_ACKREQ_MASK				0x40	// bit 6: Ack required
#define RSP_FRM_ACKREQ_REQUIRED                         0x40
#define RSP_FRM_ACKREQ_NOT_REQUIRED                     0x00

#define RSP_FRM_CTRL_MASK               (RSP_FRM_TYPE_MASK | RSP_FRM_ACKREQ_MASK)

// Command Control for CMD_FRAME
#define RSP_CMD_NONE					0x00	// None command
#define	RSP_CMD_ACK                     0x01	// ACK command, which returned when a frame is processed successfully
#define RSP_CMD_NACK					0x02	// NACK command, which returned when a frame is processed unsuccessfully

// Command for USB-CAN converter

#define RSP_CMD_USBCAN_SET_CAN_STDID            0x10
#define RSP_CMD_USBCAN_ENABLE_EXTID		0x11
#define RSP_CMD_USBCAN_ENABLE_RTR		0x12
#define RSP_CMD_USBCAN_SET_TX_PARAMS            0x13            // Set StdID, ExtIDEn, RTREn for Can TxMsg

#define RSP_CMD_USBCAN_SET_CAN_PARAMS           0x14            // Set CAN Bus baudrate, support 6 mode: 100k, 200k, 250k, 300k, 400k, 500k, 1M

#define TRANSL2_WAITACK_TIMEOUT_TICK            200		// Time out for waiting ACK
#define TRANSL2_RESEND_NUMBER			4		// The number of resending when a frame didn't get ACK

#define TRANSL2_REQ_BUS_TIMEOUT_TICK            10		// Time out for requesting Master to use bus
#define TRANSL2_REQUEST_BUS_NUMBER		50		// The number of request bus if master doesn't allow slave to use bus

#define	RSP_TX_FRAME_LIST_MAX_SIZE		16		// Maximum size of link list of send frames



/////////////////////////////////////// Type Definitions /////////////////////////////////////////////

typedef enum _eCANBaudrate
{
    RSP_CAN_BAUD_100k = 0,
    RSP_CAN_BAUD_200k,
    RSP_CAN_BAUD_250k,
    RSP_CAN_BAUD_300k,
    RSP_CAN_BAUD_400k,
    RSP_CAN_BAUD_500k,
    RSP_CAN_BAUD_1M
} CANBaudTypedef;


#pragma pack(1)
typedef struct _S_TransRSPFrame{
    uint16_t    u16Preamble;
    uint16_t    u16Dlen;
    uint8_t     u8Flags;
    uint16_t    u16DstAddr;
    uint16_t    u16SrcAddr;
    uint8_t     u8CRC_H;
    uint8_t     u8CRC_D;
//    uint8_t*    pu8DataPayload;
} TransRSPFrame;


///////////////////////////// Macros (Inline Functions) Definitions //////////////////////////////////
//#define ntoh16(p) ((*(p+1)<<8) + *(p))
//#define ntoh32(p)   ((*(p+3)<<24) + *(p+2)<<16 + *(p+1)<<8 + *(p))
//uint16_t hton16(uint16_t val){
//    return ((val & (uint16_t)0xFF00) >> 8) | ((val & (uint16_t)0x00FF) << 8);
//}

//uint16_t ntoh16(uint16_t val){
//    return ((val & (uint16_t)0xFF00) >> 8) | ((val & (uint16_t)0x00FF) << 8);
//}
///////////////////////////////////// Function Prototypes ////////////////////////////////////////////

///////////////////////////////////// Variable Definitions ///////////////////////////////////////////

///////////////////////////////////// Function implements ////////////////////////////////////////////

///////////////////////////////////// Class declaration ////////////////////////////////////////////




#ifdef __cplusplus
}
#endif

#endif // TRANSRSPCOMMON_H
