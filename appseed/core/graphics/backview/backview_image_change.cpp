#include "framework.h"


namespace backview
{


   ImageChange::ImageChange(Main & view) :
      Helper(view),
      m_spdib(view.allocer()),
      m_evImageChangeFinish(view.get_app())
   {

      m_bLastLoadImageSynch = false;
      uint32_t dwTime = get_tick_count();
      m_dwLoadStartTime = dwTime;
      m_dwBackgroundUpdateMillis = 1000;

   }


   void ImageChange::OnEventLoadNow()
   {

      Main & main = HelperGetMain();

      main.GetTransitionEffect().Reset();
      if(LoadNextImage(false))
      {
         main.SetState(StateLoading);
      }
   }



   bool ImageChange::LoadImageSync()
   {
      string str;
      HelperGetMain().GetNextImagePath(str);
      return LoadImageSync(str);
   }

   bool ImageChange::LoadImageAsync()
   {
      string str;
      HelperGetMain().GetNextImagePath(str);
      return LoadImageAsync(str);
   }

   bool ImageChange::LoadImageAsync(const char * lpcwszImagePath)
   {
      m_strCurrentImagePath = lpcwszImagePath;
      m_dwLoadCounter = 0;
      Main & main = HelperGetMain();
      load_image loadimage(m_spdib, main.GetIdleThread(), &main, lpcwszImagePath);
      //m_evImageLoad.ResetEvent();
      main.GetIdleThread()->m_evInitialized.wait();
      main.GetIdleThread()->LoadImageAsync(loadimage);
      return true;
   }

   bool ImageChange::LoadNextImage(bool bSynch)
   {

      uint32_t dwTime = get_tick_count();

      if(m_dwLoadStartTime - dwTime < 1000)
         return false;

      m_dwLoadStartTime = dwTime;


      string strPath(m_strCurrentImagePath);

      Main & main = HelperGetMain();

      main.GetNextImagePath(strPath);

      if(strPath.is_empty())
         return false;

      m_bLastLoadImageSynch = bSynch;

      if(bSynch)
         return LoadImageSync(strPath);
      else
         return LoadImageAsync(strPath);

   }

   bool ImageChange::LoadImageSync(const char * lpcwszImagePath)
   {

      m_strCurrentImagePath = lpcwszImagePath;

      Main & main = HelperGetMain();

      string str;

      if(!System.visual().imaging().LoadImageSync(m_spdib, lpcwszImagePath, get_app()))
         return false;

      TRACE("ImageChange::OnLoadImageSynch lpcwszImagePath.lock\n");

      main.GetGraphics().GetDib(_graphics::DibSource)->from(m_spdib);

      TRACE("ImageChange::OnLoadImageSynch slGdi.UnLock\n");

      main.ImageChangePostEvent(EventLoaded);

      return true;

   }

   uint32_t ImageChange::GetBackgroundUpdateMillis()
   {
      return m_dwBackgroundUpdateMillis;
   }

   void ImageChange::SetBackgroundUpdateMillis(uint32_t dwMillis)
   {
      m_dwBackgroundUpdateMillis = MAX(dwMillis, 1000);
   }


} // namespace backview








