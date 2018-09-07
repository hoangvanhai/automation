#ifndef TESTCONFIG_H
#define TESTCONFIG_H

#include <string>
#include <stdint.h>
#include <vector>

/* COMMON */
#define CONFIG_FILE_NAME                   "config.xml"
#define DEFAULT_INSTR_IP                   "192.168.1.11"
#define DEFAULT_INSTR_PORT                 5025

#define DEFAULT_SPECT_IP                   "192.168.1.12"
#define DEFAULT_SPECT_PORT                 5026

#define DEFAULT_SERVER_IP                   "192.168.1.2"
#define DEFAULT_SERVER_PORT                 12348
#define DEFAULT_SERVER_UDP_PORT             12399

#define DEFAULT_LOCAL_IP                    "192.168.1.99"

#define STATUS_IN_COLUM                    1
#define VALUE_IN_COLUM                     2


/* TEST IFRF CONFIG SECTION */
#define IFRF_STR_TEST_SENSITIVE            std::string("Do nhay phat hien tin hieu (dBm)")
#define IFRF_STR_TEST_IP3                  std::string("Meo hai bac ba (dBm)")
#define IFRF_STR_TEST_P1dB                 std::string("INPUT P1dB (dBm)")
#define IFRF_STR_TEST_DO_CL_ANH            std::string("Do chon loc anh (dB)")
#define IFRF_STR_TEST_CL_F_M               std::string("Do chon loc trung tan (dB)")
#define IFRF_STR_TEST_DYN_LINEAR           std::string("Dai dong tuyen tinh (dB)")
#define IFRF_STR_TEST_BW_SIG_F_M           std::string("Bang thong tin hieu trung tan (MHz)")
#define IFRF_STR_TEST_SPUR                 std::string("Spurious all")
#define IFRF_STR_TEST_IMD_IN_RANGE         std::string("IMD trong bang (dB)")
#define IFRF_STR_TEST_IMD_OUT_RANGE        std::string("IMD ngoai bang (dB)")
#define IFRF_STR_TEST_OP_RANGE_JAM         std::string("Dai hoat dong khi bi che ap (dB)")
#define IFRF_STR_TEST_PWR_CONSUM           std::string("Cong suat tieu thu (W)")


#define CONFIG_TEST_TRACK_IFRF             "ifrfdatabase.dat"

#define FILENAME_RES_IFRF                   "BBKT_CTKT_VSI3_IFRF"
#define TEMPLATE_IFRF_THUONG                "BBKT_CTKT_VSI3_IFRF_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_IFRF_THUNGHIEM             "BBKT_CTKT_VSI3_IFRF_TEMPLATE_THUNGHIEM.xlsx"

/* TEST FPTA CONFIG SECTION */
#define FPGA_TEST_EHTERNET_10G_23           std::string("GIAO TIEP ETHERNET 10G")
#define FPGA_TEST_PS_RAM                    std::string("PL RAM")
#define FPGA_TEST_PL_RAM                    std::string("PS RAM")
#define FPGA_TEST_ADC                       std::string("ADC")
#define FPGA_TEST_SSD_1                     std::string("SSD SLOT 1")
#define FPGA_TEST_SSD_2                     std::string("SSD SLOT 2")
#define FPGA_TEST_SSD_3                     std::string("SSD SLOT 3")
#define FPGA_TEST_SSD_4                     std::string("SSD SLOT 4")
#define FPGA_TEST_IFRF_1                    std::string("IFRF INTERFACE 1")
#define FPGA_TEST_IFRF_2                    std::string("IFRF INTERFACE 2")
#define FPGA_TEST_GPSDO                     std::string("GPSDO INTERFACE")
#define FPGA_TEST_EXTEN                     std::string("EXTEN INTERFACE")
#define FPGA_TEST_FLASH                     std::string("FLASH IC")

#define CONFIG_TEST_TRACK_FPGA             "fpgadatabase.dat"
#define FILENAME_RES_FPGA                  "BBKT_CTKT_VSI3_FPGA"
#define TEMPLATE_FPGA_THUONG               "BBKT_CTKT_VSI3_FPGA_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_FPGA_THUNGHIEM            "BBKT_CTKT_VSI3_FPGA_TEMPLATE_THUNGHIEM.xlsx"


