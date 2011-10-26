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

namespace compress
{
   namespace rar1
   {

      const uint32 kNumRepDists = 4;


      class decoder :
         public ::compress::coder_interface,
         public ::compress::set_decoder_properties2_interface
      {
      public:
         ::compress::lz_out_window        m_OutWindowStream;
         ::ex1::bitm::in_buffer_decoder   m_InBitStream;

         uint32 m_RepDists[kNumRepDists];
         uint32 m_RepDistPtr;

         uint32 LastDist;
         uint32 LastLength;

         int64 m_UnpackSize;
         bool m_IsSolid;

         uint32 ReadBits(int numBits);
         HRESULT CopyBlock(uint32 distance, uint32 len);

         uint32 DecodeNum(const uint32 *posTab);
         HRESULT ShortLZ();
         HRESULT LongLZ();
         HRESULT HuffDecode();
         void GetFlagsBuf();
         void InitData();
         void InitHuff();
         void CorrHuff(uint32 *CharSet, uint32 *NumToPlace);
         void OldUnpWriteBuf();

         uint32 ChSet[256],ChSetA[256],ChSetB[256],ChSetC[256];
         uint32 Place[256],PlaceA[256],PlaceB[256],PlaceC[256];
         uint32 NToPl[256],NToPlB[256],NToPlC[256];
         uint32 FlagBuf,AvrPlc,AvrPlcB,AvrLn1,AvrLn2,AvrLn3;
         int Buf60,NumHuf,StMode,LCount,FlagsCnt;
         uint32 Nhfb,Nlzb,MaxDist3;

         void InitStructures();

         HRESULT CodeReal(::ex1::reader *inStream, ::ex1::writer *outStream, const file_size *inSize, const file_size *outSize, ::compress::progress_info_interface *progress);

      public:
         decoder();

         //MY_UNKNOWN_IMP1(ICompressSetDecoderProperties2)

            void ReleaseStreams()
         {
            m_OutWindowStream.ReleaseStream();
            m_InBitStream.ReleaseStream();
         }

         virtual ex1::HRes Code(::ex1::reader *inStream, ::ex1::writer *outStream, const file_size *inSize, const file_size *outSize, ::compress::progress_info_interface *progress);

         virtual ex1::HRes SetDecoderProperties2(const byte *data, uint32 size);

      };

   } // namespace rar1

} // namespace compress

