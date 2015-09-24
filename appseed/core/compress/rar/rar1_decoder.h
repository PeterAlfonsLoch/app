// Rar1Decoder.h
// According to unRAR license, this code may not be used to develop
// a program that creates RAR archives
// from 7-zip on 2012-12-22
#pragma once

/*#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "../Common/InBuffer.h"

#include "BitmDecoder.h"
#include "HuffmanDecoder.h"
#include "LzOutWindow.h"*/

namespace libcompress
{
   namespace rar1
   {

      const uint32_t kNumRepDists = 4;


      class decoder :
         public ::libcompress::coder_interface,
         public ::libcompress::set_decoder_properties2_interface
      {
      public:
         ::libcompress::lz_out_window        m_OutWindowStream;
         ::file::bitm::in_buffer_decoder   m_InBitStream;

         uint32_t m_RepDists[kNumRepDists];
         uint32_t m_RepDistPtr;

         uint32_t LastDist;
         uint32_t LastLength;

         int64_t m_UnpackSize;
         bool m_IsSolid;

         uint32_t ReadBits(int32_t numBits);
         HRESULT CopyBlock(uint32_t distance, uint32_t len);

         uint32_t DecodeNum(const uint32_t *posTab);
         HRESULT ShortLZ();
         HRESULT LongLZ();
         HRESULT HuffDecode();
         void GetFlagsBuf();
         void InitData();
         void InitHuff();
         void CorrHuff(uint32_t *CharSet, uint32_t *NumToPlace);
         void OldUnpWriteBuf();

         uint32_t ChSet[256],ChSetA[256],ChSetB[256],ChSetC[256];
         uint32_t Place[256],PlaceA[256],PlaceB[256],PlaceC[256];
         uint32_t NToPl[256],NToPlB[256],NToPlC[256];
         uint32_t FlagBuf,AvrPlc,AvrPlcB,AvrLn1,AvrLn2,AvrLn3;
         int32_t Buf60,NumHuf,StMode,LCount,FlagsCnt;
         uint32_t Nhfb,Nlzb,MaxDist3;

         void InitStructures();

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

   } // namespace rar1

} // namespace libcompress

