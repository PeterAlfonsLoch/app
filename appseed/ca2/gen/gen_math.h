#pragma once


namespace gen
{
   namespace math
   {



      CLASS_DECL_ca int ceil_div(int num, int den);

      class CLASS_DECL_ca math :
         virtual public ::radix::object  
      {
      private:
         double         dPi;
#if WINVER >= 0x500
/*         HCRYPTPROV     hCryptProv;
         HCRYPTKEY      hOriginalKey;
         HCRYPTKEY      hDuplicateKey;*/
#endif
         DWORD          dwMode;
         BYTE           pbData[16];
         rng            m_rng;
      public:
         math(::ca::application * papp);
         virtual ~math();
         int RandRange(int iMin, int iMax);
         int LinearMap(int iMin, int iMax, int iValue, int iValueMin, int iValueMax);
         int gen_rand();
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
         
         static BOOL IsPowerOfTwo(unsigned int uiValue);
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
