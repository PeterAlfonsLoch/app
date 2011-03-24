#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// DesktopView

IMPLEMENT_DYNCREATE(DesktopView, BaseView)

DesktopView::DesktopView()
: m_penActive(PS_SOLID, 2, RGB(255, 255, 255))
{
   m_iDesktop = 0;

   
   Desktop desktopBlue;
   desktopBlue.m_cr = RGB(0, 0, 255);
   desktopBlue.m_crDisable = RGB(127, 127, 192);
   desktopBlue.m_crHover = RGB(192, 192, 255);
   desktopBlue.m_rectButton.left = 10;
   desktopBlue.m_rectButton.right = 310;
   desktopBlue.m_rectButton.top = 100;
   desktopBlue.m_rectButton.bottom = 120;
   m_desktopa.Add(desktopBlue);

   Desktop desktopYellow;
   desktopYellow.m_cr = RGB(255, 255, 0);
   desktopYellow.m_crDisable = RGB(192, 192, 127);
   desktopYellow.m_crHover = RGB(255, 255, 192);
   desktopYellow.m_rectButton.left = 320;
   desktopYellow.m_rectButton.right = 620;
   desktopYellow.m_rectButton.top = 100;
   desktopYellow.m_rectButton.bottom = 120;
   m_desktopa.Add(desktopYellow);

   m_infoa.SetSize(2);

   m_iListTop           = 200;
   m_iListItemHeight    = 40;

   
   m_bOverrideKaraokeCodePage = false;
   m_bFileOverrideKaraokeCodePage = false;


   m_iActiveItemDesktop = -1;
   m_iActiveItemWindow  = -1;


   m_wndrender.SetWindow(this);

   m_iTempo = 1;
   m_iPos = 2;
   m_iKeyShift = 3;


   m_bWaitingToPlay = false;
   m_bDestroy = false;
}

DesktopView::~DesktopView()
{
}

void DesktopView::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);


	IGUI_WIN_MSG_LINK(WM_DESTROY        , this, this, &DesktopView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE           , this, this, &DesktopView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT          , this, this, &DesktopView::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE         , this, this, &DesktopView::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , this, this, &DesktopView::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR      , this, this, &DesktopView::_001OnSetCursor);

   IGUI_WIN_ON_COMMAND(ID_CANCEL_EDIT_SRVR         , this, this, &DesktopView::_001OnCancelEditSrvr);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, this, this, &DesktopView::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, this, this, &DesktopView::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, this, this, &DesktopView::_001OnMouseMove);

   IGUI_WIN_MSG_LINK(WM_APP + 351, this, this, &DesktopView::_001OnAppMessage);
}




BEGIN_MESSAGE_MAP(DesktopView, BaseView)
	//{{AFX_MSG_MAP(DesktopView)
   /*
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PLAY, OnUpdateExecutePlay)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(ID_KARAOKE_BOUNCING_BALL, OnKaraokeBouncingBall)
	ON_UPDATE_COMMAND_UI(ID_KARAOKE_BOUNCING_BALL, OnUpdateKaraokeBouncingBall)
	ON_COMMAND(ID_KARAOKE_GRADUAL_FILLING, OnKaraokeGradualFilling)
	ON_UPDATE_COMMAND_UI(ID_KARAOKE_GRADUAL_FILLING, OnUpdateKaraokeGradualFilling)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_STOP, OnUpdateExecuteStop)
	ON_COMMAND(ID_EXECUTE_PAUSE, OnExecutePause)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PAUSE, OnUpdateExecutePause)
	ON_COMMAND(ID_EXECUTE_MINUS_ONE, OnExecuteMinusOne)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_MINUS_ONE, OnUpdateExecuteMinusOne)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OPEN_LINK_IN_NEW_WINDOW, OnOpenLinkInNewWindow)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_COPY_LINK_LOCATION, OnCopyLinkLocation)
	ON_COMMAND(ID_PLAYLIST_EXECUTE_PLAY, OnPlaylistExecutePlay)
	ON_UPDATE_COMMAND_UI(ID_PLAYLIST_EXECUTE_PLAY, OnUpdatePlaylistExecutePlay)
	ON_COMMAND(ID_EXECUTE_PREVIOUS, OnExecutePrevious)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_PREVIOUS, OnUpdateExecutePrevious)
	ON_COMMAND(ID_EXECUTE_NEXT, OnExecuteNext)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_NEXT, OnUpdateExecuteNext)
	//}}AFX_MSG_MAP
	// Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
   ON_COMMAND_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnViewEncoding)
   ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ENCODING_1, ID_VIEW_ENCODING_12, OnUpdateViewEncoding)
	ON_COMMAND(ID_EXECUTE_AUTO_RECORD, OnExecuteAutoRecord)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_AUTO_RECORD, OnUpdateExecuteAutoRecord)
   */
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DesktopView diagnostics

