#include "sram_helper.h"


#if !(__ARMCC_VERSION >= 6010050)   /* 不是AC6编译器，即使用AC5编译器时 */
/* 内存池(64字节对齐) */
static __align(64) uint8_t sramMemoryPoll[SRAM_MEMORY_1_MAX_SIZE];									/* 内部SRAM内存池 */
#if SRAM_POLL_NUM > 1
static __align(64) uint8_t ccmMemoryPoll[SRAM_MEMORY_2_MAX_SIZE] __attribute__((at(0x10000000)));	/* 内部CCM内存池 */
#endif
/* 内存管理表 */
/* 内部SRAM内存池MAP */
static SRAM_DATA_TYPE sramMemoryTable[SRAM_MEMORY_1_ALLOC_TABLE_SIZE];
#if SRAM_POLL_NUM > 1
/* 内部CCM内存池MAP */
static SRAM_DATA_TYPE ccmMemoryTable[SRAM_MEMORY_2_ALLOC_TABLE_SIZE] __attribute__((at(0x10000000 + SRAM_MEMORY_2_MAX_SIZE)));
#endif
#else      /* 使用AC6编译器时 */
/* 内存池(64字节对齐) */
/* 内部SRAM内存池 */
static __ALIGNED(64) uint8_t sramMemoryPoll[SRAM_MEMORY_1_MAX_SIZE];
#if SRAM_POLL_NUM > 1
/* 内部CCM内存池 */
static __ALIGNED(64) uint8_t ccmMemoryPoll[SRAM_MEMORY_2_MAX_SIZE] __attribute__((section(".bss.ARM.__at_0x10000000")));
#endif
/* 内存管理表 */
/* 内部SRAM内存池 */
static SRAM_DATA_TYPE sramMemoryTable[SRAM_MEMORY_1_ALLOC_TABLE_SIZE];
#if SRAM_POLL_NUM > 1
/* 内部CCM内存池 */
static SRAM_DATA_TYPE ccmMemoryTable[SRAM_MEMORY_2_ALLOC_TABLE_SIZE] __attribute__((section(".bss.ARM.__at_0x1000F000")));
#endif
#endif

/* 内存管理参数 */
/* 内存表大小 */
const uint32_t  memoryTableSize[SRAM_POLL_NUM]= { SRAM_MEMORY_1_ALLOC_TABLE_SIZE, SRAM_MEMORY_2_ALLOC_TABLE_SIZE };
/* 内存分块大小 */
const uint32_t  memoryBlockSize[SRAM_POLL_NUM]= { SRAM_MEMORY_1_BLOCK_SIZE, SRAM_MEMORY_2_BLOCK_SIZE };
/* 内存总大小 */
const uint32_t  memorySize[SRAM_POLL_NUM]= { SRAM_MEMORY_1_MAX_SIZE, SRAM_MEMORY_2_MAX_SIZE };


void SRAM_Memory_Copy(void *des, void *src, uint32_t n)
{
    uint8_t *xdes = des;
    uint8_t *xsrc = src;

    while (n--) *xdes++ = *xsrc++;
}

void SRAM_Memory_Set(void *map, uint8_t val, uint32_t count)
{
    uint8_t *temp = map;

    while (count--) *temp++ = val;
}

void SRAM_Init(void)
{
    uint8_t dataTypeSize = 0, i;
    for (i = 0; i < SRAM_POLL_NUM; ++i)
    {
        dataTypeSize = sizeof(SRAM_DATA_TYPE);      /* 获取memoryTable数组的类型长度(uint16_t /uint32_t)*/
        SRAM_Memory_Set(SRAMHelper.memoryTable[i], 0, memoryTableSize[i] * dataTypeSize); /* 内存状态表数据清零 */
        SRAMHelper.Instance[i] = INITIALIZED;       /* 内存管理初始化OK */
    }
}

uint16_t SRAM_UsageRate(SRAM_MEMORY_TypeDef memoryPollNo)
{
    uint32_t used = 0;
    uint32_t i;

    for (i = 0; i < memoryTableSize[memoryPollNo]; ++i)
    {
        if (SRAMHelper.memoryTable[memoryPollNo][i])
        {
            ++used;
        }
    }

    return (used * 1000) / (memoryTableSize[memoryPollNo]);
}