/* TEST GPSDO CONFIG SECTION */
#define GPSDO_TEST_PPS                      std::string("TEST_PPS")
#define GPSDO_TEST_MESSAGE                  std::string("TEST_MESSAGE")
#define GPSDO_TEST_10M_OUT                  std::string("TEST_10M_OUT")


#define CONFIG_TEST_TRACK_GPSDO             "gpsdodatabase.dat"
#define FILENAME_RES_GPSDO                  "BBKT_CTKT_VSI3_GPSDO"
#define TEMPLATE_GPSDO_THUONG               "BBKT_CTKT_VSI3_GPSDO_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_GPSDO_THUNGHIEM            "BBKT_CTKT_VSI3_GPSDO_TEMPLATE_THUNGHIEM.xlsx"


/* TEST CTRLPT CONFIG SECTION */
#define CTRLPT_TEST_PAN                      std::string("GIAO TIEP ETHERNET 10G")
#define CTRLPT_TEST_TILT                     std::string("PL RAM")
#define CTRLPT_TEST_RS485                    std::string("PS RAM")

#define CONFIG_TEST_TRACK_CTRLPT             "ctrlptdatabase.dat"
#define FILENAME_RES_CTRLPT                  "BBKT_CTKT_VSI3_CTRLPT"
#define TEMPLATE_CTRLPT_THUONG               "BBKT_CTKT_VSI3_CTRLPT_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_CTRLPT_THUNGHIEM            "BBKT_CTKT_VSI3_CTRLPT_TEMPLATE_THUNGHIEM.xlsx"



/* TEST SENSOR CONFIG SECTION */
#define SENSOR_STR_TEST_CURRENT             std::string("Dong_tieu_thu_(A)")
#define SENSOR_STR_TEST_SENSITIVE           std::string("Do_nhay_phat_hien_tin_hieu_(dBm)")
#define SENSOR_STR_TEST_ERR_PWR             std::string("Sai_so_do_cong_suat_(dBm)")
#define SENSOR_STR_TEST_ERR_BW_25KH         std::string("Sai_so_do_bang_thong_25k+_(%)")
#define SENSOR_STR_TEST_ERR_BW_25KL         std::string("Sai_so_do_bang_thong_25k-_(Hz)")
#define SENSOR_STR_TEST_ERR_FREQ            std::string("Sai_so_do_tan_so_(Hz)")
#define SENSOR_STR_TEST_THIRD_INTP          std::string("Meo_hai_bac_ba_(dBm)")

#define CONFIG_TEST_TRACK_SENSOR            "sensordatabase.dat"

#define FILENAME_RES_SENSOR                 "BBKT_CTKT_VSI3_SENSOR"
#define TEMPLATE_SENSOR_THUONG              "BBKT_CTKT_VSI3_SENSOR_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_SENSOR_THUNGHIEM           "BBKT_CTKT_VSI3_SENSOR_TEMPLATE_THUNGHIEM.xlsx"

#define FILENAME_RES_SYSTEM                 "BBKT_CTKT_VSI3_SYSTEM"
#define TEMPLATE_SYSTEM_THUONG              "BBKT_CTKT_VSI3_SENSOR_TEMPLATE_THUONG.xlsx"
#define TEMPLATE_SYSTEM_THUNGHIEM           "BBKT_CTKT_VSI3_SENSOR_TEMPLATE_THUNGHIEM.xlsx"


/* CALIB SENSOR CONFIG SECTION */
#define CALIB_STR_TEST_1                    std::string("Power1")
#define CALIB_STR_TEST_2                    std::string("Power2")
#define CALIB_STR_TEST_3                    std::string("Power3")



/* TEST SYSTEM CONFIG SECTION */
#define SYSTEM_STR_TEST_TDOA                std::string("TU DONG TDOA")
#define CONFIG_TEST_TRACK_SYSTEM            "systemdatabase.dat"


#define VSI3_FREQ_MAX                       3000000000  //3Ghz
#define VSI3_FREQ_MIN                       20000000    //20Mhz

#define NO_INSTRUMENT                       0

enum InstrMsgType{
    INSTR_SET_Freq_Hz,
    INSTR_SET_Freq_Khz,
    INSTR_SET_Freq_Mhz,
    INSTR_SET_PWR,
};

enum Banwidth {
    BW_10_MHZ   =   10000000,
    BW_20_MHZ   =   20000000,
    BW_30_MHZ   =   30000000,
    BW_40_MHZ   =   40000000,
};



