#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "network/instrument/agilent5182.h"
//#include "network/datastream.h"
#include "network/secureclient.h"
#include "network/ethertrans.h"
#include "isc/layer2.h"
#include <QObject>
#include "client_msg/msg.pb.h"
#include "client_msg/connection/pingpong.pb.h"
#include "client_msg/msg.pb.h"
#include "client_msg/connection/authentication.pb.h"
#include "client_msg/configuration/mission.pb.h"
#include "client_msg/configuration/online.pb.h"
#include "client_msg/configuration/noisefloor.pb.h"
#include "client_msg/configuration/signalcalc.pb.h"
#include "client_msg/calibration/table.pb.h"
#include "client_msg/server/operation.pb.h"
#include "client_msg/signal/async.pb.h"
#include "client_msg/common.pb.h"
#include "client_msg/sensor/gain.pb.h"
#include "client_msg/sensor/update.pb.h"
#include "client_msg/server/clear.pb.h"
#include "client_msg/test/sensor_configuration.pb.h"

// TDOA feature
#include "client_msg/geolocation/geo_request.pb.h"
#include "client_msg/geolocation/geo_response.pb.h"
#include "client_msg/geolocation/geo_cancel.pb.h"
#include "client_msg/geolocation/geo_statistic.pb.h"
#include "client_msg/geolocation/geo_status.pb.h"
#include "instrument/spectrumfsv.h"
#include "network/devicecontrol.h"
#include "ui/testconfig.h"
#include "fpga.h"





class Controller : public QObject
{

    Q_OBJECT
public:
    Controller();
    ~Controller();

    void ConfigInstrument2(std::string ipAddr, int port) {m_sigGen1TcpAddr = ipAddr; m_sigGen1TcpPort = port;}

    std::string GetIpV4Address();        
    void getAllNetworkInterface();

    void CreateConnection();
    void StopAll();

    void ConfigIsc(std::string devName, int baudRate) { m_rfDevName = devName, m_rfDevBaudrate = baudRate;}
    void Dev_Start();
    void Dev_Stop();

    bool Dev_GetStatus() { return m_serialDev->Mac_GetStatus();}
    void Dev_IFRFSendCommand(uint8_t type, uint8_t command,
                             uint8_t *data, uint8_t len, bool ackRreq = false);
    void Dev_SetFreqency(uint64_t freq, bool ackReq = false);
    void Dev_SetAttent(double value, bool ackReq);
    void Dev_ReqConnect(bool ackReq = false);
    void Dev_SetAtten(uint8_t value, bool ackReq = false);


    void Dev_RFDLSendCommand(uint8_t command, uint8_t *data, uint8_t len, bool ackRreq = false);
    void Dev_RFDLSetParam(uint64_t freq, uint32_t on, uint32_t off,
                          uint32_t ns1, uint32_t ns2, uint32_t ns3, uint32_t ns4);

    void Dev_SendData(uint8_t dest, uint8_t *data, uint8_t len, bool ackReq = false);


    void Server_ProcessSecureTcpMessage(uint8_t *data, uint32_t len);
    void Server_ProcessSpectrumData(uint8_t *data, uint32_t len);
    void Server_ProcessSignalListData(uint8_t *data, uint32_t len);
    void Server_ProcessAudioData(uint8_t *data, uint32_t len);
    void Server_ProcessNoiseFloor(uint8_t *data, uint32_t len);
    void Server_ProcessSpectrumOffline(uint8_t *data, uint32_t len);
    void ConvertToFloatArray(float *data, uint8_t *buffer, uint32_t len);
    //void AnalizeSignalList(SignalData *sigList, uint8_t *data, uint16_t sigCount);

    bool Server_CheckHasSignalFrequency(uint64_t freq, uint64_t err);
    void Server_ClearSignaListReceived();

    double Server_CheckSignalPower(uint64_t freq, uint64_t err);
    double Server_CheckHasSignalPower(uint64_t freq, uint64_t err);
    FreqPoint Server_CheckCalibSignal(uint64_t freq, uint64_t err);
    uint32_t Server_CheckBandwidth(uint64_t freq, uint64_t err);
    uint64_t Server_GetReceivedFrequency(uint64_t freq, uint64_t err);
    external::client::Signal Server_GetSignalHasPower(uint64_t freq, uint64_t err);
    external::client::Signal Server_GetSignalTdoa(uint64_t freq, uint64_t err);

