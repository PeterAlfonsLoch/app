// Rar3Decoder.cpp
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives

/* This code uses Carryless rangecoder (1999): Dmitry Subbotin : Public domain */

#include "framework.h"

/*#include "../../../C/Alloc.h"

#include "../Common/StreamUtils.h"

#include "Rar3Decoder.h"*/

namespace libcompress
{

   namespace rar3
   {

      static void *SzBigAlloc(void *, size_t size) { return BigAlloc(size); }
      static void SzBigFree(void *, void *address) { BigFree(address); }
      static ::core::ISzAlloc g_BigAlloc = { SzBigAlloc, SzBigFree };

      static const uint32_t kNumAlignReps = 15;

      static const uint32_t kSymbolReadTable = 256;
      static const uint32_t kSymbolRep = 259;
//      static const uint32_t kSymbolLen2 = kSymbolRep + kNumReps;

      static const byte kLenStart[kLenTableSize]      = {0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,32,40,48,56,64,80,96,112,128,160,192,224};
      static const byte kLenDirectBits[kLenTableSize] = {0,0,0,0,0,0,0,0,1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4,  4,  5,  5,  5,  5};

      static const byte kDistDirectBits[kDistTableSize] =
      {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,
      16,16,16,16,16,16,16,16,16,16,16,16,16,16,
      18,18,18,18,18,18,18,18,18,18,18,18};

//      static const byte kLevelDirectBits[kLevelTableSize] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

      static const byte kLen2DistStarts[kNumLen2Symbols]={0,4,8,16,32,64,128,192};
      static const byte kLen2DistDirectBits[kNumLen2Symbols]={2,2,3, 4, 5, 6,  6,  6};

      static const uint32_t kDistLimit3 = 0x2000 - 2;
      static const uint32_t kDistLimit4 = 0x40000 - 2;

      static const uint32_t kNormalMatchMinLen = 3;

      static const uint32_t kVmDataSizeMax = 1 << 16;
      static const uint32_t kVmCodeSizeMax = 1 << 16;

      extern "C" {

         static uint32_t Range_GetThreshold(void *pp, uint32_t total)
         {
            CRangeDecoder *p = (CRangeDecoder *)pp;
            return p->Code / (p->range /= total);
         }

         static void Range_Decode(void *pp, uint32_t start, uint32_t size)
         {
            CRangeDecoder *p = (CRangeDecoder *)pp;
            start *= p->range;
            p->Low += start;
            p->Code -= start;
            p->range *= size;
            p->Normalize();
         }

         static uint32_t Range_DecodeBit(void *pp, uint32_t size0)
         {
            CRangeDecoder *p = (CRangeDecoder *)pp;
            if (p->Code / (p->range >>= 14) < size0)
            {
               Range_Decode(p, 0, size0);
               return 0;
            }
            else
            {
               Range_Decode(p, size0, (1 << 14) - size0);
               return 1;
            }
         }

      }

      CRangeDecoder::CRangeDecoder()
      {
         s.GetThreshold = Range_GetThreshold;
         s.Decode = Range_Decode;
         s.DecodeBit = Range_DecodeBit;
      }

      decoder::decoder():
      _window(0),
         _winPos(0),
         _wrPtr(0),
         _lzSize(0),
         _writtenFileSize(0),
         _vmData(0),
         _vmCode(0),
         m_IsSolid(false)
      {
         Ppmd7_Construct(&_ppmd);
      }

      decoder::~decoder()
      {
         InitFilters();
         ::MidFree(_vmData);
         ::MidFree(_window);
         Ppmd7_Free(&_ppmd, &g_BigAlloc);
      }

      HRESULT decoder::WriteDataToStream(const byte *data, uint32_t size)
      {
         return ::file::write(_outStream, data, size);
      }

      HRESULT decoder::WriteData(const byte *data, uint32_t size)
      {
         HRESULT res = S_OK;
         if (_writtenFileSize < _unpackSize)
         {
            uint32_t curSize = size;
            uint64_t remain = _unpackSize - _writtenFileSize;
            if (remain < curSize)
               curSize = (uint32_t)remain;
            res = WriteDataToStream(data, curSize);
         }
         _writtenFileSize += size;
         return res;
      }

