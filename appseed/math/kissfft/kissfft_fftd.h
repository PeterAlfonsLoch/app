#pragma once


namespace kissfft
{


   class CLASS_DECL_CA2_MATH fftd :
      virtual public ::object
   {
   public:


      int32_t                           m_iSize;
      kiss_fftr_cfg                 m_cfg;


      fftd(int32_t iSize);
      virtual ~fftd();

      void fft(double * pIn, kiss_fft_cpx * pOut);


   };


} // namespace kissfft

