/* 7zCrc.h -- CRC32 calculation
2009-11-21 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once


CLASS_DECL_CORE extern uint32_t * g_pCrcTable;

/* Call CrcGenerateTable one time before other CRC functions */
CLASS_DECL_CORE void CrcGenerateTable();

#define CRC_INIT_VAL 0xFFFFFFFF
#define CRC_GET_DIGEST(crc) ((crc) ^ CRC_INIT_VAL)
#define CRC_UPDATE_BYTE(crc, b) (g_pCrcTable[((crc) ^ (b)) & 0xFF] ^ ((crc) >> 8))

CLASS_DECL_CORE uint32_t crc_update(uint32_t crc, const void * data, memory_size_t size);
CLASS_DECL_CORE uint32_t crc_calc(const void * data, memory_size_t size);

