#pragma once


namespace backview
{


   class CLASS_DECL_CORE ImageChange :
      public Helper
   {
   public:


      struct NO_PRECISION_TIMER
      {

         uint32_t                      m_dwHundredCounter;
         uint32_t                      m_dwThousandCounter;

      } m_noprecisiontimer;


      uint32_t                         m_dwBackgroundUpdateMillis;
      EImagePlacement                  m_eplacement;

      event                            m_evImageChangeFinish;
      uint32_t                         m_dwLoadCounter;
      uint32_t                         m_dwBackgroundLastUpdateTime;
      uint32_t                         m_dwBackgroundPreTransitionStartTime;
      bool                             m_bLastLoadImageSynch;
      string                           m_strCurrentImagePath;
      uint32_t                         m_dwLoadStartTime;

      ::draw2d::dib_sp                 m_spdib;



      ImageChange(Main & view);


      void OnEventLoadNow();

      bool LoadNextImage(bool bSynch);
      bool LoadImageSync();
      bool LoadImageSync(const char * lpcwszImagePath);
      bool LoadImageAsync(const char * lpcwszImagePath);
      bool LoadImageAsync();

      uint32_t GetBackgroundUpdateMillis();
      void SetBackgroundUpdateMillis(uint32_t dwMillis);


   };


} // namespace backview





