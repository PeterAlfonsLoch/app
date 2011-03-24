#include "StdAfx.h"

namespace gcom
{
   namespace backview
   {


      ImageChange::ImageChange(Main & view) :
         Helper(view)
      {
         m_bLastLoadImageSynch = false;
         DWORD dwTime = GetTickCount();
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
         m_wstrCurrentImagePath = lpcwszImagePath;
         m_dwLoadCounter = 0;
         Main & main = HelperGetMain();
         load_image loadimage(main.GetIdleThread(), &main, lpcwszImagePath);
         //m_evImageLoad.ResetEvent();
         main.GetIdleThread()->m_evInitialized.Lock();
         main.GetIdleThread()->LoadImageAsync(loadimage);
         return true;
      }

      bool ImageChange::LoadNextImage(bool bSynch)
      {
         DWORD dwTime = GetTickCount();
         
         if(m_dwLoadStartTime - dwTime < 1000)
            return false;

         m_dwLoadStartTime = dwTime;


         string wstrPath(m_wstrCurrentImagePath);

         Main & main = HelperGetMain();

         main.GetNextImagePath(wstrPath);

         if(wstrPath.is_empty())
            return false;


         m_bLastLoadImageSynch = bSynch;
         if(bSynch)
            return LoadImageSync(wstrPath);
         else
            return LoadImageAsync(wstrPath);
      }

      bool ImageChange::LoadImageSync(const char * lpcwszImagePath)
      {
         m_wstrCurrentImagePath = lpcwszImagePath;
         Main & main = HelperGetMain();
         string str;
         ::ca::bitmap * pbitmap = System.imaging().LoadImageSync(lpcwszImagePath, get_app());
         TRACE("ImageChange::OnLoadImageSyn lpcwszImagePath.Lock\n");
         Graphics & graphics = main.GetGraphics();
         CSingleLock sl3Source(&graphics.m_mutex3Source, TRUE);
         ::ca::graphics_sp spgraphics(get_app());
         spgraphics->CreateCompatibleDC(NULL);
         spgraphics->SelectObject(pbitmap);
         graphics.GetDib(_graphics::DibSource)->create(spgraphics);
         delete pbitmap;
         TRACE("ImageChange::OnLoadImageSyn slGdi.UnLock\n");
         main.ImageChangePostEvent(EventLoaded);
         return true;

      }

      DWORD ImageChange::GetBackgroundUpdateMillis()
      {
         return m_dwBackgroundUpdateMillis;
      }

      void ImageChange::SetBackgroundUpdateMillis(DWORD dwMillis)
      {
         m_dwBackgroundUpdateMillis = max(dwMillis, 1000);
      }

   } // namespace backview
} // namespace gcom
