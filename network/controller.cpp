#include "controller.h"
#include "isc/fifo.h"
#include "isc/utils.h"
#include <cstdlib>
#include <math.h>
#include <QHostAddress>
#include <QNetworkInterface>
#ifdef WIN32
#include <pcap/pcap.h>
#endif

using namespace external::client;
using namespace external::client::configuration;
using namespace external::client::connection;
using namespace external::client::signal;
using namespace external::client::calibration;
using namespace external::client::server;
using namespace external::client::sensor;
using namespace external::client::test;
using namespace communication::isc;

Controller::Controller()
{
    m_serialDev     = nullptr;
    m_sigGenAgilent = nullptr;
    m_spectFsv      = nullptr;
    //m_serverUdp     = nullptr;
    m_serverSsl     = nullptr;

    m_serialDev     = std::make_shared<Layer2>();
    m_fpga          = std::make_shared<Fpga>();
    m_sigGenAgilent = std::make_shared<Agilent5182>();
    m_spectFsv      = std::make_shared<SpectrumFsv>();
    //m_serverUdp     = std::make_shared<DataStream>();
    m_serverSsl     = std::make_shared<SecureClient>();
    m_etherTrans    = std::make_shared<EtherTrans>();

    m_sigType = SigGen_Agilent_5182;
    m_spectType = Spect_Aeroflex_Type1;
    m_powerType = Power_Agilent_Type1;

    LREP("Controller created at: {}\n", this);
}

Controller::~Controller()
{
    //Server_StopUdpClient();
    Server_StopSslClient();
    SigGen_Stop();
    Fpga_Stop();
    Ether_Stop();
    Spect_Stop();
    if(Dev_GetStatus())
        Dev_Stop();
    LREP("Controller stop all \r\n");
}

void Controller::Server_StartSslClient()
{
    if(m_serverSsl == nullptr)
        m_serverSsl = std::make_shared<SecureClient>();

    m_serverSsl->SetEventDataCallback([&](const void *data, int len) {
        ProcessServerControlMsg(data, len);
    }, 0);

    m_serverSsl->SetEventConnectionCallback([&](communication::Event_Network evt) {
        emit sigServerStatus(evt);
    }, 0);
    m_serverSsl->Start(m_serverSslAddr, m_serverSslPort);
}

void Controller::Server_StopSslClient() {
    m_serverSsl->Stop();
}

void Controller::Server_StartUdpClient()
{
//    if(m_serverUdp == nullptr)
//        m_serverUdp = std::make_shared<DataStream>();

//    m_serverUdp->registerCallback([&](uint8_t type, uint8_t* data, uint32_t dlen) {
//        //printf("%02x %02x %02x %02x - length: %d\r\n", data[0], data[1], data[2], data[3], dlen);
//        switch(type) {
//        case SPECTRUM_DATA:
//            Server_ProcessSpectrumData(data, dlen);
//            break;
//        case SIGNAL_DATA:
//            Server_ProcessSignalListData(data, dlen);
//            break;
//        case AUDIO_DEMODULATION:
//            Server_ProcessAudioData(data, dlen);
//            break;
//        case THRESHOLD_DATA:
//            //LREP("Threadhold data\r\n");
//            Server_ProcessNoiseFloor(data, dlen);
//            break;
//        case SPECTRUM_OFFLINE_DATA:
//            Server_ProcessSpectrumOffline(data, dlen);
//            break;
//        default:
//            LREP("unhandled msg: {}\n", (int)type);
//            break;
//        }

//    });

//    m_serverUdp->Start(m_serverUdpAddr, m_serverUdpPort);
}


void Controller::Server_StopUdpClient()
{
//    m_serverUdp->Stop();
}

void Controller::SigGen_Start()
{
    if(m_sigGenAgilent == nullptr) {
        m_sigGenAgilent = std::make_shared<Agilent5182>();
    }

    m_sigGenAgilent->SetEventConnectionCallback([&](communication::Event_Network evt) {
        emit sigSigGenStatus(evt);
    }, 0);

    m_sigGenAgilent->Start(m_sigGen1TcpAddr, m_sigGen1TcpPort);
}

void Controller::SigGen_Stop()
{
    m_sigGenAgilent->Stop();    
}

void Controller::Dev_Start()
{
    if(m_serialDev == nullptr) {
        m_serialDev = std::make_shared<Layer2>();
    }

    m_serialDev->Mac_RegisterClbEvent(communication::isc::Layer2::MAC_EVT_RECV_DATA,
                                  [&](std::shared_ptr<uint8_t> pMem, void *pParam) {
        (void)pParam;
        Layer2::SFrameInfo *pFrameInfo = (Layer2::SFrameInfo*)pMem.get();
        emit sigSerialDevRecvData(pFrameInfo->pu8Data, (int)pFrameInfo->u16DLen);
    }, 0);

    if(m_serialDev->Mac_Start(m_rfDevName, m_rfDevBaudrate, PC_ID)) {
        emit sigSerialDevStatus(communication::Event_Connected);
    } else {
        emit sigSerialDevStatus(communication::Event_Disconnected);
    }
}

void Controller::Dev_Stop()
{
    m_serialDev->Mac_Stop();
}

void Controller::Dev_IFRFSendCommand(uint8_t type, uint8_t command,
                                     uint8_t *data, uint8_t len, bool ackRreq)
{
    uint8_t *sendData = new uint8_t[len + 3];
    uint8_t ctrl;
    if(ackRreq) ctrl = DATA_FRAME | ACK_REQ;
    else ctrl = DATA_FRAME;
    sendData[0] = type;
    sendData[1] = command;
    //sendData[2] = len;
    if(len > 0 && data != NULL) {
        memcpy(&sendData[2], data, len);
    }
    fflush(stdout);

    m_serialDev->Mac_SendDataImmediate(IFRF_ID, ctrl, sendData, len + 2);

    delete[] sendData;
}

void Controller::Dev_SetFreqency(uint64_t freq, bool ackReq)
{
    printf("set rf freq = %lld\n", freq);
    uint8_t data[10];
    data[0] = freq & 0xFF;
    data[1] = (freq >> 8) & 0xFF;
    data[2] = (freq >> 16) & 0xFF;
    data[3] = (freq >> 24) & 0xFF;
    data[4] = (freq >> 32) & 0xFF;
    data[5] = (freq >> 40) & 0xFF;
    data[6] = (freq >> 48) & 0xFF;
    data[7] = (freq >> 56) & 0xFF;

//    for(int i = 0; i < 8; i++) {
//        printf("0x%x ", data[i]);
//    }

    fflush(stdout);

    Dev_IFRFSendCommand(MODE_APP_NORMAL ,MASTER_SET_FREQ, data, 8, ackReq);
}


void Controller::Dev_SetAttent(double value, bool ackReq)
{

    uint8_t data[10];
    if(value == 0) data[0] = 0;
    else data[0] = (uint8_t)(value / 0.25);
    Dev_IFRFSendCommand(MODE_APP_SUPPORT, MASTER_SET_ATTEN, data, 1, ackReq);
    LREP("Set dev atten {}\n", (int)data[0]);
}


