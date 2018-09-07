/**
 * @addtogroup app
 * @{
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <inttypes.h>
#include <string>
#include <mutex>

#ifdef __cplusplus
extern "C"{
#endif
    /**
     * @brief In chuỗi 'sz' ra màn hình
     * @param sz Chuỗi cần in
     * @param raw Nếu 'raw'==0 in kèm thông tin ngày giờ
     */
    void __print_debug(const char* sz, int raw);
#ifdef __cplusplus
}
#endif

namespace app{
/**
 * @brief Quản lý luồng dữ liệu debug
 * @author Various
 * @date 2017/03/08
 * @version 2017/03/08
 * - Thêm comment
 * @note Thiết kết theo mô hình Singleton
 */
class AppDebugger{
public:
    /**
     * @brief Hướng của luồng dữ liệu debug
     */ 
    enum Mode{
        Mode_STDIO = 0x01,  ///< Ghi dữ liệu debug ra stdout
        Mode_SYSLOG= 0x02,  ///< Ghi dữ liệu debug ra syslog (/var/log/messages hoặc /var/log/syslog)
    };
    AppDebugger();
    virtual ~AppDebugger();
    /** @brief Lấy đối tượng của class
     *  @return  AppDebugger* Đối tượng của class
     */ 
    static AppDebugger* getInstance();
    /** @brief Hủy đối tượng của class
     */ 
    static void         destroyInstance();
    /**
     * @brief Thiết lập hướng của luồng dữ liệu
     * @param mode Hướng của luồng dữ liệu, là giá trị OR của enum Mode
     */ 
    void setMode(unsigned int mode);
    /**
     * @brief In chuỗi 'sz' ra màn hình
     * @param str Chuỗi cần in
     * @param raw Nếu 'raw'==0 in kèm thông tin ngày giờ
     */
    void print(const char* str, int raw);
private:
    unsigned int            m_mode;     ///< Hướng dữ liệu
    std::recursive_mutex    m_lock;     ///< Đối tượng khóa 
    std::chrono::high_resolution_clock::time_point  m_startupTimestamp; ///< Thời điểm bắt đầu chạy chương trình
    static AppDebugger*     m_inst;     ///< Đối tượng của class
    std::string             m_name;

    int initialize();
};
}
#endif
/** @} */