      HRESULT decoder::WriteArea(uint32_t startPtr, uint32_t endPtr)
      {
         if (startPtr <= endPtr)
            return WriteData(_window + startPtr, endPtr - startPtr);
         RINOK(WriteData(_window + startPtr, kWindowSize - startPtr));
         return WriteData(_window, endPtr);
      }

      void decoder::ExecuteFilter(int32_t tempFilterIndex, vm::CBlockRef &outBlockRef)
      {
         temp_filter *tempFilter = _tempFilters[tempFilterIndex];
         tempFilter->InitR[6] = (uint32_t)_writtenFileSize;
         vm::SetValue32(&tempFilter->GlobalData[0x24], (uint32_t)_writtenFileSize);
         vm::SetValue32(&tempFilter->GlobalData[0x28], (uint32_t)(_writtenFileSize >> 32));
         filter *filter = _filters[tempFilter->FilterIndex];
         _vm.Execute(filter, tempFilter, outBlockRef, filter->GlobalData);
         delete tempFilter;
         _tempFilters[tempFilterIndex] = 0;
      }

      HRESULT decoder::WriteBuf()
      {
         uint32_t writtenBorder = _wrPtr;
         uint32_t writeSize = (_winPos - writtenBorder) & kWindowMask;
         for (int32_t i = 0; i < _tempFilters.get_size(); i++)
         {
            temp_filter *filter = _tempFilters[i];
            if (filter == NULL)
               continue;
            if (filter->NextWindow)
            {
               filter->NextWindow = false;
               continue;
            }
            uint32_t blockStart = filter->BlockStart;
            uint32_t blockSize = filter->BlockSize;
            if (((blockStart - writtenBorder) & kWindowMask) < writeSize)
            {
               if (writtenBorder != blockStart)
               {
                  RINOK(WriteArea(writtenBorder, blockStart));
                  writtenBorder = blockStart;
                  writeSize = (_winPos - writtenBorder) & kWindowMask;
               }
               if (blockSize <= writeSize)
               {
                  uint32_t blockEnd = (blockStart + blockSize) & kWindowMask;
                  if (blockStart < blockEnd || blockEnd == 0)
                     _vm.SetMemory(0, _window + blockStart, blockSize);
                  else
                  {
                     uint32_t tailSize = kWindowSize - blockStart;
                     _vm.SetMemory(0, _window + blockStart, tailSize);
                     _vm.SetMemory(tailSize, _window, blockEnd);
                  }
                  vm::CBlockRef outBlockRef;
                  ExecuteFilter(i, outBlockRef);
                  while (i + 1 < _tempFilters.get_size())
                  {
                     temp_filter *nextFilter = _tempFilters[i + 1];
                     if (nextFilter == NULL || nextFilter->BlockStart != blockStart ||
                        nextFilter->BlockSize != outBlockRef.Size || nextFilter->NextWindow)
                        break;
                     _vm.SetMemory(0, _vm.GetDataPointer(outBlockRef.offset), outBlockRef.Size);
                     ExecuteFilter(++i, outBlockRef);
                  }
                  WriteDataToStream(_vm.GetDataPointer(outBlockRef.offset), outBlockRef.Size);
                  _writtenFileSize += outBlockRef.Size;
                  writtenBorder = blockEnd;
                  writeSize = (_winPos - writtenBorder) & kWindowMask;
               }
               else
               {
                  for (int32_t j = i; j < _tempFilters.get_size(); j++)
                  {
                     temp_filter *filter = _tempFilters[j];
                     if (filter != NULL && filter->NextWindow)
                        filter->NextWindow = false;
                  }
                  _wrPtr = writtenBorder;
                  return S_OK; // check it
               }
            }
         }

         _wrPtr = _winPos;
         return WriteArea(writtenBorder, _winPos);
      }

      void decoder::InitFilters()
      {
         _lastFilter = 0;
         int32_t i;
         for (i = 0; i < _tempFilters.get_size(); i++)
            delete _tempFilters[i];
         _tempFilters.remove_all();
         for (i = 0; i < _filters.get_size(); i++)
            delete _filters[i];
         _filters.remove_all();
      }

