#include "framework.h"

// defines for the random number generator
#define TWIST_LEN       (m_uinta.get_count())
#define TWIST_IA        397
#define TWIST_IB        (TWIST_LEN - TWIST_IA)
#define UMASK           0x80000000
#define LMASK           0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)   ((b)[i] & UMASK) | ((b)[j] & LMASK)
#define MAGIC_TWIST(s) (((s) & 1) * MATRIX_A)

namespace math
{
   rng::rng() : m_value( 0 )
   {
      seed(624, 0);
   }

   void rng::seed(int32_t iTwistLen, uint32_t seed)
   {
      iTwistLen = max(TWIST_IA + 10, iTwistLen);
      m_uinta.allocate(iTwistLen);
      m_uinta[0]= seed & 0xffffffffUL;
      for (int32_t i = 1; i < m_uinta.get_count(); i++)
      {
         m_uinta[i] = (1812433253UL * (m_uinta[i - 1] ^ (m_uinta[i - 1] >> 30)) + i);
      }
   }


   uint32_t rng::get()
   {
      if(m_uinta.get_size() == 0)
         return 0;
      uint32_t val = m_uinta[m_value % m_uinta.get_size()];
      ++m_value;
      if (m_value == TWIST_LEN)
      {
         int32_t i = 0;
         for (i = 0; i < TWIST_IB; ++i)
         {
            uint32_t s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i + TWIST_IA] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         for (; i < TWIST_LEN - 1; ++i)
         {
            uint32_t s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i - TWIST_IB] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         uint32_t s = TWIST(m_uinta, TWIST_LEN - 1, 0);
         m_uinta[TWIST_LEN - 1] = m_uinta[TWIST_IA - 1] ^ (s >> 1) ^ MAGIC_TWIST(s);

         m_value = 0;
      }
      return val;
   }

} // namespace rng
