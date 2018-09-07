#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <thread>
#include <list>

#define USE_Q_TIMER

#ifdef USE_Q_TIMER
#include <QTimer>
#endif
typedef void* TimerHandle;

typedef void (*FClbTimer)(uint32_t currTick, void *pClbParam);

typedef struct {
    uint32_t tickCount;
    uint32_t tickResolution;
    uint32_t tickUpdateRate;
}SSysTick;


typedef  struct _STickNode {
    struct _STickNode   *pNext;
    bool                isRun;
    uint32_t            rate;
    uint32_t            currTick;
    void*               pClbParam;
    FClbTimer           pClbFunc;

}STickNode;



typedef struct _STimerList{
    STickNode*  tickHead;
    STickNode*  tickTail;
}STimerList;



#if defined USE_Q_TIMER

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer();
    Timer(uint32_t res);
    void    StartTimerObject(void);
    void    StopTimerObject(void);
    void    Purge(void);
    TimerHandle Create(FClbTimer fClbTimer, void *pClbParam);
    bool    Delete(TimerHandle tmrHandle);
    void    SetRate(TimerHandle tmrHandle, uint32_t rate);
    uint32_t GetRate(TimerHandle tmrHandle);
    void    Update(void);
    void    Start(TimerHandle);
    void    StartAt(TimerHandle, uint32_t);
    void    Stop(TimerHandle);
    void    Reset(TimerHandle);
    bool    IsRunning(TimerHandle);
    void    TimerFunction(void);
    bool    PauseMicroSec(uint32_t time);

public slots:
    void TimerObjectTimeoutEvent();
private:

    std::list<STickNode*> sTimerList;
    SSysTick    sSysTick;
    QTimer      *timer;
    bool        term;
    uint32_t   resolution;  // Microsecond
};


#else
class Timer
{
public:
    Timer();
    Timer(uint32_t res);
    void    StartTimerThread(void);
    void    StopTimerThread(void);
    void    Purge(void);
    TimerHandle Create(FClbTimer fClbTimer, void *pClbParam);
    bool    Delete(TimerHandle tmrHandle);
    void    SetRate(TimerHandle tmrHandle, uint32_t rate);
    uint32_t GetRate(TimerHandle tmrHandle);
    void    Update(void);
    void    Start(TimerHandle);
    void    StartAt(TimerHandle, uint32_t);
    void    Stop(TimerHandle);
    void    Reset(TimerHandle);
    bool    IsRunning(TimerHandle);
    void    TimerFunction(void);
    bool    PauseMicroSec(uint32_t time);
private:

    std::list<STickNode*> sTimerList;
    SSysTick    sSysTick;
    std::thread timerThread;
    bool        term;
    uint32_t   resolution;  // Microsecond
};

#endif // USE_Q_TIMER

#endif // TIMER_H
