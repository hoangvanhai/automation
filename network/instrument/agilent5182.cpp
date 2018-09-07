#include "agilent5182.h"
#include <QDebug>

Agilent5182::Agilent5182(Transceiver *parent)
{

}

/**************************************************************************************************
 * @brief Control instrument section
 */

int Agilent5182::InitDevice()
{
    int ret;
    std::string cmd1("*CLS\r\n");
    std::string cmd2("*RST\r\n");
    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return ret;
}
/**
 * @brief Agilent5182::SetRFPower
 * @param dPwr
 * @param unit
 * @return
 */
int Agilent5182::SetRFPower(double dPwr, PowerUnit unit)
{
    std::ostringstream astream;
    std::string astr;
    astream << "SOUR:POW " << dPwr;

    switch(unit) {
        case Power_dBm:
        astream << "DBM\r\n"; break;
        case Power_MV:
        astream << "MV\r\n"; break;
        case Power_UV:
        astream << "UV\r\n"; break;
        case Power_Wat:
        astream << "DBM\r\n"; break;
    default:
        return 0;
    }

    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

/**
 * @brief Agilent5182::SetRFFrequency
 * @param dFreq
 * @param unit
 * @return
 */
int Agilent5182::SetRFFrequency(double dFreq, FrequencyUnit unit)
{
    std::ostringstream astream;
    std::string astr;
    double freq = dFreq;
    uint64_t    sendFreq;
    switch(unit) {
    case Freq_Hz:
        break;
    case Freq_Khz:
        freq *= 1000;
        break;
    case Freq_Mhz:
        freq *= 1000000;
        break;
    }
    sendFreq = (uint64_t)freq;
    astream << ":FREQ " << sendFreq << "\r\n";
    astr = astream.str();
    //LREP("Length: {}\r\n", astr.length());
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), astr.length());
}

/**
 * @brief Agilent5182::SetSignalOut
 * @param on
 * @param sigPort
 * @return
 */
int Agilent5182::SetSignalOut(bool on, int sigPort)
{
    (void)sigPort;
    std::string cont;
    if(on) {
        cont = ":OUTP ON\r\n";
    } else {
        cont = ":OUTP OFF\r\n";
    }
    return sendDataToServerWoLength((uint8_t*)cont.c_str(), (uint32_t)cont.length());
}

/**
 * @brief Agilent5182::SetALC
 * @param on
 * @return
 */
int Agilent5182::SetALC(bool on)
{
    std::string cont;
    if(on) {
        cont = ":POWer:ALC ON\r\n";
    } else {
        cont = ":POWer:ALC OFF\r\n";
    }
    return sendDataToServerWoLength((uint8_t*)cont.c_str(), (uint32_t)cont.length());
}

/**
 * @brief Agilent5182::GetCurrRFPower
 * @return
 */
int Agilent5182::GetCurrRFPower()
{
    std::string cont("SOUR:POW?\r\n");
    return sendDataToServerWoLength((uint8_t*)cont.c_str(), (uint32_t)cont.length());
}

int Agilent5182::SetModOut(bool on)
{
    std::string cont;
    if(on) {
        cont = ":OUTP:MOD ON\r\n";
    } else {
        cont = ":OUTP:MOD OFF\r\n";
    }
    return sendDataToServerWoLength((uint8_t*)cont.c_str(), (uint32_t)cont.length());
}

int Agilent5182::SetFMRate(double rate, FrequencyUnit unit)
{
    std::ostringstream astream;
    std::string astr;
    double      freq = rate;
    uint64_t    sendFreq;
    switch(unit) {
    case Freq_Hz:
        break;
    case Freq_Khz:
        freq *= 1000;
        break;
    case Freq_Mhz:
        freq *= 1000000;
        break;
    }
    sendFreq = (uint64_t)freq;
    astream << ":FM1:INT:FUNC:FREQ " << sendFreq << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), astr.length());
}

int Agilent5182::SetFMOut(bool on)
{
    std::string cont;
    if(on) {
        cont = ":FM1:STAT ON\r\n";
    } else {
        cont = ":FM1:STAT OFF\r\n";
    }
    return sendDataToServerWoLength((uint8_t*)cont.c_str(), (uint32_t)cont.length());
}
/**
 * @brief Agilent5182::SetFMDeviation
 * USE noise 16K, noise 25K
 * Set DUAL ARB
 * @param dev
 * @param unit
 * @return
 */

