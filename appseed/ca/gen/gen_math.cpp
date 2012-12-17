#include "framework.h"
#include <time.h>


namespace gen
{


   namespace math
   {


      int ceil_div(int num, int den)
      {
         int quo = num / den;
         if((num % den) > 0)
            quo++;
         return quo;
      }


      int64_t ceil_div(int64_t num, int64_t den)
      {
         int64_t quo = num / den;
         if((num % den) > 0)
            quo++;
         return quo;
      }



      math::math(::ca::application * papp) :
         ca(papp)
      {
         // initial rng seed
         dPi = atan(1.0) * 4.0;

#ifdef WINDOWSEX
         hCryptProv = NULL;
         hOriginalKey = NULL;
         hDuplicateKey = NULL;

         if(!CryptAcquireContext(
            &hCryptProv,
            NULL,
            NULL,
            PROV_RSA_FULL,
            0))
         {
            if(CryptAcquireContext(
               &hCryptProv,
               NULL,
               NULL,
               PROV_RSA_FULL,
               CRYPT_NEWKEYSET))
            {
                printf("CryptAcquireContext succeeded. \n");
            }
            else
            {
//           TRACELASTERROR();
             printf("Error during CryptAcquireContext!\n");

            }

         }
         else
         {
                printf("CryptAcquireContext succeeded. \n");
         }
         //-------------------------------------------------------------------
         // Generate a key.
         if (CryptGenKey(
              hCryptProv,
              CALG_RC4,
              0,
              &hOriginalKey))
         {
            printf("Original session key is created. \n");
         }
         else
         {
            printf("ERROR - CryptGenKey.");
         }
         //-------------------------------------------------------------------
         // Duplicate the key.

         if (CryptDuplicateKey(
              hOriginalKey,
              NULL,
              0,
              &hDuplicateKey))
         {
            printf("The session key has been duplicated. \n");
         }
         else
         {
            printf("ERROR - CryptDuplicateKey");
         }
         //-------------------------------------------------------------------
         // Set additional parameters on the original key.
         // First, set the cipher mode.

         dwMode = CRYPT_MODE_ECB;
         if(CryptSetKeyParam(
            hOriginalKey,
            KP_MODE,
            (BYTE*)&dwMode,
            0))
         {
              printf("Key Parameters set. \n");
         }
         else
         {
              printf("Error during CryptSetKeyParam.");
         }

         // Generate a random initialization vector.
         if(CryptGenRandom(
            hCryptProv,
            8,
            pbData))
         {
              printf("Random sequence generated. \n");
         }
         else
         {
              printf("Error during CryptGenRandom.");
         }
         //-------------------------------------------------------------------
         // Set the initialization vector.
         if(CryptSetKeyParam(
            hOriginalKey,
            KP_IV,
            pbData,
            0))
         {
              printf("Parameter set with random sequence as "
                "initialization vector. \n");
         }
         else
         {
              printf("Error during CryptSetKeyParam.");
         }

#endif

         {
          //  m_chRngReSeedCountDown = -1;
            //unsigned long ulRnd = rnd();
         }

      }

      uint64_t math::gen_rand()
      {
#if defined(METROWIN)
         uint64_t uiLo = Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
         uint64_t uiHi = Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
         return uiLo | (uiHi << 32);
#else
         uint64_t ui = 0;
         gen_rand(&ui, sizeof(ui));
         return ui;
#endif
         
      }

      void math::gen_rand(void * buf, DWORD dwLen)
      {
#ifdef WINDOWSEX
         CryptGenRandom(hCryptProv, dwLen, (BYTE *) buf);
#elif defined(METROWIN)
         Windows::Storage::Streams::IBuffer ^ buffer = Windows::Security::Cryptography::CryptographicBuffer::GenerateRandom(dwLen);
         simple_memory mem;
         mem.set_os_stream_buffer(buffer);
         memcpy(buf, mem.get_data(), mem.get_size());
#else

         byte * puch = (byte *) buf;
         while(dwLen > 0)
        {
           *puch = (byte) rnd() % 256;
           puch++;
           dwLen--;
         }
#endif
      }

