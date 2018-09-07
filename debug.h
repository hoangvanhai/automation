/**
 * @addtogroup adapter-app-radio
 * @{
 * @file debug.h
 * @brief Định nghĩa lệnh debug
 * @author Various
 * @date 2017/03/08
 * @version 2017/03/08
 * -- Thêm comment
 */ 
#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <string/StringUtils.h>

#ifdef __cplusplus
extern "C"{
#endif
    extern void __print_debug(const char* sz, int raw);
#ifdef __cplusplus
}
#endif

#if defined(__linux__)
/**
 * @brief In dòng debug ra màn hình, hoặc syslog...
 * @param s Chuỗi kèm định dạng
 * @param args Danh sách tham số được định dạng trong s
 */
#define LREP(s, args...) {\
    std::string sz = cppframework::str::Util::format(s, ##args);\
    __print_debug(sz.c_str(), 1);      /*__print_debug(sz.c_str(), 0);\ */ \
}
/*
 * @brief In dòng debug kèm theo vị trí, tên tập tin
 * @param s Chuỗi kèm định dạng
 * @param args Danh sách tham số được định dạng trong s
 */
#define LREP_WARN(s, args...) {\
    std::string sz = cppframework::str::Util::format("WARN {}@{}: \n\n" s, __LINE__, __FILE__, ##args);\
    __print_debug(sz.c_str(), 1);\
}

#define ASSERT(cond) {\
    if(!(cond)) {\
        std::ostringstream astream; std::string astr;\
        astream << "ASSERT FAILED: " << __FILE__ << " " << __LINE__ << "\n\n";\
        astr = astream.str();\
        __print_debug(astr.c_str(), 1);\
    }\
}


#define ASSERT_MSG(cond, s, args...) {\
    if(!cond) {\
    std::string sz = cppframework::str::Util::format("WARN {}@{}: \n\n" s, __LINE__, __FILE__, ##args);\
    __print_debug(sz.c_str(), 0);\
    }\
}

#elif defined(_MSC_VER)
#define LREP(s, ...) {\
    std::string sz = cppframework::str::Util::format(s, __VA_ARGS__);\
    std::cout << sz.c_str(); fflush(stdout);\
}

#define ASSERT(cond) {\
    if(!(cond)) {\
        std::ostringstream astream; std::string astr;\
        astream << "ASSERT FAILED: " << __FILE__ << " " << __LINE__ << "\n\n";\
        astr = astream.str();\
        std::cout << astr.c_str(); fflush(stdout); \
    }\
}



#define LREP_WARN(s, ...) {\
    std::string sz = cppframework::str::Util::format("WARN {}@{}: " s, __LINE__, __FILE__, __VA_ARGS__);\
    __print_debug(sz.c_str(), 0);\
}
#endif

#endif
/** @} */
