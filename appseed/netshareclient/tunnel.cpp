#include "StdAfx.h"
#include "include/FreeImage.h"
#include <math.h>

namespace netshareclient
{

   tunnel::tunnel(::sockets::socket_handler_base & h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      ::sockets::http_tunnel(h)
   {
   }

   void tunnel::netshare_connect()
   {
      EnableSSL();
      if(!open())
         throw 0;
   }

   void tunnel::OnFirst()
   {
      ::sockets::http_tunnel::OnFirst();
   }

   void tunnel::OnHeader(const string & strKey, const string & strValue)
   {
      ::sockets::http_tunnel::OnHeader(strKey, strValue);
   }

   void tunnel::OnHeaderComplete()
   {
      ::sockets::http_tunnel::OnHeaderComplete();
      m_iFrame = inheader("Image-Frame");
      m_strImageType = inheader("Image-Type");
      m_iFrameCount = inheader("Image-Frame-Count");

      if(m_strImageType.get_length() > 0)
      {
         TRACE("Frame=%d, ImageType=%s, FrameCount=%d\n", m_iFrame, m_strImageType, m_iFrameCount);
      }
      else
      {
         TRACE("Event\n");
      }
   }

   void tunnel::OnData(const char * psz, size_t size)
   {
      ::sockets::http_tunnel::OnData(psz, size);
   }

   void tunnel::netshare_receive_body()
   {
      rect rectClient;
      static int top = 0;
      m_pview->GetClientRect(rectClient);
      m_parea->m_dib1->create(rectClient.width(), rectClient.height());
      if(m_eaction == ActionSetCursor ||
         m_eaction == ActionEvent)
      {
         if(m_straEvent.get_size() > 0)
         {
            m_eaction = ActionEvent;
            m_strRequest = m_straEvent[0];
            m_straEvent.remove_at(0);
         }
         else
         {
            m_eaction = ActionSnapshot;
            if(m_rectClient != rectClient)
            {
               m_rectClient = rectClient;
               m_strRequest = "/snapshotf.png?w=" + gen::str::itoa(rectClient.width()) + "&h=" + gen::str::itoa(rectClient.height());
            }
            else
            {
               m_strRequest = "/snapshoti.png";
            }
         }
      }
      else if(m_eaction == ActionSnapshot)
      {
         if(m_memoryBody.get_size() > 0)
         {
            FIMEMORY * pfimemory = FreeImage_OpenMemory(
               m_memoryBody.get_data(), 
               m_memoryBody.get_size());
            //            DWORD dw1 = ::GetTickCount();
            FIBITMAP * pfi1 = FreeImage_LoadFromMemory(FIF_PNG, pfimemory, 0);
            //DWORD dw2 = ::GetTickCount();
            //            DWORD dw21 = dw2 - dw1;
            FIBITMAP * pfi2 = FreeImage_ConvertTo32Bits(pfi1);
            //DWORD dw3 = ::GetTickCount();
            //DWORD dw32 = dw3 - dw2;
            single_lock sl(&m_parea->m_cs, TRUE);
            //            void * pdata = FreeImage_GetBits(pfi2);
            BITMAPINFO * pi = FreeImage_GetInfo(pfi2);
            int iFrame = m_iFrame;
            int iSliceCount = (int) sqrt((double) m_iFrameCount);
            int iFrameW = pi->bmiHeader.biWidth;
            int iFrameH = pi->bmiHeader.biHeight;
            int iFrameX = (iFrame % iSliceCount) * iFrameW;
            int iFrameY = (iFrame / iSliceCount) * iFrameH;
            point ptFrame(iFrameX, iFrameY);
            size sizeFrame(iFrameW, iFrameH);
            ::ca::bitmap * pbitmap = Application.imaging().FItoHBITMAP(pfi2, TRUE);
            ::ca::graphics_sp graphics(get_app());
            graphics->CreateCompatibleDC(NULL);
            graphics->SelectObject(pbitmap);
            if(m_strImageType == "f")
            {
               m_parea->m_dib1->from(ptFrame, graphics, null_point(), sizeFrame);
            }
            else if(m_strImageType == "d")
            {
               m_parea->m_dib1->from(ptFrame, graphics, null_point(), sizeFrame);
            }
            else
            {
               m_parea->m_dib1->from(ptFrame, graphics, null_point(), sizeFrame);
            }
            pbitmap->delete_object();
            FreeImage_Unload(pfi1);
            FreeImage_CloseMemory(pfimemory);
            m_pview->PostMessage(WM_USER + 1024);
         }
         if(m_straEvent.get_size() > 0)
         {
            m_eaction = ActionEvent;
            m_strRequest = m_straEvent[0];
            m_straEvent.remove_at(0);
         }
         else
         {
            m_eaction = ActionSetCursor;
            string strQuery;
            point ptCursor = m_ptCursor;
            strQuery.Format("x=%d&y=%d", ptCursor.x, ptCursor.y);
            m_strRequest = "/set_cursor_pos?" + strQuery;
         }
      }
   }



   void tunnel::netshare_request(const char * psz, primitive::memory & storage)
   {
      UNREFERENCED_PARAMETER(psz);
      UNREFERENCED_PARAMETER(storage);
   }


   void tunnel::netshare_receive(primitive::memory & storage)
   {
      UNREFERENCED_PARAMETER(storage);
      //   m_memoryBody = storage;
      netshare_receive_body();
   }


   void tunnel::netshare_start()
   {
      rect rectClient;
      m_pview->GetClientRect(rectClient);

      m_eaction = ActionSnapshot;
      m_rectClient = rectClient;
      m_strRequest = "/snapshotf.png?w=" + gen::str::itoa(rectClient.width()) + "&h=" + gen::str::itoa(rectClient.height());
   }





   void tunnel::set_cursor(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
   }

   void tunnel::OnDataComplete()
   {
      netshare_receive_body();
      step();
      SetLineProtocol();
      Reset();
   }

} // netshareclient