#ifdef _DEBUG
void DesktopView::AssertValid() const
{
	BaseView::AssertValid();
}

void DesktopView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}

MusicalPlayerLightDoc* DesktopView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MusicalPlayerLightDoc)));
	return (MusicalPlayerLightDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// DesktopView message handlers

// vmpLightView.cpp : implementation of the DesktopView class
//


/////////////////////////////////////////////////////////////////////////////
// DesktopView


BOOL DesktopView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style |= WS_CLIPSIBLINGS;
	return BaseView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// DesktopView printing

BOOL DesktopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void DesktopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void DesktopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void DesktopView::_001OnCancelEditSrvr(gen::signal_object * pobj)
{
//	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// DesktopView message handlers






void DesktopView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
	BaseView::_001OnInitialUpdate(pobj);
}



void DesktopView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{

   BaseView::OnUpdate(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(CVmpLightViewUpdateHint)))
      {
         CVmpLightViewUpdateHint * puh = (CVmpLightViewUpdateHint * ) phint;
      }
      else if(phint->IsKindOf(RUNTIME_CLASS(PaneViewUpdateHint)))
      {
         PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
         if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnShowKaraoke))
         {
            ((BaseFrameWnd *) GetTopLevelFrame())->SetActiveView(this);
         }
         else if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnShowView))
         {
            int iTab;
            if(puh->m_eview == PaneViewContextMenu)
            {
               m_tab._001AddSel(0);
            }
            else
            {
               switch(puh->m_eview)
               {
               case PaneViewDesktop:
                  iTab = 1;
                  break;
               case PaneViewOptions:
                  iTab = 2;
                  break;
               }
               m_tab._001SetSel(iTab);
            }
            
         }
      }
   }


/*	if(lHint == 1000)
   {

      PrepareLyricLines();
      m_lpbouncingball->SetQuarterNoteDuration(
          GetMidiSequence().GetFile().m_pFileHeader->GetQuarterNoteTicks());

   }

   if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(CVmpLightViewUpdateHint)))
      {
         CVmpLightViewUpdateHint * puh = (CVmpLightViewUpdateHint * ) phint;
         if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeDoPlay))
         {
            ExecutePlay(true);
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypePlayIfNotPlaying))
         {
            if(!GetMidiSequence().IsPlaying())
            {
               ExecutePlay(true);
            }
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeGetMidiPlayerInterface)
            && puh->m_pmidiplayer == NULL)
         {
            puh->m_pmidiplayer = this;
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeAttachPlaylist)
            && puh->m_pplaylistdoc != NULL)
         {
            puh->m_pplaylistdoc->SetCallback(m_pplaylistcallback);
            m_pplaylistcallback->m_pplaylistdoc = puh->m_pplaylistdoc;
         }
         else if(puh->IsTypeOf(CVmpLightViewUpdateHint::TypeFullScreen))
         {
            if(puh->m_bFullScreen)
            {
               ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
            }
            else
            {
               ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
            }
         }
      }
   }*/
	
	
}

/*base_wnd & DesktopView::BackViewGetWnd()
{
   return *this;
}

void DesktopView::BackViewUpdateScreen(LPCRECT lpcrect)
{
   RedrawWindow(lpcrect);
}

void DesktopView::BackViewUpdateScreen()
{
   RedrawWindow();
}

void DesktopView::BackViewGetData(
   gcom::backview::CInterfaceData & data)
{

   if(data.IsSignalized(gcom::backview::InterfaceDataNextImagePath))
   {
      DBCentral * pdb = DB();
      String str;
      DILoad(_T("Images.CurrentPath"), str);
      WString wstrCurrentImagePath;
      wstrCurrentImagePath.SetOEM(str);
      data.m_wstrNextImagePath = pdb->GetNextImagePath(wstrCurrentImagePath);
   //   data.m_wstrNextImagePath = L"C:\\camilo.jpg";
   }
   if(data.IsSignalized(gcom::backview::InterfaceDataEnhancedMetaFile))
   {
//      data.m_henhmetafile = m_enhmetafile;
      data.m_henhmetafile = NULL;
   }

}

void DesktopView::BackViewSetData(
   gcom::backview::CInterfaceData & data)
{

   if(data.IsSignalized(gcom::backview::InterfaceDataCurrentImagePath))
   {
      DBCentral * pdb = DB();
      String str;
      International::UnicodeToACP(
         str,
         data.m_wstrCurrentImagePath);
      DISave(_T("Images.CurrentPath"), str);
   }

}

bool DesktopView::BackViewGetDestroy()
{
   return m_bDestroy; 
}*/