      bool decoder::AddVmCode(uint32_t firstByte, uint32_t codeSize)
      {
         mem_bit_decoder inp;
         inp.Init(_vmData, codeSize);

         uint32_t filterIndex;
         if (firstByte & 0x80)
         {
            filterIndex = vm::ReadEncodedUInt32(inp);
            if (filterIndex == 0)
               InitFilters();
            else
               filterIndex--;
         }
         else
            filterIndex = _lastFilter;
         if (filterIndex > (uint32_t)_filters.get_size())
            return false;
         _lastFilter = filterIndex;
         bool newFilter = (filterIndex == (uint32_t)_filters.get_size());

         filter *filter;
         if (newFilter)
         {
            // check if too many filters
            if (filterIndex > 1024)
               return false;
            filter = new struct filter();
            _filters.add(filter);
         }
         else
         {
            filter = _filters[filterIndex];
            filter->ExecCount++;
         }

         int32_t numEmptyItems = 0;
         int32_t i;
         for (i = 0; i < _tempFilters.get_size(); i++)
         {
            _tempFilters[i - numEmptyItems] = _tempFilters[i];
            if (_tempFilters[i] == NULL)
               numEmptyItems++;
            if (numEmptyItems > 0)
               _tempFilters[i] = NULL;
         }
         if (numEmptyItems == 0)
         {
            _tempFilters.add(NULL);
            numEmptyItems = 1;
         }
         temp_filter *tempFilter = new temp_filter;
         _tempFilters[_tempFilters.get_size() - numEmptyItems] = tempFilter;
         tempFilter->FilterIndex = filterIndex;
         tempFilter->ExecCount = filter->ExecCount;

         uint32_t blockStart = vm::ReadEncodedUInt32(inp);
         if (firstByte & 0x40)
            blockStart += 258;
         tempFilter->BlockStart = (blockStart + _winPos) & kWindowMask;
         if (firstByte & 0x20)
            filter->BlockSize = vm::ReadEncodedUInt32(inp);
         tempFilter->BlockSize = filter->BlockSize;
         tempFilter->NextWindow = _wrPtr != _winPos && ((_wrPtr - _winPos) & kWindowMask) <= blockStart;

         memset(tempFilter->InitR, 0, sizeof(tempFilter->InitR));
         tempFilter->InitR[3] = vm::kGlobalOffset;
         tempFilter->InitR[4] = tempFilter->BlockSize;
         tempFilter->InitR[5] = tempFilter->ExecCount;
         if (firstByte & 0x10)
         {
            uint32_t initMask = inp.ReadBits(vm::kNumGpRegs);
            for (int32_t i = 0; i < vm::kNumGpRegs; i++)
               if (initMask & (1 << i))
                  tempFilter->InitR[i] = vm::ReadEncodedUInt32(inp);
         }
         if (newFilter)
         {
            uint32_t vmCodeSize = vm::ReadEncodedUInt32(inp);
            if (vmCodeSize >= kVmCodeSizeMax || vmCodeSize == 0)
               return false;
            for (uint32_t i = 0; i < vmCodeSize; i++)
               _vmCode[i] = (byte)inp.ReadBits(8);
            _vm.PrepareProgram(_vmCode, vmCodeSize, filter);
         }

         tempFilter->AllocateEmptyFixedGlobal();

         byte *globalData = &tempFilter->GlobalData[0];
         for (i = 0; i < vm::kNumGpRegs; i++)
            vm::SetValue32(&globalData[i * 4], tempFilter->InitR[i]);
         vm::SetValue32(&globalData[vm::NGlobalOffset::kBlockSize], tempFilter->BlockSize);
         vm::SetValue32(&globalData[vm::NGlobalOffset::kBlockPos], 0); // It was commented. why?
         vm::SetValue32(&globalData[vm::NGlobalOffset::kExecCount], tempFilter->ExecCount);

         if (firstByte & 8)
         {
            uint32_t dataSize = vm::ReadEncodedUInt32(inp);
            if (dataSize > vm::kGlobalSize - vm::kFixedGlobalSize)
               return false;
            byte_array &globalData = tempFilter->GlobalData;
            int32_t requredSize = (int32_t)(dataSize + vm::kFixedGlobalSize);
            if (globalData.get_size() < requredSize)
            {
               globalData.allocate(globalData.get_size(), requredSize);
               for (; globalData.get_size() < requredSize; i++)
                  globalData.add(0);
            }
            for (uint32_t i = 0; i < dataSize; i++)
               globalData[vm::kFixedGlobalSize + i] = (byte)inp.ReadBits(8);
         }
         return true;
      }

