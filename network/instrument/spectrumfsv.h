#ifndef SPECT_FSV_H
#define SPECT_FSV_H

#include "network/transceiver.h"
#include "testconfig.h"

#define DEFAULT_PORT    5025

/*

```set reference level:
:DISPlay:WINDow:TRACe:Y:SCALe:RLEVel -30dBm
```set resolution bandwidth:
ADEMod:SPECtrum:BANDwidth:RESolution 100000
```set resolution bandwidth
BAND 1 MHz

```set center freq:
:FREQuency:CENTer 120000000
```set span:
:FREQ:SPAN 300000
```set marker max:
CALC:MARKer1:MAX
```get value at marker:
CALC:MARKer1:Y?
CALC:MARKer1:X?
```get Carrier to noise ratio
CALC:MARK:FUNC:POW:RES? CN
CALC:MARK:FUNC:POW:SEL CN

tinh SNR:
set resolution bw: 30Hz
set span 10Khz


BAND:VID:RAT 0.0001
BAND:RAT 0.0001

:FM1:INTernal:SWEep:RATE1


CONFIG FSV GET SINAG

MODE -> ANALOG DEMOE -> FM -> FREQ DEMOD 140M -> DEMOD BW ->25K -> Meas time -> 20ms -> AF filter -> low pass 3K
Display FM spectrum ->


DISP:TRAC:Y:RLEV -60dBm


```set Demod on/off:
ADEM:STAT ON
```select mode FM:
CALC:MARK:FUNC:DEM:SEL FM
```set FREQ DEMOD 140M:
FREQ:CENT 140MHz
```set demod bandwidth:
BAND:DEM 25kHz
```set AF filter low pass:
FILT:LPAS 1
```set AF filter 3K:
FILT:LPAS:FREQ 3000
```set meas time:
SWE:TIME 0.02
```change to FM Specturm windows
CALC:FEED 'XTIM:FM:AFSP'
```get SNR value:
CALC:MARK:FUNC:ADEM:SIN:RES?



FM[1]|2:INTernal:SWEep:RATE

:FM:INT:SWE:RATE1 1000

:FM1:DEV  5600
:FM1:INT:FUNC:SHAP SINE
:FM1:INT:FUNC:FREQ 1kHz
SOUR:POW -90DBM
:POWer:ALC OFF
:FREQ 100000000
:OUTP:MOD ON
:OUTP ON
:FM1:STAT ON



:FM1:INT:FUNC:SHAP SINE
:FM1:INT:FUNC:FREQ 1MHz


:FREQ:CENT 140000000

:FREQ:SPAN 40000000

BAND 3 kHz

SWE:POIN 32000

SWE:COUN 0

DISP:TRAC:MODE AVER

:FORM:DATA REAL,32
:FORM:DATA ASC,0
:FORM:DATA UINT,32
:FORM:DATA MATLAB,32


:TRACE:DATA? TRACE1

:TRACE:DATA:X? TRACE1
:TRACE:DATA:Y? TRACE1

 */
class SpectrumFsv : public Transceiver
{

public:
    SpectrumFsv();
    int InitDevice();
    int SetupSpecAnalyzer();
    int SetupSpecAnalyzerMode(MeasurementMode mode);
    int SetCenterFreq(double dFreq, FrequencyUnit freqUnit);
    int SetSpan(double dSpanValue, FrequencyUnit freqUnit);
    int SetReferentLevel(double dReferValue);
    int SetSpecAnttenuation(double dAttenuatonValue);
    int SetStopFreq(double dStopFreq, FrequencyUnit freqUnit);
    int SetResolutionBandwidth(double dRbw, FrequencyUnit freqUnit);
    int SetMarker(bool bOnOff, int iMakerIndex);
    int SetMarkerMax();
    int SetNextMarkerMax(int iMaxker, SearchDirection searchDir);
    int SetMarkerAtFreq(double dFreq, FrequencyUnit freqUnit, int iMarker);
    int SetModeView(ModeView eMode);
    int GetCenterFreq(FrequencyUnit freqUnit);
    int SendCommand(const std::string &command);
    int GetValueAtMarker(MarkerValueType valType);
    int GetValueAtMarker(MarkerValueType valType, int idx);
    int GetHarmonicDistortion(double dFreq, int iNumHarm, FrequencyUnit freqUnit);
    int GetSpurious(double dFreq, double dSpanValue,
                    double dBandWidthRaw, FrequencyUnit freqUnit);

    int SetFMDemod(double freq, FrequencyUnit fUnit,
                   uint32_t bw, double time,
                   uint32_t timeoutMillisec = 200);

    int SetSpectrumWindow(double freq, FrequencyUnit freqUnit,
                          double span, FrequencyUnit spanUnit, double reflevel,
                          uint32_t timeoutMillisec = 200);

    int GetScreenSpectrum(uint32_t timeout);

    int GetSinad();



};


#endif // SPECT_FSV_H