/*bool DesktopView::BackViewIsFullScreen()
{
   return false; // TODO
}*/

void DesktopView::_001OnDestroy(gen::signal_object * pobj) 
{
   ShowDesktopWindowInfo(true);

	BaseView::OnDestroy();


	
   m_bDestroy = true;	
}



void DesktopView::_001OnSize(gen::signal_object * pobj) 
{
   pobj->previous();

   CRect rectClient;

   GetClientRect(rectClient);

   int iSideMargin = 64;
   int iHeight = 16;
   int iBottomMargin = 32;

}

void DesktopView::_001OnPaint(gen::signal_object * pobj) 
{
	CPaintDC dc(this); // device context for painting

   _001OnDraw(&dc);
}


void DesktopView::_001OnDraw(CDC * pdc)
{
   BaseRect rect;
   BaseRect rectText;

   rect.left = 40;
   rect.top = 0;
   rect.right = 400;
   rect.bottom = 100;


   String str;
   str = "Oi! Eu sou o veriwell Desktop!";

   pdc->DrawText(str, str.GetLength(), rect, DT_BOTTOM | DT_LEFT);


   bool bDisable;
   BaseRect rectBk;
   for(int i = 0; i < m_desktopa.GetSize(); i++)
   {
      Desktop & desktop = m_desktopa[i];
      GetRect(rect, i, -1);
      COLORREF cr;
      COLORREF crBk = desktop.m_crDisable;
      if(i == m_iDesktop)
      {
         bDisable = false;
         cr = desktop.m_cr;
      }
      else if(i == m_iHoverDesktopButton)
      {
         bDisable = false;
         cr = desktop.m_crHover;
      }
      else
      {
         bDisable = true;
         crBk = RGB(192, 192, 192);
         cr = desktop.m_cr;
      }
      CBrush brush(cr);
      CBrush brushBk(crBk);
      rectBk = rect;
      rectBk.InflateRect(3, 3, 3, 2000);
      pdc->FillRect(rectBk, &brushBk);
      if(bDisable)
      {
         pdc->FillRect(rect, &brush);
      }
      else
      {
         pdc->SelectObject(brush);
         pdc->SelectObject(m_penActive);
         pdc->Rectangle(rect);
      }
   }


   for(int iDesktop = 0; iDesktop < m_desktopa.GetSize(); iDesktop++)
   {
      DesktopWindowInfo info;
      GetDesktopWindowInfo(iDesktop, info);
      for(int iWindow = 0; iWindow < info.GetSize(); iWindow++)
      {
         DesktopWindow & window = info[iWindow];
         base_wnd * pwnd = base_wnd::FromHandle(window.m_hwnd);

         GetRect(rect, iDesktop, iWindow);
         pwnd->GetWindowTextA(str);
         rectText = rect;
         rectText.left += 40;
         if(iDesktop == m_iActiveItemDesktop
         && iWindow  == m_iActiveItemWindow)
         {
            CBrush brush(RGB(255, 255, 255));
            pdc->SelectObject(m_penActive);
            pdc->Rectangle(rect);
         }
         pdc->DrawText(str, str.GetLength(), rectText, DT_BOTTOM | DT_LEFT);
         pdc->DrawIcon(rect.left, rect.top, window.m_hicon);


      }
   }

   
}

void DesktopView::ShowDesktopWindowInfo(bool bShow)
{
   for(int iDesktop = 0; iDesktop < m_infoa.GetSize(); iDesktop++)
   {
      ShowDesktopWindowInfo(m_infoa[iDesktop], bShow);
   }
}

   

void DesktopView::GetDesktopWindowInfo(int iDesktop, DesktopWindowInfo & info)
{
   if(iDesktop == m_iDesktop)
   {
      GetDesktopWindowInfo(info);
      m_infoa[iDesktop] = info;
   }
   else
   {
      FilterDesktopWindowInfo(m_infoa[iDesktop]);
      info = m_infoa[iDesktop];
   }
}