      bool decoder::ReadVmCodeLZ()
      {
         uint32_t firstByte = ReadBits(8);
         uint32_t length = (firstByte & 7) + 1;
         if (length == 7)
            length = ReadBits(8) + 7;
         else if (length == 8)
            length = ReadBits(16);
         if (length > kVmDataSizeMax)
            return false;
         for (uint32_t i = 0; i < length; i++)
            _vmData[i] = (byte)ReadBits(8);
         return AddVmCode(firstByte, length);
      }

      bool decoder::ReadVmCodePPM()
      {
         int32_t firstByte = DecodePpmSymbol();
         if (firstByte < 0)
            return false;
         uint32_t length = (firstByte & 7) + 1;
         if (length == 7)
         {
            int32_t b1 = DecodePpmSymbol();
            if (b1 < 0)
               return false;
            length = b1 + 7;
         }
         else if (length == 8)
         {
            int32_t b1 = DecodePpmSymbol();
            if (b1 < 0)
               return false;
            int32_t b2 = DecodePpmSymbol();
            if (b2 < 0)
               return false;
            length = b1 * 256 + b2;
         }
         if (length > kVmDataSizeMax)
            return false;
         for (uint32_t i = 0; i < length; i++)
         {
            int32_t b = DecodePpmSymbol();
            if (b < 0)
               return false;
            _vmData[i] = (byte)b;
         }
         return AddVmCode(firstByte, length);
      }

#define RIF(x) { if (!(x)) return S_FALSE; }

      uint32_t decoder::ReadBits(int32_t numBits) { return m_InBitStream.bitDecoder.ReadBits(numBits); }

      /////////////////////////////////////////////////
      // PPM

      HRESULT decoder::InitPPM()
      {
         byte maxOrder = (byte)ReadBits(7);

         bool reset = ((maxOrder & 0x20) != 0);
         int32_t maxMB = 0;
         if (reset)
            maxMB = (byte)ReadBits(8);
         else
         {
            if (PpmError || !Ppmd7_WasAllocated(&_ppmd))
               return S_FALSE;
         }
         if (maxOrder & 0x40)
            PpmEscChar = (byte)ReadBits(8);
         m_InBitStream.InitRangeCoder();
         /*
         if (m_InBitStream.m_BitPos != 0)
         return S_FALSE;
         */
         if (reset)
         {
            PpmError = true;
            maxOrder = (maxOrder & 0x1F) + 1;
            if (maxOrder > 16)
               maxOrder = 16 + (maxOrder - 16) * 3;
            if (maxOrder == 1)
            {
               Ppmd7_Free(&_ppmd, &g_BigAlloc);
               return S_FALSE;
            }
            if (!Ppmd7_Alloc(&_ppmd, (maxMB + 1) << 20, &g_BigAlloc))
               return E_OUTOFMEMORY;
            Ppmd7_Init(&_ppmd, maxOrder);
            PpmError = false;
         }
         return S_OK;
      }

      int32_t decoder::DecodePpmSymbol() { return Ppmd7_DecodeSymbol(&_ppmd, &m_InBitStream.s); }