      int math::rand_max()
      {
         return 0xffffff;
      }

      unsigned long math::rnd()
      {
         synch_lock lock(this);
         static int s_iRngReSeedCountDown = -1;
         if(s_iRngReSeedCountDown < 0)
         {
            s_iRngReSeedCountDown = random_context_entropy(19840, 8777);
            m_rng.seed(1984, random_context_entropy(19841511, 19770402));
         }
         else
         {
            s_iRngReSeedCountDown--;
         }
         return m_rng.get();
      }


      int math::random_context_entropy(int iMin, int iMax, int iLevel)
      {
         int iValue;
         if(iLevel > 0)
         {
            iLevel = min(iLevel, 3);
            iValue = abs(random_context_entropy(iMin, iMax, iLevel - 1) + random_context_entropy(iMin, iMax, iLevel - 1)) % abs(iMax - iMin);
         }
         else
         {

            gen::microtimer timer;

            double d1 = timer.getTimeInMicroSec();

            sleep(millis(1));

            double d2 = timer.getTimeInMicroSec();

//            LARGE_INTEGER tick;
  //          QueryPerformanceCounter(&tick);
    //        PERFORMANCE_INFORMATION pi;
      //      memset(&pi, 0, sizeof(pi));
        //    GetPerformanceInfo(&pi, sizeof(pi));
//            FILETIME fta[3];
  //          memset(&fta, 0, sizeof(fta));
    //        GetSystemTimes(&fta[0], &fta[1], &fta[2]);
      //      int64_t v1 = tick.QuadPart;
        //    int64_t v2 = time(NULL);
          //  int64_t v3 = ca4::crypt::crc32(tick.QuadPart % 0xffffffff, &pi, sizeof(pi));
            //int64_t v4 = ca4::crypt::crc32(tick.QuadPart % 0xffffffff, fta, sizeof(fta));

            int v1 = (int) timer.getTimeInMicroSec();

            int v2 = (int) time(NULL);

            int v3 = (int) ::crc32(((uint32_t) timer.getTimeInMicroSec()) % 0xffffffff, (const Bytef *) &d1, sizeof(double));

            int v4 = (int) ::crc32(((uint32_t) timer.getTimeInMicroSec()) % 0xffffffff, (const Bytef *) &d2, sizeof(double));

            iValue = abs(v1 + v2 + v3 + v4) % (iMax - iMin);

         }
         if(iMax > iMin)
         {
            return iMin + iValue;
         }
         else
         {
            return iMin - iValue;
         }
      }

      math::~math()
      {
      /*if (hOriginalKey)
          if (!CryptDestroyKey(hOriginalKey))
              TRACE("Failed CryptDestroyKey\n");

      if (hDuplicateKey)
          if (!CryptDestroyKey(hDuplicateKey))
                  TRACE("Failed CryptDestroyKey\n");

      if(hCryptProv)
          if (!CryptReleaseContext(hCryptProv, 0))
              TRACE("Failed CryptReleaseContext\n");
*/

      }

      double math::GetPi()
      {
         return dPi;
      }

      bool math::IsPowerOfTwo(
         unsigned int uiValue)
      {
          if (uiValue < 2)
              return FALSE;

          if (uiValue & (uiValue - 1)) // Thanks to 'byang' for this cute trick!
              return FALSE;

          return TRUE;
      }