void DesktopView::GetDesktopWindowInfo(DesktopWindowInfo & info)
{
   info.RemoveAll();
   HWND hwndDesktop = ::GetDesktopWindow();

   HWND hwndFirst = ::GetNextWindow(hwndDesktop, GW_CHILD);

   HWND hwndFrame = GetParentFrame()->GetSafeHwnd();

   TCHAR szModule[2048];
   TCHAR szClassName[2048];
   HWND hwnd = hwndFirst;
   int i = 1;
   String strNumber;
   WNDCLASS wndclass;
   DWORD dwThreadId;
   DWORD dwProcessId;
   String strClassName;
   HINSTANCE hinstance;
   BOOL bGetClassInfo;
   HMODULE hmodule;
   while(hwnd != NULL)
   {
      bGetClassInfo = false;
      hmodule = NULL;
      base_wnd * pwnd = base_wnd::FromHandle(hwnd);
      ::GetClassName(hwnd, szClassName, sizeof(szClassName));
      dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
      HICON hicon = pwnd->GetIcon(FALSE);
      if(hicon == NULL)
      {
         hicon = pwnd->GetIcon(TRUE);
      }
      int iStyle = pwnd->GetStyle();
      int iStyleEx = pwnd->GetExStyle();
      if((iStyle & WS_VISIBLE)
        && !(iStyleEx & WS_EX_TOOLWINDOW)
        && hwnd != hwndFrame
        &&((iStyleEx & WS_EX_APPWINDOW)
        || (!(iStyle & WS_CHILD)
        && pwnd->GetOwner() == NULL)))
      {
         DesktopWindow window;
         window.m_hwnd = hwnd;
         window.m_hicon = hicon;
         info.Add(window);
      }
      hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);
   }
}

void DesktopView::FilterDesktopWindowInfo(DesktopWindowInfo & info)
{
   for(int i = 0; i < info.GetSize();)
   {
      if(!::IsWindow(info[i].m_hwnd))
      {
         info.RemoveAt(i);
      }
      else
      {
         i++;
      }
   }
  
}

void DesktopView::ShowDesktopWindowInfo(DesktopWindowInfo & info, bool bShow)
{
   for(int i = 0; i < info.GetSize();)
   {
      if(::IsWindow(info[i].m_hwnd))
      {
         if(bShow)
         {
            ::ShowWindow(info[i].m_hwnd, SW_SHOW);
         }
         else
         {
            ::ShowWindow(info[i].m_hwnd, SW_HIDE);
         }
         i++;
      }
      else
      {
         info.RemoveAt(i);
      }
   }
  
}

void DesktopView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;



   SetTimer(gen::Timer::ID_HOVER, 100, NULL);

   m_tab.AddIconTab(IDS_KARAOKEVIEW_TAB_MENU, IDI_CONTEXT_MENU);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_KARAOKE);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_OPEN);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_PLAYLIST);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_ALBUM);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_OPTIONS);
   m_tab.AddTab(IDS_KARAOKEVIEW_TAB_AUDIOCONTROL);

   m_tab._001SetSel(1);

   m_tab.m_pcallback = this;





}

int DesktopView::InitGL()
{
/*	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
	glEnable(GL_LIGHTING);								// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);						// Enable Coloring Of Material

	BuildFont();										// Build The Font*/

	return TRUE;										// Initialization Went OK

}


void DesktopView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   CPoint point = pcontextmenu->GetPoint();
	
}



void DesktopView::_001OnTabClick(int iTab)
{
   PaneView * pview = GetParentPane();
   
   if(pview != NULL)
   {
      EPaneView eview = PaneViewNone;
      switch(iTab)
      {
      case 0:
         eview = PaneViewContextMenu;
         break;
      case 1:
         eview = PaneViewDesktop;
         break;
      case 2:
         eview = PaneViewOptions;
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      pview->ShowView(eview);
   }
}



DWORD DesktopView::CommandToCodePage(UINT uiID)
{
   DesktopApp * papp = (DesktopApp *) AfxGetApp();
   return papp->CommandToCodePage(uiID);
}

void DesktopView::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
   if(key == VMSDATAKEY(KaraokeEncoding))
   {
      RedrawWindow();
   }
   else if(key == VMSDATAKEY(GlobalLyricsDelay))
   {     
      VmsDataGet(VMSDATAKEY(GlobalLyricsDelay), 0, 0, m_iDelay);
   }
}


LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{

 

    HKEY hkey;

 

    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

 

 

 

    if (retval == ERROR_SUCCESS) {

 

        long datasize = MAX_PATH;

 

        TCHAR data[MAX_PATH];

 

        RegQueryValue(hkey, NULL, data, &datasize);

 

        lstrcpy(retdata,data);

 

        RegCloseKey(hkey);

 

    }

 

 

 

    return retval;

 

}

 

 

void URLOpenNew(LPCTSTR lpcsz)

{

   TCHAR key1[MAX_PATH + MAX_PATH];
   TCHAR key2[MAX_PATH + MAX_PATH];
   TCHAR key3[MAX_PATH + MAX_PATH];

   if(GetRegKey(HKEY_CLASSES_ROOT, _T(".html"), key1) != ERROR_SUCCESS)
      if(GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key1) != ERROR_SUCCESS)
         return;

   lstrcpy(key2, key1);
   lstrcat(key2, _T("\\shell\\opennew\\command"));

   if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
   {
      lstrcpy(key2, key1);
      lstrcat(key2, _T("\\shell\\open\\command"));
      if(GetRegKey(HKEY_CLASSES_ROOT, key2, key3) != ERROR_SUCCESS)
      {
         return;
      }
   }

   String str(key3);

   str.Replace("%1", lpcsz);

   WinExec(str,SW_SHOW);

        
}

void DesktopView::_001OnOpenLinkInNewWindow(gen::signal_object * pobj) 
{
   ASSERT(!m_wstrCurrentLink.IsEmpty());	
   String str;
   International::UnicodeToACP(str, m_wstrCurrentLink);
   //::ShellExecute(m_hWnd, _T("opennew"), str, NULL, NULL, SW_RESTORE);
   URLOpenNew(str);
	
}

void DesktopView::OnLinkClick(WString &wstrLink)
{
   ASSERT(!wstrLink.IsEmpty());	
   String str;
   International::UnicodeToACP(str, wstrLink);
   ::ShellExecute(m_hWnd, _T("open"), str, NULL, NULL, SW_RESTORE);
}

void DesktopView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}

HCURSOR DesktopView::KaraokeGetHandCursor()
{
   return AfxGetApp()->LoadCursor(IDC_HAND_POINTER);
}

void DesktopView::_001OnCopyLinkLocation(gen::signal_object * pobj) 
{
   if (!OpenClipboard())
   {
      AfxMessageBox( "Cannot open the Clipboard" );
      return;
   }
   
   // Remove the current Clipboard contents
   if(!EmptyClipboard())
   {
      AfxMessageBox( "Cannot empty the Clipboard" );
      CloseClipboard();
      return;
   }
   String str;
   International::UnicodeToACP(str, m_wstrCurrentLink);

   HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 
            (str.GetLength() + 1) * sizeof(TCHAR)); 
        if (hglbCopy == NULL) 
        { 
            CloseClipboard(); 
            return; 
        } 
 
        // Lock the handle and copy the text to the buffer. 
 
        LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy); 
        memcpy(lptstrCopy, (LPCTSTR) str, 
            str.GetLength() * sizeof(TCHAR)); 
        lptstrCopy[str.GetLength()] = (TCHAR) 0;    // null character 
        GlobalUnlock(hglbCopy); 
   // ...
   // Get the currently selected data
   // ...
   // For the appropriate data formats...
   if ( ::SetClipboardData( CF_TEXT, hglbCopy ) == NULL )
   {
      AfxMessageBox( "Unable to set Clipboard data" );
      CloseClipboard();
      return;
   }
   // ...
   CloseClipboard();	
}

int DesktopView::KaraokeGetLyricsDelay()
{
   return m_iDelay;
}

Ex1VirtualGuieContainer * DesktopView::Create(int i)
{
   if(i == 1)
   {
   }
   return NULL;
}

PaneView * DesktopView::GetParentPane()
{
   base_wnd * pwnd = GetParent();
   if(pwnd->IsKindOf(RUNTIME_CLASS(PaneView)))
   {
      return dynamic_cast < PaneView * > (pwnd);
   }
   return NULL;
}






void DesktopView::OnSetScalar(int i, double d)
{
}
double DesktopView::GetMinScalar(int i)
{
   if(i == m_iPos)
   {
      return 0.0;
   }
   else
   {
      ASSERT(FALSE);
   }
}
double DesktopView::GetScalar(int i)
{
   return 0.0;
}
double DesktopView::GetMaxScalar(int i)
{
   return 0.0;
   
}


