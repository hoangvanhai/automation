#ifndef ISCCONFIG_H
#define ISCCONFIG_H


namespace commnuication {
namespace isc {
#define DEFAULT_SIZE_RECV_BUF		4096

#if defined (__linux__)
#define DEFAULT_PORT_NAME   "/dev/ttyUSB0"
#else
#define DEFAULT_PORT_NAME   "COM1"
#endif


#define DEFAULT_BAUDRATE    115200




#define FORM_CTRL(ACKReq,FrmTpy)                (((ACKReq) ? 0x80 : 0x00) | (FrmTpy & 0x1F))
#define IS_ACK_REQ(ctrl)                        ((ctrl) & 0x80 ? true : false)
#define IS_CRCD_REQ(ctrl)                       ((ctrl) & 0x40 ? true : false)
#define GET_FRM_TYPE(ctrl)                      ((ctrl) & 0x1F)
#define CLEAR_ACK_REQ_BIT(ctrl)                 ((ctrl) & 0x7F)
#define GET_CTRL(ctrl)                          ((ctrl) & 0x3F)

#define SET_CRCD_REQ_BIT(ctrl)                  ((ctrl) |= 0x40)
#define CLR_CRCD_REQ_BIT(ctrl)                  ((ctrl) &= 0xBF)

#define MASK_DATA                               0x20
#define CMD_NONE                                0x00
#define	CMD_ACK                                 0x01
#define CMD_NACK                                0x02
#define CMD_SLV_SEND_EN                         0x03	//only for IBC
#define CMD_NOTDONE                             0x04
#define CMD_ERROR                               0x05

#define FRM_DATA                                0x20
#define FRM_CMD                                 0x00
#define ACK_REQ                                 0x80

#define IS_DATA_FRM(fk)				(((fk) & MASK_DATA) ? true : false)
#define IS_CMD_FRM(fk)				(((fk) & MASK_DATA) ? false : true)

#define ADDR_BROADCAST				0xFF

#define MAX_NUM_SEND				(3)

#define TRANS_TIMEOUT_TICK			(100L)	//in mili-ten second

#define	CST_PREAMBLE				'!'
#define	CST_TERMINATE				'#'

// Byte Index
#define IDX_SFRM_PREAM				0
#define IDX_SFRM_SRCADR				1
#define IDX_SFRM_DSTADR				2
#define IDX_SFRM_SEQNUM				3
#define IDX_SFRM_CTRL				4

#define IDX_SFRM_DLEN				5
#define IDX_SFRM_CRCD				6
#define IDX_SFRM_CRCH				7
#define IDX_SFRM_DATA0				8

#define SFRM_MAX_DLEN				(240)   //Max. Val = 256
#define SFRM_HDR_SIZE				8
#define SFRM_MAX_SIZE                           (SFRM_MAX_DLEN + SFRM_HDR_SIZE)
#define SFRAME_GET_DLEN(frm)                    ((frm)[IDX_SFRM_DLEN])
#define SFRAME_SIZE(frm)                        (SFRAME_GET_DLEN(frm) + SFRM_HDR_SIZE)

#define SFRAME_SET_DLEN(frm,val)                ((frm)[IDX_SFRM_DLEN] = val)

#define SFRAME_GET_SRCADR(frm)                  ((frm)[IDX_SFRM_SRCADR])
#define SFRAME_GET_DSTADR(frm)                  ((frm)[IDX_SFRM_DSTADR])
#define SFRAME_GET_SEQ(frm)                     ((frm)[IDX_SFRM_SEQNUM])
#define SFRAME_GET_CTRL(frm)                    ((frm)[IDX_SFRM_CTRL])
#define SFRAME_GET_CRCD(frm)                    ((frm)[IDX_SFRM_CRCD])
#define SFRAME_GET_CRCH(frm)                    ((frm)[IDX_SFRM_CRCH])

#define SFRAME_GET_DATAPTR(frm)                 (&(frm)[IDX_FRM_DATA0])

#define SFRAME_SET_SRCADR(frm,val)              ((frm)[IDX_SFRM_SRCADR] = val)
#define SFRAME_SET_DSTADR(frm,val)              ((frm)[IDX_SFRM_DSTADR] = val)
#define SFRAME_SET_SEQ(frm,val)                 ((frm)[IDX_SFRM_SEQNUM] = val)
#define SFRAME_SET_CTRL(frm,val)                ((frm)[IDX_SFRM_CTRL]   = val)
#define SFRAME_SET_CRCD(frm,val)                ((frm)[IDX_SFRM_CRCD]   = val)
#define SFRAME_SET_CRCH(frm,val)                ((frm)[IDX_SFRM_CRCH]   = val)


/*---------------------------------------------------------------------------*/
/*Memory Pool for Trans Module*/

#define TOTAL_NUMBER_OF_LARGE_MEMS                      (20)
#define TOTAL_NUMBER_OF_SMALL_MEMS                      (10)

/*NOTE MEM_SIZE must be a event number*/
#define LARGE_FRAME_SIZE                                (SFRM_MAX_SIZE)

#define LARGE_MEM_SIZE                                  ((sizeof(SFrameInfo)) + LARGE_FRAME_SIZE)

#define SMALL_FRAME_SIZE                                (64)//(32)
#define SMALL_MEM_SIZE                                  ((sizeof(SFrameInfo)) + SMALL_FRAME_SIZE)

#define TOTAL_NUMBER_OF_MEMS                            (TOTAL_NUMBER_OF_LARGE_MEMS + TOTAL_NUMBER_OF_SMALL_MEMS)

#define CALCULATE_MEM_SIZE(DataSize)                    ((sizeof(SFrameInfo)) + (DataSize))



#define ISCL3_UPDATE_TIMER_RATE_MS		(10)    //10ms

#define ISCL3_TIMEOUT_TICK				(10)	//in mili-ten second
#define ISCL3_MAX_NUM_SEND				(4)

#define ISCL3_MAX_DLEN					(240)

class IscConfig
{
public:
    IscConfig();
};
}
}
#endif // ISCCONFIG_H
