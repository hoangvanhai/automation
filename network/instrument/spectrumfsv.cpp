#include "spectrumfsv.h"
#include <QDebug>

SpectrumFsv::SpectrumFsv()
{

}

/**************************************************************************************************
 * @brief Control instrument section
 */

int SpectrumFsv::InitDevice()
{
    int ret;
    std::string cmd1(":CONFigure:SANalyzer");
    std::string cmd2("*CLS\r\n");
    std::string cmd3("*RST\r\n");
    std::string cmd4("UNIT:POW DBM\r\n");
    std::string cmd5(":CALCulate:MARKer1:STATe ON\r\n");

    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());    
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ret = sendDataToServerWoLength((uint8_t*)cmd3.c_str(), (uint32_t)cmd3.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ret = sendDataToServerWoLength((uint8_t*)cmd4.c_str(), (uint32_t)cmd4.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ret = sendDataToServerWoLength((uint8_t*)cmd5.c_str(), (uint32_t)cmd5.length());

    return ret;
}


/**
 * @brief SpectrumFsv::SetupSpecAnalyzer
 * @return
 */
int SpectrumFsv::SetupSpecAnalyzer()
{
    int ret;

    std::string cmd1("INIT:CONT 1\r\n");
    std::string cmd2("INSTrument:SANalyzer\r\n");
    std::string cmd3(":AVER OFF\r\n");
    std::string cmd4(":BAND:AUTO ON\r\n");
    std::string cmd5(":SWE:TIME:AUTO ON\r\n");
    std::string cmd6(":FREQ:SPAN 1MHz\r\n");
    std::string cmd7(":INP:COUP DC\r\n");
    std::string cmd8(":UNIT:POWer DBM\r\n");
    std::string cmd9("INP:ATT:AUTO ON\r\n");
    std::string cmd10("DISPlay:TRACe:Y:RLEVel:OFFSet 30dB\r\n");


    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd3.c_str(), (uint32_t)cmd3.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd4.c_str(), (uint32_t)cmd4.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd5.c_str(), (uint32_t)cmd5.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd6.c_str(), (uint32_t)cmd6.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd7.c_str(), (uint32_t)cmd7.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd8.c_str(), (uint32_t)cmd8.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd9.c_str(), (uint32_t)cmd9.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ret = sendDataToServerWoLength((uint8_t*)cmd10.c_str(), (uint32_t)cmd10.length());

    return ret;
}

/**
 * @brief SpectrumFsv::SetupSpecAnalyzerMode
 * @param mode
 * @return
 */
int SpectrumFsv::SetupSpecAnalyzerMode(MeasurementMode mode)
{
    int ret;
    if(mode == Mode_Single) {
        std::string cmd("INIT:CONT 0\r\n");
        ret = sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
    } else {
        std::string cmd("INIT:CONT 1\r\n");
        ret = sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
    }
    return ret;
}

int SpectrumFsv::SetCenterFreq(double dFreq, FrequencyUnit freqUnit)
{
    double dFreqInput = dFreq;
    switch(freqUnit) {
    case Freq_Hz:
        dFreqInput = dFreq;
        break;

    case Freq_Khz:
        dFreqInput = dFreq * 1E3;
        break;

    case Freq_Mhz:
        dFreqInput = dFreq * 1E6;
        break;

    default:
        break;

    }

    std::ostringstream astream;
    std::string astr;
    astream << ":FREQuency:CENTer " << dFreqInput << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetSpan(double dSpanValue, FrequencyUnit freqUnit)
{
    double dSpanInput = dSpanValue;
    switch(freqUnit) {
    case Freq_Hz:
        dSpanInput = dSpanValue;
        break;

    case Freq_Khz:
        dSpanInput = dSpanValue * 1E3;
        break;

    case Freq_Mhz:
        dSpanInput = dSpanValue * 1E6;
        break;

    default:
        break;

    }

    std::ostringstream astream;
    std::string astr;
    astream << ":FREQ:SPAN " << dSpanInput << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetReferentLevel(double dReferValue)
{
    std::ostringstream astream;
    std::string astr;
    astream << ":DISPlay:WINDow:TRACe:Y:SCALe:RLEVel " << dReferValue << "dBm\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetSpecAnttenuation(double dAttenuatonValue)
{
    int ret;
    std::string cmd("INPut:ATTenuation:AUTO OFF\r\n");
    ret = sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::ostringstream astream;
    std::string astr;
    astream << "INPut:ATTenuation " << dAttenuatonValue << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetStopFreq(double dStopFreq, FrequencyUnit freqUnit)
{
    double dStopFreqInput = dStopFreq;
    switch(freqUnit) {
    case Freq_Hz:
        dStopFreqInput = dStopFreq;
        break;

    case Freq_Khz:
        dStopFreqInput = dStopFreq * 1E3;
        break;

    case Freq_Mhz:
        dStopFreqInput = dStopFreq * 1E6;
        break;

    default:
        break;

    }

    std::ostringstream astream;
    std::string astr;
    astream << ":SENSe:FREQuency:STOP " << dStopFreqInput << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetResolutionBandwidth(double dRbw, FrequencyUnit freqUnit)
{
    double dRbwInput = dRbw;
    switch(freqUnit) {
    case Freq_Hz:
        dRbwInput = dRbw;
        break;

    case Freq_Khz:
        dRbwInput = dRbw * 1E3;
        break;

    case Freq_Mhz:
        dRbwInput = dRbw * 1E6;
        break;

    default:
        break;

    }

    std::ostringstream astream;
    std::string astr;
    astream << "ADEMod:SPECtrum:BANDwidth:RESolution " << dRbwInput << "\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetMarker(bool bOnOff, int iMakerIndex)
{
    std::ostringstream astream;
    std::string astr;

    if(bOnOff) {
        astream << ":CALCulate:MARKer" << iMakerIndex << ":STATe ON" <<"\r\n";
    } else {
        astream << ":CALCulate:MARKer" << iMakerIndex << ":STATe OFF" <<"\r\n";
    }

    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetMarkerMax()
{
    std::string cmd("CALC:MARKer1:MAX\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int SpectrumFsv::SetNextMarkerMax(int iMaxker, SearchDirection searchDir)
{
    std::ostringstream astream;
    std::string astr;
    switch(searchDir) {
    case SearchDirection_Left:
        astream << ":CALCulate:MARKer" << iMaxker << ":MAXimum:LEFT\r\n";
        break;
    case SearchDirection_Right:
        astream << ":CALCulate:MARKer" << iMaxker << ":MAXimum:RIGHt\r\n";
        break;
    case SearchDirection_None:
        astream << ":CALCulate:MARKer" << iMaxker << ":MAXimum:NEXT\r\n";
        break;

    }

    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetMarkerAtFreq(double dFreq, FrequencyUnit freqUnit, int iMarker)
{
    double dFreqInput = dFreq;
    switch(freqUnit) {
    case Freq_Hz:
        dFreqInput = dFreq;
        break;

    case Freq_Khz:
        dFreqInput = dFreq * 1E3;
        break;

    case Freq_Mhz:
        dFreqInput = dFreq * 1E6;
        break;

    default:
        break;

    }

    std::ostringstream astream;
    std::string astr;
    astream << ":CALCulate:MARKer" << iMarker << ":X " <<  dFreqInput <<"MHZ\r\n";
    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}

int SpectrumFsv::SetModeView(ModeView eMode)
{
    std::string cmd;
    switch(eMode) {
    case ModeView_MinHold:
        cmd = "DISP:TRAC1:MODE MINH\r\n";
        break;
    case ModeView_MaxHold:
        cmd = "DISP:TRAC1:MODE MAXH\r\n";
        break;
    case ModeView_ClearWrite:
        cmd = "DISP:TRAC1:MODE WRIT\r\n";
        break;

    default:
        break;
    }

    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int SpectrumFsv::GetCenterFreq(FrequencyUnit freqUnit)
{
    (void)freqUnit;
    std::string cmd(":FREQuency:CENTer?\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int SpectrumFsv::SendCommand(const std::string &command)
{
    if(command.length() > 0)
        return sendDataToServerWoLength((uint8_t*)command.c_str(), (uint32_t)command.length());
    else
        return 0;
}

int SpectrumFsv::GetValueAtMarker(MarkerValueType valType)
{
    std::string cmd;
    if(valType == MarkerValueType_Level) {
        cmd = "CALC:MARKer1:Y?\r\n";
    } else {
        cmd = "CALC:MARKer1:X?\r\n";
    }

    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}

int SpectrumFsv::GetValueAtMarker(MarkerValueType valType, int idx)
{
    std::ostringstream astream;
    std::string astr;
    if(valType == MarkerValueType_Level) {
        astream << "CALC:MARKer" << idx << ":Y?\r\n";
    } else {
        astream << "CALC:MARKer" << idx << ":X?\r\n";
    }

    astr = astream.str();
    return sendDataToServerWoLength((uint8_t*)astr.c_str(), (uint32_t)astr.length());
}



int SpectrumFsv::GetHarmonicDistortion(double dFreq, int iNumHarm, FrequencyUnit freqUnit)
{

    return 0;
}

int SpectrumFsv::GetSpurious(double dFreq, double dSpanValue,
                             double dBandWidthRaw, FrequencyUnit freqUnit)
{

    return 0;
}

int SpectrumFsv::SetFMDemod(double freq,
                            FrequencyUnit fUnit,
                            uint32_t bw, double time,
                            uint32_t timeoutMillisec)
{
    int ret = 0;
    std::string cmd1("ADEM:STAT ON\r\n");
    std::string cmd2("CALC:MARK:FUNC:DEM:SEL FM\r\n");
    std::string cmd3("BAND:DEM " + std::to_string(bw) + "\r\n");
    std::string cmd4("FILT:LPAS 1\r\n");
    std::string cmd5("FILT:LPAS:FREQ 3000\r\n");
    std::string cmd6("SWE:TIME " + std::to_string(time) +"\r\n");
    std::string cmd7("CALC:FEED 'XTIM:FM:AFSP'\r\n");
    std::string cmd8("DISP:TRAC:MODE AVER\r\n");

    SetCenterFreq(freq, fUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd3.c_str(), (uint32_t)cmd3.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd4.c_str(), (uint32_t)cmd4.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd5.c_str(), (uint32_t)cmd5.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd6.c_str(), (uint32_t)cmd6.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd7.c_str(), (uint32_t)cmd7.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd8.c_str(), (uint32_t)cmd8.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));

    return ret;
}

int SpectrumFsv::SetSpectrumWindow(double freq,
                                   FrequencyUnit freqUnit,
                                   double span,
                                   FrequencyUnit spanUnit,
                                   double reflevel,
                                   uint32_t timeoutMillisec)
{
    int ret = 0;
    std::string cmd1("BAND 3 kHz\r\n");
    std::string cmd2("SWE:POIN 1600\r\n");
    //std::string cmd2("SWE:POIN 32000\r\n");
    std::string cmd3("SWE:COUN 0\r\n");
    std::string cmd4("DISP:TRAC:MODE AVER\r\n");
    std::string cmd5(":FORM:DATA ASC,0\r\n");

    SetCenterFreq(freq, freqUnit);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    SetSpan(span, spanUnit);
    ret = sendDataToServerWoLength((uint8_t*)cmd1.c_str(), (uint32_t)cmd1.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd3.c_str(), (uint32_t)cmd3.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd4.c_str(), (uint32_t)cmd4.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd5.c_str(), (uint32_t)cmd5.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    SetReferentLevel(reflevel);

    return ret;
}

int SpectrumFsv::GetScreenSpectrum(uint32_t timeoutMillisec)
{
    int ret;
    std::string cmd(":FORM:DATA ASC,0\r\n");
    std::string cmd2(":TRACE:DATA? TRACE1\r\n");
    //ret = sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
    //std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    ret = sendDataToServerWoLength((uint8_t*)cmd2.c_str(), (uint32_t)cmd2.length());
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMillisec));
    return ret;
}

int SpectrumFsv::GetSinad()
{
    std::string cmd("CALC:MARK:FUNC:ADEM:SIN:RES?\r\n");
    return sendDataToServerWoLength((uint8_t*)cmd.c_str(), (uint32_t)cmd.length());
}


/**

  :MODulation[:TYPE]
  :BWIDth

  */



