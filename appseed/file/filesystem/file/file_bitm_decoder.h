// BitmDecoder.h -- the Most Significant Bit of byte is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../IStream.h"

namespace file
{

   namespace bitm
   {

      const uint32_t kNumBigValueBits = 8 * 4;
      const uint32_t kNumValueBytes = 3;
      const uint32_t kNumValueBits = 8  * kNumValueBytes;

      const uint32_t kMask = (1 << kNumValueBits) - 1;

      template<class TInByte>
      class decoder
      {
         uint32_t m_BitPos;
         uint32_t m_Value;
      public:
         TInByte m_Stream;
         bool Create(uint32_t bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(reader *inStream) { m_Stream.SetStream(inStream);}
         void ReleaseStream() { m_Stream.ReleaseStream();}

         void Init()
         {
            m_Stream.Init();
            m_BitPos = kNumBigValueBits;
            Normalize();
         }

         uint64_t GetProcessedSize() const { return m_Stream.GetProcessedSize() - (kNumBigValueBits - m_BitPos) / 8; }

         void Normalize()
         {
            for (;m_BitPos >= 8; m_BitPos -= 8)
               m_Value = (m_Value << 8) | m_Stream.ReadByte();
         }

         uint32_t GetValue(uint32_t numBits) const
         {
            // return (m_Value << m_BitPos) >> (kNumBigValueBits - numBits);
            return ((m_Value >> (8 - m_BitPos)) & kMask) >> (kNumValueBits - numBits);
         }

         void MovePos(uint32_t numBits)
         {
            m_BitPos += numBits;
            Normalize();
         }

         uint32_t ReadBits(uint32_t numBits)
         {
            uint32_t res = GetValue(numBits);
            MovePos(numBits);
            return res;
         }

         void AlignToByte() { MovePos((32 - m_BitPos) & 7); }
      };

      typedef CLASS_DECL_CA2_FILE decoder < in_buffer > in_buffer_decoder;

   } // namespace bitm

} // namespace file
