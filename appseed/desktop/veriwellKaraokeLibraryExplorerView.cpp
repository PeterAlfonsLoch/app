// veriwellKaraokeLibraryExplorerView.cpp : implementation file
//

#include "stdafx.h"
#include "PaneView1.h"

#include "veriwellKaraokeLibraryExplorerTreeView.h"
#include "veriwellKaraokeLibraryExplorerView.h"
#include "veriwellKaraokeLibraryListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerView

IMPLEMENT_DYNCREATE(veriwellKaraokeLibraryExplorerView, BaseSplitView)

veriwellKaraokeLibraryExplorerView::veriwellKaraokeLibraryExplorerView()
{
   m_pinetsession = NULL;
   IGUI_WIN_MSG_LINK(WM_CREATE, this, this, &veriwellKaraokeLibraryExplorerView::_001OnCreate);
}

veriwellKaraokeLibraryExplorerView::~veriwellKaraokeLibraryExplorerView()
{
   if(m_pinetsession != NULL)
      delete m_pinetsession;
}


BEGIN_MESSAGE_MAP(veriwellKaraokeLibraryExplorerView, BaseSplitView)
	//{{AFX_MSG_MAP(veriwellKaraokeLibraryExplorerView)
   /*
	ON_WM_CREATE()
   */
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerView drawing

void veriwellKaraokeLibraryExplorerView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerView diagnostics

#ifdef _DEBUG
void veriwellKaraokeLibraryExplorerView::AssertValid() const
{
	BaseSplitView::AssertValid();
}

void veriwellKaraokeLibraryExplorerView::Dump(CDumpContext& dc) const
{
	BaseSplitView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerView message handlers

void veriwellKaraokeLibraryExplorerView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
}

void veriwellKaraokeLibraryExplorerView::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(OrientationVertical);
  
   SetPosition(0, 200);

   

   CreateContext cc;
   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(veriwellKaraokeLibraryExplorerTreeView);

   m_ptree = dynamic_cast < veriwellKaraokeLibraryExplorerTreeView * > (PaneView::CreateView(&cc, 100, this));

   m_ptree->m_pserver = this;

   SetPane(0, m_ptree, false);

   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(veriwellKaraokeLibraryListView);

   m_plist = dynamic_cast < veriwellKaraokeLibraryListView * > (PaneView::CreateView(&cc, 101, this));

   m_plist->m_pserver = this;

   SetPane(1, m_plist, false);

   Layout();

}

void veriwellKaraokeLibraryExplorerView::Start()
{
   m_pinetsession = new CInternetSession;

   CHttpFile * pfile = (CHttpFile *) m_pinetsession->OpenURL(
      "http://karaoke.veriwell.com.br/vmplightfolder.php");

   String str;
   String strLine;
   while(pfile->ReadString(strLine))
   {
      str += strLine;
      str += "\n";
      TRACE(str);
   }

   m_ptree->Parse(NULL, str);
   m_plist->Parse(str);


}


void veriwellKaraokeLibraryExplorerView::Request(LPCTSTR lpsz)
{
   String strId;

   strId = lpsz;

   String strURL;

   strURL = "http://karaoke.veriwell.com.br/vmplightfolder.php";

   strURL += "?id=" + strId;

   CHttpFile * pfile = (CHttpFile *) m_pinetsession->OpenURL(
      strURL);

   String str;
   String strLine;
   while(pfile->ReadString(strLine))
   {
      str += strLine;
      str += "\n";
      TRACE(strLine);
   }

   m_ptree->Parse(lpsz, str);
   m_plist->Parse(str);

}

void veriwellKaraokeLibraryExplorerView::OpenSongFile(
   int iId,
   LPCTSTR lpszFileName)
{
   DesktopApp * papp = (DesktopApp *) AfxGetApp();

   String strURL;

   strURL.Format("http://karaoke.veriwell.com.br/get/download.php?p_songid=%d", iId);
   CHttpFile * pfile = (CHttpFile *) m_pinetsession->OpenURL(
      strURL, 1, INTERNET_FLAG_TRANSFER_BINARY);

   String wstrPath;
   if(!win::SHGetSpecialFolderPath(
      NULL,
      wstrPath,
      CSIDL_PERSONAL,
      TRUE))
      return;
   wstrPath += "\\veriwell.com.br";
   if(win::GetFileAttributes(wstrPath) == -1)
   {
      if(!win::CreateDirectory(wstrPath, NULL))
      {
         return;
      }
      if(win::GetFileAttributes(wstrPath) == -1)
      {
         return;
      }
   }
   wstrPath += L"\\karaoke files";
   if(win::GetFileAttributes(wstrPath) == -1)
   {
      if(!win::CreateDirectory(wstrPath, NULL))
      {
         return;
      }
      if(win::GetFileAttributes(wstrPath) == -1)
      {
         return;
      }
   }
   wstrPath += "\\";
   wstrPath += lpszFileName;

   Ex1File file;

   file.Open(wstrPath, _File::typeBinary | _File::modeWrite | _File::modeCreate);

   BYTE buf[1024];
   int iRead;
   do
   {
      iRead = pfile->Read(&buf, sizeof(buf));
      file.Write(&buf, iRead);
   }
   while(iRead > 0);

   file.Close();

   PlaylistDoc * pdoc = papp->GetPlaylistCentral().GetCurrentPlaylist(true, false);
   if(pdoc != NULL)
   {
      pdoc->AddSong(
         wstrPath,
         PlaylistDoc::AddSongAndPlayIfNotPlaying, 
         false,
         true);
   }
}
