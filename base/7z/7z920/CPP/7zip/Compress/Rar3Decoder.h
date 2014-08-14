// Rar3Decoder.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives

/* This code uses Carryless rangecoder (1999): Dmitry Subbotin : Public domain */

#ifndef __COMPRESS_RAR3_DECODER_H
#define __COMPRESS_RAR3_DECODER_H

#include "../../../C/Ppmd7.h"

#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "../Common/InBuffer.h"

#include "BitmDecoder.h"
#include "HuffmanDecoder.h"
#include "Rar3Vm.h"

namespace NCompress {
namespace NRar3 {

const uint32 kWindowSize = 1 << 22;
const uint32 kWindowMask = (kWindowSize - 1);

const uint32 kNumReps = 4;
const uint32 kNumLen2Symbols = 8;
const uint32 kLenTableSize = 28;
const uint32 kMainTableSize = 256 + 1 + 1 + 1 + kNumReps + kNumLen2Symbols + kLenTableSize;
const uint32 kDistTableSize = 60;

const int kNumAlignBits = 4;
const uint32 kAlignTableSize = (1 << kNumAlignBits) + 1;

const uint32 kLevelTableSize = 20;

const uint32 kTablesSizesSum = kMainTableSize + kDistTableSize + kAlignTableSize + kLenTableSize;

class CBitDecoder
{
  uint32 m_Value;
  unsigned m_BitPos;
public:
  CInBuffer m_Stream;
  bool Create(uint32 bufferSize) { return m_Stream.Create(bufferSize); }
  void SetStream(ISequentialInStream *inStream) { m_Stream.SetStream(inStream);}
  void ReleaseStream() { m_Stream.ReleaseStream();}

  void Init()
  {
    m_Stream.Init();
    m_BitPos = 0;
    m_Value = 0;
  }
  
  UInt64 GetProcessedSize() const { return m_Stream.GetProcessedSize() - (m_BitPos) / 8; }
  uint32 GetBitPosition() const { return ((8 - m_BitPos) & 7); }
  
  uint32 GetValue(unsigned numBits)
  {
    if (m_BitPos < numBits)
    {
      m_BitPos += 8;
      m_Value = (m_Value << 8) | m_Stream.ReadByte();
      if (m_BitPos < numBits)
      {
        m_BitPos += 8;
        m_Value = (m_Value << 8) | m_Stream.ReadByte();
      }
    }
    return m_Value >> (m_BitPos - numBits);
  }
  
  void MovePos(unsigned numBits)
  {
    m_BitPos -= numBits;
    m_Value = m_Value & ((1 << m_BitPos) - 1);
  }
  
  uint32 ReadBits(unsigned numBits)
  {
    uint32 res = GetValue(numBits);
    MovePos(numBits);
    return res;
  }
};

const uint32 kTopValue = (1 << 24);
const uint32 kBot = (1 << 15);

struct CRangeDecoder
{
  IPpmd7_RangeDec s;
  uint32 Range;
  uint32 Code;
  uint32 Low;
  CBitDecoder bitDecoder;
  SRes Res;

public:
  void InitRangeCoder()
  {
    Code = 0;
    Low = 0;
    Range = 0xFFFFFFFF;
    for (int i = 0; i < 4; i++)
      Code = (Code << 8) | bitDecoder.ReadBits(8);
  }

  void Normalize()
  {
    while ((Low ^ (Low + Range)) < kTopValue ||
       Range < kBot && ((Range = (0 - Low) & (kBot - 1)), 1))
    {
      Code = (Code << 8) | bitDecoder.m_Stream.ReadByte();
      Range <<= 8;
      Low <<= 8;
    }
  }

  CRangeDecoder();
};

struct CFilter: public NVm::CProgram
{
  byte_array GlobalData;
  uint32 BlockStart;
  uint32 BlockSize;
  uint32 ExecCount;
  CFilter(): BlockStart(0), BlockSize(0), ExecCount(0) {}
};

struct CTempFilter: public NVm::CProgramInitState
{
  uint32 BlockStart;
  uint32 BlockSize;
  uint32 ExecCount;
  bool NextWindow;
  