void DesktopView::OnSetScalar(int i, int iValue)
{
}
void DesktopView::GetMinScalar(int i, int & iValue)
{
}
void DesktopView::GetScalar(int i, int & iValue)
{
}
void DesktopView::GetMaxScalar(int i, int & iValue)
{
}


void DesktopView::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
}

void DesktopView::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);

   int iDesktop, iWindow;
   HitTest(pmouse->m_pt, iDesktop, iWindow);

   if(iDesktop >= 0)
   {
      if(iWindow == -1)
      {
         if(m_iActiveItemDesktop >= 0)
         {
            if(m_iActiveItemDesktop != iDesktop)
            {
               m_infoa[iDesktop].Add(m_infoa[m_iActiveItemDesktop][m_iActiveItemWindow]);
               m_infoa[m_iActiveItemDesktop].RemoveAt(m_iActiveItemWindow);
               if(m_iActiveItemDesktop == m_iDesktop)
               {
                  ::ShowWindow(m_infoa[iDesktop].LastElement().m_hwnd, SW_HIDE);
               }
               else if(m_iDesktop == iDesktop)
               {
                  ::ShowWindow(m_infoa[iDesktop].LastElement().m_hwnd, SW_SHOW);
               }
            }
         }
         else
         {
            ChangeDesktop(iDesktop);
         }
         m_iActiveItemDesktop = -1;
         m_iActiveItemWindow = -1;
      }
      else
      {
         m_iActiveItemDesktop = iDesktop;
         m_iActiveItemWindow = iWindow;
      }
   }
   else
   {
      m_iActiveItemDesktop = -1;
      m_iActiveItemWindow = -1;
   }
   _001RedrawWindow();

}

void DesktopView::_001OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   int iDesktop, iWindow;
   HitTest(pmouse->m_pt, iDesktop, iWindow);

   if(iWindow == -1)
   {
      m_iHoverDesktopButton = iDesktop;
   }
   else
   {
      m_iHoverDesktopButton = -1;
   }

   _001RedrawWindow();

}

void DesktopView::HitTest(CPoint pt, int & iDesktop, int & iWindow)
{
   bool bDesktopButton = HitTest(pt, iDesktop);
   if(iDesktop == -1 || bDesktopButton)
   {
      iWindow = -1;
      return;
   }
   DesktopWindowInfo info;
   GetDesktopWindowInfo(iDesktop, info);
   BaseRect rect;
   for(int i = 0; i < info.GetSize(); i++)
   {
      GetRect(rect, iDesktop, i);
      if(pt.y >= rect.top && pt.y <= rect.bottom)
      {
         iWindow = i;
         return;
      }
   }
   iWindow = -1;
   iDesktop = -1;
}

bool DesktopView::HitTest(CPoint pt, int & iDesktop)
{
   BaseRect rect;
   for(int i = 0; i < 2; i++)
   {
      GetRect(rect, i, -1);
      if(pt.x >= rect.left && pt.x <= rect.right)
      {
         iDesktop = i;
         return rect.PtInRect(pt);
      }
   }
   iDesktop = -1;
}

void DesktopView::GetRect(LPRECT lprect, int iDesktop, int iWindow)
{
   if(iDesktop < 0 || iDesktop > 1)
      return;
   if(iWindow < -1)
      return;
   *lprect = m_desktopa[iDesktop].m_rectButton;
   if(iWindow == -1)
      return;

   lprect->top    = m_iListTop + m_iListItemHeight * iWindow;
   lprect->bottom = lprect->top + m_iListItemHeight;
}

void DesktopView::OnDraw(CDC * pdc)
{
}

base_wnd * DesktopView::BackViewGetWnd()
{
   return this;
}

void DesktopView::_001OnAppMessage(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj);

   if(pbase->m_wparam == 1)
   {
      ChangeDesktop(pbase->m_lparam);
   }

}

void DesktopView::ChangeDesktop(int iDesktop)
{
   if(iDesktop < 0)
      return;
   if(iDesktop >= m_desktopa.GetSize())
      return;
   if(iDesktop != m_iDesktop)
   {
      GetDesktopWindowInfo(m_infoa[m_iDesktop]);
      ShowDesktopWindowInfo(m_infoa[m_iDesktop], false);
      m_iDesktop = iDesktop;
      ShowDesktopWindowInfo(m_infoa[m_iDesktop], true);
      GetParentFrame()->BringWindowToTop();
   }
}
