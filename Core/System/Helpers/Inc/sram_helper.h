#ifndef __MY_COMMON_SRAM_HELPER_H__
    #define __MY_COMMON_SRAM_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    #if SYS_SRAM_MANAGE_ENABLE
    #define SRAM_POLL_NUM                   2           /* �����ڴ���� */
    #define SRAM_DATA_TYPE                  uint16_t
    
    /* SRAM_MEMORY_1�ڴ�����趨.SRAM_1 ��ȫ�����ڲ�SRAM���� */
    #define SRAM_MEMORY_1_BLOCK_SIZE        32          /* �ڴ���СΪ32�ֽ� */
    #define SRAM_MEMORY_1_MAX_SIZE          30 * 1024   /* �������ڴ� 100K, ���ڱ���ʹ�ã�����ֻ��20K */
    #define SRAM_MEMORY_1_ALLOC_TABLE_SIZE  SRAM_MEMORY_1_MAX_SIZE / SRAM_MEMORY_1_BLOCK_SIZE   /* �ڴ���С */

    /* SRAM_MEMORY_2�ڴ�����趨. SRAM_MEMORY_2����CCM,���ڹ���CCM(��CPU���Է���) */
    #define SRAM_MEMORY_2_BLOCK_SIZE        32          /* �ڴ���СΪ32�ֽ� */
    #define SRAM_MEMORY_2_MAX_SIZE          60 * 1024   /* �������ڴ� 60K��ֻ��10K */
    #define SRAM_MEMORY_2_ALLOC_TABLE_SIZE	SRAM_MEMORY_2_MAX_SIZE / SRAM_MEMORY_2_BLOCK_SIZE   /* �ڴ���С */
    typedef enum
    {
        SRAM_INTERNAL = 0,
        SRAM_CCM
    } SRAM_MEMORY_TypeDef;
    typedef struct
    {
        uint8_t Instance[SRAM_POLL_NUM];                    /* �ڴ���Ƿ�ʵ���� */
        uint8_t *memoryPoll[SRAM_POLL_NUM];                 /* �ڴ�� ����SRAMBANK��������ڴ� */
        SRAM_DATA_TYPE *memoryTable[SRAM_POLL_NUM];         /* �ڴ����״̬�� */
        uint16_t (*GetUsageRate)(SRAM_MEMORY_TypeDef);      /* �ڴ�ʹ���� */
        void (*Init)(void);                                 /* ��ʼ�� */
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
