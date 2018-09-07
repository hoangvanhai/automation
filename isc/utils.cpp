#include "utils.h"
#include "iostream"

Utils::Utils()
{

}

int Utils::getInt32(const char* data){
    int result;
    Int32 num;
    memmove(num.buffer, data, 4);
    if(isLittleEndian()){
        swapChars((char*)&num.buffer[0], (char*)&num.buffer[3]);
        swapChars((char*)&num.buffer[1], (char*)&num.buffer[2]);

    }
    result = num.num;
    return result;
}

short Utils::getInt16(const char* data){
    short result;
    Int16 num;
    memmove(num.buffer, data, 2);
    if(isLittleEndian()){
        swapChars((char*)&num.buffer[0], (char*)&num.buffer[1]);
    }
    result = num.num;
    return result;
}

int64_t Utils::getInt64(const char *data)
{
    int64_t result;
    Int64 num;
    memmove(num.buffer, data, 8);
    if(isLittleEndian()) {
        std::cout << "Swap " << std::endl;
        swapChars((char*)&num.buffer[0], (char*)&num.buffer[3]);
        swapChars((char*)&num.buffer[1], (char*)&num.buffer[2]);
        swapChars((char*)&num.buffer[4], (char*)&num.buffer[7]);
        swapChars((char*)&num.buffer[5], (char*)&num.buffer[6]);
    } else {
        std::cout << "BIG" << std::endl;
    }

    result = num.num;
    return result;
}

int64_t Utils::convert2Int64(const char* data) {
    Int64 num;
    memmove(num.buffer, data, 8);
    return num.num;
}



int64_t Utils::convert2Int64Revert(const char *data)
{
    Int64 num;
    memmove(num.buffer, data, 8);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[7]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[6]);
    swapChars((char*)&num.buffer[2], (char*)&num.buffer[5]);
    swapChars((char*)&num.buffer[3], (char*)&num.buffer[4]);
    return num.num;
}

uint64_t Utils::convert2Uint64(const char *data)
{
    Uint64 num;
    memmove(num.buffer, data, 8);
    return num.num;
}

uint64_t Utils::convert2Uint64Revert(const char *data)
{
    Uint64 num;
    memmove(num.buffer, data, 8);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[7]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[6]);
    swapChars((char*)&num.buffer[2], (char*)&num.buffer[5]);
    swapChars((char*)&num.buffer[3], (char*)&num.buffer[4]);
    return num.num;
}

int32_t Utils::convert2Int32Revert(const char *data)
{
    Int32 num;
    memmove(num.buffer, data, 4);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[3]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[2]);
    return num.num;
}

uint32_t Utils::convert2Uint32Revert(const char *data)
{
    Uint32 num;
    memmove(num.buffer, data, 4);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[3]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[2]);
    return num.num;
}


double Utils::convert2Double(const char *data)
{
    Int64 num;
    memmove(num.buffer, data, 8);
    return num.num;
}

double Utils::convert2DoubleRevert(const char *data)
{
    Double num;
    memmove(num.buffer, data, 8);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[7]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[6]);
    swapChars((char*)&num.buffer[2], (char*)&num.buffer[5]);
    swapChars((char*)&num.buffer[3], (char*)&num.buffer[4]);
    return num.num;
}

float Utils::convert2Float(const char *data)
{
    Float num;
    memmove(num.buffer, data, 4);
    return num.num;
}

float Utils::convert2FloatRevert(const char *data)
{
    Float num;
    memmove(num.buffer, data, 4);
    swapChars((char*)&num.buffer[0], (char*)&num.buffer[3]);
    swapChars((char*)&num.buffer[1], (char*)&num.buffer[2]);
    return num.num;
}

bool Utils::isExist(std::string filename)
{

    if(FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void Utils::swapChars(char* pChar1, char* pChar2)
{
    char temp = *pChar1;
    *pChar1 = *pChar2;
    *pChar2 = temp;
}


bool Utils::isLittleEndian(){
    int num = 1;
    return (*(char *)&num == 1);
}

