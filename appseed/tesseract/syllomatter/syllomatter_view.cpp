#include "StdAfx.h"
#include "syllomatter_view.h"
#include "syllomatter_document.h"

/*
 // BEGIN_MESSAGE_MAP(syllomatter_view, ::userbase::view)
   //{{AFX_MSG_MAP(syllomatter_view)
/*
   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_WM_VERISVNWELL()
   ON_WM_CREATE()
   ON_WM_CONTEXTMENU()
   ON_WM_SETCURSOR()
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
   ON_COMMAND(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()
syllomatter_view::extract::extract(::ca::application * papp) :
   ca(papp)
{
}


syllomatter_view::syllomatter_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
      m_iMessageId = -1;

   m_dataid = "syllomatter_view";
   m_iBufSize = 1024 * 1024;
   m_buf1 = new char[m_iBufSize];
   m_buf2 = new char[m_iBufSize];
}

syllomatter_view::~syllomatter_view()
{
}

void syllomatter_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   form_view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &syllomatter_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &syllomatter_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &syllomatter_view::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &syllomatter_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &syllomatter_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &syllomatter_view::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &syllomatter_view::_001OnEraseBkgnd);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &syllomatter_view::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &syllomatter_view::_001OnWavePlayerEvent);
   //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
  // IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


}
/////////////////////////////////////////////////////////////////////////////
// syllomatter_view drawing

void syllomatter_view::OnDraw(::ca::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// syllomatter_view diagnostics

#ifdef _DEBUG
void syllomatter_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void syllomatter_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// syllomatter_view message handlers

// vmpLightView.cpp : implementation of the syllomatter_view class
//


/////////////////////////////////////////////////////////////////////////////
// syllomatter_view


BOOL syllomatter_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::view::PreCreateWindow(cs);
}
void syllomatter_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);

   
}

void syllomatter_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   form_view::on_update(pSender, lHint, phint);
}

void syllomatter_view::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnDestroy(pobj);

}

void syllomatter_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::size, psize, pobj)


/*   pobj->previous();

   double d = psize->m_size.cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   GetClientRect(m_rectKaraokeView);


   rect rectClient;
   GetClientRect(rectClient);
   rect rect = rectClient;

   rect.top = rect.bottom - 24;
   m_viewlineStatus.SetPlacement(rect);


   m_rectKaraokeView.bottom -= 16;

   LayoutTitleLines();
   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();*/
}

void syllomatter_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   CPaintDC spgraphics(this); // device context for syllomattering
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void syllomatter_view:: _001OnDraw(::ca::graphics * pdc)
{
//   m_hwnd = GetSafeHwnd();
   pdc->SetBkMode(TRANSPARENT);

   //FIBITMAP * pdib = CImaging::LoadImageFile("C:\\screenshot.jpeg");

   //::ca::bitmap bmp2;

   //bmp2.Attach(CImaging::FItoHBITMAP(pdib, true));
   //::ca::graphics_sp dc2;
   //dc2.CreateCompatibleDC(pdc);
   //dc2.SelectObject(bmp2);

   //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

   //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
//   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
  // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
   form_view::_001OnDraw(pdc);
}

void syllomatter_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
   

}
void syllomatter_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}


void syllomatter_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      System.simple_message_box(NULL, "Playlist");
   }
}

void syllomatter_view::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
}

void syllomatter_view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
}
void syllomatter_view::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::command, pcommand, pobj)
}


/*xxxvoid syllomatter_view::data_on_after_change(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
{
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
      PrepareLyricLines();
      RedrawWindow();
   }
}*/


void syllomatter_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}
void syllomatter_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

void syllomatter_view::on_document_complete(const char * pszUrl) 
{
   UNREFERENCED_PARAMETER(pszUrl);
   /*::user::interaction * pguie = GetChildByName("check");
   text_interface * ptext = dynamic_cast < text_interface * > (pguie);
   string str;
   DILoad("check", str);
   ptext->_001SetText(str);
   pguie = GetChildByName("copy");
   ptext = dynamic_cast < text_interface * > (pguie);
   DILoad("copy", str);
   ptext->_001SetText(str);*/
}


syllomatter_document * syllomatter_view::get_document()
{
   return dynamic_cast < syllomatter_document * > (::userbase::view::get_document());
}


