#include "StdAfx.h"
#include "include/FreeImage.h"
#include <math.h>

namespace netshareserver
{

   socket::socket(::sockets::socket_handler_base & h) :
      ::ca::ca(((::sockets::socket_handler_base &)h).get_app()),
      ::sockets::socket(h),
      stream_socket(h),
      tcp_socket(h),
      httpd_socket(h)
   {
      
      m_strCat = Application.dir().matter("fontopus.com.cat");

      m_psession = NULL;
	      
      m_nBytesSent = 0;
      m_nBytesBufferSize = 1024;

   }

   socket::~socket(void)
   {
   }

   void socket::send_response()
   {
	   string strUri(inattr("request_uri"));
      string strHost(inheader("host"));
      string strScript = System.url().object_get_script(strUri);
      get(strUri);
   }

   void socket::OnExecute()
   {
      send_response();
   }

   void socket::OnResponseComplete()
   {
   }

   void socket::netshareSend()
   {
      if(!outheaders().has_property("content-type") 
      && response().file().get_size() > 0)
      {
         outheader("Content-Type") = "text/html; charset=UTF-8";
      }
      int iStatusCode;
      string strStatus;
      if(outheader("location").is_set())
      {
         iStatusCode = 303; // 303 (See Other Location)
         strStatus = "See Other";
      }
      else
      {
         iStatusCode = 200;
         strStatus = "OK";
      }
      outattr("http_status_code") = iStatusCode;
      outattr("http_status") = strStatus;
      outattr("http_version") = "HTTP/1.1";
      Respond();
   }

