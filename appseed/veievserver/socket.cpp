#include "StdAfx.h"
#include "include/FreeImage.h"



namespace veievserver
{

   socket::socket(::sockets::socket_handler_base & h) :
      ::ca::ca(((::sockets::socket_handler_base &)h).get_app()),
      ::sockets::socket(h),
      stream_socket(h),
      smtpd_socket(h)
   {
      
//      m_strCat = Application.dir().matter("fontopus.com.cat");

      m_psession = NULL;
	   /*
      m_strHead += "HTTP/1.1 200 OK\n";
	   m_strHead += "Server: netnode/1.0 (Windows)\n";
	   m_strHead += "Accept-Ranges: bytes\n";
	   m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
	   m_strHead += "Server: netnode/1.0 (Windows)\n";
	   m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";
	   //m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
	   m_strHead += "Accept-Ranges: bytes\n";
	   // m_memfileSend += "Content-Length: 438";
	   //m_strHead += "Connection: close\n";
      */

      /*	
      m_memfileBody << "<html>\n";
      m_memfileBody << "<head>\n";
      m_memfileBody << "</head>\n";
      m_memfileBody << "<body>\n";
      m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
      m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
      m_memfileBody << "</body>\n";
      m_memfileBody.Truncate(0);
      */

      /*
      m_plistensocket = plistensocket;
	   m_strHead += "HTTP/1.1 200 OK\n";
	   m_strHead += "Server: netnode/1.0 (Windows)\n";
	   m_strHead += "Accept-Ranges: bytes\n";
	   m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
	   m_strHead += "Server: netnode/1.0 (Windows)\n";
	   m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";*/
	   //m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
	   //m_strHead += "Accept-Ranges: bytes\n";
	   // m_memfileSend += "Content-Length: 438";
	   //m_strHead += "Connection: close\n";

	   /*
      m_memfileBody << "<html>\n";
	   m_memfileBody << "<head>\n";
	   m_memfileBody << "</head>\n";
	   m_memfileBody << "<body>\n";
	   m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
	   m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
	   m_memfileBody << "</body>\n";
      */
	      
      m_nBytesSent = 0;
      m_nBytesBufferSize = 1024;

   }

   socket::~socket(void)
   {
   }

   void socket::send_response()
   {
//	   string strUri(inattr("request_uri"));
  //    string strHost(inheader("host"));
    //  string strScript = Application.url().object_get_script(strUri);
      //get(strUri);
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
/*      if(!outheaders().has_property("content-type") 
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
      Respond();*/
   }

   void socket::get(const char * lpcsz)
   {

      /*defer_initialize_session();

      string str(lpcsz);

      string strObject = m_psession->m_papp->url().object_get_script(str);
      string strQuery = m_psession->m_papp->url().object_get_query(str);
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
         rectScreen = m_psession->m_papp->m_rectScreen;
         if(rectScreen.width() > 0 && rectScreen.height() > 0)
         {
            m_psession->m_pframe->SetWindowPos(0, 0, 0, rectScreen.width(), rectScreen.height(), SWP_NOZORDER);
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
         m_psession->m_papp->m_ptCursor = pt;
         int iMouseFlagPress = 0;
         m_psession->PostMessage(
            WM_MOUSEMOVE, 
            iMouseFlagPress, 
            MAKELONG(m_psession->m_papp->m_ptCursor.x, m_psession->m_papp->m_ptCursor.y));
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
         m_psession->m_papp->m_ptCursor = pt;
         m_psession->PostMessage(
            WM_LBUTTONDOWN, 
            MK_LBUTTON, 
            MAKELONG(m_psession->m_papp->m_ptCursor.x, m_psession->m_papp->m_ptCursor.y));
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
         m_psession->m_papp->m_ptCursor = pt;
         m_psession->PostMessage(
            WM_LBUTTONUP, 
            0, 
            MAKELONG(m_psession->m_papp->m_ptCursor.x, m_psession->m_papp->m_ptCursor.y));
         netshareSend();
         return;
      }*/
   }

   void socket::image_query(const char * pszQuery)
   {
      /*gen::property_set q(get_app());
      q.parse_url_query(pszQuery);
      int w = q["w"].get_integer();
      int h = q["h"].get_integer();
      if(w > 0 && h > 0)
      {
         m_psession->m_papp->m_rectScreen.left = 0;
         m_psession->m_papp->m_rectScreen.top = 0;
         m_psession->m_papp->m_rectScreen.right = w;
         m_psession->m_papp->m_rectScreen.bottom = h;
      }
      m_psession->take_screenshot();*/
   }

