#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

#define     EW_DEBUG_ENABLE 0

#if EW_DEBUG_ENABLE
    #define EW_DBG      (qDebug("[EW] "))
#else
    #define EW_DBG(s)
#endif

#endif // COMMAND_H
