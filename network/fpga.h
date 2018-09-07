#ifndef FPGA_H
#define FPGA_H

#include "network/transceiver.h"
#include "ui/testconfig.h"

#define DEFAULT_PORT    5025





class Fpga : public Transceiver
{

public:
    Fpga();

};

#endif // FPGA_H