enum PowerUnit {
    Power_dBm = 0,
    Power_MV,
    Power_UV,
    Power_Wat,
};

enum FrequencyUnit {
    Freq_Hz = 0,
    Freq_Khz,
    Freq_Mhz,
};

enum CommandStatus {
    Cmd_Wait_None = 0,
    Cmd_Wait_Rf_Pwr,
};

enum MeasurementMode {
    Mode_Single = 0,
    Mose_Couple,
};

enum SearchDirection {
    SearchDirection_Left = 0,
    SearchDirection_Right,
    SearchDirection_None,
};


enum MarkerValueType {
    MarkerValueType_Level = 0,
    MarkerValueType_dBm,
};

enum ModeView {
    ModeView_MinHold = 0,
    ModeView_MaxHold,
    ModeView_ClearWrite,
};

enum SigGenType {
    SigGen_Agilent_5182 = 0,
    SigGen_Aeroflex_2023,
};

enum SpectrumType {
    Spect_RohdeSchwarz_FSV = 0,
    Spect_Aeroflex_Type1,
};

enum PowerType {
    Power_Agilent_Type1 = 0,
    Power_Aeroflex_Type1,
};


typedef struct {
    uint64_t point;
    float value;
}FreqPoint;

enum CalibMode{
    Calib_Mode_Normal = 0,
    Calib_Mode_Hot,
    Calib_Mode_Cool,
};

enum ServerOperationMode {
    Server_Normal = 0,
    Server_Calibration,
    Server_Test,
};

///* Frame format
// *
//   Idx:           0             1     2      3      4           5            6     7                        7+DLEN
//        ----------------------------------------------------------------------------------------------------------
//        | Automation_Config | len0 | len1 | len2 | len3 | Sensor_Command | DLEN | DATA[0] ... DATA[DLEN-1] | CRCD |
//        ----------------------------------------------------------------------------------------------------------
//                                                                                | Sensor_Type_List |
//                                                                                | Sensor_Result    |
//                                                                                | IpAddress:ip-port|
//                                                                                                        CRCD check from DATA[0]-DATA[7+DLEN]
// *

enum Automation_Config {
    Auto_Reset_Sensor = 13,
    Auto_Debug_Sensor = 14,
    Auto_Config_Sensor = 15,
};

enum Sensor_Command {
    Command_Write_Type = 1,
    Command_Read_Type,
    Command_Write_Ip,
    Command_Read_Ip,
    Command_Write_Fpga_Serial,
    Command_Read_Fpga_Serial,
    Command_Write_Ifrf_Serial,
    Command_Read_Ifrf_Serial,
    Command_Test_Ethernet_23_10G,
    Command_Test_Ps_Ram,
    Command_Test_Pl_Ram,
    Command_Test_ADC,
    Command_Test_SSD_1,
    Command_Test_SSD_2,
    Command_Test_SSD_3,
    Command_Test_SSD_4,
    Command_Test_Ifrf_1,
    Command_Test_Ifrf_2,
    Command_Test_GpsDo_Interface,
    Command_Test_Exten_Interface,
    Command_Test_Flash,
    Command_Test_Max,
};

enum Sensor_Type_List {
    Sensor_Local = 0,
    Sensor_Remote_1,
    Sensor_Remote_2,
    Sensor_Remote_3,
};

enum Sensor_Result {
    Sensor_Failed = 0,
    Sensor_Passed,
};

struct IpAddress {
    union {
        uint32_t ipValue;
        uint8_t  ipByte[4];
    }ip;
    union {
        uint16_t portValue;
        uint8_t  portByte[2];
    }port;
};


enum Gpsdo_Command{
    Gpsdo_Set_Param = 1,
    Gpsdo_Test_Message,
    Gpsdo_Test_PPS,
    Gpsdo_Test_10Mhz,
    Gpsdo_Write_Serial,
    Gpsdo_Read_Serial,
    Gpsdo_Cmd_Max,
};



enum PanTilt_Command{
    Pantilt_Set_Param = 1,
    Pantilt_Test_Pan,
    Pantilt_Test_Tilt,
    Pantilt_Test_Rs485,
    Pantilt_Write_Serial,
    Pantilt_Read_Serial,
    Pantilt_Cmd_Max,
};


#endif // TESTCONFIG_H