int Agilent5182::SetFMDeviation(double dev, FrequencyUnit unit)
{
    std::ostringstream astream;
    std::string astr;
    double      freq = dev;
    uint64_t    sendFreq;
    switch(unit) {
    case Freq_Hz:
        break;
    case Freq_Khz:
        freq *= 1000;
        break;
    case Freq_Mhz:
        freq *= 1000000;
        break;
    }
    sendFreq = (uint64_t)freq;
    astream << ":FM1:DEV " << sendFreq << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), astr.length());

}

int Agilent5182::SetFMARB(uint32_t sampleClock,
                          double freq, FrequencyUnit freqUnit, std::string file,
                          double power, PowerUnit pwrUnit, uint32_t delay) {

    int ret;
    std::ostringstream astream;

    SetSignalOut(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    SetRFFrequency(freq, freqUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    SetRFPower(power, pwrUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::string cmd1(":SOUR:RAD:ARB:STAT OFF\r\n");
    astream << ":SOUR:RAD:ARB:SCL:RATE " << sampleClock << "\r\n";
    std::string cmd3(":SOUR:RAD:ARB:TRIG:TYPE CONT\r\n");
    std::string cmd4(":RAD:ARB:TRIG:TYPE:CONT:TYPE FREE\r\n");
    std::string cmd5(":MMEMory:COPY \"" + file + "\",\"WFM1:" + file + "\"\r\n");
    std::string cmd6(":SOUR:RAD:ARB:WAV \"WFM1:" + file + "\"\r\n");
    std::string cmd7(":FM:STAT OFF\r\n");
    std::string cmd8(":SOUR:RAD:ARB:STAT ON\r\n");

    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)astream.str().c_str(), (uint32_t)astream.str().length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd3.c_str(), (uint32_t)cmd3.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd4.c_str(), (uint32_t)cmd4.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd5.c_str(), (uint32_t)cmd5.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd6.c_str(), (uint32_t)cmd6.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd7.c_str(), (uint32_t)cmd7.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ret = sendDataToServerWoLength((uint8_t*)cmd8.c_str(), (uint32_t)cmd8.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    SetModOut(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    SetSignalOut(true);
    return ret;
}

int Agilent5182::SetTwoToneClear()
{
    std::string cmd(":RAD:TTON:ARB:HEAD:CLE\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int Agilent5182::SetTwoToneSpace(double Space, FrequencyUnit unit)
{
    std::ostringstream astream;
    std::string astr;
    double      freq = Space;
    uint64_t    sendFreq;
    switch(unit) {
    case Freq_Hz:
        break;
    case Freq_Khz:
        freq *= 1000;
        break;
    case Freq_Mhz:
        freq *= 1000000;
        break;
    }
    sendFreq = (uint64_t)freq;
    astream << ":RAD:TTON:ARB:FSP " << sendFreq << "HZ\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), astr.length());
}

int Agilent5182::SetToneAlign()
{
    std::string cmd(":RAD:TTON:ARB:ALIG CENT\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int Agilent5182::SetToneApply()
{
    std::string cmd(":RAD:TTON:ARB:APPL\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int Agilent5182::SetTwoToneState(bool state)
{
    std::string cmd;
    if(state)
        cmd = ":RAD:TTON:ARB ON\r\n";
    else
        cmd = ":RAD:TTON:ARB OFF\r\n";

    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int Agilent5182::SetTwoTone(double freq, FrequencyUnit freqUnit,
                            double space, FrequencyUnit spaceUnit,
                            double power, PowerUnit pwrUnit, uint64_t delayMillisec )
{
    int ret;
    ret = InitDevice();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec *5));
//    ret = SetTwoToneClear();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetRFFrequency(freq, freqUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetALC(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetRFPower(power, pwrUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetTwoToneSpace(space, spaceUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetToneAlign();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetToneApply();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetTwoToneState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetModOut(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMillisec));
    ret = SetSignalOut(true);

    return ret;
}



/**

  :MODulation[:TYPE]
  :BWIDth

  */



