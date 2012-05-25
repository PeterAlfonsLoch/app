/* 7zCrc.h -- CRC32 calculation
2009-11-21 : Igor Pavlov : Public domain */
// from 7-zip on 2010-12-19
#pragma once


extern CLASS_DECL_ca uint32 g_CrcTable[];

/* Call CrcGenerateTable one time before other CRC functions */
CLASS_DECL_ca void CrcGenerateTable();

#define CRC_INIT_VAL 0xFFFFFFFF
#define CRC_GET_DIGEST(crc) ((crc) ^ CRC_INIT_VAL)
#define CRC_UPDATE_BYTE(crc, b) (g_CrcTable[((crc) ^ (b)) & 0xFF] ^ ((crc) >> 8))

CLASS_DECL_ca uint32 crc_update(uint32 crc, const void * data, ::primitive::memory_size size);
CLASS_DECL_ca uint32 crc_calc(const void * data, ::primitive::memory_size size);

