#pragma once


namespace gen
{


   namespace math
   {


      CLASS_DECL_ca int ceil_div(int num, int den);
      CLASS_DECL_ca int64_t ceil_div(int64_t num, int64_t den);


      class CLASS_DECL_ca math :
         virtual public ::radix::object
      {
      private:
         double         dPi;
//#if WINVER >= 0x500
#ifdef WINDOWSEX
         HCRYPTPROV     hCryptProv;
         HCRYPTKEY      hOriginalKey;
         HCRYPTKEY      hDuplicateKey;
#endif
//#endif
         DWORD          dwMode;
         BYTE           pbData[16];
         rng            m_rng;

      public:

         math(::ca::application * papp);
         virtual ~math();


         int64_t RandRange(int64_t iMin, int64_t iMax);


         int LinearMap(int iMin, int iMax, int iValue, int iValueMin, int iValueMax);
         uint64_t gen_rand();
         void gen_rand(void * buf, DWORD dwLen);
         unsigned long rnd();
         int random_context_entropy(int iMin, int iMax, int iLevel = 3);
         int rand_max();
         double LinearMap(
            double dMin, double dMax,
            double dValue,
            double dValueMin,
            double dValueMax);
         double GetPi();

         static bool IsPowerOfTwo(unsigned int uiValue);
         static unsigned int ReverseBits (unsigned index, unsigned NumBits );
      //   template <class N> static inline void MaxClip(N * pnClipValue, N nMaxValue);
      //   template <class N> static inline void MinClip(N * pnClipValue, N nMinValue);
         static inline void MaxClip(double * pnClipValue, double nMaxValue);
         static inline void MinClip(double * pnClipValue, double nMinValue);

         int RangeRate(int iMin, int iMax, double dRate);



      };

      /*template <class N> inline void math::MaxClip(N * pnClipValue, N nMaxValue)
      {
         if(*pnClipValue > nMaxValue)
            *pnClipValue = nMaxValue;
      }

      template <class N> inline void math::MinClip(N * pnClipValue, N nMinValue)
      {
         if(*pnClipValue < nMinValue)
            *pnClipValue = nMinValue;
      }*/

      inline void math::MaxClip(double * pnClipValue, double nMaxValue)
      {
         if(*pnClipValue > nMaxValue)
            *pnClipValue = nMaxValue;
      }

      inline void math::MinClip(double * pnClipValue, double nMinValue)
      {
         if(*pnClipValue < nMinValue)
            *pnClipValue = nMinValue;
      }


   } // namespace math


} // namespace gen


