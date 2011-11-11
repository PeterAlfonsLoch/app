#pragma once


namespace kissfft
{


   class CLASS_DECL_ca fftd :
      virtual public ::radix::object
   {
   public:


      int                           m_iSize;
      kiss_fftr_cfg                 m_cfg;


      fftd(int iSize);
      virtual ~fftd();

      void fft(double * pIn, kiss_fft_cpx * pOut);


   };


} // namespace kissfft

