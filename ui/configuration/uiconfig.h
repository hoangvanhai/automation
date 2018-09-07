#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <iostream>
#include <configuration/pugixml.hpp>
#include <ui/testconfig.h>
#include <fstream>
#include <memory>
#include <string/StringUtils.h>
#include <debug.h>
#include <QString>
#include <QDir>


using namespace cppframework;
template <typename T>
class Singleton {
public:
    Singleton() {};
    ~Singleton() {};

    static T* getInstance() {
        if(m_instance == nullptr) {
            m_instance = new T();
        }
        return m_instance;
    }

    static void destroyInstance() {
        std::cout << "Delete instance\n";
        delete m_instance;
    }

protected:
    static T* m_instance;
};

template <typename T>
T* Singleton<T>::m_instance = nullptr;


template <typename T>
std::string ToString(T const & in_val)
{
    return std::to_string(in_val);
}


typedef struct {
    SigGenType      sigGenType;
    SpectrumType    spectType;
    PowerType       powerType;
    std::string     localIp;
    uint16_t        localPort;
    std::string     loadFileHighName;
    std::string     loadFileLowName;
    uint32_t        siggenDelay;
    uint32_t        spectDelay;
    uint32_t        serverDelay;
    uint32_t        bandwidthHigh;
    uint32_t        bandwidthLow;
    uint32_t        mainTabUsed;
    uint32_t        tabUsed;
    uint32_t        setupInOut;
    std::string     inputDir;
    std::string     outputDir;
}GeneralConfig;

typedef struct  {
    std::string SigGenIp;
    uint32_t    siggenPort;
    std::string spectIp;
    uint32_t    spectPort;
    uint32_t    keepTestIfFaled;
    uint32_t    reTestIfFailed;
}IfrfConfig;

typedef struct {
    uint32_t    keepTestIfFaled;
    uint32_t    reTestIfFailed;
    std::string ServerIp;
    uint32_t    sslPort;
    uint32_t    udpPort;
}SystemConfig ;

typedef struct {
    uint32_t    keepTestIfFaled;
    uint32_t    reTestIfFailed;
    uint32_t    pauseTest;

    std::string fpgaIp;
    uint16_t    fpgaPort;
}FpgaConfig ;

typedef struct {
    uint32_t    keepTestIfFaled;
    uint32_t    reTestIfFailed;

    int32_t     utc;
    double       longitude;
    double       latitude;
}GpsdoConfig ;

typedef struct {
    std::string ServerIp;
    uint16_t    sslPort;
    uint16_t    udpPort;
    std::string SigGenIp;
    uint16_t    siggenPort;
    uint32_t    keepTestIfFaled;
    uint32_t    reTestIfFailed;
}SensorConfig;

typedef struct  {
    IfrfConfig          ifrfCfg;
    SensorConfig        sensorCfg;
    SensorConfig        calibSenCfg;
    SystemConfig        sysCfg;
    FpgaConfig          fpgaCfg;
    GpsdoConfig          gpsdoCfg;
    FpgaConfig          ctrlPtCfg;
    GeneralConfig       genCfg;
}UserConfig;



class UiConfig : public Singleton<UiConfig>
{

public:
    UiConfig();
    ~UiConfig();

    bool openXmlFile(const std::string &filename);    
    bool closeXmlFile();
    void loadConfigFromXmlFile();
    bool saveNodeLevel2(const std::string &parent, const std::string &name,
                         const std::string &value);
    std::string loadNodeLevel2(const std::string &parent, const std::string &name, const std::string &defValue);
    bool searchNode(pugi::xml_node &searchIn, std::string &name);

    static double convertToDouble(std::string string, double def);
    static float convertToFloat(std::string value, float def);

    UserConfig getUserConfig() {return m_userCfg;}
    void setUserConfig(UserConfig cfg) {m_userCfg = cfg;}