      HRESULT decoder::DecodePPM(int32_t num, bool &keepDecompressing)
      {
         keepDecompressing = false;
         if (PpmError)
            return S_FALSE;
         do
         {
            if (((_wrPtr - _winPos) & kWindowMask) < 260 && _wrPtr != _winPos)
            {
               RINOK(WriteBuf());
               if (_writtenFileSize > _unpackSize)
               {
                  keepDecompressing = false;
                  return S_OK;
               }
            }
            int32_t ca = DecodePpmSymbol();
            if (ca < 0)
            {
               PpmError = true;
               return S_FALSE;
            }
            if (ca == PpmEscChar)
            {
               int32_t nextCh = DecodePpmSymbol();
               if (nextCh < 0)
               {
                  PpmError = true;
                  return S_FALSE;
               }
               if (nextCh == 0)
                  return ReadTables(keepDecompressing);
               if (nextCh == 2 || nextCh == -1)
                  return S_OK;
               if (nextCh == 3)
               {
                  if (!ReadVmCodePPM())
                  {
                     PpmError = true;
                     return S_FALSE;
                  }
                  continue;
               }
               if (nextCh == 4 || nextCh == 5)
               {
                  uint32_t distance = 0;
                  uint32_t length = 4;
                  if (nextCh == 4)
                  {
                     for (int32_t i = 0; i < 3; i++)
                     {
                        int32_t ca = DecodePpmSymbol();
                        if (ca < 0)
                        {
                           PpmError = true;
                           return S_FALSE;
                        }
                        distance = (distance << 8) + (byte)ca;
                     }
                     distance++;
                     length += 28;
                  }
                  int32_t ca = DecodePpmSymbol();
                  if (ca < 0)
                  {
                     PpmError = true;
                     return S_FALSE;
                  }
                  length += ca;
                  if (distance >= _lzSize)
                     return S_FALSE;
                  CopyBlock(distance, length);
                  num -= (int32_t)length;
                  continue;
               }
            }
            PutByte((byte)ca);
            num--;
         }
         while (num >= 0);
         keepDecompressing = true;
         return S_OK;
      }

      /////////////////////////////////////////////////
      // LZ

      HRESULT decoder::ReadTables(bool &keepDecompressing)
      {
         keepDecompressing = true;
         ReadBits((8 - m_InBitStream.bitDecoder.GetBitPosition()) & 7);
         if (ReadBits(1) != 0)
         {
            _lzMode = false;
            return InitPPM();
         }

         _lzMode = true;
         PrevAlignBits = 0;
         PrevAlignCount = 0;

         byte levelLevels[kLevelTableSize];
         byte newLevels[kTablesSizesSum];

         if (ReadBits(1) == 0)
            memset(m_LastLevels, 0, kTablesSizesSum);

         int32_t i;
         for (i = 0; i < kLevelTableSize; i++)
         {
            uint32_t length = ReadBits(4);
            if (length == 15)
            {
               uint32_t zeroCount = ReadBits(4);
               if (zeroCount != 0)
               {
                  zeroCount += 2;
                  while (zeroCount-- > 0 && i < kLevelTableSize)
                     levelLevels[i++]=0;
                  i--;
                  continue;
               }
            }
            levelLevels[i] = (byte)length;
         }
         RIF(m_LevelDecoder.SetCodeLengths(levelLevels));
         i = 0;
         while (i < kTablesSizesSum)
         {
            uint32_t number = m_LevelDecoder.DecodeSymbol(&m_InBitStream.bitDecoder);
            if (number < 16)
            {
               newLevels[i] = byte((number + m_LastLevels[i]) & 15);
               i++;
            }
            else if (number > kLevelTableSize)
               return S_FALSE;
            else
            {
               int32_t num;
               if (((number - 16) & 1) == 0)
                  num = ReadBits(3) + 3;
               else
                  num = ReadBits(7) + 11;
               if (number < 18)
               {
                  if (i == 0)
                     return S_FALSE;
                  for (; num > 0 && i < kTablesSizesSum; num--, i++)
                     newLevels[i] = newLevels[i - 1];
               }
               else
               {
                  for (; num > 0 && i < kTablesSizesSum; num--)
                     newLevels[i++] = 0;
               }
            }
         }
         TablesRead = true;

         // original code has check here:
         /*
         if (InAddr > ReadTop)
         {
         keepDecompressing = false;
         return true;
         }
         */

         RIF(m_MainDecoder.SetCodeLengths(&newLevels[0]));
         RIF(m_DistDecoder.SetCodeLengths(&newLevels[kMainTableSize]));
         RIF(m_AlignDecoder.SetCodeLengths(&newLevels[kMainTableSize + kDistTableSize]));
         RIF(m_LenDecoder.SetCodeLengths(&newLevels[kMainTableSize + kDistTableSize + kAlignTableSize]));

         memcpy(m_LastLevels, newLevels, kTablesSizesSum);
         return S_OK;
      }