void Controller::Dev_ReqConnect(bool ackReq)
{

}

void Controller::Dev_RFDLSendCommand(uint8_t command, uint8_t *data, uint8_t len, bool ackRreq)
{
    uint8_t *sendData = new uint8_t[len + 3];
    uint8_t ctrl;
    if(ackRreq) ctrl = DATA_FRAME | ACK_REQ;
    else ctrl = DATA_FRAME;
    sendData[0] = MODE_APP_NORMAL;
    sendData[1] = command;
    sendData[2] = len;
    if(len > 0 && data != NULL) {
        memcpy(&sendData[2], data, len);
    }
    m_serialDev->Mac_SendDataImmediate(RFDELAY_ID, ctrl, sendData, len + 3);
    delete[] sendData;
}

void Controller::Dev_RFDLSetParam(uint64_t freq, uint32_t on,
                                  uint32_t off, uint32_t ns1,
                                  uint32_t ns2, uint32_t ns3, uint32_t ns4)
{

}


void Controller::Dev_SendData(uint8_t dest, uint8_t *data, uint8_t len, bool ackReq)
{
    uint8_t ctrl;
    ctrl = ackReq ? (0x20 | 0x80) : 0x20;
    m_serialDev->Mac_SendDataImmediate(dest, ctrl, data, len);
}

std::string Controller::GetIpV4Address()
{
    QNetworkInterface nwkif = QNetworkInterface::interfaceFromName("eno1");

    QList<QHostAddress> list =  nwkif.allAddresses();

    for(int iter = 0; iter < list.count(); iter++) {
        if(!list[iter].isLoopback()) {
            if(list[iter].protocol() == QAbstractSocket::IPv4Protocol) {
                //qDebug() << list[iter].toString();
            }
        }
    }
    return "";
}


void Controller::Server_ProcessSpectrumData(uint8_t *data, uint32_t len)
{
//    SpecTrum spect;
//    (void)len;
//    uint8_t flag[SPECT_SIZE_FLAG];
//    uint8_t action[SPECT_SIZE_ACTION];
//    uint8_t freqMin[SPECT_SIZE_FREQ_MIN];
//    uint8_t freqMax[SPECT_SIZE_FREQ_MAX];
//    uint8_t smpCount[SPECT_SIZE_FREQ_SMPCNT];
//    uint8_t freqIdx[SPECT_SIZE_FREQ_IDX];
//    uint8_t timeStamp[SPECT_SIZE_TIMESTAMP];
//    float *dataArray;

//    GET_SPECT_FLAG(flag, data);
//    GET_SPECT_ACTION(action, data);
//    GET_SPECT_FREQ_MIN(freqMin, data);
//    GET_SPECT_FREQ_MAX(freqMax, data);
//    GET_SPECT_FREQ_SMPCNT(smpCount, data);
//    GET_SPECT_FREQ_IDX(freqIdx, data);
//    GET_SPECT_TIME_STAMP(timeStamp, data);

//    spect.sampleCount = smpCount[0] << 8 | smpCount[1];
//    spect.freqMin = (uint64_t)((uint64_t)freqMin[0] << 32 | freqMin[1] << 24 | freqMin[2] << 16 | freqMin[3] << 8 | freqMin[4]);
//    spect.freqMax = (uint64_t)((uint64_t)freqMax[0] << 32 | freqMax[1] << 24 | freqMax[2] << 16 | freqMax[3] << 8 | freqMax[4]);
//    spect.timeStamp = Utils::convert2Uint64((const char*)timeStamp);
//    //printf("Time:%llu-count:%d-Max:%ld-Min:%ld\r\n", spect.timeStamp, spect.sampleCount, spect.freqMax, spect.freqMin);
//    dataArray = new float[spect.sampleCount];

//    ConvertToFloatArray(dataArray, &data[SPECT_IDX_DATA], spect.sampleCount * sizeof(float));
//    delete[] dataArray;
}

void Controller::Server_ProcessSignalListData(uint8_t *data, uint32_t len)
{
//    (void)len;
//    uint8_t signalID[SIGNAL_SIZE_ID];
//    uint8_t signalFlag[SIGNAL_SIZE_FLAGS];
//    uint8_t signalCount[SIGNAL_SIZE_SIG_CNT];

//    GET_SIGNAL_ID(signalID, data);
//    GET_SIGNAL_FLAG(signalFlag, data);
//    GET_SIGNAL_SIG_COUNT(signalCount, data);
//    uint16_t sigCount = signalCount[0] << 8 | signalCount[1];
//    SignalData *signalData = new SignalData[sigCount];
//    LREP("Signal count: {}\r\n", sigCount);
//    AnalizeSignalList(signalData, &data[SIGNAL_IDX_DATA], sigCount);
//    delete[] signalData;
}

void Controller::Server_ProcessAudioData(uint8_t *data, uint32_t len)
{
    (void)data;
    (void)len;

}

void Controller::Server_ProcessNoiseFloor(uint8_t *data, uint32_t len)
{
    (void)data;
    (void)len;
}

void Controller::Server_ProcessSpectrumOffline(uint8_t *data, uint32_t len)
{
    (void)data;
    (void)len;
}

/**
 * @brief Controller::ConvertToFloatArray
 * @param data
 * @param buffer
 * @param len
 */
void Controller::ConvertToFloatArray(float *data, uint8_t *buffer, uint32_t len)
{
    uint32_t dataIdx, bufferIdx;
    for(bufferIdx = 0, dataIdx = 0; bufferIdx < len; bufferIdx += sizeof(float), dataIdx++) {
        data[dataIdx] = buffer[bufferIdx]     << 24 |
                        buffer[bufferIdx + 1] << 16 |
                        buffer[bufferIdx + 2] << 8  |
                        buffer[bufferIdx + 3];
    }
}

/**
 * @brief Controller::AnalizeSignalList
 * @param sigList
 * @param data
 * @param sigCount
 */
//void Controller::AnalizeSignalList(SignalData *sigList, uint8_t *data, uint16_t sigCount)
//{
//    (void)sigList;
//    (void)data;
//    uint8_t *dataPtr;

//    uint8_t sigID[SIGDAT_SIZE_SIG_ID];
//    uint8_t autoID[SIGDAT_SIZE_AUTO_ID];
//    uint8_t properties[SIGDAT_SIZE_PROPERTIES];
//    uint8_t freq[SIGDAT_SIZE_FREQ];
//    uint8_t bandWidth[SIGDAT_SIZE_BANDWIDTH];
//    uint8_t timeStamp[SIGDAT_SIZE_TIME_STAMP];
//    uint8_t duration[SIGDAT_SIZE_DURATION];
//    uint8_t power[SIGDAT_SIZE_POWER];
//    uint8_t longitude[SIGDAT_SIZE_LONGITUDE];
//    uint8_t latitude[SIGDAT_SIZE_LATITUDE];
//    uint8_t modeSch[SIGDAT_SIZE_MODE_SCH];

//    uint16_t    idx;
//    uint32_t    idxptr;