   void socket::get(const char * lpcsz)
   {

      defer_initialize_session();

      if(m_dibSnapshot.is_null())
         m_dibSnapshot.create(m_pbergedge);

      string str(lpcsz);

      string strObject = CaSys(m_psession).url().object_get_script(str);
      string strQuery = CaSys(m_psession).url().object_get_query(str);
      int iFrame;
      if(strObject == "/snapshoti.png")
		{
         image_query(strQuery);
         iFrame = send_snapshot("i");
         return;
	   }
		else if(strObject == "/snapshotd.png")
		{
         image_query(strQuery);
         iFrame = send_snapshot("d");
         return;
	   }
		else if(strObject == "/snapshotb.png") // less bandwidth snapshot
		{
         image_query(strQuery);
         iFrame = send_snapshot("b");
         return;
	   }
		else if(strObject == "/snapshotf.png") // full screen snapshot
      {
         image_query(strQuery);
         rect rectScreen;
         rectScreen = m_psession->m_pbergedge->m_rectScreen;
         if(rectScreen.width() > 0 && rectScreen.height() > 0)
         {
            m_psession->SetWindowPos(0, 0, 0, rectScreen.width(), rectScreen.height(), SWP_NOZORDER);
         }
         iFrame = send_snapshot("f");
         return;
		}
		else if(strObject == "/close")
		{
         close();
         return;
		}
      else if(gen::str::begins_eat(str, "/set_cursor_pos?"))
	   {
         gen::property_set q(get_app());
         q.parse_url_query(str);
         int x = q["x"].get_integer();
         int y = q["y"].get_integer();
         point pt(x, y);
         m_psession->m_pframe->ClientToScreen(&pt);
         int iMouseFlagPress = 0;
         m_psession->PostMessage(WM_MOUSEMOVE, iMouseFlagPress, MAKELONG(pt.x, pt.y));
         netshareSend();
         return;

      }
      else if(gen::str::begins_eat(str, "/l_button_down?"))
	   {
         gen::property_set q(get_app());
         q.parse_url_query(str);
         int x = q["x"].get_integer();
         int y = q["y"].get_integer();
         point pt(x, y);
         m_psession->m_pframe->ClientToScreen(&pt);
         m_psession->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(pt.x, pt.y));
         netshareSend();
         return;

      }
      else if(gen::str::begins_eat(str, "/l_button_up?"))
	   {
         gen::property_set q(get_app());
         q.parse_url_query(str);
         int x = q["x"].get_integer();
         int y = q["y"].get_integer();
         point pt(x, y);
         m_psession->m_pframe->ClientToScreen(&pt);
         m_psession->PostMessage(WM_LBUTTONUP, 0, MAKELONG(pt.x, pt.y));
         netshareSend();
         return;
      }
   }

   void socket::image_query(const char * pszQuery)
   {
      gen::property_set q(get_app());
      q.parse_url_query(pszQuery);
      int w = q["w"].get_integer();
      int h = q["h"].get_integer();
      if(w > 0 && h > 0)
      {
         m_psession->m_pbergedge->m_rectScreen.left = 0;
         m_psession->m_pbergedge->m_rectScreen.top = 0;
         m_psession->m_pbergedge->m_rectScreen.right = w;
         m_psession->m_pbergedge->m_rectScreen.bottom = h;
      }
      m_psession->take_screenshot();
   }

   int socket::send_snapshot(string str)
   {
      session * psession = m_psession;
      single_lock sl (&psession->m_mutexSnapshot, TRUE);
//      int iRetry = 0;
//   start:
      int iFrame = psession->m_iFrame;
      int iFrameCount = 1;
      class size size = m_psession->m_pbergedge->m_rectScreen.size();
      int iSliceCount;;
      int iFrameWidth;;
      int iFrameHeight;;
      class size sizeFrame;
      int iFrameX;
      int iFrameY;
      ::ca::dib_sp & dib  = m_dibSnapshot;

      m_psession->m_dibScreen->get_graphics()->SetViewportOrg(null_point());
      m_psession->m_dibUser->get_graphics()->SetViewportOrg(null_point());


      if(str == "i")
      {
         iFrameCount = 1;
         if(iFrame >= iFrameCount)
            iFrame = 0;
         iSliceCount = (int) sqrt((double) iFrameCount);
         iFrameWidth = size.cx / iSliceCount;
         iFrameHeight = size.cy / iSliceCount;
         sizeFrame = class size(iFrameWidth, iFrameHeight);
         dib->create(sizeFrame);
         int i;
         bool bFound = false;
         for(i = iFrame; i < iFrameCount; i++)
         {
            iFrameX = (i % iSliceCount) * iFrameWidth;
            iFrameY = (i / iSliceCount) * iFrameHeight;
            dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibScreen->get_graphics(), iFrameX, iFrameY, SRCCOPY);
            dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibUser->get_graphics(), iFrameX, iFrameY, SRCINVERT);
            COLORREF * p = dib->get_data();
            __int64 iArea = dib->area();
            while(*p == 0 && iArea > 0)
            {
               p++;
               iArea--;
            }
            if(*p != 0)
            {
               bFound = true;
               iFrame = i;
               break;
            }
         }
         if(!bFound)
         {
            for(i = 0; i < iFrame; i++)
            {
               iFrameX = (i % iSliceCount) * iFrameWidth;
               iFrameY = (i / iSliceCount) * iFrameHeight;
               dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibScreen->get_graphics(), iFrameX, iFrameY, SRCCOPY);
               dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibUser->get_graphics(), iFrameX, iFrameY, SRCINVERT);
               COLORREF * p = dib->get_data();
               __int64 iArea = dib->area();
               while(*p == 0 && iArea > 0)
               {
                  p++;
                  iArea--;
               }
               if(*p != 0)
               {
                  bFound = true;
                  iFrame = i;
                  break;
               }
            }
         }
      }
      else
      {
         iFrame = 0;
         iFrameCount = 1;
         size = m_psession->m_pbergedge->m_rectScreen.size();
         iSliceCount = (int) sqrt((double) iFrameCount);
         iFrameWidth = size.cx / iSliceCount;
         iFrameHeight = size.cy / iSliceCount;
         sizeFrame = class size(iFrameWidth, iFrameHeight);
      }
      psession->m_iFrame = iFrame + 1;
      
      ex1::filesp spfile(get_app());
      primitive::memory st;
      FIBITMAP * pfi3 = NULL;
      if(str == "f")
      {
         iFrameX = (iFrame % iSliceCount) * iFrameWidth;
         iFrameY = (iFrame / iSliceCount) * iFrameHeight;
         pfi3 = CaSys(m_psession).imaging().HBITMAPtoFI(psession->m_dibScreen->get_bitmap());
         psession->m_dibUser->from(null_point(), psession->m_dibScreen->get_graphics(), null_point(), size);
         m_dwLastITime = ::GetTickCount();

         string strLen;
         outheader("Content-Type") = "image/png";
         outheader("Image-Type") = str;
         outheader("Image-Frame") = iFrame;
         outheader("Image-Frame-Count") =  iFrameCount;


         FIBITMAP * pfi4 = FreeImage_ConvertTo24Bits(pfi3);
         FIMEMORY * pfimem = FreeImage_OpenMemory();
         FreeImage_SaveToMemory(FIF_PNG, pfi4, pfimem, PNG_DEFAULT);
         BYTE * pdata; 
         DWORD dwSize;
         FreeImage_AcquireMemory(pfimem, &pdata, &dwSize);
         response().file().Truncate(0);
         response().file().write(pdata, dwSize);
         FreeImage_CloseMemory(pfimem);
         FreeImage_Unload(pfi4);
         FreeImage_Unload(pfi3);
         netshareSend();
      }
      else if(str == "i")
      {
         point ptFrame(iFrameX, iFrameY);
         dib->from(null_point(), psession->m_dibScreen->get_graphics(), ptFrame, sizeFrame);
         pfi3 = CaSys(m_psession).imaging().HBITMAPtoFI(dib->get_bitmap());
         psession->m_dibUser->from(ptFrame, psession->m_dibScreen->get_graphics(), ptFrame, sizeFrame);
         m_dwLastITime = ::GetTickCount();

         string strLen;
         outheader("Content-Type") = "image/png";
         outheader("Image-Type") = str;
         outheader("Image-Frame") = iFrame;
         outheader("Image-Frame-Count") =  iFrameCount;


         FIBITMAP * pfi4 = FreeImage_ConvertTo24Bits(pfi3);
         FIMEMORY * pfimem = FreeImage_OpenMemory();
         FreeImage_SaveToMemory(FIF_PNG, pfi4, pfimem, PNG_DEFAULT);
         BYTE * pdata; 
         DWORD dwSize;
         FreeImage_AcquireMemory(pfimem, &pdata, &dwSize);
         response().file().Truncate(0);
         response().file().write(pdata, dwSize);
         FreeImage_CloseMemory(pfimem);
         FreeImage_Unload(pfi4);
         FreeImage_Unload(pfi3);
         netshareSend();
      }
      else
      { 
            iFrameX = (iFrame % iSliceCount) * iFrameWidth;
            iFrameY = (iFrame / iSliceCount) * iFrameHeight;
         ::ca::dib_sp dib(get_app());
         dib->create(sizeFrame);
         dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibScreen->get_graphics(), iFrameX, iFrameY, SRCCOPY);
         dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibUser->get_graphics(), iFrameX, iFrameY, SRCINVERT);
         pfi3 = CaSys(m_psession).imaging().HBITMAPtoFI(dib->get_bitmap());
         point ptFrame(iFrameX, iFrameY);
         psession->m_dibUser->from(ptFrame, psession->m_dibScreen->get_graphics(), ptFrame, size);
         
         FIBITMAP * pfi4 = FreeImage_ConvertTo24Bits(pfi3);
         FIMEMORY * pfimemD = FreeImage_OpenMemory();
         FreeImage_SaveToMemory(FIF_PNG, pfi4, pfimemD, PNG_DEFAULT);
         FreeImage_Unload(pfi4);
         FreeImage_Unload(pfi3);
         m_dwLastITime = ::GetTickCount();


         pfi4 = FreeImage_ConvertTo24Bits(pfi3);
         FIMEMORY * pfimemI = FreeImage_OpenMemory();
         FreeImage_SaveToMemory(FIF_PNG, pfi4, pfimemI, PNG_DEFAULT);
         FreeImage_Unload(pfi4);
         FreeImage_Unload(pfi3);
         string strLen;


         BYTE * pdataD; 
         DWORD dwSizeD;
         FreeImage_AcquireMemory(pfimemD, &pdataD, &dwSizeD);


         BYTE * pdataI; 
         DWORD dwSizeI;
         FreeImage_AcquireMemory(pfimemI, &pdataI, &dwSizeI);


         if(dwSizeI < dwSizeD)
            str = "i";
         else
            str = "d";

         outheader("Content-Type") = "image/png";
         outheader("Image-Type") = str;
         outheader("Image-Frame") = iFrame;
         outheader("Image-Frame-Count") =  iFrameCount;
         if(str == "i")
         {
            response().file().Truncate(0);
            response().file().write(pdataI, dwSizeI);
         }
         else
         {
            response().file().Truncate(0);
            response().file().write(pdataD, dwSizeD);
         }
         FreeImage_CloseMemory(pfimemD);
         FreeImage_CloseMemory(pfimemI);
         netshareSend();
      }
      
      return 0;
   }


   void socket::OnConnect()
   {
      ::sockets::httpd_socket::OnConnect();
   }

   void socket::OnSSLConnect()
   {
      ::sockets::httpd_socket::OnConnect();
   }

   void socket::defer_initialize_session()
   {
      if(m_psession == NULL)
      {
         m_psession = new session(get_app());
         m_psession->initialize();
      }
   }


} // namespace netshareserver