/* 7z.h -- 7z interface
2010-03-11 : Igor Pavlov : Public domain */

#ifndef __7Z_H
#define __7Z_H

#include "7zBuf.h"

EXTERN_C_BEGIN

#define k7zStartHeaderSize 0x20
#define k7zSignatureSize 6
extern Byte k7zSignature[k7zSignatureSize];
#define k7zMajorVersion 0

enum EIdEnum
{
  k7zIdEnd,
  k7zIdHeader,
  k7zIdArchiveProperties,
  k7zIdAdditionalStreamsInfo,
  k7zIdMainStreamsInfo,
  k7zIdFilesInfo,
  k7zIdPackInfo,
  k7zIdUnpackInfo,
  k7zIdSubStreamsInfo,
  k7zIdSize,
  k7zIdCRC,
  k7zIdFolder,
  k7zIdCodersUnpackSize,
  k7zIdNumUnpackStream,
  k7zIdEmptyStream,
  k7zIdEmptyFile,
  k7zIdAnti,
  k7zIdName,
  k7zIdCTime,
  k7zIdATime,
  k7zIdMTime,
  k7zIdWinAttributes,
  k7zIdComment,
  k7zIdEncodedHeader,
  k7zIdStartPos,
  k7zIdDummy
};

typedef struct
{
  uint32 NumInStreams;
  uint32 NumOutStreams;
  UInt64 MethodID;
  CBuf Props;
} CSzCoderInfo;

void SzCoderInfo_Init(CSzCoderInfo *p);
void SzCoderInfo_Free(CSzCoderInfo *p, ISzAlloc *alloc);

typedef struct
{
  uint32 InIndex;
  uint32 OutIndex;
} CSzBindPair;

typedef struct
{
  CSzCoderInfo *Coders;
  CSzBindPair *BindPairs;
  uint32 *PackStreams;
  UInt64 *UnpackSizes;
  uint32 NumCoders;
  uint32 NumBindPairs;
  uint32 NumPackStreams;
  int UnpackCRCDefined;
  uint32 UnpackCRC;

  uint32 NumUnpackStreams;
} CSzFolder;

void SzFolder_Init(CSzFolder *p);
UInt64 SzFolder_GetUnpackSize(CSzFolder *p);
int SzFolder_FindBindPairForInStream(CSzFolder *p, uint32 inStreamIndex);
uint32 SzFolder_GetNumOutStreams(CSzFolder *p);
UInt64 SzFolder_GetUnpackSize(CSzFolder *p);

SRes SzFolder_Decode(const CSzFolder *folder, const UInt64 *packSizes,
    ILookInStream *stream, UInt64 startPos,
    Byte *outBuffer, size_t outSize, ISzAlloc *allocMain);

typedef struct
{
  uint32 Low;
  uint32 High;
} CNtfsFileTime;

typedef struct
{
  CNtfsFileTime MTime;
  UInt64 Size;
  uint32 Crc;
  uint32 Attrib;
  Byte HasStream;
  Byte IsDir;
  Byte IsAnti;
  Byte CrcDefined;
  Byte MTimeDefined;
  Byte AttribDefined;
} CSzFileItem;

void SzFile_Init(CSzFileItem *p);

typedef struct
{
  UInt64 *PackSizes;
  Byte *PackCRCsDefined;
  uint32 *PackCRCs;
  CSzFolder *Folders;
  CSzFileItem *Files;
  uint32 NumPackStreams;
  uint32 NumFolders;
  uint32 NumFiles;
} CSzAr;

void SzAr_Init(CSzAr *p);
void SzAr_Free(CSzAr *p, ISzAlloc *alloc);


/*
  SzExtract extracts file from archive

  *outBuffer must be 0 before first call for each new archive.

  Extracting cache:
    If you need to decompress more than one file, you can send
    these values from previous call:
      *blockIndex,
      *outBuffer,
      *outBufferSize
    You can consider "*outBuffer" as cache of solid block. If your archive is solid,
    it will increase decompression speed.
  
    If you use external function, you can declare these 3 cache variables
    (blockIndex, outBuffer, outBufferSize) as static in that external function.
    
    Free *outBuffer and set *outBuffer to 0, if you want to flush cache.
*/

typedef struct
{
  CSzAr db;
  
  UInt64 startPosAfterHeader;
  UInt64 dataPos;

  uint32 *FolderStartPackStreamIndex;
  UInt64 *PackStreamStartPositions;
  uint32 *FolderStartFileIndex;
  uint32 *FileIndexToFolderIndexMap;

  size_t *FileNameOffsets; /* in 2-byte steps */
  CBuf FileNames;  /* UTF-16-LE */
} CSzArEx;

void SzArEx_Init(CSzArEx *p);
void SzArEx_Free(CSzArEx *p, ISzAlloc *alloc);
UInt64 SzArEx_GetFolderStreamPos(const CSzArEx *p, uint32 folderIndex, uint32 indexInFolder);
int SzArEx_GetFolderFullPackSize(const CSzArEx *p, uint32 folderIndex, UInt64 *resSize);

/*
if dest == NULL, the return value specifies the required size of the buffer,
  in 16-bit characters, including the NULL-terminating character.
if dest != NULL, the return value specifies the number of 16-bit characters that
  are written to the dest, including the NULL-terminating character. */

size_t SzArEx_GetFileNameUtf16(const CSzArEx *p, size_t fileIndex, UInt16 *dest);

SRes SzArEx_Extract(
    const CSzArEx *db,
    ILookInStream *inStream,
    uint32 fileIndex,         /* index of file */
    uint32 *blockIndex,       /* index of solid block */
    Byte **outBuffer,         /* pointer to pointer to output buffer (allocated with allocMain) */
    size_t *outBufferSize,    /* buffer size for output buffer */
    size_t *offset,           /* offset of stream for required file in *outBuffer */
    size_t *outSizeProcessed, /* size of file in *outBuffer */
    ISzAlloc *allocMain,
    ISzAlloc *allocTemp);


/*
SzArEx_Open Errors:
SZ_ERROR_NO_ARCHIVE
SZ_ERROR_ARCHIVE
SZ_ERROR_UNSUPPORTED
SZ_ERROR_MEM
SZ_ERROR_CRC
SZ_ERROR_INPUT_EOF
SZ_ERROR_FAIL
*/

SRes SzArEx_Open(CSzArEx *p, ILookInStream *inStream, ISzAlloc *allocMain, ISzAlloc *allocTemp);

EXTERN_C_END

#endif
