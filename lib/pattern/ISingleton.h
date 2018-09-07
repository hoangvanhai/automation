/**
 * @addtogroup cppframework
 * @{
 * @defgroup pattern Design Pattern Template
 * @addtogroup pattern
 * @{
 *
 */ 
#ifndef __PATTERN_I_SINGLETON_H__
#define __PATTERN_I_SINGLETON_H__

#include <memory>
#include <mutex>

/**
 * @brief Define a singleton class
   @code
   in .h file
        PATTERN_SINGLETON(ClassName,
            // class's content here
        )
    in .cpp file
        PATTERN_SINGLETON_IMPLEMENT(ClassName)
    use
        // init instance
        std::shared_ptr<ClassName> inst = ClassName::getInstance();
        // destroy object
        ClassName::destroyInstance();
   @endcode
 */
#define PATTERN_SINGLETON(name, content) \
class name{ \
public: \
    static std::shared_ptr<name> getInstance(){\
        std::call_once(m_initFlag, [](){\
            m_inst = std::make_shared<name>();\
        });\
        return m_inst;\
    }\
    static void destroyInstance(){\
        if(m_inst) m_inst.reset();\
    }\
private:\
    static std::shared_ptr<name> m_inst;\
    static std::once_flag        m_initFlag;\
    content\
};
/**
 * @brief Implement a singleton
 */
#define PATTERN_SINGLETON_IMPLEMENT(name) \
    std::shared_ptr<name> name::m_inst;\
    std::once_flag        name::m_initFlag;

#endif
/**
 * @} @}
 */ 
