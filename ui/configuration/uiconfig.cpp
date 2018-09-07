#include "uiconfig.h"
#include <string.h>


//namespace config {


UiConfig::UiConfig()
{
    m_doc = nullptr;
    m_result.status = pugi::status_file_not_found;
    isSave = false;
}

UiConfig::~UiConfig()
{
    destroyInstance();
}

bool UiConfig::openXmlFile(const std::string &filename)
{
    m_filename = filename;
    std::ifstream infile(m_filename);
    if(m_doc == nullptr) {
        m_doc = std::make_shared<pugi::xml_document>();
    }

    if(m_doc == nullptr)
        return false;

    if(infile.good()) {
        m_result = m_doc->load_file(m_filename.c_str(), pugi::parse_default|pugi::parse_declaration);
        if (m_result.status != pugi::status_ok) {
            std::cout << "Parse error: " << m_result.description() << ", character pos= " << m_result.offset;
            return false;
        }
        return true;
    } else {
        LREP("Create new file\n");
        auto declarationNode = m_doc->append_child(pugi::node_declaration);
        declarationNode.append_attribute("version")    = "1.0";
        declarationNode.append_attribute("encoding")   = "ISO-8859-1";
        declarationNode.append_attribute("standalone") = "yes";
        m_doc->append_child("MyRoot");
        m_result.status = pugi::status_ok;
        isSave = true;
        return true;
    }
}

bool UiConfig::closeXmlFile()
{
    if(isSave) {        
        return m_doc->save_file(m_filename.c_str(), PUGIXML_TEXT("  "));
        LREP("SAVE CFG FILE\n");
    }
    else
        return false;
}

void UiConfig::loadConfigFromXmlFile()
{
    loadGeneralSigGenType();
    loadGeneralSpectrumType();
    loadGeneralPowerType();
    loadGeneralLocalIp   ();
    loadGeneralLocalPort();
    loadGeneralFileNameHigh();
    loadGeneralFileNameLow();
    loadGeneralSigGenDelay();
    loadGeneralSpectrumDelay();
    loadGeneralServerDelay();
    loadGeneralBandwidthHigh();
    loadGeneralBandwidthLow();
    loadGeneralTabUsed();
    loadGeneralMainTabUsed();
    loadGeneralOutputDir();
    loadGeneralInputDir();
    loadGeneralSetupInOut();


    loadSensorServerIp();
    loadSensorServerSslPort();
    loadSensorServerUdpPort();
    loadSensorSigGenIp();
    loadSensorSigGenPort();
    loadSensorKeepTestIfFailed();
    loadSensorReTestIfFailed();


    loadSystemServerIp();
    loadSystemServerSslPort();
    loadSystemServerUdpPort();
    loadSystemKeepTestIfFailed();
    loadSystemReTestIfFailed();


    loadIfrfSigGenIp();
    loadIfrfSigGenPort();
    loadIfrfSpectIp();
    loadIfrfSpectPort();
    loadIfrfmKeepTestIfFailed();
    loadIfrfReTestIfFailed();


    loadFpgaFpgaIp();
    loadFpgaFpgaPort();
    loadFpgaKeepTestIfFailed();
    loadFpgaReTestIfFailed();
    loadFpgaPauseTest();


    loadCalibSensorServerIp();
    loadCalibSensorServerSslPort();
    loadCalibSensorServerUdpPort();
    loadCalibSensorSigGenIp();
    loadCalibSensorSigGenPort();


    loadGpsdoKeepTestIfFailed();
    loadGpsdoReTestIfFailed();
    loadGpsdoUTC();
    loadGpsdoLongitude();
    loadGpsdoLatitude();

    loadCtrlPtKeepTestIfFailed();
    loadCtrlPtReTestIfFailed();
}

bool UiConfig::saveNodeLevel2(const std::string &parent, const std::string &name,
                                  const std::string &value)
{    
    if(m_result.status == pugi::status_ok && m_doc) {
        pugi::xml_node root = m_doc->document_element();
        pugi::xpath_node xpathNode = root.select_single_node(parent.c_str());
        pugi::xml_node nodeParent;
        if(xpathNode) { // If parent found
            nodeParent = xpathNode.node();            
        } else {
            return false;
        }

        pugi::xpath_node xPathNameNode = nodeParent.select_single_node(name.c_str());
        pugi::xml_node nodeChild;

        if(xPathNameNode) {  // If found node
            nodeChild = xPathNameNode.node();            
            pugi::xml_text text = nodeChild.text();
            text.set(value.c_str());            
        } else { // Not found the node
            return false;
        }
        //LREP("UPDATE ");
        isSave = true;
        return true;
    } else  {
        return false;
    }

}

std::string UiConfig::loadNodeLevel2(const std::string &parent, const std::string &name, const std::string &defValue)
{
    std::string ret = "";
    if(m_result.status == pugi::status_ok && m_doc) {
        pugi::xml_node root = m_doc->document_element();
        pugi::xpath_node xpathNode = root.select_single_node(parent.c_str());
        pugi::xml_node nodeParent;
        if(xpathNode) { // If parent found
            nodeParent = xpathNode.node();
        } else { // Create new parent
            std::cout << "Create parent " << parent << std::endl;
            nodeParent = root.append_child(parent.c_str());
        }

        pugi::xpath_node xPathNameNode = nodeParent.select_single_node(name.c_str());
        pugi::xml_node nodeChild;

        if(xPathNameNode) {  // If found node
            nodeChild = xPathNameNode.node();
            //std::cout << "Load value " << nodeChild.child_value() << std::endl;
            ret = nodeChild.child_value();
        } else { // Not found the node
            nodeChild = nodeParent.append_child(name.c_str());
            nodeChild.append_child(pugi::node_pcdata).set_value(defValue.c_str());
            std::cout << "Create default value\n";
            ret = defValue;
        }
    } else {
        std::cout << "Doc file is not opened " << m_result.status << std::endl;
    }
    return ret;
}

double UiConfig::convertToDouble(std::string value, double def)
{
    std::replace(value.begin(), value.end(), ',', '.');
    return str::Util::convert<double>(value, def);
}


float UiConfig::convertToFloat(std::string value, float def)
{
    std::replace(value.begin(), value.end(), ',', '.');
    return str::Util::convert<float>(value, def);
}
//}