    IfrfConfig          getIfrfConfig() {return m_userCfg.ifrfCfg;}
    void                setIfrfConfig(IfrfConfig cfg) {m_userCfg.ifrfCfg = cfg;}

    SensorConfig        getSensorConfig() {return m_userCfg.sensorCfg;}
    void                setSensorConfig(SensorConfig cfg) {m_userCfg.sensorCfg = cfg;}

    SensorConfig        getCalibSenConfig() {return m_userCfg.calibSenCfg;}
    void                setCalibSenConfig(SensorConfig cfg) {m_userCfg.calibSenCfg = cfg;}

    SystemConfig        getSystemConfig() {return m_userCfg.sysCfg;}
    void                setSystemConfig(SystemConfig cfg) {m_userCfg.sysCfg = cfg;}

    FpgaConfig          getFpgaConfig() {return m_userCfg.fpgaCfg;}
    void                setFpgaConfig(FpgaConfig cfg) {m_userCfg.fpgaCfg = cfg;}

    GpsdoConfig         getGpsdoConfig() {return m_userCfg.gpsdoCfg;}
    void                setGpsdoConfig(GpsdoConfig cfg) {m_userCfg.gpsdoCfg = cfg;}

    FpgaConfig          getCtrlPtConfig() {return m_userCfg.ctrlPtCfg;}
    void                setCtrlPtConfig(FpgaConfig cfg) {m_userCfg.ctrlPtCfg = cfg;}

    GeneralConfig       getGeneralConfig() {return m_userCfg.genCfg;}
    void                setGeneralConfig(GeneralConfig cfg) {m_userCfg.genCfg = cfg;}

protected:
    std::string m_filename;
    std::shared_ptr<pugi::xml_document> m_doc;
    pugi::xml_parse_result m_result;
    bool    isSave;
    UserConfig m_userCfg;


public:

