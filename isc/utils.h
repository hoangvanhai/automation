#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdint.h>
#include <string>

//#define ABS(a)          ((a) > 0 ? (a) : (-a))

class Utils
{
public:
    Utils();
    static int      getInt32(const char* data);
    static short    getInt16(const char* data);
    static int64_t  getInt64(const char *data);

    static int64_t  convert2Int64(const char* data);
    static int64_t  convert2Int64Revert(const char* data);

    static uint64_t convert2Uint64(const char* data);
    static uint64_t convert2Uint64Revert(const char *data);

    static int32_t  convert2Int32Revert(const char *data);
    static uint32_t  convert2Uint32Revert(const char *data);

    static double   convert2Double(const char* data);
    static double   convert2DoubleRevert(const char* data);
    static float    convert2Float(const char *data);
    static float    convert2FloatRevert(const char* data);
    static bool     isExist(std::string filename);

    typedef union Float {
        int8_t buffer[4];
        float num;
    }Float;

    typedef union Double {
        int8_t buffer[8];
        double num;
    }Double;


private:
    typedef union Int32
    {
        int8_t buffer[4];
        int num;
    } Int32 ;

    typedef union Uint32
    {
        int8_t buffer[4];
        int num;
    } Uint32 ;

    typedef union Int64
    {
        int8_t  buffer[8];
        int64_t num;
    }Int64;

    typedef union Uint64
    {
        int8_t buffer[8];
        uint64_t num;
    }Uint64;

    typedef union Int16
    {
        int8_t buffer[2];
        short num;
    } Int16 ;



    static void swapChars(char* pChar1, char* pChar2);
    static bool isLittleEndian();
};



#endif // UTILS_H