bool syllomatter_view::BaseOnControlEvent(::user::control_event * pevent)
{
   if(pevent->m_eevent == ::user::event_button_clicked)
   {
      if(pevent->m_puie->m_id == "submit")
      {
         string strCheck;
         string strCopy;
         ::user::interaction* pguie = GetChildByName("check");
         text_interface * ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001GetText(strCheck);
         pguie = GetChildByName("copy");
         ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001GetText(strCopy);
         data_set("check", strCheck);
         data_set("copy", strCopy);
         start_syllomatter_extract(strCopy, strCheck);
      }
      else if(gen::str::begins(pevent->m_puie->m_id, "message_"))
      {
         string str = pevent->m_puie->m_id;
         gen::str::begins_eat(str, "message_");
         if(m_iMessageId >= 0)
         {
            string strId;
            strId.Format("messagetext_%d", m_iMessageId);
            html::elemental * pelemental = get_html_data()->get_element_by_id(strId);
            pelemental->m_style.m_propertyset["background-color"] = "#FFFFFF";
         }
         m_iMessageId = atoi(str);
         string strId;
         strId.Format("messagetext_%d", m_iMessageId);
         html::elemental * pelemental = get_html_data()->get_element_by_id(strId);
         pelemental->m_style.m_propertyset["background-color"] = "#CCFFC2";
         _001RedrawWindow();
      }
   }
   return false;
}

void syllomatter_view::start_syllomatter_extract(const char * pszCopy, const char * pszCheck)
{
   extract * pextract = new extract(get_app());
   pextract->m_strCopy = pszCopy;
   pextract->m_strCheck = pszCheck;
   pextract->m_pview = this;
   GetParentFrame()->GetParent()->SendMessage(WM_USER + 1123);
   AfxBeginThread(get_app(), ThreadProc_syllomatter_extract, pextract);
}

UINT AFX_CDECL syllomatter_view::ThreadProc_syllomatter_extract(LPVOID lpParam)
{
   extract * pextract = (extract *) lpParam;
   pextract->m_pview->syllomatter_extract(pextract);
   delete pextract;
   return 0;
}

syllomatter_list_view * syllomatter_view::get_list()
{
   return get_document()->get_typed_view < syllomatter_list_view > ();
}

void syllomatter_view::syllomatter_extract(extract * pextract)
{
   stringa straPath;
//   cube1::application * papp = &App(pextract->get_app());
   stringa straRepos;
   straRepos.add("appmatter");
   straRepos.add("appseed");
   straRepos.add("appseedcore");
   //straRepos.add("ccvotagus");
   //straRepos.add("matter");
   //straRepos.add("netmatter");
   //straRepos.add("netseed");
   //straRepos.add("netseedcore");
   straRepos.add("node");
   straRepos.add("seed");
   for(int i = 0; i < straRepos.get_size(); i++)
   {
      System.dir().rls(System.dir().path(
         pextract->m_strCheck,
         straRepos[i]), &straPath);
   }

   class time time;
   time = time::get_current_time();
   string strFileTitle;
   int iSerial = 0;
   while(iSerial <= 99)
   {
      if(iSerial == 0)
      {
         strFileTitle.Format("syllomatter%04d-%02d-%02d_%02d-%02d-%02d.txt",
            time.GetYear(), 
            time.GetMonth(), 
            time.GetDay(),
            time.GetHour(), 
            time.GetMinute(),
            time.GetSecond());
      }
      else
      {
         strFileTitle.Format("syllomatter%04d-%02d-%02d_%02d-%02d-%02d %02d.txt",
            time.GetYear(), 
            time.GetMonth(), 
            time.GetDay(),
            time.GetHour(), 
            time.GetMinute(),
            time.GetSecond(),
            iSerial);
      }
      strFileTitle = System.dir().path(
      pextract->m_strCopy, strFileTitle);
      if(!System.file().exists(strFileTitle))
      {
         break;
      }
      iSerial++;
   }
   pextract->m_strLogFilePath = strFileTitle;
   ex1::text_file_sp spfile(get_app());
   System.dir().mk(System.dir().name(pextract->m_strLogFilePath));
   spfile->open(pextract->m_strLogFilePath, ::ex1::file::type_text | ::ex1::file::mode_create | ::ex1::file::mode_write);
   spfile->close();

   int iLen = pextract->m_strCheck.get_length();
   syllomatter_list_view * plist = get_list();
   int iCount = straPath.get_size();
   int iProgress = 0;
//   int iAnimation = 0;
   DWORD dwLastUpdate = ::GetTickCount();
   string strFormat;
   plist->m_straStatus.add("");
   plist->m_stra.add("...");
   int iCmp;
   string strStatus;
   for(int i = 0; i < iCount; i++)
   {
      string & strPath = straPath[i];
      if(strPath.Left(iLen).CompareNoCase(pextract->m_strCheck) == 0)
      {
         iCmp = syllomatter_defer_extract(pextract, strPath.Mid(iLen + 1));
         if(iCmp != 0)
         {
            switch(iCmp)
            {
            case 1:
            case -1:
               strStatus = "Modified";
               break;
            case 5:
               strStatus = "Added";
               break;
            case -5:
               strStatus = "Deleted";
               break;
            default:
               strStatus = "";
            }
            plist->m_stra.insert_at(plist->m_stra.get_upper_bound(), strPath);
            plist->m_straStatus.insert_at(plist->m_straStatus.get_upper_bound(), strStatus);
            plist->_001OnUpdateItemCount();
         }
      }
      if((::GetTickCount() - dwLastUpdate) > 100)
      {
         dwLastUpdate = ::GetTickCount();
         strFormat.Format("%d/%d", i, iCount);
         plist->m_stra[plist->m_stra.get_upper_bound()] = strFormat;
         plist->_001RedrawWindow();
      }
      iProgress++;
   }
   plist->m_stra[plist->m_stra.get_upper_bound()] = "OK";
}