      unsigned int math::ReverseBits (unsigned index, unsigned NumBits )
      {
          unsigned i, rev;

          for ( i=rev=0; i < NumBits; i++ )
          {
              rev = (rev << 1) | (index & 1);
              index >>= 1;
          }

          return rev;
      }

/*      int math::RandRange(int i1, int i2)
      {
         // dRandRange == 0.0 is impossible event due this next statement;
         if(i1 == i2)
            return i1;
         int iMin = min(i1, i2);
         int iMax = max(i1, i2);
         double dRand = 0.0;
         double dRange = (double) (iMax - iMin);
         double dRandRange = 1.0;
         int i = 1;
         while((dRandRange - 1.0) < dRange)
         {
            dRand += dRandRange * gen_rand();
            dRandRange = pow((double) rand_max() + 1, (double) i);
            i++;
         }
         dRandRange -= 1.0;
         dRand *= (dRange) / (double) dRandRange;
         dRand += (double) iMin;
         dRand += 0.5;
         return (int) dRand;
      }

      unsigned int math::RandRange(unsigned int ui1, unsigned int ui2)
      {
         // dRandRange == 0.0 is impossible event due this next statement;
         if(ui1 == ui2)
            return ui1;
         int iMin = min(ui1, ui2);
         int iMax = max(ui1, ui2);
         double dRand = 0.0;
         double dRange = (double) (iMax - iMin);
         double dRandRange = 1.0;
         int i = 1;
         while((dRandRange - 1.0) < dRange)
         {
            dRand += dRandRange * gen_rand();
            dRandRange = pow((double) rand_max() + 1, (double) i);
            i++;
         }
         dRandRange -= 1.0;
         dRand *= (dRange) / (double) dRandRange;
         dRand += (double) iMin;
         dRand += 0.5;
         return (int) dRand;
      }*/

      int64_t math::RandRange(int64_t i1, int64_t i2)
      {
         // dRandRange == 0.0 is impossible event due this next statement;
         if(i1 == i2)
            return i1;
         int64_t iMin = min(i1, i2);
         int64_t iMax = max(i1, i2);
         uint64_t uiRange = iMax - iMin;
         return (gen_rand() % (uiRange + 1)) + iMin;
      }
      
      /*

      uint64_t math::RandRange(uint64_t ui1, uint64_t ui2)
      {
         // dRandRange == 0.0 is impossible event due this next statement;
         if(ui1 == ui2)
            return ui1;
         uint64_t uiMin = min(ui1, ui2);
         uint64_t uiMax = max(ui1, ui2);
         double dRand = 0.0;
         double dRange = (double) (uiMax - uiMin);
         double dRandRange = 1.0;
         int i = 1;
         while((dRandRange - 1.0) < dRange)
         {
            dRand += dRandRange * gen_rand();
            dRandRange = pow((double) rand_max() + 1, (double) i);
            i++;
         }
         dRandRange -= 1.0;
         dRand *= (dRange) / (double) dRandRange;
         dRand += (double) uiMin;
         dRand += 0.5;
         return (int) dRand;
      }
       
       
       */

      int math::LinearMap(int iMin, int iMax, int iValue, int iValueMin, int iValueMax)
      {
         double d = iValue - iValueMin;
         d *= (iMax - iMin) / (double) (iValueMax - iValueMin);
         d += iMin;
         d += 0.5;
         return (int) d;
      }

      double math::LinearMap(
         double dMin, double dMax,
         double dValue,
         double dValueMin,
         double dValueMax)
      {
         double d = dValue - dValueMin;
         d *= (dMax - dMin) / (double) (dValueMax - dValueMin);
         d += dMin;
         return d;
      }


      int math::RangeRate(int iMin, int iMax, double dRate)
      {
         return (int)((iMax - iMin) * dRate) + iMin;
      }



   } // namespace math


} // namespace gen



namespace gen
{


   namespace lemon
   {

      int CLASS_DECL_ca time_seed();

      void CLASS_DECL_ca srand();
      
      int CLASS_DECL_ca time_seed()
      {
         return (time(NULL) % 5000 + (::get_tick_count() / 100) % 5000) % 1000;
      }


      void CLASS_DECL_ca srand()
      {
         int iSeed = time_seed();
         ::srand(iSeed);
         iSeed %= 64;
         for(int i = 0; i < iSeed; i++)
         {
            ::srand(rand());
         }
         for(int i = 0; i < iSeed; i++)
         {
            rand();
         }
      }


   } // lemon


} // gen


