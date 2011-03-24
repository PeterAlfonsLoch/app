#include "StdAfx.h"

namespace veiev
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      ::user::interaction(papp)
   {
      m_pdoc = NULL;
      m_puie = NULL;
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
	   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
	   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

   //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);
   
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &view::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

      IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &view::_001OnOp);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &view::_001OnShowWindow);




   }
   /////////////////////////////////////////////////////////////////////////////
   // view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // view diagnostics

   #ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = Application.RegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
	   return ::userbase::view::PreCreateWindow(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnInitialUpdate(pobj);
   }


   void view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
   {
      ::view::on_update(pSender, lHint, phint);
      if(lHint == document::hint_open_veiev_profile)
      {
         open_elemental();
      }
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
	   ::userbase::view::_001OnDestroy(pobj);
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
   //   SCAST_PTR(::user::win::message::size, psize, pobj)

      rect rectDesktop;
      Application.get_screen_rect(rectDesktop);

      rect rectClient;
      GetClientRect(rectClient);
      rectClient.deflate(2, 2);
      int iW = rectClient.width() / 2;
      int iH = rectClient.height() / 2;
      iH = min(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (int) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (int) (iH * rScreen);
      }
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      SetTimer(543218, 1000, NULL);
   }


   void view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();


   }


   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         Application.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	   pobj->previous();
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }



   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
   //   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);
      KillTimer(5432180);


   }

   void view::_001OnRButtonUp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnOp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::user::win::message::base, pbase, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::_001OnTimer(gen::signal_object * pobj)
   {
      //SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::GetDateTime(string & strDateTime)
   {
      class time time = time::get_current_time();
      string strDate;
      string strWeekDay;
      string strTime;
      strDate.Format(
         "%04d-%02d-%02d",
         time.GetYear(),
         time.GetMonth(),
         time.GetDay());
      switch(time.GetDayOfWeek())
      {
      case 1:
         strWeekDay = "domingo";
         break;
      case 2:
         strWeekDay = "segunda-feira";
         break;
      case 3:
         strWeekDay = "terça-feira";
         break;
      case 4:
         strWeekDay = "quarta-feira";
         break;
      case 5:
         strWeekDay = "quinta-feira";
         break;
      case 6:
         strWeekDay = "sexta-feira";
         break;
      case 7:
         strWeekDay = "sábado";
         break;
      }
      strTime.Format("%02d:%02d:%02d",
         time.GetHour(),
         time.GetMinute(),
         time.GetSecond());
      strDateTime.Format("%s %s %s", strDate, strWeekDay, strTime);
   }

   void view::_001OnShowWindow(gen::signal_object * pobj) 
   {
   //   SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::open_elemental()
   {

      application * papp = dynamic_cast < application * > (get_app());

      if(papp->m_pveievlist == NULL)
         return;

      class var var = papp->m_pveievlist->get_selected_message();

      string strMessage = var.propset()["message"];

      int iFind = strMessage.find("\r\n\r\n");
      string strHeaders = strMessage.Left(iFind);
      strMessage = strMessage.Mid(iFind + 4);

      bool bMultipart = false;
      stringa straHeaders;
      straHeaders.add_tokens(strHeaders, "\r\n", TRUE);
      string strLine;
      string strKey;
      string strValue;
      string strKey2;
      string strValue2;
      string strItem;
      string strBoundary;
      int iPos;
      bool bHtml = false;
      bool bQuotedPrintable = false;
      for(int i = 0; i < straHeaders.get_size(); i++)
      {
         strLine = straHeaders[i];
         iPos = strLine.find(":");
         if(iPos > 0)
         {
            strKey = strLine.Mid(0, iPos);
            strValue = strLine.Mid(iPos + 1);
            if(strKey.CompareNoCase("Content-type") == 0)
            {
               stringa straItems;
               straItems.add_tokens(strValue, ";", FALSE);
               for(int j = 0; j < straItems.get_size(); j++)
               {
                  int iPos2;
                  strItem = straItems[j];
                  if(gen::str::find_wwci("text/html", strItem) >= 0)
                     bHtml = true;
                  iPos2 = strItem.find("=");
                  if(iPos2 > 0)
                  {
                     strKey2 = strItem.Mid(0, iPos2);
                     strKey2.trim();
                     strValue2 = strItem.Mid(iPos2 + 1);
                     if(strKey2.CompareNoCase("boundary") == 0)
                     {
                        strValue2.replace(" ", "");
                        strValue2.replace("\"", "");
                        strBoundary = "--" + strValue2;
                     }
                  }
                  if(strItem.find("multipart/") >= 0)
                  {
                     bMultipart = true;
                  }
               }
            }
            else if(strKey.CompareNoCase("Content-Transfer-Encoding") == 0)
            {
               stringa straItems;
               straItems.add_tokens(strValue, ";", FALSE);
               for(int j = 0; j < straItems.get_size(); j++)
               {
                  strItem = straItems[j];
                  if(gen::str::find_wwci("quoted-printable", strItem) >= 0)
                     bQuotedPrintable = true;
               }
            }
         }
      }
      string strDoc;
      string strDocHtml; 
      string strLines;
      stringa straLines;
      stringa straSep;
      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");
      straSep.add("\n\r");
      straLines.add_smallest_tokens(strMessage, straSep, TRUE);
      bool bInMultipart = false;
      for(int i = 0; i < straLines.get_size(); i++)
      {
         strLine = straLines[i];
         if(bMultipart)
         {
            if(strLine == strBoundary)
            {
               if(strLines.has_char())
               {
                  if(bHtml)
                  {
                     if(gen::str::find_ci("<html>", strLines) >= 0 || gen::str::find_wwci("<html", strLines) >= 0)
                     {
                        strDocHtml = strLines;
                     }
                     else
                     {
                        strDocHtml  = "<html><head></head><body>";
                        strDocHtml += strLines;
                        strDocHtml += "</body></html>";
                     }
                  }
                  else
                  {
                     strDoc  = "<html><head></head><body>";
                     strDoc += strLines;
                     strDoc += "</body></html>";
                  }
               }
               strLines.Empty();
               bInMultipart = true;
               bQuotedPrintable = false;
               bHtml = false;
               while(straLines[i] != "" && i < straLines.get_size())
               {
                  strLine = straLines[i];
                  iPos = strLine.find(":");
                  if(iPos > 0)
                  {
                     strKey = strLine.Mid(0, iPos);
                     strValue = strLine.Mid(iPos + 1);
                     if(strKey.CompareNoCase("Content-type") == 0)
                     {
                        stringa straItems;
                        straItems.add_tokens(strValue, ";", FALSE);
                        for(int j = 0; j < straItems.get_size(); j++)
                        {
                           strItem = straItems[j];
                           if(gen::str::find_wwci("text/html", strItem) >= 0)
                              bHtml = true;
                        }
                     }
                     else if(strKey.CompareNoCase("Content-Transfer-Encoding") == 0)
                     {
                        stringa straItems;
                        straItems.add_tokens(strValue, ";", FALSE);
                        for(int j = 0; j < straItems.get_size(); j++)
                        {
                           strItem = straItems[j];
                           if(gen::str::find_wwci("quoted-printable", strItem) >= 0)
                              bQuotedPrintable = true;
                        }
                     }
                  }
                  i++;
               }
               continue;
            }
            if(bQuotedPrintable)
            {
               if(gen::str::ends_eat(strLine, "="))
               {
               }
               else
               {
                  if(bHtml)
                  {
                     strLine += "\r\n";
                  }
               }
               int iFind = 0;
               while((iFind = strLine.find("=", iFind)) >= 0)
               {
                  char str[2];
                  int i;
                  gen::str::atoi(strLine.Mid(iFind + 1, 2), i, 16);
                  str[0] = static_cast < char > (i);
                  str[1] = '\0';
                  strLine = strLine.Left(iFind) + str + strLine.Mid(iFind + 3);
                  iFind = iFind + 1;
               }
            }
            if(bInMultipart)
            {
               if(bHtml)
               {
                  strLines += strLine;
               }
               else
               {
                  if(bHtml)
                  {
                     strLines += strLine;
                  }
                  else
                  {
                     strLines += "<span style=\"font-family: Courier New, fixed-width;\">";
                     strLines += System.html().entities(strLine);
                     strLines += "</span>";
                     strLines += "<br>";
                  }
               }
            }
         }
         else
         {
            if(bHtml)
            {
               strLines += strLine;
            }
            else
            {
               strLines += "<span style=\"font-family: Courier New, fixed-width;\">";
               strLines += System.html().entities(strLine);
               strLines += "</span>";
               strLines += "<br>";
            }
         }
      }
      if(strLines.has_char())
      {
         if(bHtml)
         {
            if(gen::str::find_ci("<html>", strLines) >= 0 || gen::str::find_wwci("<html", strLines) >= 0)
            {
               strDocHtml = strLines;
            }
            else
            {
               strDocHtml  = "<html><head></head><body>";
               strDocHtml += strLines;
               strDocHtml += "</body></html>";
            }
         }
         else
         {
            strDoc  = "<html><head></head><body>";
            strDoc += strLines;
            strDoc += "</body></html>";
         }
      }
      if(m_pdoc != NULL)
      {
         m_pdoc->on_close_document();
      }
      m_pdoc = Application.create_form(this, this);
      if(strDocHtml.has_char())
      {
         TRACE0(strDocHtml);
         m_pdoc->get_html_data()->load(strDocHtml);
      }
      else
      {
         m_pdoc->get_html_data()->load(strDoc);
      }
      m_puie = m_pdoc->get_html_data()->get_frame();
      html_view_update_hint uh;
      uh.m_etype = html_view_update_hint::type_document_complete;
      uh.m_strUrl = var.propset()["datetime"] + "/" + var.propset()["message"];
      m_pdoc->update_all_views(NULL, 0, &uh);
      layout();
   }


   void view::layout()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_puie != NULL)
      {
         m_puie->SetWindowPos(NULL, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
   }

} // namespace veiev