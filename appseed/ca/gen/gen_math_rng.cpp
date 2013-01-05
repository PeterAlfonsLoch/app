#include "framework.h"

// defines for the random number generator
#define TWIST_LEN       (m_dwa.get_count())
#define TWIST_IA        397
#define TWIST_IB        (TWIST_LEN - TWIST_IA)
#define UMASK           0x80000000
#define LMASK           0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)   ((b)[i] & UMASK) | ((b)[j] & LMASK)
#define MAGIC_TWIST(s) (((s) & 1) * MATRIX_A)

namespace gen
{
   namespace math
   {
      rng::rng() : m_value( 0 )
      {
         seed(624, 0);
      }

      void rng::seed(int32_t iTwistLen, uint32_t long seed)
      {
         iTwistLen = max(TWIST_IA + 10, iTwistLen);
         m_dwa.set_size(iTwistLen);
         m_dwa[0]= seed & 0xffffffffUL;
         for (int32_t i = 1; i < m_dwa.get_count(); i++)
         {
            m_dwa[i] = (1812433253UL * (m_dwa[i - 1] ^ (m_dwa[i - 1] >> 30)) + i);
         }
      }


      uint32_t long rng::get()
      {
         if(m_dwa.get_size() == 0)
            return 0;
         uint32_t long val = m_dwa[m_value % m_dwa.get_size()];
         ++m_value;
         if (m_value == TWIST_LEN)
         {
            int32_t i = 0;
            for (i = 0; i < TWIST_IB; ++i)
            {
               uint32_t long s = TWIST(m_dwa, i, i + 1);
               m_dwa[i] = m_dwa[i + TWIST_IA] ^ (s >> 1) ^ MAGIC_TWIST(s);
            }
            for (; i < TWIST_LEN - 1; ++i)
            {
               uint32_t long s = TWIST(m_dwa, i, i + 1);
               m_dwa[i] = m_dwa[i - TWIST_IB] ^ (s >> 1) ^ MAGIC_TWIST(s);
            }
            uint32_t long s = TWIST(m_dwa, TWIST_LEN - 1, 0);
            m_dwa[TWIST_LEN - 1] = m_dwa[TWIST_IA - 1] ^ (s >> 1) ^ MAGIC_TWIST(s);

            m_value = 0;
         }
         return val;
      }

   } // namespace rng

} // namespace gen