      class CCoderReleaser
      {
         decoder *m_Coder;
      public:
         CCoderReleaser(decoder *coder): m_Coder(coder) {}
         ~CCoderReleaser()
         {
            m_Coder->ReleaseStreams();
         }
      };

      HRESULT decoder::ReadEndOfBlock(bool &keepDecompressing)
      {
         if (ReadBits(1) != 0)
         {
            // old file
            TablesRead = false;
            return ReadTables(keepDecompressing);
         }
         // new file
         keepDecompressing = false;
         TablesRead = (ReadBits(1) == 0);
         return S_OK;
      }

      uint32_t kDistStart[kDistTableSize];

      class CDistInit
      {
      public:
         CDistInit() { Init(); }
         void Init()
         {
            uint32_t start = 0;
            for (uint32_t i = 0; i < kDistTableSize; i++)
            {
               kDistStart[i] = start;
               start += (1 << kDistDirectBits[i]);
            }
         }
      } g_DistInit;

      HRESULT decoder::DecodeLZ(bool &keepDecompressing)
      {
         uint32_t rep0 = _reps[0];
         uint32_t rep1 = _reps[1];
         uint32_t rep2 = _reps[2];
         uint32_t rep3 = _reps[3];
         uint32_t length = _lastLength;
         for (;;)
         {
            if (((_wrPtr - _winPos) & kWindowMask) < 260 && _wrPtr != _winPos)
            {
               RINOK(WriteBuf());
               if (_writtenFileSize > _unpackSize)
               {
                  keepDecompressing = false;
                  return S_OK;
               }
            }
            uint32_t number = m_MainDecoder.DecodeSymbol(&m_InBitStream.bitDecoder);
            if (number < 256)
            {
               PutByte((byte)number);
               continue;
            }
            else if (number == kSymbolReadTable)
            {
               RINOK(ReadEndOfBlock(keepDecompressing));
               break;
            }
            else if (number == 257)
            {
               if (!ReadVmCodeLZ())
                  return S_FALSE;
               continue;
            }
            else if (number == 258)
            {
               if (length == 0)
                  return S_FALSE;
            }
            else if (number < kSymbolRep + 4)
            {
               if (number != kSymbolRep)
               {
                  uint32_t distance;
                  if (number == kSymbolRep + 1)
                     distance = rep1;
                  else
                  {
                     if (number == kSymbolRep + 2)
                        distance = rep2;
                     else
                     {
                        distance = rep3;
                        rep3 = rep2;
                     }
                     rep2 = rep1;
                  }
                  rep1 = rep0;
                  rep0 = distance;
               }

               uint32_t number = m_LenDecoder.DecodeSymbol(&m_InBitStream.bitDecoder);
               if (number >= kLenTableSize)
                  return S_FALSE;
               length = 2 + kLenStart[number] + m_InBitStream.bitDecoder.ReadBits(kLenDirectBits[number]);
            }
            else
            {
               rep3 = rep2;
               rep2 = rep1;
               rep1 = rep0;
               if (number < 271)
               {
                  number -= 263;
                  rep0 = kLen2DistStarts[number] + m_InBitStream.bitDecoder.ReadBits(kLen2DistDirectBits[number]);
                  length = 2;
               }
               else if (number < 299)
               {
                  number -= 271;
                  length = kNormalMatchMinLen + (uint32_t)kLenStart[number] + m_InBitStream.bitDecoder.ReadBits(kLenDirectBits[number]);
                  uint32_t number = m_DistDecoder.DecodeSymbol(&m_InBitStream.bitDecoder);
                  if (number >= kDistTableSize)
                     return S_FALSE;
                  rep0 = kDistStart[number];
                  int32_t numBits = kDistDirectBits[number];
                  if (number >= (kNumAlignBits * 2) + 2)
                  {
                     if (numBits > kNumAlignBits)
                        rep0 += (m_InBitStream.bitDecoder.ReadBits(numBits - kNumAlignBits) << kNumAlignBits);
                     if (PrevAlignCount > 0)
                     {
                        PrevAlignCount--;
                        rep0 += PrevAlignBits;
                     }
                     else
                     {
                        uint32_t number = m_AlignDecoder.DecodeSymbol(&m_InBitStream.bitDecoder);
                        if (number < (1 << kNumAlignBits))
                        {
                           rep0 += number;
                           PrevAlignBits = number;
                        }
                        else if (number  == (1 << kNumAlignBits))
                        {
                           PrevAlignCount = kNumAlignReps;
                           rep0 += PrevAlignBits;
                        }
                        else
                           return S_FALSE;
                     }
                  }
                  else
                     rep0 += m_InBitStream.bitDecoder.ReadBits(numBits);
                  length += ((kDistLimit4 - rep0) >> 31) + ((kDistLimit3 - rep0) >> 31);
               }
               else
                  return S_FALSE;
            }
            if (rep0 >= _lzSize)
               return S_FALSE;
            CopyBlock(rep0, length);
         }
         _reps[0] = rep0;
         _reps[1] = rep1;
         _reps[2] = rep2;
         _reps[3] = rep3;
         _lastLength = length;

         return S_OK;
      }