   int socket::send_snapshot(string str)
   {
      /*session * psession = m_psession;
      CSingleLock sl (&psession->m_mutexSnapshot, TRUE);
      int iRetry = 0;
   start:
      //string strI;
      //string strD;
      //string strF;
      int iFrame = psession->m_iFrame;
      //strI.Format("C:\\ca2\\veievserver\\screenshotI%d.png", iFrame);
      //strD.Format("C:\\ca2\\veievserver\\screenshotD%d.png", iFrame);
      //strF.Format("C:\\ca2\\veievserver\\screenshotF.png", iFrame);
      psession->m_iFrame++;
      if(psession->m_iFrame >= psession->m_iFrameCount)
         psession->m_iFrame = 0;
      int iFrameCount = psession->m_iFrameCount;
      /*if(str == "b")
      {
//         int iSize1 = m_psession->m_papp->file().length(strI);
  //       int iSize2 = m_psession->m_papp->file().length(strD);
         if(iSize2 == 0)
         {
            iRetry++;
            if(iRetry <= psession->m_iFrameCount)
               goto start;
         }
         if(iSize1 <= iSize2)
            str = "i";
         else
            str = "d";
      }*/

      /*ex1::filesp spfile(get_app());
      memory st;
      FIBITMAP * pfi3 = NULL;
      iFrameCount = psession-> m_iFrameCount;
      class size size = m_psession->m_papp->m_rectScreen.size();
      int iSliceCount = (int) sqrt((double) iFrameCount);
      int iFrameWidth = size.cx / iSliceCount;
      int iFrameHeight = size.cy / iSliceCount;
      int iFrameX = (iFrame % iSliceCount) * iFrameWidth;
      int iFrameY = (iFrame / iSliceCount) * iFrameHeight;
      class size sizeFrame(iFrameWidth, iFrameHeight);
      point ptFrame(iFrameX, iFrameY);
      if(str == "f")
      {
         pfi3 = m_psession->m_papp->imaging().HBITMAPtoFI(psession->m_dibScreen->get_bitmap(), false);
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
         ::ca::dib_sp dib(get_app());
         dib->create(sizeFrame);
         dib->from(null_point(), psession->m_dibScreen->get_graphics(), ptFrame, sizeFrame);
         pfi3 = m_psession->m_papp->imaging().HBITMAPtoFI(dib->get_bitmap(), false);
         psession->m_dibUser->from(ptFrame, psession->m_dibScreen->get_graphics(), ptFrame, size);
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
         ::ca::dib_sp dib(get_app());
         dib->create(sizeFrame);
         dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibScreen->get_graphics(), iFrameX, iFrameY, SRCCOPY);
         dib->get_graphics()->BitBlt(0, 0, iFrameWidth, iFrameHeight, psession->m_dibUser->get_graphics(), iFrameX, iFrameY, SRCINVERT);
         pfi3 = m_psession->m_papp->imaging().HBITMAPtoFI(dib->get_bitmap(), false);
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
      }*/
      return 0;
   }


   void socket::OnConnect()
   {
      ::sockets::smtpd_socket::OnConnect();
   }

   void socket::OnSSLConnect()
   {
      ::sockets::smtpd_socket::OnConnect();
   }

   void socket::defer_initialize_session()
   {
      if(m_psession == NULL)
      {
         m_psession = new session(get_app());
         m_psession->initialize();
      }
   }

   bool socket::OnHello(const string & strHello)
   {
      m_strHello = strHello;
      TRACE("veievserver::socket::OnHello hello=%s", strHello);
      return true;
   }

   bool socket::OnMailFrom(const ::email::address & addr)
   {
      m_froma.add(addr);
      return true;
   }

   bool socket::OnRcptTo(const ::email::address & addr)
   {
      SetNonblocking(false);
      m_toa.add(addr);
      mysql::database db(get_app());

      if(!db.connect(
         "localhost",
         "fontopus_web",
         "5dCAzq43",
         "veiev"))
         return false;

      var varCount = db.query_item("SELECT COUNT(*) FROM veiev.site WHERE value = '" + addr.get_domain() + "'");
      if(varCount.get_integer() != 1)
         return false;

      varCount = db.query_item("SELECT COUNT(*) FROM fontopus.fun_user WHERE email = '" + addr.to_string() + "'");
      if(varCount.get_integer() != 1)
         return false;

      return true;
   }

