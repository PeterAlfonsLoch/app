// BitmDecoder.h -- the Most Significant Bit of byte is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../IStream.h"

namespace ex1
{

   namespace bitm
   {

      const unsigned kNumBigValueBits = 8 * 4;
      const unsigned kNumValueBytes = 3;
      const unsigned kNumValueBits = 8  * kNumValueBytes;

      const uint32 kMask = (1 << kNumValueBits) - 1;

      template<class TInByte>
      class decoder
      {
         unsigned m_BitPos;
         uint32 m_Value;
      public:
         TInByte m_Stream;
         bool Create(uint32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(reader *inStream) { m_Stream.SetStream(inStream);}
         void ReleaseStream() { m_Stream.ReleaseStream();}

         void Init()
         {
            m_Stream.Init();
            m_BitPos = kNumBigValueBits;
            Normalize();
         }

         uint64 GetProcessedSize() const { return m_Stream.GetProcessedSize() - (kNumBigValueBits - m_BitPos) / 8; }

         void Normalize()
         {
            for (;m_BitPos >= 8; m_BitPos -= 8)
               m_Value = (m_Value << 8) | m_Stream.ReadByte();
         }

         uint32 GetValue(unsigned numBits) const
         {
            // return (m_Value << m_BitPos) >> (kNumBigValueBits - numBits);
            return ((m_Value >> (8 - m_BitPos)) & kMask) >> (kNumValueBits - numBits);
         }

         void MovePos(unsigned numBits)
         {
            m_BitPos += numBits;
            Normalize();
         }

         uint32 ReadBits(unsigned numBits)
         {
            uint32 res = GetValue(numBits);
            MovePos(numBits);
            return res;
         }

         void AlignToByte() { MovePos((32 - m_BitPos) & 7); }
      };

      typedef CLASS_DECL_ca decoder < in_buffer > in_buffer_decoder;

   } // namespace bitm

} // namespace compress
