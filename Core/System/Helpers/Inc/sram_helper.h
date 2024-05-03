#ifndef __MY_COMMON_SRAM_HELPER_H__
    #define __MY_COMMON_SRAM_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    #if SYS_SRAM_MANAGE_ENABLE
    #define SRAM_POLL_NUM                   2           /* 定义内存池数 */
    #define SRAM_DATA_TYPE                  uint16_t
    
    /* SRAM_MEMORY_1内存参数设定.SRAM_1 完全处于内部SRAM里面 */
    #define SRAM_MEMORY_1_BLOCK_SIZE        32          /* 内存块大小为32字节 */
    #define SRAM_MEMORY_1_MAX_SIZE          30 * 1024   /* 最大管理内存 100K, 由于别处有使用，所有只给20K */
    #define SRAM_MEMORY_1_ALLOC_TABLE_SIZE  SRAM_MEMORY_1_MAX_SIZE / SRAM_MEMORY_1_BLOCK_SIZE   /* 内存表大小 */

    /* SRAM_MEMORY_2内存参数设定. SRAM_MEMORY_2处于CCM,用于管理CCM(仅CPU可以访问) */
    #define SRAM_MEMORY_2_BLOCK_SIZE        32          /* 内存块大小为32字节 */
    #define SRAM_MEMORY_2_MAX_SIZE          60 * 1024   /* 最大管理内存 60K，只给10K */
    #define SRAM_MEMORY_2_ALLOC_TABLE_SIZE	SRAM_MEMORY_2_MAX_SIZE / SRAM_MEMORY_2_BLOCK_SIZE   /* 内存表大小 */
    typedef enum
    {
        SRAM_INTERNAL = 0,
        SRAM_CCM
    } SRAM_MEMORY_TypeDef;
    typedef struct
    {
        uint8_t Instance[SRAM_POLL_NUM];                    /* 内存池是否实例化 */
        uint8_t *memoryPoll[SRAM_POLL_NUM];                 /* 内存池 管理SRAMBANK个区域的内存 */
        SRAM_DATA_TYPE *memoryTable[SRAM_POLL_NUM];         /* 内存管理状态表 */
        uint16_t (*GetUsageRate)(SRAM_MEMORY_TypeDef);      /* 内存使用率 */
        void (*Init)(void);                                 /* 初始化 */
        void* (*Malloc)(SRAM_MEMORY_TypeDef, uint32_t);
        void (*Free)(SRAM_MEMORY_TypeDef, void *);
        void* (*Realloc)(SRAM_MEMORY_TypeDef, void *, uint32_t);
    } SRAMHelper_TypeDef;
    extern SRAMHelper_TypeDef SRAMHelper;
    #endif
    #ifdef __cplusplus
    }
    #endif
#endif
