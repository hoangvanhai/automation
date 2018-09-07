#ifndef DATAFLOWEXTRACT_H
#define DATAFLOWEXTRACT_H

#include <stdint.h>

#define SPECT_SIZE_ID                           1
#define SPECT_SIZE_FLAG                         1
#define SPECT_SIZE_ACTION                       1
#define SPECT_SIZE_FREQ_MIN                     5
#define SPECT_SIZE_FREQ_MAX                     5
#define SPECT_SIZE_FREQ_SMPCNT                  2
#define SPECT_SIZE_FREQ_IDX                     1
#define SPECT_SIZE_TIMESTAMP                    8
#define SPECT_SIZE_ATTR_EN                      2


#define SPECT_IDX_ID                            0
#define SPECT_IDX_FLAG                          (SPECT_IDX_ID +         SPECT_SIZE_ID)
#define SPECT_IDX_ACTION                        (SPECT_IDX_FLAG +       SPECT_SIZE_FLAG)
#define SPECT_IDX_FREQ_MIN                      (SPECT_IDX_ACTION +     SPECT_SIZE_ACTION)
#define SPECT_IDX_FREQ_MAX                      (SPECT_IDX_FREQ_MIN +   SPECT_SIZE_FREQ_MIN)
#define SPECT_IDX_FREQ_SMPCNT                   (SPECT_IDX_FREQ_MAX +   SPECT_SIZE_FREQ_MAX)
#define SPECT_IDX_FREQ_IDX                      (SPECT_IDX_FREQ_SMPCNT+ SPECT_SIZE_FREQ_SMPCNT)
#define SPECT_IDX_TIMESTAMP                     (SPECT_IDX_FREQ_IDX +   SPECT_SIZE_FREQ_IDX)
#define SPECT_IDX_ATTR_EN                       (SPECT_IDX_TIMESTAMP +  SPECT_SIZE_TIMESTAMP)
#define SPECT_IDX_DATA                          (SPECT_IDX_ATTR_EN +    SPECT_SIZE_ATTR_EN)


#define SIGNAL_SIZE_ID                          1
#define SIGNAL_SIZE_FLAGS                       1
#define SIGNAL_SIZE_SIG_CNT                     2
#define SIGNAL_SIZE_DATA                        2


#define SIGNAL_IDX_ID                           0
#define SIGNAL_IDX_FLAGS                        (SIGNAL_IDX_ID +        SIGNAL_SIZE_ID)
#define SIGNAL_IDX_SIG_CNT                      (SIGNAL_IDX_FLAGS +     SIGNAL_SIZE_FLAGS)
#define SIGNAL_IDX_DATA                         (SIGNAL_IDX_SIG_CNT +   SIGNAL_SIZE_SIG_CNT)

#define SIGDAT_SIZE_SIG_ID                      8
#define SIGDAT_SIZE_AUTO_ID                     8
#define SIGDAT_SIZE_PROPERTIES                  8
#define SIGDAT_SIZE_FREQ                        8
#define SIGDAT_SIZE_BANDWIDTH                   4
#define SIGDAT_SIZE_TIME_STAMP                  8
#define SIGDAT_SIZE_DURATION                    8
#define SIGDAT_SIZE_POWER                       4
#define SIGDAT_SIZE_LONGITUDE                   8
#define SIGDAT_SIZE_LATITUDE                    8
#define SIGDAT_SIZE_MODE_SCH                    2


#define SIGDAT_IDX_SIG_ID                       0
#define SIGDAT_IDX_AUTO_ID                      (SIGDAT_IDX_SIG_ID +        SIGDAT_SIZE_SIG_ID)
#define SIGDAT_IDX_PROPERTIES                   (SIGDAT_IDX_AUTO_ID +       SIGDAT_SIZE_AUTO_ID)
#define SIGDAT_IDX_FREQ                         (SIGDAT_IDX_PROPERTIES +    SIGDAT_SIZE_PROPERTIES)
#define SIGDAT_IDX_BANDWIDTH                    (SIGDAT_IDX_FREQ +          SIGDAT_SIZE_FREQ)
#define SIGDAT_IDX_TIME_STAMP                   (SIGDAT_IDX_BANDWIDTH +     SIGDAT_SIZE_BANDWIDTH)
#define SIGDAT_IDX_DURATION                     (SIGDAT_IDX_TIME_STAMP +    SIGDAT_SIZE_TIME_STAMP)
#define SIGDAT_IDX_POWER                        (SIGDAT_IDX_DURATION +      SIGDAT_SIZE_DURATION)
#define SIGDAT_IDX_LONGITUDE                    (SIGDAT_IDX_POWER +         SIGDAT_SIZE_POWER)
#define SIGDAT_IDX_LATITUDE                     (SIGDAT_IDX_LONGITUDE +     SIGDAT_SIZE_LONGITUDE)
#define SIGDAT_IDX_MODE_SCH                     (SIGDAT_IDX_LATITUDE +      SIGDAT_SIZE_LATITUDE)
#define SIGDAT_SIZE                             (SIGDAT_IDX_MODE_SCH +      SIGDAT_SIZE_MODE_SCH)

