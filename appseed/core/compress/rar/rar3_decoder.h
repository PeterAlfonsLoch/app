// Rar3Decoder.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives

/* This code uses Carryless rangecoder (1999): Dmitry Subbotin : Public domain */
// from 7-zip on 2012-12-23, dawn
#pragma once

/*#include "../../../C/Ppmd7.h"

#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "../Common/InBuffer.h"

#include "BitmDecoder.h"
#include "HuffmanDecoder.h"
#include "Rar3Vm.h"*/

#include "rar3_vm.h"

namespace libcompress
{

   namespace rar3
   {

      const uint32_t kWindowSize = 1 << 22;
      const uint32_t kWindowMask = (kWindowSize - 1);

      const uint32_t kNumReps = 4;
      const uint32_t kNumLen2Symbols = 8;
      const uint32_t kLenTableSize = 28;
      const uint32_t kMainTableSize = 256 + 1 + 1 + 1 + kNumReps + kNumLen2Symbols + kLenTableSize;
      const uint32_t kDistTableSize = 60;

      const int32_t kNumAlignBits = 4;
      const uint32_t kAlignTableSize = (1 << kNumAlignBits) + 1;

      const uint32_t kLevelTableSize = 20;

      const uint32_t kTablesSizesSum = kMainTableSize + kDistTableSize + kAlignTableSize + kLenTableSize;

      class bit_decoder
      {
         uint32_t m_Value;
         uint32_t m_BitPos;
      public:
         ::file::in_buffer m_Stream;
         bool Create(uint32_t bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(::file::reader *inStream) { m_Stream.SetStream(inStream);}
         void ReleaseStream()
         {
            m_Stream.ReleaseStream();
         }

         void Init()
         {
            m_Stream.Init();
            m_BitPos = 0;
            m_Value = 0;
         }

         uint64_t GetProcessedSize() const { return m_Stream.GetProcessedSize() - (m_BitPos) / 8; }
         uint32_t GetBitPosition() const { return ((8 - m_BitPos) & 7); }

         uint32_t GetValue(uint32_t numBits)
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

         void MovePos(uint32_t numBits)
         {
            m_BitPos -= numBits;
            m_Value = m_Value & ((1 << m_BitPos) - 1);
         }

         uint32_t ReadBits(uint32_t numBits)
         {
            uint32_t res = GetValue(numBits);
            MovePos(numBits);
            return res;
         }
      };

      const uint32_t kTopValue = (1 << 24);
      const uint32_t kBot = (1 << 15);

      struct CRangeDecoder
      {
         IPpmd7_RangeDec s;
         uint32_t range;
         uint32_t Code;
         uint32_t Low;
         bit_decoder bitDecoder;
         ::core::SRes Res;

      public:
         void InitRangeCoder()
         {
            Code = 0;
            Low = 0;
            range = 0xFFFFFFFF;
            for (int32_t i = 0; i < 4; i++)
               Code = (Code << 8) | bitDecoder.ReadBits(8);
         }

         void Normalize()
         {
            while ((Low ^ (Low + range)) < kTopValue ||
               range < kBot && ((range = (0 - Low) & (kBot - 1)), 1))
            {
               Code = (Code << 8) | bitDecoder.m_Stream.ReadByte();
               range <<= 8;
               Low <<= 8;
            }
         }

         CRangeDecoder();
      };

      struct filter :
         public vm::CProgram
      {
         byte_array GlobalData;
         uint32_t BlockStart;
         uint32_t BlockSize;
         uint32_t ExecCount;
         filter(): BlockStart(0), BlockSize(0), ExecCount(0) {}
      };

      struct temp_filter: public vm::CProgramInitState
      {
         uint32_t BlockStart;
         uint32_t BlockSize;
         uint32_t ExecCount;
         bool NextWindow;

         uint32_t FilterIndex;
      };

      const int32_t kNumHuffmanBits = 15;

      class decoder:
         public ::libcompress::coder_interface,
         public ::libcompress::set_decoder_properties2_interface
      {
         CRangeDecoder m_InBitStream;
         byte *_window;
         uint32_t _winPos;
         uint32_t _wrPtr;
         uint64_t _lzSize;
         uint64_t _unpackSize;
         uint64_t _writtenFileSize; // if it's > _unpackSize, then _unpackSize only written
         ::file::writer * _outStream;
         huffman::decoder<kNumHuffmanBits, kMainTableSize> m_MainDecoder;
         huffman::decoder<kNumHuffmanBits, kDistTableSize> m_DistDecoder;
         huffman::decoder<kNumHuffmanBits, kAlignTableSize> m_AlignDecoder;
         huffman::decoder<kNumHuffmanBits, kLenTableSize> m_LenDecoder;
         huffman::decoder<kNumHuffmanBits, kLevelTableSize> m_LevelDecoder;

         uint32_t _reps[kNumReps];
         uint32_t _lastLength;

         byte m_LastLevels[kTablesSizesSum];

         byte *_vmData;
         byte *_vmCode;
         vm::vm _vm;
         array<filter *> _filters;
         array<temp_filter *>  _tempFilters;
         uint32_t _lastFilter;

         bool m_IsSolid;

         bool _lzMode;

         uint32_t PrevAlignBits;
         uint32_t PrevAlignCount;

         bool TablesRead;

         CPpmd7 _ppmd;
         int32_t PpmEscChar;
         bool PpmError;

         HRESULT WriteDataToStream(const byte *data, uint32_t size);
         HRESULT WriteData(const byte *data, uint32_t size);
         HRESULT WriteArea(uint32_t startPtr, uint32_t endPtr);
         void ExecuteFilter(int32_t tempFilterIndex, vm::CBlockRef &outBlockRef);
         HRESULT WriteBuf();

         void InitFilters();
         bool AddVmCode(uint32_t firstByte, uint32_t codeSize);
         bool ReadVmCodeLZ();
         bool ReadVmCodePPM();

         uint32_t ReadBits(int32_t numBits);

         HRESULT InitPPM();
         int32_t DecodePpmSymbol();
         HRESULT DecodePPM(int32_t num, bool &keepDecompressing);

         HRESULT ReadTables(bool &keepDecompressing);
         HRESULT ReadEndOfBlock(bool &keepDecompressing);
         HRESULT DecodeLZ(bool &keepDecompressing);
         HRESULT CodeReal(::libcompress::progress_info_interface *progress);
      public:
         decoder();
         ~decoder();

         //MY_UNKNOWN_IMP1(ICompressSetDecoderProperties2)

            void ReleaseStreams()
         {
            //_outStream.Release();
            m_InBitStream.bitDecoder.ReleaseStream();
         }

         virtual HRes Code(::file::reader *inStream, ::file::writer *outStream,
            const file_size_t *inSize, const file_size_t *outSize, ::libcompress::progress_info_interface *progress);

         virtual HRes SetDecoderProperties2(const byte *data, uint32_t size);

         void CopyBlock(uint32_t distance, uint32_t len)
         {
            _lzSize += len;
            uint32_t pos = (_winPos - distance - 1) & kWindowMask;
            byte *window = _window;
            uint32_t winPos = _winPos;
            if (kWindowSize - winPos > len && kWindowSize - pos > len)
            {
               const byte *src = window + pos;
               byte *dest = window + winPos;
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

         void PutByte(byte b)
         {
            _window[_winPos] = b;
            _winPos = (_winPos + 1) & kWindowMask;
            _lzSize++;
         }


      };

   } // namespace rar3

} // namespace libcompress
