#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#define   MONITOR_ID						                         0x00
#define   PC_ID                                                      0x01
#define   IFRF_ID							                         0x02
#define   RFDELAY_ID							                     0x02
#define   JIG_GPSDO_ID                                               0x03
#define   JIG_PANTILT_ID                                             0x04


#define   CMD_FRAME						                             0x00
#define   DATA_FRAME						                         0x20
#define   DEBUG_FRAME						                         0x40

#define MODE_APP_NORMAL                 0x00
#define MODE_APP_SUPPORT                0xFF


#define MASTER_REQ_CONNECT              0x01
#define MASTER_SET_FREQ                 0x02
#define MASTER_SET_ATTEN                0x03
#define MASTER_RESET_FOR_BOOTLOADER     0x04
#define MASTER_RESET_IFRF_BOARD         0x05
#define MASTER_GET_WORKING_STATE        0x06
#define MASTER_RESET_WORKING_STATE      0x07
#define MASTER_DEBUG_EN                 0x08
#define MASTER_SAVE_FREQ_PARAM          0x09
#define MASTER_LOAD_FREQ_PARAM          0x0A
#define MASTER_SAVE_POWER_PARAM         0x0B
#define MASTER_LOAD_POWER_PARAM         0x0C


//
#define   TESTPOINT_DATA_LENGTH                                     8
#define   TESTPOINT_MESSAGE_LENGTH                                  10





#define RFDL_SET_FREQ                   0x01
#define RFDL_SET_DELAY_1                0x02
#define RFDL_SET_DELAY_2                0x03
#define RFDL_SET_DELAY_3                0x04


enum {
    Spect_Clear_All = 0,
    Spect_Get_Center_Freq           = 0x0001,
    Spect_Get_ValueAt_Marker        = 0x0002,
    Spect_Get_Harmonic_Distorion    = 0x0004,
    Spect_Get_Spurious              = 0x0008,
    Spect_Mark_All = 0xFFFF,
};


#endif // DEVICECONTROL_H