#define GET_SPECT_ID(data, buffer)              {memcpy(data, &buffer[SPECT_IDX_ID],             SPECT_SIZE_ID);}
#define GET_SPECT_FLAG(data, buffer)            {memcpy(data, &buffer[SPECT_IDX_FLAG],           SPECT_SIZE_FLAG);}
#define GET_SPECT_ACTION(data, buffer)          {memcpy(data, &buffer[SPECT_IDX_ACTION],         SPECT_SIZE_ACTION);}
#define GET_SPECT_FREQ_MIN(data, buffer)        {memcpy(data, &buffer[SPECT_IDX_FREQ_MIN],       SPECT_SIZE_FREQ_MIN);}
#define GET_SPECT_FREQ_MAX(data, buffer)        {memcpy(data, &buffer[SPECT_IDX_FREQ_MAX],       SPECT_SIZE_FREQ_MAX);}
#define GET_SPECT_FREQ_SMPCNT(data, buffer)     {memcpy(data, &buffer[SPECT_IDX_FREQ_SMPCNT],    SPECT_SIZE_FREQ_SMPCNT);}
#define GET_SPECT_FREQ_IDX(data, buffer)        {memcpy(data, &buffer[SPECT_IDX_FREQ_IDX],       SPECT_SIZE_FREQ_IDX);}
#define GET_SPECT_TIME_STAMP(data, buffer)      {memcpy(data, &buffer[SPECT_IDX_TIMESTAMP],      SPECT_SIZE_TIMESTAMP);}
#define GET_SPECT_ATTR(data, buffer)            {memcpy(data, &buffer[SPECT_IDX_ATTR_EN],        SPECT_SIZE_ATTR_EN);}
#define GET_SPECT_DATA(data, buffer)            {memcpy(data, &buffer[SPECT_IDX_DATA],           SPECT_SIZE_FLAG);}


#define GET_SIGNAL_ID(data, buffer)             {memcpy(data, &buffer[SIGNAL_IDX_ID],            SIGNAL_SIZE_ID);}
#define GET_SIGNAL_FLAG(data, buffer)           {memcpy(data, &buffer[SIGNAL_IDX_FLAGS],         SIGNAL_SIZE_FLAGS);}
#define GET_SIGNAL_SIG_COUNT(data, buffer)      {memcpy(data, &buffer[SIGNAL_IDX_SIG_CNT],       SIGNAL_SIZE_SIG_CNT);}
#define GET_SIGNAL_DATA(data, buffer)           {memcpy(data, &buffer[SIGNAL_IDX_DATA],          SIGNAL_SIZE_DATA);}