    void  SetLocalIp(std::string localIp) { m_localIpAddress = localIp;}
    void  SetSigenType(SigGenType type) { m_sigType = type;}
    void  SetSpectType(SpectrumType type) { m_spectType = type;}
    void  SetPowerType(PowerType type) { m_powerType = type;}

public slots:

signals:
    // Recv signal list from server
    void sigSignalRecv(quint64 freq);
    // Notify server connected status
    void sigServerStatus(int evt);
    // Notiry signal gen connected status
    void sigSigGenStatus(int evt);
    // Notify spectrum connected status
    void sigSpectStatus(int evt);
    // Notify spectrum data event
    void sigSpectRecvData(uint8_t *data, int len);
    // Notify fpga connected status
    void sigFpgaStatus(int evt);
    // Notify fpga recv data event
    void sigFpgaRecvData(uint8_t *data, int len);
    // Notify sensor recv data event
    void sigEtherRecvData(uint8_t *data, int len);
    // Notify ifrf connected status
    void sigSerialDevStatus(int evt);
    // Notify ifrf recv data event
    void sigSerialDevRecvData(uint8_t *data, int len);
    // Notify Server recv TDOA status
    void sigServerTdoa(external::client::geolocation::Status status);

public:

    void disconnectAllConnection();
    void addConnection(const QMetaObject::Connection &connection);

    /**
     * @brief Server control
     */
    void ConfigSslClient(std::string sslTcpAddr, int sslTcpPort) {
        m_serverSslAddr = sslTcpAddr;
        m_serverSslPort = sslTcpPort;
    }

    void ConfigUdp(std::string streamUdpAddr, int streamUdpPort) {
        m_serverUdpAddr = streamUdpAddr;
        m_serverUdpPort = streamUdpPort;
    }

    void Server_StartSslClient();
    void Server_StopSslClient();
    void Server_StartUdpClient();
    void Server_StopUdpClient();
    void ProcessServerControlMsg(const void *data, uint32_t len);
    void Server_SendMessage(external::client::Message &msg);
    void Server_SetRecvFreq(double freq, uint32_t bandwidth, uint64_t timeoutMillisec = 0);
    void Server_SetGain(uint8_t sensorId, double gain, uint64_t timeoutMillisec = 0);
    //void Server_ReqDatachannel(DataTransferType type, std::string ipAddr, int port, uint64_t timeoutMillisec = 0);
    void Server_SetTimeRecvDuration(uint32_t time);
    void Server_GetSignalList();
    void Server_SetNoiseFloor(uint32_t mode, float factor, uint64_t timeoutMillisec = 0 );
    void Server_SetSigCalc(uint32_t mode, uint32_t option, float factor, uint64_t timeoutMillisec = 0);
    void Server_SaveCalibTable(CalibMode mode, std::list<FreqPoint> &list, uint64_t timeoutMillisec = 0);
    void Server_SetServerOperationMode(ServerOperationMode mode);
    void Server_ClearSignalDataBase();
    void Server_SendTdoaMessage(external::client::Signal &signal, external::client::geolocation::Request::Mode mode);
    void Server_SendSensorInfo(double lat0, double long0, double lat1,
                               double long1, double lat2,double long2,
                               double lat3, double long3, int numSensor);
    communication::Status_Network Server_GetStatus() {return m_serverSsl->getStatus();}

    /**
     * @brief Signal generator control
     */
    void ConfigSigGen(std::string ipAddr, int port) {
        m_sigGen1TcpAddr = ipAddr;
        m_sigGen1TcpPort = port;        
    }
    void SigGen_Start();
    void SigGen_Stop();
    communication::Status_Network SigGen_GetStatus();
    bool SigGen_InitDevice();
    bool SigGen_SetRFPower(double pwr, PowerUnit unit,
                          uint32_t timeoutMillisec = 200);
    bool SigGen_SetRFSignalOut(bool on, uint32_t timeoutMillisec = 200);
    bool SigGen_SetFMOut(bool on, uint32_t timeoutMillisec = 200);
    bool SigGen_SetRFFreq(double freq, FrequencyUnit unit,
                         uint32_t timeoutMillisec = 200);
    bool SigGen_GetCurrRFPower();