//    // If many signal is saved, clear for push new once
//    if(m_listSignal.size() > 100) {
//        m_listSignal.clear();
//    }

//    for(idx = 0, idxptr = 0; idx < sigCount; idx++, idxptr+= SIGDAT_SIZE) {
//        dataPtr = &data[idxptr];
//        GET_SIGDAT_SIG_ID(sigID,            dataPtr);
//        GET_SIGDAT_AUTO_ID(autoID,          dataPtr);
//        GET_SIGDAT_PROPERTIES(properties,   dataPtr);
//        GET_SIGDAT_FREQ(freq,               dataPtr);
//        GET_SIGDAT_BANDWIDTH(bandWidth,     dataPtr);
//        GET_SIGDAT_TIMESTAMP(timeStamp,     dataPtr);
//        GET_SIGDAT_DURATION(duration,       dataPtr);
//        GET_SIGDAT_POWER(power,             dataPtr);
//        GET_SIGDAT_LONGITUDE(longitude,     dataPtr);
//        GET_SIGDAT_LATITUDE(latitude,       dataPtr);
//        GET_SIGDAT_MODE_SCH(modeSch,        dataPtr);

//        sigList[idx].signalID       = Utils::convert2Uint64Revert((const char*)sigID);
//        sigList[idx].automationID   = Utils::convert2Uint64Revert((const char*)autoID);
//        sigList[idx].properties.all = Utils::convert2Uint64Revert((const char*)properties);
//        sigList[idx].freq           = Utils::convert2Uint64Revert((const char*)freq);
//        sigList[idx].bandwidth      = Utils::convert2Uint32Revert((const char*)bandWidth);
//        sigList[idx].timestamp      = Utils::convert2Uint64Revert((const char*)timeStamp);
//        sigList[idx].duration       = Utils::convert2Uint64Revert((const char*)duration);
//        sigList[idx].power          = Utils::convert2FloatRevert((const char*)power);
//        sigList[idx].longitude      = Utils::convert2DoubleRevert((const char*)longitude);
//        sigList[idx].latitude       = Utils::convert2DoubleRevert((const char*)latitude);
//        sigList[idx].modeScheme.all = modeSch[1] << 8 | modeSch[0];

//        /* Print all
//        printf("signalID [%llu]\n automationID [%d]\n properties [%x]\n freq [%llu]\n bandwidth [%ld]\n "
//            "timestamp [%llu]\n duration [%llu]\n power [%f]\n longitude [%f]\n latitude [%f]\n mode [%x]\n",
//            sigList[idx].signalID,
//            sigList[idx].automationID,
//            sigList[idx].properties.all,
//            sigList[idx].freq,
//            sigList[idx].bandwidth,
//            sigList[idx].timestamp,
//            sigList[idx].duration,
//            sigList[idx].power,
//            sigList[idx].longitude,
//            sigList[idx].latitude,
//            sigList[idx].modeScheme.all);
//        */

////        // Not print location
////        printf("signalID [%llu]\n automationID [%d]\n properties [%x]\n freq [%llu]\n bandwidth [%ld]\n "
////            "timestamp [%llu]\n duration [%llu]\n power [%f]\n mode [%x]\n",
////            sigList[idx].signalID,
////            sigList[idx].automationID,
////            sigList[idx].properties.all,
////            sigList[idx].freq,
////            sigList[idx].bandwidth,
////            sigList[idx].timestamp,
////            sigList[idx].duration,
////            sigList[idx].power,
////            sigList[idx].modeScheme.all);


//        //m_listSignal.push_back(sigList[idx]);

//    }
//}

bool Controller::Server_CheckHasSignalFrequency(uint64_t freq, uint64_t err)
{
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err) {
            return true;
        }
    }

    return false;
}


double Controller::Server_CheckSignalPower(uint64_t freq, uint64_t err) {
    static uint32_t count = 0;
    //printf("CHECK %lld %d ", freq, count++); fflush(stdout);
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err) {
            return s.power();
        }
    }
    //LREP("NO FREQ EXIST\n");
    return 0;
}


double Controller::Server_CheckHasSignalPower(uint64_t freq, uint64_t err) {
    static uint32_t count = 0;
    //printf("CHECK %lld %d ", freq, count++); fflush(stdout);
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err && s.power() < 0) {
            return s.power();
        }
    }
    //LREP("NO PWR\n");
    return 0;
}

FreqPoint Controller::Server_CheckCalibSignal(uint64_t freq, uint64_t err)
{
    FreqPoint ret = {0,1000.0};
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err && s.power()!= 0 ) {
            ret.point = s.frequency();
            ret.value = float(s.power());
            return ret;
        }
    }
    return ret;
}

uint32_t Controller::Server_CheckBandwidth(uint64_t freq, uint64_t err) {
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err && s.power() < 0) {
            return s.bandwidth();
        }
    }
    return 0;
}

uint64_t Controller::Server_GetReceivedFrequency(uint64_t freq, uint64_t err)
{
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err && s.power() < 0) {
            return s.frequency();
        }
    }

    return 0;
}


external::client::Signal Controller::Server_GetSignalHasPower(uint64_t freq, uint64_t err)
{
    external::client::Signal sig;
    sig.set_power(0);
    for(auto s : m_listSignal) {
        if(std::llabs(s.frequency() - freq) < err && s.power() < 0) {
            return s;
        }
    }
    return sig;
}


external::client::Signal Controller::Server_GetSignalTdoa(uint64_t freq, uint64_t err)
{
    external::client::Signal sig;
    sig.set_power(0);
    for(auto s : m_resTdoaSignalList) {
        if(std::llabs(s.frequency() - freq) < err && s.power() < 0) {
            return s;
        }
    }
    return sig;
}



void Controller::disconnectAllConnection()
{
    for(auto var : m_connections) {
        QObject::disconnect(var);
    }
    m_connections.clear();
}

void Controller::addConnection(const QMetaObject::Connection &connection)
{
    m_connections << connection;
}


void Controller::Server_ClearSignaListReceived() {
    m_listSignal.clear();
}


/* SENDING SECTION */

void Controller::Server_SendMessage(external::client::Message &msg)
{
    int dlen = msg.ByteSize();
    uint8_t *data = new uint8_t[dlen];

    if(msg.SerializeToArray(data, dlen)) {
        m_serverSsl->sendDataToServer(data, dlen);
    }
    delete[] data;
}


/**
 * @brief Controller::Server_SetRecvFreq
 * @param freq
 * @param bandwidth
 * @param timeoutMillisec
 */
