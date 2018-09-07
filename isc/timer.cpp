#include "timer.h"
#include "debug.h"

/**
 * @brief Timer::Timer
 */
Timer::Timer()
{
    sTimerList.clear();
    term = true;
    resolution = 1000; // 1ms
    StartTimerObject();
}

/**
 * @brief Timer::Timer
 * @param res
 */
Timer::Timer(uint32_t res)
{
    uint32_t value = res;
    sTimerList.clear();
    term = true;
    if(value < 1000) value = 1000; // shoud not allow Timer running faster 1ms
                                         // prevent eat more cpu time
    resolution = value; // 1ms
}

/**
 * @brief Timer::StopTimerThread
 */
void Timer::StopTimerObject()
{
    timer->stop();
    timer->destroyed();
    //Purge();
}

/**
 * @brief Timer::StartTimerThread
 */
void Timer::StartTimerObject(void) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
              this, SLOT(TimerObjectTimeoutEvent()));

    timer->start(1);
}

void Timer::Purge()
{
    STickNode *pTick;

    std::list<STickNode*>::iterator iter = sTimerList.begin();
    while(iter != sTimerList.end()) {
        pTick = *iter;
        delete pTick;
        iter = sTimerList.erase(iter);
    }

    //LREP("Timer list size: {}\r\n", sTimerList.size());
}

/**
 * @brief Timer::Create
 * @param fClbTimer
 * @param pClbParam
 * @return
 */
TimerHandle Timer::Create(FClbTimer fClbTimer, void *pClbParam)
{
    STickNode *newNode = 0;

    if(fClbTimer) {
        newNode = (STickNode*) new STickNode;

        if(newNode)
        {
            newNode->pClbFunc   = fClbTimer;
            newNode->pClbParam  = pClbParam;
            newNode->pNext      = 0;
            newNode->isRun      = false;

            sTimerList.push_back(newNode);
        }
    }
    return (TimerHandle)newNode;
}


/**
 * @brief Timer::Delete
 * @param tmrHandle
 * @return
 */
bool Timer::Delete(TimerHandle tmrHandle)
{
    if(sTimerList.size() == 0) {
        return false;   // no registered handlers
    }

    std::list<STickNode*>::iterator iter = sTimerList.begin();
    while(iter != sTimerList.end()) {
        if((STickNode*)(*iter) == (STickNode*)tmrHandle) {
            delete (STickNode*)tmrHandle;
            iter = sTimerList.erase(iter);
            return true;
        }
        iter++;
    }
    // Not found timer node
    return false;
}

/**
 * @brief Timer::SetRate
 * @param tmrHandle
 * @param rate
 */
void Timer::SetRate(TimerHandle tmrHandle, uint32_t rate)
{
    STickNode*  tNode;
    tNode = (STickNode*)tmrHandle;
    tNode->rate = tNode->currTick = rate;
}

/**
 * @brief Timer::GetRate
 * @param tmrHandle
 * @return
 */
uint32_t Timer::GetRate(TimerHandle tmrHandle)
{
    return (uint32_t(((STickNode*)tmrHandle)->rate));
}

/**
 * @brief Timer::Update
 */
void Timer::Update()
{
    STickNode *pTick;

    std::list<STickNode*>::iterator iter = sTimerList.begin();
    while(iter != sTimerList.end()) {
        pTick = *iter;
        if((pTick->rate != 0) && (pTick->isRun == true))
        {
            if(--pTick->currTick==0)
            {
                pTick->currTick=pTick->rate;
                /* Callback function is called */
                (*pTick->pClbFunc)(sSysTick.tickCount, pTick->pClbParam);
            }
        }
        iter++;
    }

}

/**
 * @brief Timer::Start
 * @param tmrHandle
 */
void Timer::Start(TimerHandle tmrHandle)
{
    STickNode*  pTick;

    pTick = (STickNode*)tmrHandle;

    pTick->isRun = true;
    pTick->currTick = pTick->rate;
}

/**
 * @brief Timer::StartAt
 * @param tmrHandle
 * @param u16CurrCnt
 */
void Timer::StartAt(TimerHandle tmrHandle, uint32_t u16CurrCnt)
{
    STickNode*  pTick;
    pTick = (STickNode*)tmrHandle;
    pTick->isRun = true;
    pTick->currTick = u16CurrCnt;
}

/**
 * @brief Timer::Stop
 * @param tmrHandle
 */
void Timer::Stop(TimerHandle tmrHandle)
{
    STickNode*  pTick;

    pTick = (STickNode*)tmrHandle;
    pTick->isRun = false;
}

/**
 * @brief Timer::Reset
 * @param tmrHandle
 */
void Timer::Reset(TimerHandle tmrHandle)
{
    STickNode*  pTick;
    pTick = (STickNode*)tmrHandle;
    pTick->currTick = pTick->rate;
}


/**
 * @brief Timer::IsRunning
 * @param tmrHandle
 * @return
 */
bool Timer::IsRunning(TimerHandle tmrHandle)
{
    STickNode*  pTick;
    bool  bRunning = false;
    pTick = (STickNode*)tmrHandle;

    bRunning=pTick->isRun;

    return bRunning;
}


#if defined (__linux__)
/**
 * @brief Timer::TimerFunction
 */
void Timer::TimerFunction()
{
    while(!term) {
        PauseMicroSec(resolution);
        sSysTick.tickCount++;
        Update();
    }
}

/**
 * @brief Timer::PauseMicroSec
 * @param time
 * @return
 */
bool Timer::PauseMicroSec(uint32_t time)
{
    struct timespec tmr1,tmr2;

    //assume you are not trying to pause more than 1s
    tmr1.tv_sec = 0;
    tmr1.tv_nsec = time * 1000;
    if(nanosleep(&tmr1, &tmr2) < 0) {
        printf("Nano second pause failed\n");
        return false;
    }
    return true;
}

#elif defined (_MSC_VER)
void Timer::TimerFunction() {


}



#endif

void Timer::TimerObjectTimeoutEvent()
{
    sSysTick.tickCount++;
    Update();
}