    int SigGen_SetCombo(double freq, FrequencyUnit fUnit,
                        double pwr,  PowerUnit pUnit,
                        double bw, FrequencyUnit bwUnit,
                        uint32_t timeoutMillisec = 200);

    int SigGen_SetupFMMod(double freq, FrequencyUnit fUnit,
                    double pwr, PowerUnit pUnit, double bw, FrequencyUnit bwUnit,
                    uint32_t timeoutMillisec = 200);

    bool SigGen_DeSetCombo(uint32_t timeoutMillisec = 200);

    bool SigGen_PresetDevice();

    bool SigGen_SetALC(bool on, uint32_t timeoutMillisec = 200);
    bool SigGen_SetModOut(bool on, uint32_t timeoutMillisec = 200);
    bool SigGen_SetFMDeviation(double dev,
                              FrequencyUnit unit,
                              uint32_t timeoutMillisec = 200);
    bool SigGen_SetFMRate(double rate,
                         FrequencyUnit unit,
                         uint32_t timeoutMillisec = 200);

    bool SigGen_SetFMARB(uint32_t sampleClock,
                         double freq, FrequencyUnit freqUnit, std::string file,
                         double power, PowerUnit pwrUnit, uint32_t timeoutMillisec = 200);

    bool SigGen_SetTwoTone(double freq, FrequencyUnit freqUnit,
                           double space, FrequencyUnit spaceUnit,
                           double power, PowerUnit pwrUnit, uint64_t delayMillisec = 200);


    /**
     * @brief Spectrum control
     *
     */
    void ConfigSpectrum(std::string ipAddr, int port) {
        m_spectAddr = ipAddr; m_spectPort = port;
    }

    void Spect_Start();
    void Spect_Stop();
    communication::Status_Network Spect_GetStatus() {return m_spectFsv->getStatus();}

    bool Spect_InitDevice();
    bool Spect_SendCommand(const std::string &command);
    bool Spect_SetupSpecAnalyzer(uint32_t timeoutMillisec = 200);
    bool Spect_SetupSpecAnalyzerMode(MeasurementMode mode, uint32_t timeoutMillisec = 200);
    bool Spect_SetCenterFreq(double dFreq, FrequencyUnit freqUnit,
                             uint32_t timeoutMillisec = 200);
    bool Spect_SetSpan(double dSpanValue, FrequencyUnit freqUnit,
                       uint32_t timeoutMillisec = 200);
    bool Spect_SetReferentLevel(double dReferValue,
                                uint32_t timeoutMillisec = 200);
    bool Spect_SetSpecAnttenuation(double dAttenuatonValue,
                                   uint32_t timeoutMillisec = 200);
    bool Spect_SetStopFreq(double dStopFreq, FrequencyUnit freqUnit,
                           uint32_t timeoutMillisec = 200);
    bool Spect_SetResolutionBandwidth(double dRbw, FrequencyUnit freqUnit,
                                      uint32_t timeoutMillisec = 200);
    bool Spect_SetMarker(bool bOnOff, int iMakerIndex,
                         uint32_t timeoutMillisec = 200);
    bool Spect_SetMarkerMax(uint32_t timeoutMillisec = 200);
    bool Spect_SetNextMarkerMax(int iMaxker, SearchDirection searchDir,
                                uint32_t timeoutMillisec = 200);
    bool Spect_SetMarkerAtFreq(double dFreq, FrequencyUnit freqUnit, int iMarker,
                               uint32_t timeoutMillisec = 200);
    bool Spect_SetModeView(ModeView eMode,
                           uint32_t timeoutMillisec = 200);
    bool Spect_GetCenterFreq(FrequencyUnit freqUnit,
                             uint32_t timeoutMillisec = 200);
    bool Spect_GetValueAtMarker(MarkerValueType valType,
                                uint32_t timeoutMillisec = 200);
    bool Spect_GetValueAtMarker(MarkerValueType valType,
                                int idx,
                                uint32_t timeoutMillisec = 200);

    bool Spect_GetHarmonicDistortion(double dFreq, int iNumHarm, FrequencyUnit freqUnit,
                                     uint32_t timeoutMillisec = 200);
    bool Spect_GetSpurious(double dFreq, double dSpanValue,
                    double dBandWidthRaw, FrequencyUnit freqUnit,
                           uint32_t timeoutMillisec = 200);

