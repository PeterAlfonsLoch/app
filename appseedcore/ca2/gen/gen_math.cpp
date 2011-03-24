#include "StdAfx.h"
#include <math.h> 
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

      math::math(::ca::application * papp) :
         ca(papp)
      {
         // initial rng seed
         dPi = atan(1.0) * 4.0;
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
           TRACELASTERROR();
             TRACE("Error during CryptAcquireContext!\n");

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
            TRACE("ERROR - CryptGenKey.");
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
            TRACE("ERROR - CryptDuplicateKey");
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
              TRACE("Error during CryptSetKeyParam.");
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
              TRACE("Error during CryptGenRandom.");
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
              TRACE("Error during CryptSetKeyParam.");
         }

         {
            m_chRngReSeedCountDown = -1;
            //unsigned long ulRnd = rnd();
         }

      }

      int math::gen_rand()
      {
         int i = 0;
         gen_rand(&i, 3);
         return i;
      }

      void math::gen_rand(void * buf, DWORD dwLen)
      {
         CryptGenRandom(hCryptProv, dwLen, (BYTE *) buf);
      }

      int math::rand_max()
      {
         return 0xffffff;
      }

      unsigned long math::rnd()
      {
         ::ca::lock lock(this);
         if(m_chRngReSeedCountDown < 0)
         {
            m_chRngReSeedCountDown = (char) RandRange(23, 84);
            m_rng.seed(RandRange(777, 1984), (unsigned long) (time(NULL) + RandRange(0, 1984 * 1977)));
         }
         else
         {
            m_chRngReSeedCountDown--;
         }
         return m_rng.get();
      }

      math::~math()
      {
      if (hOriginalKey)
          if (!CryptDestroyKey(hOriginalKey))
              TRACE("Failed CryptDestroyKey\n");

      if (hDuplicateKey)
          if (!CryptDestroyKey(hDuplicateKey))
                  TRACE("Failed CryptDestroyKey\n");

      if(hCryptProv)
          if (!CryptReleaseContext(hCryptProv, 0))
              TRACE("Failed CryptReleaseContext\n");


      }

      double math::GetPi()
      {
         return dPi;
      }

      BOOL math::IsPowerOfTwo(
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

      int math::RandRange(int i1, int i2)
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


      namespace gen
      {
         namespace lemon
         {
            int CLASS_DECL_ca time_seed()
            {
               return (time(NULL) % 5000 + (::GetTickCount() / 100) % 5000) % 1000;
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

         }
      }

   }
}
