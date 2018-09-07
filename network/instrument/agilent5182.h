#ifndef CLIENT_H
#define CLIENT_H

#include <communication/socket/tcp/TCPClient.h>
#include <communication/socket/tcp/TCPServer.h>
#include <communication/protocol/StreamFraming.h>
#include "debug.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <ui/testconfig.h>
#include "network/transceiver.h"

#define DEFAULT_PORT    5025

class Agilent5182 : public Transceiver
{

public:
    explicit Agilent5182(Transceiver *parent = 0);
    int InitDevice();
    int SetRFPower(double dPwr, PowerUnit unit);
    int SetRFFrequency(double dFreq, FrequencyUnit unit);
    int SetSignalOut(bool on, int sigPort = 0);
    int SetALC(bool on);
    int GetCurrRFPower();
    int SetModOut(bool on);
    int SetFMDeviation(double dev, FrequencyUnit unit);    
    int SetFMRate(double rate, FrequencyUnit unit);
    int SetFMOut(bool on);
    int SetFMARB(uint32_t sampleClock,
                 double freq, FrequencyUnit freqUnit, std::string file,
                 double power, PowerUnit pwrUnit, uint32_t delay = 100);

    int SetTwoToneClear();
    int SetTwoToneSpace(double Space, FrequencyUnit unit);
    int SetToneAlign();
    int SetToneApply();
    int SetTwoToneState(bool state);
    int SetTwoTone(double freq, FrequencyUnit freqUnit,
                   double space, FrequencyUnit spaceUnit,
                   double power, PowerUnit pwrUnit, uint64_t delayMillisec = 200);


};

#endif // CLIENT_H
