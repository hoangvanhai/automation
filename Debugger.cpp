/**
 * @author Various
 * @date 2017/03/08
 * @version 2017/03/08
 * - Thêm comment
 */
#include "Debugger.h"
//#include <ModuleAPI.h>
#include <string/StringUtils.h>
#include <cli/Console.h>
#include <dll/dll_function.h>

#include <inttypes.h>
#include <ctime>

#include <iostream>

#if defined(__linux__)
#include <syslog.h>
#elif defined(_MSC_VER)

#endif
void __print_debug(const char* sz, int raw){   
    app::AppDebugger::getInstance()->print(sz, raw);
}

using namespace app;

AppDebugger* AppDebugger::m_inst = 0;
AppDebugger::AppDebugger(){
    setMode(Mode_STDIO);
    m_startupTimestamp = std::chrono::high_resolution_clock::now();
}
AppDebugger::~AppDebugger(){
    if(m_mode & Mode_SYSLOG){
        #if defined (__linux__)
        closelog();
        #endif
    }
}
void AppDebugger::setMode(unsigned int mode){
    if(m_mode & Mode_SYSLOG){
        #if defined (__linux__)
        closelog();
        #endif
    }
    m_mode = mode;
    if(m_mode & Mode_SYSLOG){
#if defined (__linux__)
        setlogmask(LOG_UPTO(LOG_ALERT));
        openlog(m_name.c_str(), LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
#endif
    }
}
void AppDebugger::print(const char* str, int raw){
    std::string sz;

    if(!raw){
        time_t rawtime;
        time(&rawtime);
        struct tm* timeinfo = localtime(&rawtime);
        auto ts = std::chrono::high_resolution_clock::now();
        auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(ts - m_startupTimestamp);
        sz = cppframework::str::Util::format("{}-{}-{} {}:{}:{}|{}| {}",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            dif.count(),
            std::string(str)
        );
    }else{
        sz = std::string(str);
    }
    std::lock_guard<std::recursive_mutex> lck(m_lock);
    if(m_mode & Mode_STDIO){
        cppframework::cli::Console::print(sz);
        cppframework::cli::Console::flush();
    }

#if defined (_linux__)
    if(m_mode & Mode_SYSLOG){
        typedef void (*syslog_dll)(int priority, const char *format, ...);
        syslog_dll _syslog = dll_function<syslog_dll>("syslog");
        _syslog(LOG_ALERT, sz.c_str());
    }
#endif
}
AppDebugger* AppDebugger::getInstance(){
    if(!m_inst)
        m_inst = new AppDebugger();
    return m_inst;
}

void         AppDebugger::destroyInstance(){
    if(m_inst) delete m_inst;
    m_inst = 0;
}

// end of file
