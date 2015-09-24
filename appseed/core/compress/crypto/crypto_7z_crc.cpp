/* 7zCrc.ca -- CRC32 calculation
2009-11-23 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#include "framework.h"
#include "crypto_7z_crc.h"

CLASS_DECL_CORE uint32_t * CrcGetTable();

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

typedef uint32_t (*CRC_FUNC)(uint32_t v, const void *data, memory_size_t size, const uint32_t *table);

static CRC_FUNC g_CrcUpdate = NULL;

CLASS_DECL_CORE uint32_t * CrcGetTable()
{
    static uint32_t table[256 * CRC_NUM_TABLES];
    return table;
}

CLASS_DECL_CORE uint32_t * g_pCrcTable = NULL;

#if CRC_NUM_TABLES == 1

#define CRC_UPDATE_BYTE_2(crc, b) (table[((crc) ^ (b)) & 0xFF] ^ ((crc) >> 8))

static uint32_t CrcUpdateT1(uint32_t v, const void *data, size_t size, const uint32_t *table)
{
  const byte *p = (const byte *)data;
  for (; size > 0; size--, p++)
    v = CRC_UPDATE_BYTE_2(v, *p);
  return v;
}

#else

uint32_t CrcUpdateT4(uint32_t v, const void *data, memory_size_t size, const uint32_t *table);
uint32_t CrcUpdateT8(uint32_t v, const void *data, memory_size_t size, const uint32_t *table);

#endif

uint32_t crc_update(uint32_t v, const void *data, memory_size_t size)
{
  return g_CrcUpdate(v, data, size, g_pCrcTable);
}

uint32_t crc_calc(const void *data, memory_size_t size)
{
  return g_CrcUpdate(CRC_INIT_VAL, data, size, g_pCrcTable) ^ CRC_INIT_VAL;
}

void CrcGenerateTable()
{
    //   int iDebug = CRC_NUM_TABLES;
  g_pCrcTable = CrcGetTable();
  uint32_t i;
  for (i = 0; i < 256; i++)
  {
    uint32_t r = i;
    uint32_t j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ~((r & 1) - 1));
    g_pCrcTable[i] = r;
  }
#if CRC_NUM_TABLES == 1
  g_CrcUpdate = CrcUpdateT1;
#else
  for (; i < 256 * CRC_NUM_TABLES; i++)
  {
    uint32_t r = g_pCrcTable[i - 256];
    g_pCrcTable[i] = g_pCrcTable[r & 0xFF] ^ (r >> 8);
  }
  g_CrcUpdate = CrcUpdateT4;
#ifdef MY_CPU_X86_OR_AMD64
  if (!CPU_Is_InOrder())
    g_CrcUpdate = CrcUpdateT8;
#endif
#endif
}