uint32_t SRAM_Memory_Malloc(SRAM_MEMORY_TypeDef memoryPollNo, uint32_t size)
{
    long offset = 0;
    uint32_t  needMemeoryBlockNum;      /* 需要的内存块数 */
    uint32_t  emptyMemoryBlockNum = 0;  /* 连续空内存块数 */
    uint32_t  i;

    if (SRAMHelper.Instance[memoryPollNo] != INITIALIZED)
    {
        /* 未初始化,先执行初始化 */
        SRAMHelper.Init();
    }

    if (size == 0) return 0xFFFFFFFF;   /* 不需要分配 */

    /* 获取需要分配的连续内存块数 */
    needMemeoryBlockNum = size / memoryBlockSize[memoryPollNo];
    if (size % memoryBlockSize[memoryPollNo])
    {
        ++needMemeoryBlockNum;
    }
    /* 搜索整个内存控制区 */
    for (offset = memoryTableSize[memoryPollNo] - 1; offset >= 0; --offset)
    {
        if (!SRAMHelper.memoryTable[memoryPollNo][offset])
        {
            /* 连续空内存块数增加 */
            ++emptyMemoryBlockNum;
        }
        else
        {
            /* 连续内存块清零 */
            emptyMemoryBlockNum = 0;
        }
        /* 找到了连续需要的内存个空内存块 */
        if (emptyMemoryBlockNum == needMemeoryBlockNum)
        {
            /* 标注内存块非空 */
            for (i = 0; i < needMemeoryBlockNum; ++i)
            {
                SRAMHelper.memoryTable[memoryPollNo][offset + i] = needMemeoryBlockNum;
            }
            return (offset * memoryBlockSize[memoryPollNo]);    /* 返回偏移地址 */
        }
    }
    return 0xFFFFFFFF;	/* 未找到符合分配条件的内存块 */
}

HandleResult SRAM_Memory_Free(SRAM_MEMORY_TypeDef memoryPollNo, uint32_t offset)
{
    int i;

    if (offset >= memorySize[memoryPollNo])
    {
        return NOT_OK;
    }
    /* 未初始化,先执行初始化 */
    if (!SRAMHelper.Instance[memoryPollNo])
    {
        SRAMHelper.Init();
    }

    /* 偏移所在内存块号码 */
    int index = offset / memoryBlockSize[memoryPollNo];
    /* 内存块数量 */
    int memoryBlockNum = SRAMHelper.memoryTable[memoryPollNo][index];
    /* 内存块清零 */
    for (i = 0; i < memoryBlockNum; i++)
    {
        SRAMHelper.memoryTable[memoryPollNo][index + i] = 0;
    }
    return OK;
}

void MyMemoryFree(SRAM_MEMORY_TypeDef memoryPollNo, void *ptr)
{
    uint32_t offset;

    if (ptr == NULL) return;    /* 地址为0 */

    offset = (uint32_t)ptr - (uint32_t)SRAMHelper.memoryPoll[memoryPollNo];
    /* 释放内存 */
    SRAM_Memory_Free(memoryPollNo, offset);
}

void* MyMemoryMalloc(SRAM_MEMORY_TypeDef memoryPollNo, uint32_t size)
{
    uint32_t  offset;
    offset = SRAM_Memory_Malloc(memoryPollNo, size);

    if (offset == 0xFFFFFFFF)
    {
        return NULL;
    }
    else
    {
        return (void*)((uint32_t )SRAMHelper.memoryPoll[memoryPollNo] + offset);
    }
}

void* MyMemoryRealloc(SRAM_MEMORY_TypeDef memoryPollNo, void *ptr, uint32_t size)
{
    uint32_t  offset;
    offset = SRAM_Memory_Malloc(memoryPollNo, size);

    if (offset == 0xFFFFFFFF)
    {
        return NULL;
    }
    else
    {
        SRAM_Memory_Copy((void*)((uint32_t)SRAMHelper.memoryPoll[memoryPollNo] + offset), ptr, size);   /* 拷贝旧内存内容到新内存 */
        MyMemoryFree(memoryPollNo, ptr);	/* 释放旧内存 */
        return (void*)((uint32_t)SRAMHelper.memoryPoll[memoryPollNo] + offset); /* 返回新内存首地址 */
    }
}

SRAMHelper_TypeDef SRAMHelper = {
    NULL, NULL,
    sramMemoryPoll, ccmMemoryPoll,
    sramMemoryTable, ccmMemoryTable,
    SRAM_UsageRate,
    SRAM_Init,
    MyMemoryMalloc,
    MyMemoryFree,
    MyMemoryRealloc
};