int syllomatter_view::syllomatter_defer_extract(extract * pextract, const char * pszTopic)
{
  string strSrc = System.dir().path(pextract->m_strCheck, pszTopic);
   if(strSrc.find("\\.svn\\") > 0)
   {
      return 0;
   }
   if(System.dir().is(strSrc))
   {
      return 0;
   }
   string strChk = System.dir().path(pextract->m_strCheck, 
      System.dir().path(System.dir().path(
         System.dir().name(pszTopic), ".svn\\text-base"),
            System.file().name_(pszTopic))) + ".svn-base";
   string strDst = System.dir().path(pextract->m_strCopy, pszTopic);
   int iCmp = bin_cmp(strSrc, strChk);
   if(iCmp == 1 || iCmp == -1 || iCmp == 5 || iCmp == -5)
   {
      string strStatus;
      string strStatus2;
      if(iCmp == 1 || iCmp == -1)
      {
         strStatus = "Modified";
         strStatus2 = "M";
      }
      else if(iCmp == 5)
      {
         strStatus = "Added";
         strStatus2 = "A";
      }
      else if(iCmp == -5)
      {
         strStatus = "Deleted";
         strStatus2 = "D";
      }
      System.dir().mk(System.dir().name(strDst));
      ::CopyFile(strSrc, strDst, false);
      ex1::text_file_sp spfile(get_app());
      spfile->open(pextract->m_strLogFilePath, ::ex1::file::type_text | ::ex1::file::modeNoTruncate | ::ex1::file::mode_write);
      string str;
      str = strStatus2 + ": " + strSrc + "\r\n";
      spfile->seek_to_end();
      spfile->write_string(str);
      return iCmp;
   }
   return 0;
}

int syllomatter_view::bin_cmp(const char * pszFilePath1, const char * pszFilePath2)
{
   ex1::filesp spfile1(get_app());
   ex1::filesp spfile2(get_app());

   if(!spfile1->open(pszFilePath1, ::ex1::file::type_binary | ::ex1::file::mode_read))
      return -5;
   if(!spfile2->open(pszFilePath2, ::ex1::file::type_binary | ::ex1::file::mode_read))
      return 5;

   ::ex1::file_status status1;
   ::ex1::file_status status2;
   if(!spfile1->GetStatus(status1))
      return -5;
   if(!spfile2->GetStatus(status2))
      return 5;

   if(status1.m_mtime == status2.m_mtime)
      return 0;

   int iRead1;
   int iRead2;
   while(true)
   {
      iRead1 = spfile1->read(m_buf1, m_iBufSize);
      iRead2 = spfile2->read(m_buf2, m_iBufSize);
      if(iRead1 > iRead2)
         return 1;
      else if(iRead1 < iRead2)
         return -1;
      if(iRead1 == 0)
         break;
      else if(iRead2 == 0)
         break;
      int iCmp = memcmp(m_buf1, m_buf2, iRead1);
      if(iCmp > 0)
         return 1;
      else if(iCmp < 0)
         return -1;
   }
   return 0;
}