    bool Spect_SetComboFreqBw(double freq, FrequencyUnit fUnit,
                        double bw, FrequencyUnit bwUnit,
                        uint32_t timeoutMillisec = 200);

    bool Spect_GetPowerMaxHold(double freq, FrequencyUnit unit, double power,
                               uint32_t timeoutMillisec = 200);

    bool Spect_GetPowerAllHold(double freq, FrequencyUnit unit,
                               uint32_t timeoutMillisec = 200);

    bool Spect_GetFreqAtPower(double power, SearchDirection dir,
                              uint32_t timeoutMillisec = 200);

    bool Spect_SetupFMDemodSinad(double freq, FrequencyUnit fUnit,
                                 double bw, double time,
                                 uint32_t timeoutMillisec = 200);
    bool Spect_GetSinad(uint32_t timeoutMillisec = 200);

    bool Spect_SetSpectrumWindow(double freq, FrequencyUnit freqUnit,
                                 double span, FrequencyUnit spanUnit, double ref,
                                 uint32_t timeoutMillisec = 200);

    bool Spect_GetScreenSpectrum(uint32_t timeoutMillisec = 200);

    void Spect_ClearStringList() {list_spect_string_.clear(); recv_string_.clear();}

    void Spect_ClearAllRecvData();

    void Spect_ClearRecvValue() {list_spect_value_.clear();}

    void Spect_StartCalculate();

    bool Spect_GetFirstValue(double &value);
    bool Spect_GetValueAtPoint(uint64_t freq, double &value);
    bool Spect_GetValueMaxAt(uint64_t freq, double &value, uint64_t range);

    bool Spect_GetMaxValue(double &value);

    std::size_t Spect_GetListValueSize() { return list_spect_value_.size();}

    std::list<FreqPoint> Spect_GetValueExcess(double value);

    void ConfigFpga(std::string ipAddr, int port) {
        m_fpgaAddr = ipAddr;
        m_fpgaPort = port;
    }
    void Fpga_Start();
    void Fpga_Stop();
    communication::Status_Network Fpga_GetStatus();
    int Fpga_SendCommand(Sensor_Command cmd, uint8_t *data, uint8_t len);


    bool Ether_Start(std::string &name);
    void Ether_Stop();
    communication::Status_Network Ether_GetStatus();        
    int  Ether_SetSensorType(Sensor_Type_List type);
    int  Ether_SetSensorIp(std::string ip, int port);
    int  Ether_GetSensorType();
    int  Ether_GetSensorIp();
    int  Ether_ResetSensor();
    int  Ether_SendCommand(uint8_t command, uint8_t *data, uint32_t len);
    void Ether_ProcessMessage(uint8_t *data, uint32_t len);

public :
    std::shared_ptr<communication::isc::Layer2>             m_serialDev;
    std::shared_ptr<Agilent5182>        m_sigGenAgilent;
    std::shared_ptr<Fpga>               m_fpga;
    std::shared_ptr<SpectrumFsv>        m_spectFsv;
    //std::shared_ptr<DataStream>         m_serverUdp;
    std::shared_ptr<SecureClient>       m_serverSsl;
    std::shared_ptr<EtherTrans>         m_etherTrans;

    std::string m_rfDevName;
    int         m_rfDevBaudrate;

    std::string m_sigGen1TcpAddr;
    int         m_sigGen1TcpPort;


    std::string m_instr2TcpAddr;
    int         m_instr2TcpPort;

    std::string m_serverUdpAddr;
    int         m_serverUdpPort;

    std::string m_serverSslAddr;
    int         m_serverSslPort;
    std::string m_localIpAddress;

    std::string m_spectAddr;
    int         m_spectPort;

    std::string m_fpgaAddr;
    int         m_fpgaPort;

    std::string m_nicName;

    std::string m_aesKey;

    std::list<external::client::Signal> m_listSignal;
    std::list<external::client::Signal> m_resTdoaSignalList;
    QList<QMetaObject::Connection> m_connections;

    std::list<std::string> list_spect_string_;
    std::string recv_string_;
    std::list<FreqPoint>   list_spect_value_;


    SigGenType m_sigType;
    SpectrumType m_spectType;
    PowerType m_powerType;

    uint64_t currFreqExp;
    uint64_t currFreqExp2;
    uint64_t currFreqExp3;
    uint64_t currFreqExp4;
};

#endif // CONTROLLER_H