      HRESULT decoder::CodeReal(::libcompress::progress_info_interface *progress)
      {
         _writtenFileSize = 0;
         if (!m_IsSolid)
         {
            _lzSize = 0;
            _winPos = 0;
            _wrPtr = 0;
            for (int32_t i = 0; i < kNumReps; i++)
               _reps[i] = 0;
            _lastLength = 0;
            memset(m_LastLevels, 0, kTablesSizesSum);
            TablesRead = false;
            PpmEscChar = 2;
            PpmError = true;
            InitFilters();
         }
         if (!m_IsSolid || !TablesRead)
         {
            bool keepDecompressing;
            RINOK(ReadTables(keepDecompressing));
            if (!keepDecompressing)
               return S_OK;
         }

         for (;;)
         {
            bool keepDecompressing;
            if (_lzMode)
            {
               RINOK(DecodeLZ(keepDecompressing))
            }
            else
            {
               RINOK(DecodePPM(1 << 18, keepDecompressing))
            }
            uint64_t packSize = m_InBitStream.bitDecoder.GetProcessedSize();
            RINOK(progress->SetRatioInfo(&packSize, &_writtenFileSize));
            if (!keepDecompressing)
               break;
         }
         RINOK(WriteBuf());
         uint64_t packSize = m_InBitStream.bitDecoder.GetProcessedSize();
         RINOK(progress->SetRatioInfo(&packSize, &_writtenFileSize));
         if (_writtenFileSize < _unpackSize)
            return S_FALSE;
         return S_OK;
      }

      HRes decoder::Code(::file::reader *inStream, ::file::writer *outStream,
         const file_size *inSize, const file_size *outSize, ::libcompress::progress_info_interface *progress)
      {
         try
         {
            if (inSize == NULL || outSize == NULL)
               return E_INVALIDARG;

            if (_vmData == 0)
            {
               _vmData = (byte *)::MidAlloc(kVmDataSizeMax + kVmCodeSizeMax);
               if (_vmData == 0)
                  return E_OUTOFMEMORY;
               _vmCode = _vmData + kVmDataSizeMax;
            }

            if (_window == 0)
            {
               _window = (byte *)::MidAlloc(kWindowSize);
               if (_window == 0)
                  return E_OUTOFMEMORY;
            }
            if (!m_InBitStream.bitDecoder.Create(1 << 20))
               return E_OUTOFMEMORY;
            if (!_vm.Create())
               return E_OUTOFMEMORY;


            m_InBitStream.bitDecoder.SetStream(inStream);
            m_InBitStream.bitDecoder.Init();
            _outStream = outStream;

            CCoderReleaser coderReleaser(this);
            _unpackSize = *outSize;
            return CodeReal(progress);
         }
         catch(const ::file::in_buffer_exception &e)  { return e.ErrorCode; }
         catch(...) { return S_FALSE; }
         // CNewException is possible here. But probably CNewException is caused
         // by error in data stream.
      }

      HRes decoder::SetDecoderProperties2(const byte *data, uint32_t size)
      {
         if (size < 1)
            return E_INVALIDARG;
         m_IsSolid = (data[0] != 0);
         return S_OK;
      }

   } // namespace rar3

} // namespace libcompress