  uint32 FilterIndex;
};

const int kNumHuffmanBits = 15;

class decoder:
  public ICompressCoder,
  public ICompressSetDecoderProperties2,
  public CMyUnknownImp
{
  CRangeDecoder m_InBitStream;
  Byte *_window;
  uint32 _winPos;
  uint32 _wrPtr;
  UInt64 _lzSize;
  UInt64 _unpackSize;
  UInt64 _writtenFileSize; // if it's > _unpackSize, then _unpackSize only written
  ::ex1::writer * _outStream;
  huffman::decoder<kNumHuffmanBits, kMainTableSize> m_MainDecoder;
  huffman::decoder<kNumHuffmanBits, kDistTableSize> m_DistDecoder;
  huffman::decoder<kNumHuffmanBits, kAlignTableSize> m_AlignDecoder;
  huffman::decoder<kNumHuffmanBits, kLenTableSize> m_LenDecoder;
  huffman::decoder<kNumHuffmanBits, kLevelTableSize> m_LevelDecoder;

  uint32 _reps[kNumReps];
  uint32 _lastLength;
  
  Byte m_LastLevels[kTablesSizesSum];

  Byte *_vmData;
  Byte *_vmCode;
  NVm::CVm _vm;
  base_array<CFilter *> _filters;
  base_array<CTempFilter *>  _tempFilters;
  uint32 _lastFilter;

  bool m_IsSolid;

  bool _lzMode;

  uint32 PrevAlignBits;
  uint32 PrevAlignCount;

  bool TablesRead;

  CPpmd7 _ppmd;
  int PpmEscChar;
  bool PpmError;
  
  HRESULT WriteDataToStream(const Byte *data, uint32 size);
  HRESULT WriteData(const Byte *data, uint32 size);
  HRESULT WriteArea(uint32 startPtr, uint32 endPtr);
  void ExecuteFilter(int tempFilterIndex, NVm::CBlockRef &outBlockRef);
  HRESULT WriteBuf();

  void InitFilters();
  bool AddVmCode(uint32 firstByte, uint32 codeSize);
  bool ReadVmCodeLZ();
  bool ReadVmCodePPM();
  
  uint32 ReadBits(int numBits);

  HRESULT InitPPM();
  int DecodePpmSymbol();
  HRESULT DecodePPM(Int32 num, bool &keepDecompressing);

  HRESULT ReadTables(bool &keepDecompressing);
  HRESULT ReadEndOfBlock(bool &keepDecompressing);
  HRESULT DecodeLZ(bool &keepDecompressing);
  HRESULT CodeReal(ICompressProgressInfo *progress);
public:
  decoder();
  ~decoder();

  MY_UNKNOWN_IMP1(ICompressSetDecoderProperties2)

  void ReleaseStreams()
  {
    _outStream.Release();
    m_InBitStream.bitDecoder.ReleaseStream();
  }

  STDMETHOD(Code)(ISequentialInStream *inStream, ISequentialOutStream *outStream,
      const UInt64 *inSize, const UInt64 *outSize, ICompressProgressInfo *progress);

  STDMETHOD(SetDecoderProperties2)(const Byte *data, uint32 size);

  void CopyBlock(uint32 distance, uint32 len)
  {
    _lzSize += len;
    uint32 pos = (_winPos - distance - 1) & kWindowMask;
    Byte *window = _window;
    uint32 winPos = _winPos;
    if (kWindowSize - winPos > len && kWindowSize - pos > len)
    {
      const Byte *src = window + pos;
      Byte *dest = window + winPos;
      _winPos += len;
      do
        *dest++ = *src++;
      while(--len != 0);
      return;
    }
    do
    {
      window[winPos] = window[pos];
      winPos = (winPos + 1) & kWindowMask;
      pos = (pos + 1) & kWindowMask;
    }
    while(--len != 0);
    _winPos = winPos;
  }
  
  void PutByte(Byte b)
  {
    _window[_winPos] = b;
    _winPos = (_winPos + 1) & kWindowMask;
    _lzSize++;
  }


};

}}

#endif
