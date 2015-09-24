// Rar2Decoder.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives
// from 7-zip on 2012-12-23, dawn
#pragma once


/*#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "../Common/InBuffer.h"

#include "BitmDecoder.h"
#include "HuffmanDecoder.h"
#include "LzOutWindow.h"*/

namespace libcompress
{

   namespace rar2
   {

      const uint32_t kNumRepDists = 4;
      const uint32_t kDistTableSize = 48;

      const int32_t kMMTableSize = 256 + 1;

      const uint32_t kMainTableSize = 298;
      const uint32_t kLenTableSize = 28;

      const uint32_t kDistTableStart = kMainTableSize;
      const uint32_t kLenTableStart = kDistTableStart + kDistTableSize;

      const uint32_t kHeapTablesSizesSum = kMainTableSize + kDistTableSize + kLenTableSize;

      const uint32_t kLevelTableSize = 19;

      const uint32_t kMMTablesSizesSum = kMMTableSize * 4;

      const uint32_t kMaxTableSize = kMMTablesSizesSum;

      const uint32_t kTableDirectLevels = 16;
      const uint32_t kTableLevelRepNumber = kTableDirectLevels;
      const uint32_t kTableLevel0Number = kTableLevelRepNumber + 1;
      const uint32_t kTableLevel0Number2 = kTableLevel0Number + 1;

      const uint32_t kLevelMask = 0xF;


      const uint32_t kRepBothNumber = 256;
      const uint32_t kRepNumber = kRepBothNumber + 1;
      const uint32_t kLen2Number = kRepNumber + 4;

      const uint32_t kLen2NumNumbers = 8;
      const uint32_t kReadTableNumber = kLen2Number + kLen2NumNumbers;
      const uint32_t kMatchNumber = kReadTableNumber + 1;

      const byte kLenStart[kLenTableSize]      = {0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,32,40,48,56,64,80,96,112,128,160,192,224};
      const byte kLenDirectBits[kLenTableSize] = {0,0,0,0,0,0,0,0,1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4,  4,  5,  5,  5,  5};

      const uint32_t kDistStart[kDistTableSize]     = {0,1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024,1536,2048,3072,4096,6144,8192,12288,16384,24576,32768U,49152U,65536,98304,131072,196608,262144,327680,393216,458752,524288,589824,655360,720896,786432,851968,917504,983040};
      const byte kDistDirectBits[kDistTableSize] = {0,0,0,0,1,1,2, 2, 3, 3, 4, 4, 5, 5,  6,  6,  7,  7,  8,  8,   9,   9,  10,  10,  11,  11,  12,   12,   13,   13,    14,    14,   15,   15,    16,    16,    16,    16,    16,    16,    16,    16,    16,    16,    16,    16,    16,    16};

      const byte kLevelDirectBits[kLevelTableSize] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 7};

      const byte kLen2DistStarts[kLen2NumNumbers]={0,4,8,16,32,64,128,192};
      const byte kLen2DistDirectBits[kLen2NumNumbers]={2,2,3, 4, 5, 6,  6,  6};

      const uint32_t kDistLimit2 = 0x101 - 1;
      const uint32_t kDistLimit3 = 0x2000 - 1;
      const uint32_t kDistLimit4 = 0x40000 - 1;

      const uint32_t kMatchMaxLen = 255 + 2;
      const uint32_t kMatchMaxLenMax = 255 + 5;
      const uint32_t kNormalMatchMinLen = 3;

      namespace multimedia
      {

         struct filter
         {
            int32_t K1,K2,K3,K4,K5;
            int32_t D1,D2,D3,D4;
            int32_t LastDelta;
            uint32_t Dif[11];
            uint32_t ByteCount;
            int32_t LastChar;

            byte Decode(int32_t &channelDelta, byte delta);

            void Init() { memset(this, 0, sizeof(*this)); }

         };

         const int32_t kNumChanelsMax = 4;

         class filter2
         {
         public:
            filter  m_Filters[kNumChanelsMax];
            int32_t m_ChannelDelta;
            int32_t CurrentChannel;

            void Init() { memset(this, 0, sizeof(*this)); }
            byte Decode(byte delta)
            {
               return m_Filters[CurrentChannel].Decode(m_ChannelDelta, delta);
            }

         };

      }


      const int32_t kNumHuffmanBits = 15;

      class decoder :
         public ::libcompress::coder_interface,
         public ::libcompress::set_decoder_properties2_interface
      {
         ::libcompress::lz_out_window m_OutWindowStream;
         ::file::bitm::in_buffer_decoder m_InBitStream;
         huffman::decoder<kNumHuffmanBits, kMainTableSize> m_MainDecoder;
         huffman::decoder<kNumHuffmanBits, kDistTableSize> m_DistDecoder;
         huffman::decoder<kNumHuffmanBits, kLenTableSize> m_LenDecoder;
         huffman::decoder<kNumHuffmanBits, kMMTableSize> m_MMDecoders[multimedia::kNumChanelsMax];
         huffman::decoder<kNumHuffmanBits, kLevelTableSize> m_LevelDecoder;

         bool m_AudioMode;

         multimedia::filter2 m_MmFilter;
         int32_t m_NumChannels;

         uint32_t m_RepDists[kNumRepDists];
         uint32_t m_RepDistPtr;

         uint32_t m_LastLength;

         byte m_LastLevels[kMaxTableSize];

         uint64_t m_PackSize;
         bool m_IsSolid;

         void InitStructures();
         uint32_t ReadBits(int32_t numBits);
         bool ReadTables();
         bool ReadLastTables();

         bool DecodeMm(uint32_t pos);
         bool DecodeLz(int32_t pos);

         HRESULT CodeReal(::file::reader *inStream, ::file::writer *outStream, const file_size_t *inSize, const file_size_t *outSize, ::libcompress::progress_info_interface *progress);

      public:
         decoder();

         //MY_UNKNOWN_IMP1(ICompressSetDecoderProperties2)

            void ReleaseStreams()
         {
            m_OutWindowStream.ReleaseStream();
            m_InBitStream.ReleaseStream();
         }

         virtual HRes Code(::file::reader *inStream, ::file::writer *outStream, const file_size_t *inSize, const file_size_t *outSize, ::libcompress::progress_info_interface *progress);

         virtual HRes SetDecoderProperties2(const byte *data, uint32_t size);

      };

   } // namespace rar2

} // namespace libcompress


