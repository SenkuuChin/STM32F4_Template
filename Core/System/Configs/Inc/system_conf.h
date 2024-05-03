#ifndef __MY_SYSTEM_CONF_H__
    #define __MY_SYSTEM_CONF_H__
    #include "global_conf.h"
    void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);
    void sys_wfi_set(void);
    void sys_intx_disable(void);
    void sys_intx_enable(void);
    void sys_msr_msp(uint32_t addr);
    void sys_standby(void);
    void sys_soft_reset(void);
    void SystemClockConfig(uint16_t pllm, uint16_t plln, uint16_t pllp, uint16_t pllq);
#endif
