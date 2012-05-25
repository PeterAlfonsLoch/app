/* 7zCrc.c -- CRC32 calculation
2009-11-23 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#include "framework.h"


struct CCRCTableInit
{ 
   
   CCRCTableInit()
   { 
      CrcGenerateTable(); 
   } 

} g_CRCTableInit;

#define kCrcPoly 0xEDB88320

#ifdef MY_CPU_LE
#define CRC_NUM_TABLES 8
#else
#define CRC_NUM_TABLES 1
#endif

typedef uint32 (*CRC_FUNC)(uint32 v, const void *data, ::primitive::memory_size size, const uint32 *table);

static CRC_FUNC g_CrcUpdate;
uint32 g_CrcTable[256 * CRC_NUM_TABLES];

#if CRC_NUM_TABLES == 1

#define CRC_UPDATE_BYTE_2(crc, b) (table[((crc) ^ (b)) & 0xFF] ^ ((crc) >> 8))

static uint32 CrcUpdateT1(uint32 v, const void *data, size_t size, const uint32 *table)
{
  const byte *p = (const byte *)data;
  for (; size > 0; size--, p++)
    v = CRC_UPDATE_BYTE_2(v, *p);
  return v;
}

#else

uint32 CrcUpdateT4(uint32 v, const void *data, ::primitive::memory_size size, const uint32 *table);
uint32 CrcUpdateT8(uint32 v, const void *data, ::primitive::memory_size size, const uint32 *table);

#endif

uint32 crc_update(uint32 v, const void *data, ::primitive::memory_size size)
{
  return g_CrcUpdate(v, data, size, g_CrcTable);
}

uint32 crc_calc(const void *data, ::primitive::memory_size size)
{
  return g_CrcUpdate(CRC_INIT_VAL, data, size, g_CrcTable) ^ CRC_INIT_VAL;
}

void CrcGenerateTable()
{
  uint32 i;
  for (i = 0; i < 256; i++)
  {
    uint32 r = i;
    unsigned j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ~((r & 1) - 1));
    g_CrcTable[i] = r;
  }
  #if CRC_NUM_TABLES == 1
  g_CrcUpdate = CrcUpdateT1;
  #else
  for (; i < 256 * CRC_NUM_TABLES; i++)
  {
    uint32 r = g_CrcTable[i - 256];
    g_CrcTable[i] = g_CrcTable[r & 0xFF] ^ (r >> 8);
  }
  g_CrcUpdate = CrcUpdateT4;
  #ifdef MY_CPU_X86_OR_AMD64
  if (!CPU_Is_InOrder())
    g_CrcUpdate = CrcUpdateT8;
  #endif
  #endif
}