void Controller::Server_SetRecvFreq(double freq_input, uint32_t bandwidth, uint64_t timeoutMillisec)
{
    uint64_t freq = (uint64_t)freq_input;
    //LREP("CHANGE MISSION: FREQ: {} BANDWIDTHL: {}\n", freq,  bandwidth);
    ConfigureMission mission;
    if(freq == 0 || bandwidth == 0) {
        ASSERT(false);
        return;
    }
    // Convert to hezt
    uint64_t    centerFreq = (uint64_t)(freq * 1E6);
    uint32_t    halfbw = bandwidth / 2;

    if((centerFreq - halfbw) < VSI3_FREQ_MIN ) {
        centerFreq = VSI3_FREQ_MIN + halfbw;        
    }

    if((centerFreq + (bandwidth / 2)) > VSI3_FREQ_MAX) {
        centerFreq = VSI3_FREQ_MAX - (bandwidth / 2);       
    }

    //mission.set_frequency(centerFreq + 1500000);
    mission.set_frequency(centerFreq)
            \
            \
            ;
    mission.set_bandwidth(bandwidth);
    Message msg;
    msg.set_type(::Type::MISSION);
    ::google::protobuf::Any* datamsg = msg.mutable_data();
    datamsg->PackFrom(mission);
    LREP(msg.DebugString());
    Server_SendMessage(msg);
    //LREP("CONTROL SERVER\n");
    if(timeoutMillisec > 0) {
        //LREP("DELAY: {}\n", timeoutMillisec);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    }
}

void Controller::Server_SetGain(uint8_t sensorId, double gainValue, uint64_t timeoutMillisec)
{
    Gain gain;
    gain.mutable_sensor()->set_id(sensorId);
    gain.set_factor(gainValue);
    Message msg;
    msg.set_type(::Type::SENSOR);
    ::google::protobuf::Any* datamsg = msg.mutable_data();
    datamsg->PackFrom(gain);
    //LREP(msg.DebugString());
    Server_SendMessage(msg);
    //LREP("CONTROL SERVER\n");
    if(timeoutMillisec > 0) {
        //LREP("DELAY: {}\n", timeoutMillisec);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    }
}

//void Controller::Server_ReqDatachannel(DataTransferType type, std::string ipAddr, int port, uint64_t timeoutMillisec)
//{
//    DataChannelRequest dataReq;

//    dataReq.set_address(ipAddr);
//    dataReq.set_port(port);

//    if(type == DATA_ENCRYPTED) {
//        dataReq.set_protocol("udt-aes");
//    } else if(type == DATA_RAW){
//        dataReq.set_protocol("udt-raw");
//    }else {
//        ASSERT(false);
//    }

//    Message msg;
//    msg.set_type(::Type::DATA_CHANNEL);
//    ::google::protobuf::Any* datamsg = msg.mutable_data();
//    datamsg->PackFrom(dataReq);
//    Server_SendMessage(msg);
//    if(timeoutMillisec > 0) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
//    }
//}

void Controller::Server_SetTimeRecvDuration(uint32_t time)
{
    (void)time;
}

void Controller::Server_SetNoiseFloor(uint32_t mode, float factor, uint64_t timeoutMillisec)
{
    ConfigureNoisefloor nosieFloor;
    LREP("SET NOISE FLOOR: {}\n", factor);
    nosieFloor.set_mode(mode);
    nosieFloor.set_factor(factor);

    Message msg;
    msg.set_type(::Type::NOISEFLOOR);
    ::google::protobuf::Any* datamsg = msg.mutable_data();
    datamsg->PackFrom(nosieFloor);
    Server_SendMessage(msg);
    if(timeoutMillisec > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    }
}

void Controller::Server_SetSigCalc(uint32_t mode, uint32_t option, float factor, uint64_t timeoutMillisec)
{
    ConfigureSignalCalculation signalCalculation;

    signalCalculation.set_mode(mode);
    signalCalculation.set_option(option);
    signalCalculation.set_factor(factor);

    Message msg;

    msg.set_type(::Type::SIGNAL_CALC);
    ::google::protobuf::Any* datamsg = msg.mutable_data();
    datamsg->PackFrom(signalCalculation);
    Server_SendMessage(msg);
    if(timeoutMillisec > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    }
}

void Controller::Server_SaveCalibTable(CalibMode mode, std::list<FreqPoint> &list, uint64_t timeoutMillisec)
{
    Message msg;
    ::google::protobuf::Any* datamsg = msg.mutable_data();
    AddTable table;
    msg.set_type(::Type::CALIBRATION);
    switch(mode) {
        case Calib_Mode_Normal: table.set_table_index(::TableIndex::NORMAL); break;
        case Calib_Mode_Hot: table.set_table_index(::TableIndex::HOT); break;
        case Calib_Mode_Cool: table.set_table_index(::TableIndex::COOL); break;
    default:
        return;
    }

    table.set_sample_index(0);

    for(auto s : list) {
        table.add_samples(s.value);
    }
    LREP("TABLE SIZE: {}\n", table.samples_size());

    datamsg->PackFrom(table);
    Server_SendMessage(msg);

    //LREP(msg.DebugString());
    if(timeoutMillisec > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    }
}

void Controller::Server_SetServerOperationMode(ServerOperationMode mode)
{
    Message msg;
    ::google::protobuf::Any *datamsg = msg.mutable_data();
    msg.set_type(::Type::SERVER);
    ConfigureOperation operation;
    switch (mode){
    case Server_Normal: operation.set_mode(ConfigureOperation::Mode::ConfigureOperation_Mode_NORMAL); break;
    case Server_Calibration: operation.set_mode(ConfigureOperation::Mode::ConfigureOperation_Mode_CALIBRATION); break;
    case Server_Test: operation.set_mode(ConfigureOperation::Mode::ConfigureOperation_Mode_TEST); break;
    default:
        return;
    }
    datamsg->PackFrom(operation);
    Server_SendMessage(msg);
}

void Controller::Server_ClearSignalDataBase()
{
    Message msg;
    ::google::protobuf::Any *datamsg = msg.mutable_data();
    msg.set_type(::Type::SERVER);
    ClearDatabase clear;
    clear.set_username("user");
    clear.set_secret("1234");
    clear.set_signal(true);
    datamsg->PackFrom(clear);
    Server_SendMessage(msg);
}

void Controller::Server_SendTdoaMessage(external::client::Signal &signal, ::geolocation::Request::Mode mode)
{
    Message msg;
    ::google::protobuf::Any *datamsg = msg.mutable_data();
    msg.set_type(::Type::GEOLOCATION);

    ::geolocation::Request req;
    req.set_mode(mode);
    *(req.mutable_signal()) = signal;
    datamsg->PackFrom(req);
    Server_SendMessage(msg);
}

void Controller::Server_SendSensorInfo(double lat0, double long0, double lat1,
                                       double long1, double lat2,double long2,
                                       double lat3, double long3, int numSensor)
{
    LREP("lat0: {} long0: {} lat1: {} long1: {} lat2: {} long2: {}\n", lat0,
         long0, lat1, long1, lat2, long2);
    Message msg;
    ::google::protobuf::Any *datamsg = msg.mutable_data();
    msg.set_type(::Type::TEST);
    ::test::ConfigureSensor configSensor;

    external::client::Location location;
    location.set_latitude(lat0);
    location.set_longitude(long0);
    auto *sensor = configSensor.add_sensor();
    sensor->set_actived(true);
    *(sensor->mutable_location()) = location;
    sensor->set_id(0);

    location.set_latitude(lat1);
    location.set_longitude(long1);
    sensor = configSensor.add_sensor();
    sensor->set_actived(true);
    sensor->set_id(1);
    *(sensor->mutable_location()) = location;

    location.set_latitude(lat2);
    location.set_longitude(long2);
    sensor = configSensor.add_sensor();
    sensor->set_actived(true);
    sensor->set_id(2);
    *(sensor->mutable_location()) = location;

    if(numSensor == 4) {
        location.set_latitude(lat3);
        location.set_longitude(long3);
        auto sensor3 = configSensor.add_sensor();
        sensor3->set_actived(true);
        sensor3->set_id(3);
        sensor3->set_allocated_location(&location);
    }

    datamsg->PackFrom(configSensor);
    LREP(msg.DebugString());
    Server_SendMessage(msg);
}

communication::Status_Network Controller::SigGen_GetStatus()
{
    if(m_sigGenAgilent)
        return m_sigGenAgilent->getStatus();
    else
        return communication::Event_Disconnected;
}

bool Controller::SigGen_InitDevice()
{
    return (m_sigGenAgilent->InitDevice() > 0);
}

bool Controller::SigGen_SetRFPower(double pwr, PowerUnit unit,
                                  uint32_t timeoutMillisec)
{
    if(pwr >= 30) LREP("Warning: max power set\n\n");
    bool ret = false ;
#if NO_INSTRUMENT == 0
    ret = m_sigGenAgilent->SetRFPower(pwr, unit) > 0 ? true : false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
#endif
    return ret;
}


bool Controller::SigGen_SetRFSignalOut(bool on, uint32_t timeoutMillisec)
{
    bool ret = false ;
#if NO_INSTRUMENT == 0    
    ret = m_sigGenAgilent->SetSignalOut(on) > 0 ? true: false;
    //ret = m_sigGenAgilent->SetSignalOut(true);
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
#endif
    return ret;
}

bool Controller::SigGen_SetFMOut(bool on, uint32_t timeoutMillisec)
{
    bool ret = false ;
    ret = m_sigGenAgilent->SetFMOut(on) > 0 ? true: false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

bool Controller::SigGen_SetRFFreq(double freq, FrequencyUnit unit,
                                 uint32_t timeoutMillisec)
{
    bool ret = false ;
    ret = m_sigGenAgilent->SetRFFrequency(freq, unit) > 0 ? true: false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

bool Controller::SigGen_GetCurrRFPower()
{

    return true;
}

int Controller::SigGen_SetCombo(double freq, FrequencyUnit fUnit,
                                    double pwr,  PowerUnit pUnit,
                                    double bw, FrequencyUnit bwUnit,
                                    uint32_t timeoutMillisec)
{
    int ret = 0;
    if(SigGen_SetRFPower(pwr, pUnit, timeoutMillisec) <= 0)  return ret;
    if(SigGen_SetALC(false, timeoutMillisec) <= 0) return ret;
    if(SigGen_SetRFFreq(freq, fUnit, timeoutMillisec) <= 0) return ret;
    if(SigGen_SetModOut(false, timeoutMillisec) <= 0) return ret;
    if(SigGen_SetRFSignalOut(true, timeoutMillisec) <= 0) return ret;
    return ret;
}

int Controller::SigGen_SetupFMMod(double freq, FrequencyUnit fUnit,
                            double pwr,  PowerUnit pUnit,
                            double bw, FrequencyUnit bwUnit,
                            uint32_t timeoutMillisec)
{
    LREP("SetFreq: {}\r\n", freq);
    int ret = 0;
#if NO_INSTRUMENT == 0
    //1. Select modulation scheme FM, shift freq: 5.6K
    if(SigGen_SetFMDeviation(5.6, Freq_Khz, timeoutMillisec) <= 0) return ret;
    ret++;
    if(SigGen_SetFMRate(bw, bwUnit, timeoutMillisec) <= 0) return ret;
    ret++;
    if(SigGen_SetFMOut(true, timeoutMillisec) <= 0) return ret;
    ret++;
    //2. Set power -120dBm
    if(SigGen_SetRFPower(pwr, pUnit, timeoutMillisec) <= 0)  return ret;
    ret++;
    //3. Set ALC off
    if(SigGen_SetALC(false, timeoutMillisec) <= 0) return ret;
    ret++;
    //4. Set frequency output
    if(SigGen_SetRFFreq(freq, fUnit, timeoutMillisec) <= 0) return ret;
    ret++;
    //5. Turn modulation off
    if(SigGen_SetModOut(true, timeoutMillisec) <= 0) return ret;
    ret++;
    //6. Turn on RF
    if(SigGen_SetRFSignalOut(true, timeoutMillisec) <= 0) return ret;
    ret++;
#endif

    return ret;
}




bool Controller::SigGen_DeSetCombo(uint32_t timeoutMillisec)
{
#if NO_INSTRUMENT == 0
    //1. Turn modulation off
    if(SigGen_SetModOut(false, timeoutMillisec) <= 0) return false;
    //2. Turn off RF
    if(SigGen_SetRFSignalOut(false, timeoutMillisec) <= 0) return false;
#endif
    return true;
}

/**
 * @brief Controller::SigGen_PresetDevice
 * @return
 */
bool Controller::SigGen_PresetDevice()
{
    return true;
}

/**
 * @brief Controller::SigGen_SetALC
 * @param on
 * @param timeoutMillisec
 * @return
 */
bool Controller::SigGen_SetALC(bool on, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_sigGenAgilent->SetALC(on) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::SigGen_SetModOut
 * @param on
 * @param timeoutMillisec
 * @return
 */
bool Controller::SigGen_SetModOut(bool on, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_sigGenAgilent->SetModOut(on) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::SigGen_SetFMDeviation
 * @param dev
 * @param unit
 * @param timeoutMillisec
 * @return
 */
bool Controller::SigGen_SetFMDeviation(double dev, FrequencyUnit unit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_sigGenAgilent->SetFMDeviation(dev, unit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::SigGen_SetFMRate
 * @param rate
 * @param unit
 * @param timeoutMillisec
 * @return
 */
bool Controller::SigGen_SetFMRate(double rate, FrequencyUnit unit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_sigGenAgilent->SetFMRate(rate, unit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

bool Controller::SigGen_SetFMARB(uint32_t sampleClock, double freq,
                                 FrequencyUnit freqUnit, std::string file,
                                 double power, PowerUnit pwrUnit, uint32_t timeoutMillisec)
{
    return m_sigGenAgilent->SetFMARB(sampleClock, freq, freqUnit,file,  power, pwrUnit, timeoutMillisec) > 0 ? true:false;
}

bool Controller::SigGen_SetTwoTone(double freq, FrequencyUnit freqUnit,
                                   double space, FrequencyUnit spaceUnit,
                                   double power, PowerUnit pwrUnit, uint64_t delayMillisec)
{
    return m_sigGenAgilent->SetTwoTone(freq, freqUnit, space, spaceUnit, power, pwrUnit, delayMillisec) > 0 ? true:false;
}

/**
 * @brief Controller::Spect_Start
 * @return
 */
void Controller::Spect_Start()
{
    if(m_spectFsv == nullptr) {
        m_spectFsv = std::make_shared<SpectrumFsv>();
    }

    m_spectFsv->SetEventConnectionCallback([&](communication::Event_Network evt) {
        emit sigSpectStatus(evt);
    }, 0);

    m_spectFsv->SetEventDataCallback([&](const void *data, int len) {

//        LREP("\nLen = {}\n", len);
        uint8_t *ptr = (uint8_t*)data;
        ptr[len] = '\0';
//        for(int i = 0; i < len; i++)
//            printf("%x ", ptr[i]);        

        QString str = QString((const char*)ptr);
        str.remove("\r\n", Qt::CaseInsensitive);
        str.remove("\n", Qt::CaseInsensitive);
        str.remove(" ", Qt::CaseInsensitive);

        //LREP("{}", str.toStdString());
        if(recv_string_.size() < 4000000) {
            recv_string_ += str.toStdString();
        } else {
            LREP("string too large -> ignore\n");
        }
    }, 0);

    m_spectFsv->Start(m_spectAddr, m_spectPort);
}

void Controller::Spect_StartCalculate()
{
    list_spect_value_.clear();
    uint64_t freq = 120000000;
    std::vector<std::string> vect;
    vect.clear();
    //LREP("STRING: {}\nSTOP\n", recv_string_);
    cppframework::str::Util::split(recv_string_, ",", vect);
    //LREP("VECV_SIZE: {}\n", vect.size());
    for(auto &elem : vect) {
        freq += 25000;
        FreqPoint freqPoint;
        freqPoint.point = freq;
        freqPoint.value = cppframework::str::Util::convert(elem, 0.0);
        list_spect_value_.push_back(freqPoint);
    }
    recv_string_.clear();

    LREP("vect size: {}\n", list_spect_value_.size());
}

bool Controller::Spect_GetFirstValue(double &value)
{
    FreqPoint point;
    if(list_spect_value_.size() > 0) {
        point =  list_spect_value_.front();
        value = point.value;
        list_spect_value_.pop_front();
        return true;
    }
    return false;
}

bool Controller::Spect_GetValueAtPoint(uint64_t freq, double &value)
{
    for(auto &var : list_spect_value_) {
        if(var.point == freq) {
            value = var.value;
            return true;
        }
    }
    return false;
}

bool Controller::Spect_GetValueMaxAt(uint64_t freq, double &value, uint64_t range)
{
    uint64_t pad = range / 2;
    uint64_t low = freq - pad, high = freq + pad;
    double max = -200;
    bool israng = false;

    for(auto &var : list_spect_value_) {
        if(var.point >= low && var.point <= high) {
            if(max < var.value) {
                max = var.value;
                israng = true;
            }
        }
    }
    if(israng) {
        //LREP("max = {}\n", max);
        value = max;
        return true;
    }
    return false;
}

bool Controller::Spect_GetMaxValue(double &value)
{
    double max = -200;
    for(auto &var : list_spect_value_) {
        if(var.value > max)
            max = var.value;
    }
    value = max;
    return true;
}

std::list<FreqPoint> Controller::Spect_GetValueExcess(double value)
{
    std::list<FreqPoint> list;
    //LREP("list_spect_value_size: {} - value {}\n", list_spect_value_.size(), value);
    for(auto &var : list_spect_value_) {
        if(var.value >= value) {
            LREP("freq:[{}] Hz pwr:[{}] dbM ", var.point, var.value);
            if(var.point != 140000000)
                list.push_back(var);
        }
    }

    return list;
}


/**
 * @brief Controller::Spect_Stop
 * @return
 */
void Controller::Spect_Stop()
{
    m_spectFsv->Stop();
}

/**
 * @brief Controller::Spect_InitDevice
 * @return
 */
bool Controller::Spect_InitDevice()
{
    LREP("Init spectrum device\r\n");
    return(m_spectFsv->InitDevice() > 0);
}

bool Controller::Spect_SendCommand(const std::string &command)
{
    bool ret = false;
    ret = m_spectFsv->SendCommand(command) > 0 ? true:false;
    return ret;
}

/**
 * @brief Controller::Spect_SetupSpecAnalyzer
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetupSpecAnalyzer(uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetupSpecAnalyzer() > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetupSpecAnalyzerMode
 * @param mode
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetupSpecAnalyzerMode(MeasurementMode mode, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetupSpecAnalyzerMode(mode) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetCenterFreq
 * @param dFreq
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetCenterFreq(double dFreq, FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetCenterFreq(dFreq, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetSpan
 * @param dSpanValue
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetSpan(double dSpanValue, FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetSpan(dSpanValue, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetReferentLevel
 * @param dReferValue
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetReferentLevel(double dReferValue, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetReferentLevel(dReferValue) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetSpecAnttenuation
 * @param dAttenuatonValue
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetSpecAnttenuation(double dAttenuatonValue, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetSpecAnttenuation(dAttenuatonValue) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetStopFreq
 * @param dStopFreq
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetStopFreq(double dStopFreq, FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetStopFreq(dStopFreq, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetResolutionBandwidth
 * @param dRbw
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetResolutionBandwidth(double dRbw, FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetResolutionBandwidth(dRbw, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetMarker
 * @param bOnOff
 * @param iMakerIndex
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetMarker(bool bOnOff, int iMakerIndex, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetMarker(bOnOff, iMakerIndex) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetMarkerMax
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetMarkerMax(uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetMarkerMax() > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetNextMarkerMax
 * @param iMaxker
 * @param searchDir
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetNextMarkerMax(int iMaxker, SearchDirection searchDir,
                                        uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetNextMarkerMax(iMaxker, searchDir) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetMarkerAtFreq
 * @param dFreq
 * @param freqUnit
 * @param iMarker
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetMarkerAtFreq(double dFreq, FrequencyUnit freqUnit,
                                       int iMarker, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetMarkerAtFreq(dFreq, freqUnit, iMarker) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_SetModeView
 * @param eMode
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_SetModeView(ModeView eMode, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->SetModeView(eMode) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_GetCenterFreq
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_GetCenterFreq(FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{    
    bool ret = false;
    ret = m_spectFsv->GetCenterFreq(freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {        
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_GetValueAtMarker
 * @param valType
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_GetValueAtMarker(MarkerValueType valType, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->GetValueAtMarker(valType) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {        
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

bool Controller::Spect_GetValueAtMarker(MarkerValueType valType, int idx, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->GetValueAtMarker(valType, idx) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
    return true;
}

/**
 * @brief Controller::Spect_GetHarmonicDistortion
 * @param dFreq
 * @param iNumHarm
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_GetHarmonicDistortion(double dFreq, int iNumHarm,
                                             FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->GetHarmonicDistortion(dFreq, iNumHarm, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {        
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

/**
 * @brief Controller::Spect_GetSpurious
 * @param dFreq
 * @param dSpanValue
 * @param dBandWidthRaw
 * @param freqUnit
 * @param timeoutMillisec
 * @return
 */
bool Controller::Spect_GetSpurious(double dFreq, double dSpanValue, double dBandWidthRaw,
                                   FrequencyUnit freqUnit, uint32_t timeoutMillisec)
{
    bool ret = false;
    ret = m_spectFsv->GetSpurious(dFreq, dSpanValue, dBandWidthRaw, freqUnit) > 0 ? true:false;
    if(timeoutMillisec > 0 && ret) {        
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    } else {
        LREP("NO DELAY {}\r\n", __LINE__);
    }
    return ret;
}

bool Controller::Spect_SetComboFreqBw(double freq, FrequencyUnit fUnit, double bw,
                                FrequencyUnit bwUnit, uint32_t timeoutMillisec)
{
    Spect_SetCenterFreq(freq, fUnit, timeoutMillisec);
    return Spect_SetResolutionBandwidth(bw, bwUnit, timeoutMillisec);
}

bool Controller::Spect_GetPowerMaxHold(double freq, FrequencyUnit unit, double power, uint32_t timeoutMillisec)
{
    double dSpanValue = 100000; //40000000;   // 10000;   //100000; // 100Khz
    //Spect_SetCenterFreq(freq, unit, timeoutMillisec);
    Spect_SetComboFreqBw(freq, unit, 3000, Freq_Hz, timeoutMillisec);
    Spect_SetSpan(dSpanValue, Freq_Hz, timeoutMillisec);
    Spect_SetReferentLevel(power, timeoutMillisec);
    Spect_SetMarker(true, 1, timeoutMillisec);
    Spect_SetMarkerMax(timeoutMillisec);
    Spect_GetValueAtMarker(MarkerValueType_Level, timeoutMillisec);
    return true;
}

bool Controller::Spect_GetPowerAllHold(double freq, FrequencyUnit unit,
                                       uint32_t timeoutMillisec)
{
    double dSpanValue = 100000; // 100Khz
    Spect_SetCenterFreq(freq, unit, timeoutMillisec);
    Spect_SetSpan(dSpanValue, Freq_Hz, timeoutMillisec);
    Spect_SetReferentLevel(-50, timeoutMillisec);
    Spect_SetMarker(true, 1, timeoutMillisec);
    Spect_GetValueAtMarker(MarkerValueType_Level, 1, timeoutMillisec);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Spect_GetValueAtMarker(MarkerValueType_Level, 2, timeoutMillisec);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Spect_GetValueAtMarker(MarkerValueType_Level, 3, timeoutMillisec);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Spect_GetValueAtMarker(MarkerValueType_Level, 4, timeoutMillisec);
    return true;
}

bool Controller::Spect_GetFreqAtPower(double power,
                                      SearchDirection dir,
                                      uint32_t timeoutMillisec)
{
    return true;
}

bool Controller::Spect_SetupFMDemodSinad(double freq, FrequencyUnit fUnit,
                                         double bw, double time,
                                         uint32_t timeoutMillisec)
{
    m_spectFsv->SetFMDemod(freq, fUnit,
                           bw, time, timeoutMillisec);

    return true;
}

bool Controller::Spect_GetSinad(uint32_t timeoutMillisec)
{
    m_spectFsv->GetSinad();
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    return true;
}

bool Controller::Spect_SetSpectrumWindow(double freq, FrequencyUnit freqUnit,
                                         double span, FrequencyUnit spanUnit, double ref, uint32_t timeoutMillisec)
{
    m_spectFsv->SetSpectrumWindow(freq, freqUnit, span, spanUnit, ref, timeoutMillisec);
    return true;
}

bool Controller::Spect_GetScreenSpectrum(uint32_t timeoutMillisec)
{
    m_spectFsv->GetScreenSpectrum(timeoutMillisec);
    return true;
}

void Controller::Spect_ClearAllRecvData()
{
    Spect_ClearStringList();
    Spect_ClearRecvValue();
}




void Controller::Fpga_Start()
{
    if(m_fpga == nullptr) {
        m_fpga = std::make_shared<Fpga>();
    }
    m_fpga->SetEventConnectionCallback([&](communication::Event_Network evt) {
        emit sigFpgaStatus(evt);
    }, 0);

    m_fpga->SetEventDataCallback([&](const void *data, int len) {
        emit sigFpgaRecvData((uint8_t*)data, len);
    }, 0);

    m_fpga->Start(m_fpgaAddr, m_fpgaPort);
}

void Controller::Fpga_Stop()
{
    m_fpga->Stop();   
}

communication::Status_Network Controller::Fpga_GetStatus()
{
    return m_fpga->getStatus();
}

int Controller::Fpga_SendCommand(Sensor_Command cmd, uint8_t *data, uint8_t len)
{

    uint8_t *sendData = new uint8_t[len + 8];

    sendData[0] = (uint8_t)Auto_Config_Sensor;
    sendData[1] = (len >> 24) & 0xFF;
    sendData[2] = (len >> 16) & 0xFF;
    sendData[3] = (len >> 8) & 0xFF;
    sendData[4] = len & 0xFF;
    sendData[5] = cmd;
    sendData[6] = len;

    if(len > 0 && data != NULL) {
        memmove(&sendData[7], data, len);
        sendData[7+len] = CalCRC8(&sendData[7], len);
    }

    int wlen = m_fpga->sendDataToServerWoLength(sendData, len + 8);
    delete[] sendData;

    return wlen;

}

bool Controller::Ether_Start(std::string& name)
{
    m_nicName = name;
    m_etherTrans->SetEventDataCallback([&](uint8_t *data, uint32_t len) {
        Ether_ProcessMessage(data, len);
    }, 0);

    return m_etherTrans->start(m_nicName);
}

void Controller::Ether_Stop()
{
    m_etherTrans->stop();
}

communication::Status_Network Controller::Ether_GetStatus()
{
    return m_etherTrans->getStatus();
}

int Controller::Ether_SetSensorType(Sensor_Type_List type)
{
    int len = 1;
    uint8_t *sendData = new uint8_t[len];
    sendData[0] = (uint8_t)type;
    int wlen =  Ether_SendCommand(Command_Write_Ip, sendData, 1);
    delete[] sendData;
    return wlen;
}

int Controller::Ether_SetSensorIp(std::string ip, int port)
{    
    uint32_t ipValue;
    uint8_t *sendData = new uint8_t[6];
    uint16_t portValue = (uint16_t)port;

    LREP("SET: {}:{}\n", ip, port);
    ipValue = cppframework::str::Util::ipFromString(ip);
    if(ipValue == 0) return -1;
    sendData[0] = (ipValue >> 24) & 0xFF;
    sendData[1] = (ipValue >> 16) & 0xFF;
    sendData[2] = (ipValue >> 8) & 0xFF;
    sendData[3] = ipValue & 0xFF;
    sendData[4] = (portValue >> 8) & 0xFF;
    sendData[5] = portValue & 0xFF;

    int wlen =  Ether_SendCommand(Command_Write_Ip, sendData, 6);
    delete[] sendData;
    return wlen;
}

int Controller::Ether_GetSensorType()
{
    int wlen =  Ether_SendCommand(Command_Read_Type, NULL, 0);
    return wlen;
}

int Controller::Ether_GetSensorIp()
{
    int wlen =  Ether_SendCommand(Command_Read_Ip, NULL, 0);
    return wlen;
}

int Controller::Ether_ResetSensor()
{
    uint8_t *sendData = new uint8_t[33];
    sendData[0] = (uint8_t)Auto_Reset_Sensor;
    sendData[1] = '1';
    sendData[2] = '2';
    sendData[3] = '3';
    sendData[4] = '4';
    sendData[5] = 0;

    int wlen =  m_etherTrans->sendData(sendData, 33);
    delete[] sendData;
    return wlen;
}

int Controller::Ether_SendCommand(uint8_t command, uint8_t *data, uint32_t len)
{
    uint8_t *sendData = new uint8_t[len + 8];

    sendData[0] = (uint8_t)Auto_Config_Sensor;
    sendData[1] = (len >> 24) & 0xFF;
    sendData[2] = (len >> 16) & 0xFF;
    sendData[3] = (len >> 8) & 0xFF;
    sendData[4] = len & 0xFF;
    sendData[5] = command;
    sendData[6] = len;

    if(len > 0 && data != NULL) {
        memcpy(&sendData[7], data, len);
        sendData[7+len] = CalCRC8(&sendData[7], len);
    }

    int wlen = m_etherTrans->sendData(sendData, len + 8);
    delete[] sendData;

    return wlen;
}

void Controller::Ether_ProcessMessage(uint8_t *data, uint32_t len)
{    
     emit sigEtherRecvData(data, len);
}

/**
 * @brief Controller::ProcessServerControlMsg
 * @param data
 * @param len
 */
void Controller::ProcessServerControlMsg(const void *data, uint32_t len) {

    Message msg;
    if(msg.ParseFromArray(data, len)) {

        switch (msg.type()) {

        case ::Type::PONG:
//            if(!m_serverSsl->getDataInfo()) {
//                Server_ReqDatachannel(DATA_RAW, m_localIpAddress, m_serverUdpPort);
//            }
        case ::Type::RESPONSE:
            break;

        case ::Type::PERMISSION:
        {
            LREP("PERMISSION MSG\r\n");
        }
            break;
        case ::Type::DATA_CHANNEL:
        {
//            if(m_serverUdp->GetTransType() == DATA_ENCRYPTED) {
//                const ::google::protobuf::Any &datamsg = msg.data();
//                DataChannelResponse dataChannel;
//                datamsg.UnpackTo(&dataChannel);
//                m_aesKey = dataChannel.key();
//                LREP("Datachannel msg key length {}\r\n", m_aesKey.size());
//                m_serverUdp->SetAesKey(m_aesKey);
//            } else {
//                LREP_WARN("Transtype is raw\n");
//            }
//            m_serverSsl->setDataInfo(true);
        }
            break;
        case ::Type::MISSION:
        {
            LREP("Mission msg\r\n");
        }
            break;
        case ::Type::ONLINE:
        {
            LREP("Online msg\r\n");
        }
            break;
        case ::Type::SIGNAL_CALC:
        {
            LREP("Signal calc msg\r\n");
        }
            break;
        case ::Type::NOISEFLOOR:
        {
            LREP("Noise floor msg\r\n");
        }
            break;
        case ::Type::REMOTE_SENSOR:
        {
            LREP("Remote sensor msg\r\n");
        }
            break;
        case ::Type::LOCAL_SENSOR:
        {
            LREP("Local sensor msg\r\n");
        }
            break;
        case ::Type::SENSOR:
        {
            LREP("Sensor msg\r\n");
        }
            break;
        case ::Type::SERVER:
        {
            LREP("Server msg\r\n");
        }
            break;
        case ::Type::SPECTRUM_OFFLINE:
        {
            LREP("Spectrum online msg\r\n");
        }
            break;

        case ::Type::SIGNAL:
        {
            uint64_t freq;
            if(msg.data().Is<Async>()){
//                if(m_listSignal.size() >= 100) {
//                    LREP("Clear signal list\n")
//                    m_listSignal.clear();
//                }

                uint32_t size = 0;
                Async acsmsg;
                msg.data().UnpackTo(&acsmsg);                
                size = acsmsg.signal_size();

//                LREP("LIST: {}: ", size);
                for (int i = 0; i < acsmsg.signal_size(); i++) {
                    //LREP("FREQ:{}:{} ",(int)i, acsmsg.signal(i).frequency());
                    freq = acsmsg.signal(i).frequency();
                    if(std::labs(currFreqExp - freq) < 20000 ||
                            std::labs(currFreqExp2 - freq) < 20000 ||
                            std::labs(currFreqExp3 - freq) < 20000 ||
                            std::labs(currFreqExp4 - freq) < 20000)
//                    if(acsmsg.signal(i).power() < 0)
                        LREP("F:{}P:{}B:{} ", freq, acsmsg.signal(i).power(), acsmsg.signal(i).bandwidth());
                    //printf("#"); fflush(stdout);
                    if(m_listSignal.size() > 100) {
                        m_listSignal.pop_front();
                        //printf(".");
                    }
                    m_listSignal.push_back(acsmsg.signal(i));
                    //emit sigSignalRecv((quint64)freq);
                }
//                LREP("\n");
                //LREP("sig msg size: list size: {}-{}\n", m_listSignal.size(), size);
            }
        }
            break;
        case ::Type::GEOLOCATION:
        {
            LREP("Geo location msg\r\n");
            if(msg.data().Is<::geolocation::Response>()) {
                ::geolocation::Response response;
                msg.data().UnpackTo(&response);
                const Error &err = response.error();
                if(err.code() == 0) {
                    const ::external::client::Signal &signal = response.signal();
                    m_resTdoaSignalList.push_back(signal);
                } else {
                    LREP("ERROR: {}\n", err.message());
                }
            }

            if(msg.data().Is<::geolocation::Statistic>()) {
                ::geolocation::Statistic stat;
                msg.data().UnpackTo(&stat);
                for(int i = 0; i < stat.item_size(); i++) {
                    LREP(stat.item(i).DebugString());
                    LREP("State: {}\n", stat.item(i).state());
                }
            }

            if(msg.data().Is<::geolocation::Status>()) {
                ::geolocation::Status status;
                msg.data().UnpackTo(&status);
                emit sigServerTdoa(status);
            }

        }
            break;
        case ::Type::CLASSIFICATION:
        {
            LREP("Classification msg\r\n");
        }
            break;
        case ::Type::RECORDING:
        {
            LREP("Recording msg\r\n");
        }
            break;
        case ::Type::DEMODULATION:
        {
            LREP("Demodulation msg\r\n");
        }
            break;
        case ::Type::AUTOMATION:
        {
            LREP("Automation msg\r\n");
        }
            break;
        case ::Type::CALIBRATION:
        {
            LREP("Calibration msg\r\n");
        }
            break;
        case ::Type::TEST:
        {
            LREP("Test msg\r\n");
        }
            break;

        default:
            LREP("Not handled type: {}\r\n", msg.type());
            break;
        }
    } else {
        LREP("Parse failed\r\n");
    }
}


