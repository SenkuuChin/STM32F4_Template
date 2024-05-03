#include "sram_helper.h"


#if !(__ARMCC_VERSION >= 6010050)   /* ����AC6����������ʹ��AC5������ʱ */
/* �ڴ��(64�ֽڶ���) */
static __align(64) uint8_t sramMemoryPoll[SRAM_MEMORY_1_MAX_SIZE];									/* �ڲ�SRAM�ڴ�� */
#if SRAM_POLL_NUM > 1
static __align(64) uint8_t ccmMemoryPoll[SRAM_MEMORY_2_MAX_SIZE] __attribute__((at(0x10000000)));	/* �ڲ�CCM�ڴ�� */
#endif
/* �ڴ����� */
/* �ڲ�SRAM�ڴ��MAP */
static SRAM_DATA_TYPE sramMemoryTable[SRAM_MEMORY_1_ALLOC_TABLE_SIZE];
#if SRAM_POLL_NUM > 1
/* �ڲ�CCM�ڴ��MAP */
static SRAM_DATA_TYPE ccmMemoryTable[SRAM_MEMORY_2_ALLOC_TABLE_SIZE] __attribute__((at(0x10000000 + SRAM_MEMORY_2_MAX_SIZE)));
#endif
#else      /* ʹ��AC6������ʱ */
/* �ڴ��(64�ֽڶ���) */
/* �ڲ�SRAM�ڴ�� */
static __ALIGNED(64) uint8_t sramMemoryPoll[SRAM_MEMORY_1_MAX_SIZE];
#if SRAM_POLL_NUM > 1
/* �ڲ�CCM�ڴ�� */
static __ALIGNED(64) uint8_t ccmMemoryPoll[SRAM_MEMORY_2_MAX_SIZE] __attribute__((section(".bss.ARM.__at_0x10000000")));
#endif
/* �ڴ����� */
/* �ڲ�SRAM�ڴ�� */
static SRAM_DATA_TYPE sramMemoryTable[SRAM_MEMORY_1_ALLOC_TABLE_SIZE];
#if SRAM_POLL_NUM > 1
/* �ڲ�CCM�ڴ�� */
static SRAM_DATA_TYPE ccmMemoryTable[SRAM_MEMORY_2_ALLOC_TABLE_SIZE] __attribute__((section(".bss.ARM.__at_0x1000F000")));
#endif
#endif

/* �ڴ������� */
/* �ڴ���С */
const uint32_t  memoryTableSize[SRAM_POLL_NUM]= { SRAM_MEMORY_1_ALLOC_TABLE_SIZE, SRAM_MEMORY_2_ALLOC_TABLE_SIZE };
/* �ڴ�ֿ��С */
const uint32_t  memoryBlockSize[SRAM_POLL_NUM]= { SRAM_MEMORY_1_BLOCK_SIZE, SRAM_MEMORY_2_BLOCK_SIZE };
/* �ڴ��ܴ�С */
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
        dataTypeSize = sizeof(SRAM_DATA_TYPE);      /* ��ȡmemoryTable��������ͳ���(uint16_t /uint32_t)*/
        SRAM_Memory_Set(SRAMHelper.memoryTable[i], 0, memoryTableSize[i] * dataTypeSize); /* �ڴ�״̬���������� */
        SRAMHelper.Instance[i] = INITIALIZED;       /* �ڴ�����ʼ��OK */
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
    uint32_t  needMemeoryBlockNum;      /* ��Ҫ���ڴ���� */
    uint32_t  emptyMemoryBlockNum = 0;  /* �������ڴ���� */
    uint32_t  i;

    if (SRAMHelper.Instance[memoryPollNo] != INITIALIZED)
    {
        /* δ��ʼ��,��ִ�г�ʼ�� */
        SRAMHelper.Init();
    }

    if (size == 0) return 0xFFFFFFFF;   /* ����Ҫ���� */

    /* ��ȡ��Ҫ����������ڴ���� */
    needMemeoryBlockNum = size / memoryBlockSize[memoryPollNo];
    if (size % memoryBlockSize[memoryPollNo])
    {
        ++needMemeoryBlockNum;
    }
    /* ���������ڴ������ */
    for (offset = memoryTableSize[memoryPollNo] - 1; offset >= 0; --offset)
    {
        if (!SRAMHelper.memoryTable[memoryPollNo][offset])
        {
            /* �������ڴ�������� */
            ++emptyMemoryBlockNum;
        }
        else
        {
            /* �����ڴ������ */
            emptyMemoryBlockNum = 0;
        }
        /* �ҵ���������Ҫ���ڴ�����ڴ�� */
        if (emptyMemoryBlockNum == needMemeoryBlockNum)
        {
            /* ��ע�ڴ��ǿ� */
            for (i = 0; i < needMemeoryBlockNum; ++i)
            {
                SRAMHelper.memoryTable[memoryPollNo][offset + i] = needMemeoryBlockNum;
            }
            return (offset * memoryBlockSize[memoryPollNo]);    /* ����ƫ�Ƶ�ַ */
        }
    }
    return 0xFFFFFFFF;	/* δ�ҵ����Ϸ����������ڴ�� */
}

HandleResult SRAM_Memory_Free(SRAM_MEMORY_TypeDef memoryPollNo, uint32_t offset)
{
    int i;

    if (offset >= memorySize[memoryPollNo])
    {
        return NOT_OK;
    }
    /* δ��ʼ��,��ִ�г�ʼ�� */
    if (!SRAMHelper.Instance[memoryPollNo])
    {
        SRAMHelper.Init();
    }

    /* ƫ�������ڴ����� */
    int index = offset / memoryBlockSize[memoryPollNo];
    /* �ڴ������ */
    int memoryBlockNum = SRAMHelper.memoryTable[memoryPollNo][index];
    /* �ڴ������ */
    for (i = 0; i < memoryBlockNum; i++)
    {
        SRAMHelper.memoryTable[memoryPollNo][index + i] = 0;
    }
    return OK;
}

void MyMemoryFree(SRAM_MEMORY_TypeDef memoryPollNo, void *ptr)
{
    uint32_t offset;

    if (ptr == NULL) return;    /* ��ַΪ0 */

    offset = (uint32_t)ptr - (uint32_t)SRAMHelper.memoryPoll[memoryPollNo];
    /* �ͷ��ڴ� */
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
        SRAM_Memory_Copy((void*)((uint32_t)SRAMHelper.memoryPoll[memoryPollNo] + offset), ptr, size);   /* �������ڴ����ݵ����ڴ� */
        MyMemoryFree(memoryPollNo, ptr);	/* �ͷž��ڴ� */
        return (void*)((uint32_t)SRAMHelper.memoryPoll[memoryPollNo] + offset); /* �������ڴ��׵�ַ */
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