   void socket::OnHeader(const string & strKey, const string & strValue)
   {
      TRACE("veievserver::socket::OnHeader key=%s value=%s", strKey, strValue);
      m_strHeaders += strKey;
      m_strHeaders += ":";
      m_strHeaders += strValue;
      m_strHeaders += "\r\n";
      if(strKey.CompareNoCase("subject") == 0)
      {
         m_strSubject = strValue;
      }
   }

   void socket::OnHeaderComplete()
   {
   }

   void socket::OnData(const string & strData)
   {
      m_strData += strData;
      m_strData += "\r";
      m_strData += "\n";
      TRACE("veievserver::socket::OnData strData=%s", strData);
   }


   var socket::get_new_elemental_id(mysql::database & db)
   {
      var varDatetime = System.datetime().international().get_gmt_date_time();
      var varIndex = db.query_item("SELECT MAX(index) FROM elemental WHERE `datetime` = '" +varDatetime.get_string()+"' ORDER BY index");
      if(varIndex.is_empty())
      {
         varIndex = 0;
      }
      else
      {
         varIndex = varIndex.get_integer() + 1;
      }

      var var;
      var.propset()["datetime"] = varDatetime;
      var.propset()["index"] = varIndex;
      return var;
   }

   bool socket::OnDataComplete()
   {
      string strSql;
      mysql::database db(get_app());

      if(!db.connect(
         "localhost",
         "fontopus_web",
         "5dCAzq43",
         "veiev"))
         return false;

      if(m_froma.get_size() <= 0)
         return false;

      var varFrom = db.get_agent("agent", m_froma[0].to_string(), NULL);

      if(varFrom.is_empty())
         return false;

      if(m_toa.get_size() <= 0)
         return false;

      var varTo = db.get_agent("agent", m_toa[0].to_string(), NULL);

      if(varTo.is_empty())
         return false;


      var varElemental = get_new_elemental_id(db);

      strSql = "INSERT INTO elemental(`datetime`, `index`, `subject`) VALUES('" + varElemental.propset()["datetime"].get_string() + "', '" + varElemental.propset()["index"].get_string() + "', '"+m_strSubject+"')";
      if(!db.query(strSql))
         return false;

      System.file().put_contents(get_elemental_file_path(varElemental),"mail\r\n" +  m_strHeaders + "\r\n" + m_strData);

      strSql = "INSERT INTO elemental_agent(`datetime`, `index`, `agent`, `type`) VALUES('" + varElemental.propset()["datetime"].get_string() + "', '" + varElemental.propset()["index"].get_string() + "', '" + varFrom.get_string() + "', 1)";
      if(!db.query(strSql))
         return false;

      strSql = "INSERT INTO elemental_agent(`datetime`, `index`, `agent`, `type`) VALUES('" + varElemental.propset()["datetime"].get_string() + "', '" + varElemental.propset()["index"].get_string() + "', '" + varTo.get_string() + "', 2)";
      if(!db.query(strSql))
         return false;

      return true;
   }

   var socket::get_elemental_file_path(var varKey)
   {
      string strPath;
      string strDomain("ca2.se");
      strPath = "C:\\mail\\" + strDomain + "\\";
      string str;
      int iPathCount;
      __int64 i = System.datetime().strtotime(NULL, varKey["datetime"], 0, iPathCount);
      class time time(i);
      str.Format("%04d", time.GetGmtYear());
      strPath += str + "\\";
      str.Format("%02d", time.GetGmtMonth());
      strPath += str + "\\";
      str.Format("%02d", time.GetGmtDay());
      strPath += str + "\\";
      str.Format("%02d", time.GetGmtHour());
      strPath += str + "\\";
      str.Format("%02d", time.GetGmtMinute());
      strPath += str + "\\";
      str.Format("%02d", time.GetGmtSecond());
      strPath += str + "\\";
      string strIndex;
      strIndex.Format("%016d", varKey["index"].get_integer());
      strPath += strIndex;
      return strPath;
   }

   void socket::OnRset()
   {
   }

   void socket::OnAbort(sockets::smtpd_socket::reason_t ereason)
   {
   }

   void socket::OnNotSupported(const string & str1, const string & str2)
   {
      TRACE("veievserver::socket::OnNotSupported str1=%s str2=%s", str1, str2);
   }

} // namespace veievserver