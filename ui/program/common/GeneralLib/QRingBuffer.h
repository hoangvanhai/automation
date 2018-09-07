#ifndef QRINGBUFFER_H
#define QRINGBUFFER_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>


using namespace std;

class QRingBuffer
{
    typedef long (*CallbackFunction)(void* pvParent, void* pvParameter);
    typedef void (*CallbackFunctionNoIO)(void);

#define TRUE    1
#define FALSE   0

public:
    QRingBuffer();
    ~QRingBuffer();
    void			BufferInit(uint16_t u16Size,
                               CallbackFunctionNoIO callbackLockFPtr,
                               CallbackFunctionNoIO callbackUnlockFPtr);


    int 			BufferPush(void* pvData);
    uint8_t                     BufferPop(void* pvData);
    int 			BufferPushStream(void* pvStream, uint16_t u16Length);
    uint16_t                    BufferPopStream(void* pvStream, uint16_t u16Length);

    int                         BufferPushBack(uint16_t u16PushBackNumber);
    uint16_t                    BufferGetCount() {return u16ElementCount;}
    uint16_t                    BufferGetAvailableCount() {return u16BufferSize - u16ElementCount;}
    void 			BufferFlush();

    void			BufferEnablePop() {bBufferPopEnable = TRUE;}
    void			BufferDisablePop() {bBufferPopEnable = FALSE;}
    void			BufferEnablePush() {bBufferPushEnable = TRUE;}
    void			BufferDisablePush() {bBufferPushEnable = FALSE;}
    int 			BufferIsPushEnable() {return bBufferPushEnable;}
    int 			BufferIsPopEnable() {return bBufferPopEnable;}
private:
    void*                       pBuffer;					// Data buffer
    uint16_t					u16BufferSize;				// Size of buffer or the total of elements
    uint16_t    				u16ElementCount;				// The element count of buffer
    uint16_t					u16BufferPopPtr;				// The pointer to start reading
    uint16_t					u16BufferPushPtr;			// The pointer to start writing

    int                            bBufferPopEnable;			// Data popping enabling flag
    int                            bBufferPushEnable;			// Data pushing enabling flag

    CallbackFunctionNoIO			callbackLock;				// Call-back function for locking multi-access
    CallbackFunctionNoIO			callbackUnlock;				// Call-back function for unlocking multi-access
};

#endif // QRINGBUFFER_H
