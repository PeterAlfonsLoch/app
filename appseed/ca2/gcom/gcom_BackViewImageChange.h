#pragma once

namespace gcom
{
   namespace backview
   {

      class CLASS_DECL_ca ImageChange :
         public Helper
      {
      public:
         ImageChange(Main & view);

      public:
         DWORD                        m_dwBackgroundUpdateMillis;
         EImagePlacement                     m_eplacement;
         
         event                        m_evImageChangeFinish;
         DWORD                        m_dwLoadCounter;
         DWORD                        m_dwBackgroundLastUpdateTime;
         DWORD                        m_dwBackgroundPreTransitionStartTime;
         bool                        m_bLastLoadImageSynch;
         string                        m_wstrCurrentImagePath;
         DWORD                        m_dwLoadStartTime;

         struct NO_PRECISION_TIMER
         {
            DWORD                        m_dwHundredCounter;
            DWORD                        m_dwThousandCounter;
         } m_noprecisiontimer;
         



      public:

         void OnEventLoadNow();

         bool LoadNextImage(bool bSynch);
         bool LoadImageSync();
         bool LoadImageSync(const char * lpcwszImagePath);
         bool LoadImageAsync(const char * lpcwszImagePath);
           bool LoadImageAsync();

         DWORD GetBackgroundUpdateMillis();
         void SetBackgroundUpdateMillis(DWORD dwMillis);

      };

   } // namespace gcom::backview

} // namespace gcom