#define GET_SIGDAT_SIG_ID(data, buffer)         {memcpy(data, &buffer[SIGDAT_IDX_SIG_ID],        SIGDAT_SIZE_SIG_ID);}
#define GET_SIGDAT_AUTO_ID(data, buffer)        {memcpy(data, &buffer[SIGDAT_IDX_AUTO_ID],       SIGDAT_SIZE_AUTO_ID);}
#define GET_SIGDAT_PROPERTIES(data, buffer)     {memcpy(data, &buffer[SIGDAT_IDX_PROPERTIES],    SIGDAT_SIZE_PROPERTIES);}
#define GET_SIGDAT_FREQ(data, buffer)           {memcpy(data, &buffer[SIGDAT_IDX_FREQ],          SIGDAT_SIZE_FREQ);}
#define GET_SIGDAT_BANDWIDTH(data, buffer)      {memcpy(data, &buffer[SIGDAT_IDX_BANDWIDTH],     SIGDAT_SIZE_BANDWIDTH);}
#define GET_SIGDAT_TIMESTAMP(data, buffer)      {memcpy(data, &buffer[SIGDAT_IDX_TIME_STAMP],    SIGDAT_SIZE_TIME_STAMP);}
#define GET_SIGDAT_DURATION(data, buffer)       {memcpy(data, &buffer[SIGDAT_IDX_DURATION],      SIGDAT_SIZE_DURATION);}
#define GET_SIGDAT_POWER(data, buffer)          {memcpy(data, &buffer[SIGDAT_IDX_POWER],         SIGDAT_SIZE_POWER);}
#define GET_SIGDAT_LONGITUDE(data, buffer)      {memcpy(data, &buffer[SIGDAT_IDX_LONGITUDE],     SIGDAT_SIZE_LONGITUDE);}
#define GET_SIGDAT_LATITUDE(data, buffer)       {memcpy(data, &buffer[SIGDAT_IDX_LATITUDE],      SIGDAT_SIZE_LATITUDE);}
#define GET_SIGDAT_MODE_SCH(data, buffer)       {memcpy(data, &buffer[SIGDAT_IDX_MODE_SCH],      SIGDAT_SIZE_MODE_SCH);}


#define MSG_SPECT_DATA                          0x01
#define MSG_SIGNAL_DATA                         0x02
#define MSG_AUDIO_STREAMING                     0x03
#define MSG_NOISE_FLOOR                         0x04
#define MSG_SPECT_OFFLINE_DATA                  0x06

typedef struct {
    uint64_t signalID;
    uint64_t automationID;
    union {
        uint64_t all;
        struct
        {
            uint64_t notuse         :   56;
            unsigned Freq    		:   1;
            unsigned Bandwidth      :   1;
            unsigned StartTime    	:   1;
            unsigned Length         :   1;
            unsigned Power          :   1;
            unsigned Location    	:   1;
            unsigned Automation     :   1;
            unsigned ModSch         :   1;
        }Bits;
    }properties;

    uint64_t    freq;
    uint32_t    bandwidth;
    uint64_t    timestamp;
    uint64_t    duration;
    float       power;
    double      longitude;
    double      latitude;

    union {
        uint16_t all;
        struct
        {
            unsigned notuse         :  8;
            unsigned NotDetect      :  1;
            unsigned FMNarrowBand   :  1;
            unsigned FFWideBand     :  1;
            unsigned AM             :  1;
            unsigned FSK            :  1;
            unsigned USB            :  1;
            unsigned LSB            :  1;
            unsigned CW             :  1;
        }Bits;
    }modeScheme;

}SignalData ;


typedef struct {
    uint8_t         flag;
    uint8_t         action;
    uint64_t        freqMax;
    uint64_t        freqMin;
    uint16_t        sampleCount;
    uint8_t         freqIndex;
    uint64_t        timeStamp;
}SpecTrum;

enum MessageType {
    NONE = 0,
    PING = 1,
    PONG = 2,
    SET_STATE = 3,
    SET_DATA_CFG = 4,
    REQ_DATA_OFFLINE = 5,
    SET_SIGNAL_DETECTION = 6,
    SET_PERMISSION = 7,
    SET_SENSOR_STATUS = 8,
    SET_DATA_CRYPT = 9,
    SET_DATA_AUTHENTICATE = 10,
    SET_LOCALSENSOR_STATUS = 11,
    GEO_REQ = 12,
    DEMODULATION_REQ = 13,
    SEARCH_REQ = 16,
    SET_MISSION_CFG = 18,
    SIGNAL_CLASSIFICATION = 20,
    SET_SENSOR_GAIN = 21,

    //Message ID for Receive Data
    SPECTRUM_DATA = 64,
    SIGNAL_DATA = 65,
    AUDIO_DEMODULATION = 66,
    THRESHOLD_DATA = 67,
    SPECTRUM_OFFLINE_DATA = 69,

    GET_SIGNAL_DETECTION = 134,
    GET_PERMISSION = 135,
    GET_SENSOR_STATUS = 136,
    GET_LOCALSENSOR_STATUS = 139,
    SET_SYS_TICK_SYNC,
    REMOTE_WS,
    FAIL = 255
};

enum DataTransferType{
    DATA_ENCRYPTED = 0,
    DATA_RAW,
};

#endif // DATAFLOWEXTRACT_H

