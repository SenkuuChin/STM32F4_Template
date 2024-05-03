#include "RT_ThreadHelper.h"
#include "serial_helper.h"


rt_thread_t RTOSThreadCreate(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick)
{
    rt_thread_t handle = rt_thread_create(name,
                                   entry,
                                   parameter,
                                   stack_size,
                                   priority,
                                   tick);
    if (handle != RT_NULL)
    {
        rt_thread_startup(handle);
    }
    return handle;
}

rt_err_t RTOSThreadClose(rt_thread_t thread)
{
    return rt_thread_delete(thread);
}

void rt_hw_console_output(const char *str)
{
    SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, str);
}