    /***************************************** GENERAL SESSION ****************************************/
    bool setGeneralInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("General", tag, value);}

    std::string loadGeneralInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("General", tag, defValue);}

    bool saveGeneralSigGenType(uint32_t type) {
        m_userCfg.genCfg.sigGenType = (SigGenType)type;        
        return setGeneralInfo("SigGenType", ToString(type));
    }
    uint32_t loadGeneralSigGenType() {
        m_userCfg.genCfg.sigGenType =
                (SigGenType)str::Util::convert<uint32_t>(loadGeneralInfo("SigGenType", ToString(0)), 0);        
        return m_userCfg.genCfg.sigGenType;
    }

    bool saveGeneralSpectrumType(uint32_t type) {
        m_userCfg.genCfg.spectType = (SpectrumType)type;
        return setGeneralInfo("SpectrumType", ToString(type));
    }
    uint32_t loadGeneralSpectrumType() {
        m_userCfg.genCfg.spectType =
                (SpectrumType)str::Util::convert<uint32_t>(loadGeneralInfo("SpectrumType", ToString(0)), 0);
        return m_userCfg.genCfg.spectType;
    }

    bool saveGeneralPowerType(uint8_t type) {
        m_userCfg.genCfg.powerType = (PowerType)type;
        return setGeneralInfo("PowerType", ToString(type));}
    uint32_t loadGeneralPowerType() {
        m_userCfg.genCfg.powerType =
                (PowerType)str::Util::convert<uint32_t>(loadGeneralInfo("PowerType", ToString(0)), 0);
        return m_userCfg.genCfg.powerType;
    }

    bool saveGeneralLocalIp(const std::string &ip) {
        m_userCfg.genCfg.localIp = ip;
        return setGeneralInfo("LocalIp", ip);}
    std::string loadGeneralLocalIp() {
        m_userCfg.genCfg.localIp = loadGeneralInfo("LocalIp", std::string(DEFAULT_LOCAL_IP));
        return m_userCfg.genCfg.localIp;
    }

    bool saveGeneralLocalPort(uint16_t port){
        m_userCfg.genCfg.localPort = port;
        return setGeneralInfo("LocalPort", ToString(port));}
    uint16_t loadGeneralLocalPort() {
        m_userCfg.genCfg.localPort =
                str::Util::convert<uint16_t>(loadGeneralInfo("LocalPort", ToString(12399)), 12399);
        return m_userCfg.genCfg.localPort;
    }

    bool saveGeneralFileNameHigh(const std::string &fileName) {
        m_userCfg.genCfg.loadFileHighName = fileName;
        return setGeneralInfo("MeasureFileNameHigh", fileName);}
    std::string loadGeneralFileNameHigh() {
        m_userCfg.genCfg.loadFileHighName =
                loadGeneralInfo("MeasureFileNameHigh", std::string("WAVEFORM_NOISY_25KHZ"));
        return m_userCfg.genCfg.loadFileHighName;
    }

    bool saveGeneralFileNameLow(const std::string &fileName) {
        m_userCfg.genCfg.loadFileLowName = fileName;
        return setGeneralInfo("MeasureFileNameLow", fileName);}
    std::string loadGeneralFileNameLow() {
        m_userCfg.genCfg.loadFileLowName =
                loadGeneralInfo("MeasureFileNameLow", std::string("WAVEFORM_NOISY_15KHZ"));
        return m_userCfg.genCfg.loadFileLowName;
    }

    bool saveGeneralSigGenDelay(uint32_t delay) {
        m_userCfg.genCfg.siggenDelay = delay;
        return setGeneralInfo("SigGenDelay", ToString(delay));}
    uint32_t loadGeneralSigGenDelay() {
        m_userCfg.genCfg.siggenDelay =
                str::Util::convert<uint32_t>(loadGeneralInfo("SigGenDelay", ToString(200)), 200);
        return m_userCfg.genCfg.siggenDelay;
    }

    bool saveGeneralSpectrumDelay(uint32_t delay) {
        m_userCfg.genCfg.spectDelay = delay;
        return setGeneralInfo("SpectrumDelay", ToString(delay));}
    uint32_t loadGeneralSpectrumDelay() {
        m_userCfg.genCfg.spectDelay =
        str::Util::convert<uint32_t>(loadGeneralInfo("SpectrumDelay", ToString(200)), 200);
        return m_userCfg.genCfg.spectDelay;
    }

    bool saveGeneralServerDelay(uint32_t delay) {
        m_userCfg.genCfg.serverDelay = delay;
        return setGeneralInfo("ServerDelay", ToString(delay));}
    uint32_t loadGeneralServerDelay() {
        m_userCfg.genCfg.serverDelay =
        str::Util::convert<uint32_t>(loadGeneralInfo("ServerDelay", ToString(20000)), 20000);
        return m_userCfg.genCfg.serverDelay;
    }

    bool saveGeneralBandwidthHigh(uint32_t bw) {
        m_userCfg.genCfg.bandwidthHigh = bw;
        return setGeneralInfo("BandwidthHigh", ToString(bw));}
    uint32_t loadGeneralBandwidthHigh() {
        m_userCfg.genCfg.bandwidthHigh =
        str::Util::convert<uint32_t>(loadGeneralInfo("BandwidthHigh", ToString(25000)), 25000);
        return m_userCfg.genCfg.bandwidthHigh;
    }

    bool saveGeneralBandwidthLow(uint32_t bw) {
        m_userCfg.genCfg.bandwidthLow = bw;
        return setGeneralInfo("BandwidthLow", ToString(bw));}
    uint32_t loadGeneralBandwidthLow() {
        m_userCfg.genCfg.bandwidthLow =
        str::Util::convert<uint32_t>(loadGeneralInfo("BandwidthLow", ToString(15000)), 15000);
        return m_userCfg.genCfg.bandwidthLow;
    }

    bool saveGeneralTabUsed(uint32_t tab) {
        m_userCfg.genCfg.tabUsed = tab;
        return setGeneralInfo("TabUsed", ToString(tab));}
    uint32_t loadGeneralTabUsed() {
        m_userCfg.genCfg.tabUsed =
        str::Util::convert<uint32_t>(loadGeneralInfo("TabUsed", ToString(0)), 0);
        return m_userCfg.genCfg.tabUsed;
    }

    bool saveGeneralMainTabUsed(uint32_t tab) {
        m_userCfg.genCfg.mainTabUsed = tab;
        return setGeneralInfo("MainTabUsed", ToString(tab));}
    uint32_t loadGeneralMainTabUsed() {
        m_userCfg.genCfg.mainTabUsed =
        str::Util::convert<uint32_t>(loadGeneralInfo("MainTabUsed", ToString(0)), 0);
        return m_userCfg.genCfg.mainTabUsed;
    }


    bool saveGeneralInputDir(const std::string &fileName) {
        m_userCfg.genCfg.inputDir = fileName;
        return setGeneralInfo("InputDir", fileName);}
    std::string loadGeneralInputDir() {        
        m_userCfg.genCfg.inputDir =
                loadGeneralInfo("InputDir", QDir::homePath().toStdString() + "/testlist");
        return m_userCfg.genCfg.inputDir;
    }

    bool saveGeneralOutputDir(const std::string &fileName) {
        m_userCfg.genCfg.outputDir = fileName;
        return setGeneralInfo("OutputDir", fileName);}
    std::string loadGeneralOutputDir() {
        m_userCfg.genCfg.outputDir =
                loadGeneralInfo("OutputDir", QDir::homePath().toStdString() + "/testoutput");
        return m_userCfg.genCfg.outputDir;
    }

    bool saveGeneralSetupInOut(uint32_t tab) {
        m_userCfg.genCfg.setupInOut = tab;
        return setGeneralInfo("SetupInOut", ToString(tab));}
    uint32_t loadGeneralSetupInOut() {
        m_userCfg.genCfg.setupInOut =
        str::Util::convert<uint32_t>(loadGeneralInfo("SetupInOut", ToString(0)), 0);
        return m_userCfg.genCfg.setupInOut;
    }

    /***************************************** SENSOR SESSION ****************************************/
    bool setSensorInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("Sensor", tag, value);}

    std::string loadSensorInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("Sensor", tag, defValue);}

    bool saveSensorServerAddress(const std::string &ip) {
        m_userCfg.sensorCfg.ServerIp = ip;
        return setSensorInfo("ServerIp", ip);}
    std::string loadSensorServerIp() {
        m_userCfg.sensorCfg.ServerIp =
        loadSensorInfo("ServerIp", std::string(DEFAULT_SERVER_IP));
        return m_userCfg.sensorCfg.ServerIp;
    }

    bool saveSensorServerSslPort(uint16_t port) {
        m_userCfg.sensorCfg.sslPort = port;
        return setSensorInfo("ServerSslPort", ToString(port));}
    uint16_t loadSensorServerSslPort() {
        m_userCfg.sensorCfg.sslPort =
        str::Util::convert<uint16_t>(loadSensorInfo("ServerSslPort", ToString(DEFAULT_SERVER_PORT)),DEFAULT_SERVER_PORT );
        return m_userCfg.sensorCfg.sslPort;
    }

    bool saveSensorServerUdpPort(uint16_t port) {
        m_userCfg.sensorCfg.udpPort = port;
        return setSensorInfo("ServerUdpPort", ToString(port));}
    uint16_t loadSensorServerUdpPort() {
        m_userCfg.sensorCfg.udpPort =
        str::Util::convert<uint16_t>(loadSensorInfo("ServerUdpPort", ToString(DEFAULT_SERVER_UDP_PORT)), DEFAULT_SERVER_UDP_PORT);
        return m_userCfg.sensorCfg.udpPort;
    }

    bool saveSensorSigGenIp(const std::string &ip) {
        m_userCfg.sensorCfg.SigGenIp = ip;
        return setSensorInfo("SigGenIp", ip);}
    std::string loadSensorSigGenIp() {
        m_userCfg.sensorCfg.SigGenIp =
        loadSensorInfo("SigGenIp", std::string(DEFAULT_INSTR_IP));
        return m_userCfg.sensorCfg.SigGenIp;
    }


    bool saveSensorSigGenPort(uint16_t port) {
        m_userCfg.sensorCfg.siggenPort = port;
        return setSensorInfo("SigGenTcpPort", ToString(port));}
    uint16_t loadSensorSigGenPort() {
        m_userCfg.sensorCfg.siggenPort =
        str::Util::convert<uint16_t>(loadSensorInfo("SigGenTcpPort", ToString(DEFAULT_INSTR_PORT)), DEFAULT_INSTR_PORT);
        return m_userCfg.sensorCfg.siggenPort;
    }

    bool saveSensorKeepTestIfFailed(uint32_t value) {
        m_userCfg.sensorCfg.keepTestIfFaled = value;
        return setSensorInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadSensorKeepTestIfFailed() {
        m_userCfg.sensorCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadSensorInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.sensorCfg.keepTestIfFaled;
    }

    bool saveSensorReTestIfFailed(uint32_t value) {
        m_userCfg.sensorCfg.reTestIfFailed = value;
        return setSensorInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadSensorReTestIfFailed() {
        m_userCfg.sensorCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadSensorInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.sensorCfg.reTestIfFailed;
    }

    /***************************************** SYSTEM SESSION ****************************************/
    bool setSystemInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("System", tag, value);}

    std::string loadSystemInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("System", tag, defValue);}

    bool saveSystemServerAddress(const std::string &ip) {
        m_userCfg.sysCfg.ServerIp = ip;
        return setSystemInfo("ServerIp", ip);}
    std::string loadSystemServerIp() {
        m_userCfg.sysCfg.ServerIp =
        loadSystemInfo("ServerIp", std::string(DEFAULT_SERVER_IP));
        return m_userCfg.sysCfg.ServerIp;
    }

    bool saveSystemServerSslPort(uint16_t port) {
        m_userCfg.sysCfg.sslPort = port;
        return setSystemInfo("ServerSslPort", ToString(port));}
    uint16_t loadSystemServerSslPort() {
        m_userCfg.sysCfg.sslPort =
        str::Util::convert<uint16_t>(loadSystemInfo("ServerSslPort", ToString(DEFAULT_SERVER_PORT)), DEFAULT_SERVER_PORT);
        return m_userCfg.sysCfg.sslPort;
    }

    bool saveSystemServerUdpPort(uint16_t port) {
        m_userCfg.sysCfg.udpPort = port;
        return setSystemInfo("ServerUdpPort", ToString(port));}
    uint16_t loadSystemServerUdpPort() {
        m_userCfg.sysCfg.udpPort =
        str::Util::convert<uint16_t>(loadSystemInfo("ServerUdpPort", ToString(DEFAULT_SERVER_UDP_PORT)), DEFAULT_SERVER_UDP_PORT);
        return m_userCfg.sysCfg.udpPort;
    }

    bool saveSystemKeepTestIfFailed(uint32_t value) {
        m_userCfg.sysCfg.keepTestIfFaled = value;
        return setSystemInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadSystemKeepTestIfFailed() {
        m_userCfg.sysCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadSystemInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.sysCfg.keepTestIfFaled;
    }

    bool saveSystemReTestIfFailed(uint32_t value) {
        m_userCfg.sysCfg.reTestIfFailed = value;
        return setSystemInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadSystemReTestIfFailed() {
        m_userCfg.sysCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadSystemInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.sysCfg.reTestIfFailed;
    }


    /***************************************** IFRF SESSION ****************************************/
    bool setIfrfInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("IfrfBoard", tag, value);}

    std::string loadIfrfInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("IfrfBoard", tag, defValue);}


    bool saveIfrfSigGenIp(const std::string &ip) {
        m_userCfg.ifrfCfg.SigGenIp = ip;
        return setIfrfInfo("SigGenIp", ip);}
    std::string loadIfrfSigGenIp() {
        m_userCfg.ifrfCfg.SigGenIp =
        loadIfrfInfo("SigGenIp", std::string(DEFAULT_INSTR_IP));
        return m_userCfg.ifrfCfg.SigGenIp;
    }

    bool saveIfrfSigGenPort(uint16_t port) {
        m_userCfg.ifrfCfg.siggenPort = port;
        return setIfrfInfo("SigGenTcpPort", ToString(port));}
    uint16_t loadIfrfSigGenPort() {
        m_userCfg.ifrfCfg.siggenPort =
        str::Util::convert<uint16_t>(loadIfrfInfo("SigGenTcpPort", ToString(DEFAULT_INSTR_PORT)), DEFAULT_INSTR_PORT);
        return m_userCfg.ifrfCfg.siggenPort;
    }

    bool saveIfrfSpectIp(const std::string &ip) {
        m_userCfg.ifrfCfg.spectIp = ip;
        return setIfrfInfo("SpectIp", ip);}
    std::string loadIfrfSpectIp() {
        m_userCfg.ifrfCfg.spectIp =
        loadIfrfInfo("SpectIp", std::string(DEFAULT_INSTR_IP));
        return m_userCfg.ifrfCfg.spectIp;
    }

    bool saveIfrfSpectPort(uint16_t port) {
        m_userCfg.ifrfCfg.spectPort = port;
        return setIfrfInfo("SpectPort", ToString(port));}
    uint16_t loadIfrfSpectPort() {
        m_userCfg.ifrfCfg.spectPort =
        str::Util::convert<uint16_t>(loadIfrfInfo("SpectPort", ToString(DEFAULT_INSTR_PORT)), DEFAULT_INSTR_PORT);
        return m_userCfg.ifrfCfg.spectPort;
    }

    bool saveIfrfKeepTestIfFailed(uint32_t value) {
        m_userCfg.ifrfCfg.keepTestIfFaled = value;
        return setIfrfInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadIfrfmKeepTestIfFailed() {
        m_userCfg.ifrfCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadIfrfInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.ifrfCfg.keepTestIfFaled;
    }

    bool saveIfrfReTestIfFailed(uint32_t value) {
        m_userCfg.ifrfCfg.reTestIfFailed = value;
        return setIfrfInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadIfrfReTestIfFailed() {
        m_userCfg.ifrfCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadIfrfInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.ifrfCfg.reTestIfFailed;
    }

    /***************************************** FPGA SESSION ****************************************/
    bool setFpgaInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("FpgaBoard", tag, value);}

    std::string loadFpgaInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("FpgaBoard", tag, defValue);}

    bool saveFpgaFpgaIp(const std::string &ip) {
        m_userCfg.fpgaCfg.fpgaIp = ip;
        return setFpgaInfo("FpgaIp", ip);}
    std::string loadFpgaFpgaIp() {
        m_userCfg.fpgaCfg.fpgaIp =
        loadFpgaInfo("FpgaIp", std::string(DEFAULT_INSTR_IP));
        return m_userCfg.fpgaCfg.fpgaIp;
    }

    bool saveFpgaFpgaPort(uint16_t port) {
        m_userCfg.fpgaCfg.fpgaPort = port;
        return setFpgaInfo("FpgaPort", ToString(port));}
    uint16_t loadFpgaFpgaPort() {
        m_userCfg.fpgaCfg.fpgaPort =
        str::Util::convert<uint16_t>(loadFpgaInfo("FpgaPort", ToString(DEFAULT_INSTR_PORT)), DEFAULT_INSTR_PORT);
        return m_userCfg.fpgaCfg.fpgaPort;
    }

    bool saveFpgaKeepTestIfFailed(uint32_t value) {
        m_userCfg.fpgaCfg.keepTestIfFaled = value;
        return setFpgaInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadFpgaKeepTestIfFailed() {
        m_userCfg.fpgaCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadFpgaInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.fpgaCfg.keepTestIfFaled;
    }

    bool saveFpgaReTestIfFailed(uint32_t value) {
        m_userCfg.fpgaCfg.reTestIfFailed = value;
        return setFpgaInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadFpgaReTestIfFailed() {
        m_userCfg.fpgaCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadFpgaInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.fpgaCfg.reTestIfFailed;
    }

    bool saveFpgaPauseTest(uint32_t value) {
        m_userCfg.fpgaCfg.pauseTest = value;
        return setFpgaInfo("PauseTest", ToString(value));}
    uint32_t loadFpgaPauseTest() {
        m_userCfg.fpgaCfg.pauseTest =
        str::Util::convert<uint32_t>(loadFpgaInfo("PauseTest", ToString(1)), 1);
        return m_userCfg.fpgaCfg.pauseTest;
    }

    /***************************************** GPSDO SESSION ****************************************/
    bool setGpsdoInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("GpsdoBoard", tag, value);}

    std::string loadGpsdoInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("GpsdoBoard", tag, defValue);}

    bool saveGpsdoKeepTestIfFailed(uint32_t value) {
        m_userCfg.gpsdoCfg.keepTestIfFaled = value;
        return setGpsdoInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadGpsdoKeepTestIfFailed() {
        m_userCfg.gpsdoCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadGpsdoInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.gpsdoCfg.keepTestIfFaled;
    }

    bool saveGpsdoReTestIfFailed(uint32_t value) {
        m_userCfg.gpsdoCfg.reTestIfFailed = value;
        return setGpsdoInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadGpsdoReTestIfFailed() {
        m_userCfg.gpsdoCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadGpsdoInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.gpsdoCfg.reTestIfFailed;
    }


    bool saveGpsdoUTC(int32_t value) {
        m_userCfg.gpsdoCfg.utc = value;
        return setGpsdoInfo("UTC", ToString(value));}
    int32_t loadGpsdoUTC() {
        m_userCfg.gpsdoCfg.utc =
        str::Util::convert<int32_t>(loadGpsdoInfo("UTC", ToString(7)), 7);
        return m_userCfg.gpsdoCfg.utc;
    }

    bool saveGpsdoLatitude(double value) {
        m_userCfg.gpsdoCfg.latitude = value;
        return setGpsdoInfo("Latitude", ToString(value));}
    double loadGpsdoLatitude() {        
        m_userCfg.gpsdoCfg.latitude =                        
                convertToDouble(loadGpsdoInfo("Latitude", ToString(21)), 105);
        return m_userCfg.gpsdoCfg.latitude;
    }

    bool saveGpsdoLongitude(double value) {
        m_userCfg.gpsdoCfg.longitude = value;
        return setGpsdoInfo("Longitude", ToString(value));}
    double loadGpsdoLongitude() {        
        m_userCfg.gpsdoCfg.longitude =
                convertToDouble(loadGpsdoInfo("Longitude", ToString(105)), 105);
        return m_userCfg.gpsdoCfg.longitude;
    }

    /***************************************** CTRLPT SESSION ****************************************/
    bool setCtrlPtInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("CtrlPanTiltBoard", tag, value);}

    std::string loadCtrlPtInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("CtrlPanTiltBoard", tag, defValue);}

    bool saveCtrlPtKeepTestIfFailed(uint32_t value) {
        m_userCfg.ctrlPtCfg.keepTestIfFaled = value;
        return setCtrlPtInfo("KeepTestIfFailed", ToString(value));}
    uint32_t loadCtrlPtKeepTestIfFailed() {
        m_userCfg.ctrlPtCfg.keepTestIfFaled =
        str::Util::convert<uint32_t>(loadCtrlPtInfo("KeepTestIfFailed", ToString(0)), 0);
        return m_userCfg.ctrlPtCfg.keepTestIfFaled;
    }

    bool saveCtrlPtReTestIfFailed(uint32_t value) {
        m_userCfg.ctrlPtCfg.reTestIfFailed = value;
        return setCtrlPtInfo("ReTestIfFailed", ToString(value));}
    uint32_t loadCtrlPtReTestIfFailed() {
        m_userCfg.ctrlPtCfg.reTestIfFailed =
        str::Util::convert<uint32_t>(loadCtrlPtInfo("ReTestIfFailed", ToString(0)), 0);
        return m_userCfg.ctrlPtCfg.reTestIfFailed;
    }


    /***************************************** CALIB SENSOR SESSION ****************************************/
    bool setCalibSensorInfo(const std::string &tag, const std::string &value)
        {return saveNodeLevel2("CalibSensor", tag, value);}

    std::string loadCalibSensorInfo(const std::string &tag, const std::string &defValue)
        {return loadNodeLevel2("CalibSensor", tag, defValue);}

    bool saveCalibSensorServerAddress(const std::string &ip) {
        m_userCfg.calibSenCfg.ServerIp = ip;
        return setCalibSensorInfo("ServerIp", ip);}
    std::string loadCalibSensorServerIp() {
        m_userCfg.calibSenCfg.ServerIp =
        loadCalibSensorInfo("ServerIp", std::string(DEFAULT_SERVER_IP));
        return m_userCfg.calibSenCfg.ServerIp;
    }

    bool saveCalibSensorServerSslPort(uint16_t port) {
        m_userCfg.calibSenCfg.sslPort = port;
        return setCalibSensorInfo("ServerSslPort", ToString(port));}
    uint16_t loadCalibSensorServerSslPort() {
        m_userCfg.calibSenCfg.sslPort =
        str::Util::convert<uint16_t>(loadCalibSensorInfo("ServerSslPort",
                                                         ToString(DEFAULT_SERVER_PORT)),DEFAULT_SERVER_PORT );
        return m_userCfg.calibSenCfg.sslPort;
    }

    bool saveCalibSensorServerUdpPort(uint16_t port) {
        m_userCfg.calibSenCfg.udpPort = port;
        return setCalibSensorInfo("ServerUdpPort", ToString(port));}
    uint16_t loadCalibSensorServerUdpPort() {
        m_userCfg.calibSenCfg.udpPort =
        str::Util::convert<uint16_t>(loadCalibSensorInfo("ServerUdpPort",
                                                         ToString(DEFAULT_SERVER_UDP_PORT)), DEFAULT_SERVER_UDP_PORT);
        return m_userCfg.calibSenCfg.udpPort;
    }

    bool saveCalibSensorSigGenIp(const std::string &ip) {
        m_userCfg.calibSenCfg.SigGenIp = ip;
        return setCalibSensorInfo("SigGenIp", ip);}
    std::string loadCalibSensorSigGenIp() {
        m_userCfg.calibSenCfg.SigGenIp =
        loadCalibSensorInfo("SigGenIp", std::string(DEFAULT_INSTR_IP));
        return m_userCfg.calibSenCfg.SigGenIp;
    }

    bool saveCalibSensorSigGenPort(uint16_t port) {
        m_userCfg.calibSenCfg.siggenPort = port;
        return setCalibSensorInfo("SigGenTcpPort", ToString(port));}
    uint16_t loadCalibSensorSigGenPort() {
        m_userCfg.calibSenCfg.siggenPort =
        str::Util::convert<uint16_t>(loadCalibSensorInfo("SigGenTcpPort",
                                                         ToString(DEFAULT_INSTR_PORT)), DEFAULT_INSTR_PORT);
        return m_userCfg.calibSenCfg.siggenPort;
    }
};

#endif // UI_CONFIG_H
