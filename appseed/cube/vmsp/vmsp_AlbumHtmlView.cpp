#include "StdAfx.h"
#include "AlbumHtmlView.h"


AlbumHtmlView::AlbumHtmlView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp), 
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_view(papp)
{
   //{{AFX_DATA_INIT(AlbumHtmlView)
      // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
//    m_pSongsSet = new CDBSongSet(DBDataCentral());
    TRACE("AlbumHtmlView this = %x \n", this);
}

AlbumHtmlView::~AlbumHtmlView()
{
//    if(m_pSongsSet != NULL)
  //      delete m_pSongsSet;
}

//void AlbumHtmlView::DoDataExchange(CDataExchange* pDX)
//{
//   html_view::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AlbumHtmlView)
      // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
//}


 // BEGIN_MESSAGE_MAP(AlbumHtmlView, html_view)
   //{{AFX_MSG_MAP(AlbumHtmlView)
   /*ON_WM_CREATE()
   ON_COMMAND(ID_GOBACK, OnGoback)
   ON_COMMAND(ID_GOFORWARD, OnGoforward)
   ON_COMMAND(ID_GOHOME, OnGohome)
   ON_UPDATE_COMMAND_UI(ID_GOBACK, OnUpdateGoback)
   ON_UPDATE_COMMAND_UI(ID_GOFORWARD, OnUpdateGoforward)
   ON_UPDATE_COMMAND_UI(ID_GOHOME, OnUpdateGohome)
   ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
   ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
   ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
   ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
   ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
   //}}AFX_MSG_MAP*/
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumHtmlView diagnostics

#ifdef _DEBUG
void AlbumHtmlView::assert_valid() const
{
   html_view::assert_valid();
}

void AlbumHtmlView::dump(dump_context & dumpcontext) const
{
   html_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AlbumHtmlView message handlers

void AlbumHtmlView::OnInitialUpdate() 
{
   //TODO: This code navigates to a popular spot on the web.
   //Change the code to go where you'd like.
   //Navigate2("http://www.microsoft.com/visualc/",NULL,NULL);
//    CVMSApp * pApp = (CVMSApp *) &System;
  //  string strAppFolder = pApp->GetAppFolder();
    char lpszModuleFilePath[MAX_PATH + 1];
   GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
   char lpszModuleFolder[MAX_PATH + 1];
   LPTSTR lpszModuleFileName;
   GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
   string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);

    string strAppFolder = strModuleFolder;
    m_strBasePath = strAppFolder;
    m_strBasePath += "Álbum\\";
   if(System.dir().is(m_strBasePath))
   {
      System.simple_message_box(NULL, "Could not create Album Directory");
   }
   else
   {
      CreateDirectoryEx(strAppFolder, m_strBasePath, NULL);
   }
   //Navigate2(( "about:blank", NULL, NULL, NULL, NULL 
   _GoHome();
}

void AlbumHtmlView::_GoHome()
{
    string strIndexPath;
    strIndexPath = m_strBasePath;
    strIndexPath += "index.html";
    Navigate(strIndexPath);
}

bool AlbumHtmlView::GetGoForwardEnable()
{
    return m_bGoForwardEnable;
}

bool AlbumHtmlView::GetGoBackEnable()
{
    return m_bGoBackEnable;
}


void AlbumHtmlView::OnBeforeNavigate2(html::data * pdata, const char * lpszURL, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel) 
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(lpszTargetFrameName);
   UNREFERENCED_PARAMETER(baPostedData);
   UNREFERENCED_PARAMETER(lpszHeaders);
   // TODO: add your specialized code here and/or call the base class
    char lpszFolder[MAX_PATH + 1];
   LPTSTR lpszFileName;
   GetFullPathName(lpszURL, MAX_PATH + 1, lpszFolder, &lpszFileName);
    string strFileNameParam(lpszFileName);
//    int iSubIndex;
    if(strFileNameParam.Left(5).CompareNoCase("song.")== 0)
    {
        *pbCancel = true;  
        ReserveSong(lpszURL);
        return;
    }
    m_strLastFilePath = m_strFilePath;
    m_strFilePath = lpszURL;
    
    if(strFileNameParam.CompareNoCase("index.html") == 0)
    {
       throw not_implemented_exception();
        //::ca::application * pApp = &System;
/*        HRSRC hmdbFile = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_HTML_ALBUM_INDEX), RT_HTML);
        HGLOBAL hRes = ::LoadResource(AfxGetResourceHandle(), hmdbFile);
         DWORD dwResSize = ::SizeofResource(AfxGetResourceHandle(), hmdbFile);

         if (hRes != NULL)
         {
            UINT FAR* lpnRes = (UINT FAR*)::LockResource(hRes);
            //string szFileName = "Filename.mdb";

            try
            {
               // create the .mdb file
               ex1::filesp f(get_app());
               f->open(lpszURL, ::ex1::file::mode_create | ::ex1::file::mode_write );

               // write the ::fontopus::user-defined resource to the .mdb file
               f->write(lpnRes, dwResSize);
               f->Flush();
            }
            catch(ex1::file_exception_sp * pe)
            {
      #ifdef _DEBUG
             //afxdump << "File could not be opened " << pe->m_cause << "\n";
      #endif
            }
            

      #ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
            ::UnlockResource(hRes);
      #endif
            ::FreeResource(hRes);
         }*/
      
    }
    else
    {
        
        try
        {
        ex1::filesp file(get_app());
        file->open(lpszURL, ::ex1::file::mode_create | ::ex1::file::mode_write);
        if(WriteFile(lpszURL, file)== VMSR_SUCCESS)
        {
            //*pbCancel = true;
        }
        }
        catch(ex1::file_exception_sp * pfe)
        {
         delete pfe;
        }
    }

//   html_view::OnBeforeNavigate2(lpszURL, nFlags,   lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
    
}

VMSRESULT AlbumHtmlView::WriteFile(const char * lpcsz, ex1::filesp & file)
{
   UNREFERENCED_PARAMETER(file);
    char lpszFolder[MAX_PATH + 1];
   LPTSTR lpszFileName;
   GetFullPathName(lpcsz, MAX_PATH + 1, lpszFolder, &lpszFileName);
    string strFileName(lpszFileName);
    if(strFileName.CompareNoCase("index.html") == 0)
        return VMSR_E_FAIL;
//    CVMSApp * pApp = (CVMSApp *) &System;
//    CDataCentral * pDataCentral = pApp->GetDataCentral();
    //spfile->SetLength(0);
//    m_pSongsSet->WriteHtmlFile(lpcsz, file);
    return VMSR_SUCCESS;
}

BOOL AlbumHtmlView::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   cs.dwExStyle |= WS_EX_CLIENTEDGE;
   return html_view::PreCreateWindow(cs);
}

VMSRESULT AlbumHtmlView::ReserveSong(const char * lpcszFilePath)
{
    char lpszFolder[MAX_PATH + 1];
   LPTSTR lpszFileName;
   GetFullPathName(lpcszFilePath, MAX_PATH + 1, lpszFolder, &lpszFileName);
    string strFileNameParam(lpszFileName);
//    int iSubIndex;
//    int iLeafIndex;
    string_tokenizer strTokenizer;
    strTokenizer = strFileNameParam;
    string strTokenA;
    if(!strTokenizer.GetNextToken(strTokenA, ".", FALSE))
    {
        return VMSR_E_FAIL;
    }
    if(strTokenA.CompareNoCase("song") != 0)
    {
        ASSERT(FALSE);
        return VMSR_E_FAIL;
    }
    string strTokenB;
    if(!strTokenizer.GetNextToken(strTokenB, ".", FALSE))
    {
        return VMSR_E_FAIL;
    }
   int iCode = _ttoi(strTokenB);
   ::radix::application *pApp = &System;
   pApp->PostThreadMessage(WM_USER, 21, iCode);
   return VMSR_SUCCESS;
}

void AlbumHtmlView::OnCommandStateChange(long nCommand, BOOL bEnable) 
{
   if(nCommand == CSC_NAVIGATEBACK)
   {
      m_bGoBackEnable = bEnable != 0;
   }
   else if(nCommand == CSC_NAVIGATEFORWARD)
   {
      m_bGoForwardEnable = bEnable != 0;
   }
   //html_view::OnCommandStateChange(nCommand, bEnable);
}

int AlbumHtmlView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
/*   if (html_view::OnCreate(lpCreateStruct) == -1)
      return -1;*/
   // TODO: add your specialized creation code here
   
//    m_oleStreamFile.CreateMemoryStream();

   return 0;
}

void AlbumHtmlView::OnGoback() 
{
   // TODO: add your command handler code here
//   GoBack();
}

void AlbumHtmlView::OnGoforward() 
{
   // TODO: add your command handler code here
//   GoForward();
}

void AlbumHtmlView::OnGohome() 
{
   // TODO: add your command handler code here
   _GoHome();
}

void AlbumHtmlView::OnUpdateGoback(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable(GetGoBackEnable());
}

void AlbumHtmlView::OnUpdateGoforward(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable(GetGoForwardEnable());
}

void AlbumHtmlView::OnUpdateGohome(cmd_ui * pcmdui) 
{
    pcmdui->Enable();
   // TODO: add your command update UI handler code here
//   pcmdui->Enable(    char lpszFolder[MAX_PATH + 1];
//   LPTSTR lpszFileName;
//   GetFullPathName(lpszURL, MAX_PATH + 1, lpszFolder, &lpszFileName);
  //  string strFileNameParam(lpszFileName);

}

void AlbumHtmlView::OnStatusTextChange(const char * lpszText) 
{
   UNREFERENCED_PARAMETER(lpszText);
   // TODO: add your specialized code here and/or call the base class
//   html_view::OnStatusTextChange(lpszText);
}

void AlbumHtmlView::OnDocumentComplete(const char * lpszURL) 
{
   UNREFERENCED_PARAMETER(lpszURL);
   // TODO: add your specialized code here and/or call the base class
//    html_view::OnDocumentComplete(lpszURL);
    try
    {
//        ex1::filesp::remove(m_strLastFilePath);
    }
    catch(ex1::file_exception_sp *pfe)
    {
      delete pfe;
    }
}

void AlbumHtmlView::OnFilePrint() 
{
/*   ExecWB(
      OLECMDID_PRINT,
      OLECMDEXECOPT_DODEFAULT,
      NULL,
      NULL);
*/   
}

void AlbumHtmlView::OnUpdateFilePrint(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}

void AlbumHtmlView::OnFilePrintPreview() 
{
/*   ExecWB(
      OLECMDID_PRINTPREVIEW,
      OLECMDEXECOPT_DODEFAULT,
      NULL,
      NULL);
      */
}

void AlbumHtmlView::OnUpdateFilePrintPreview(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}

void AlbumHtmlView::OnFilePrintSetup() 
{
/*   ExecWB(
      OLECMDID_PAGESETUP,
      OLECMDEXECOPT_DODEFAULT,
      NULL,
      NULL);
      */
}

void AlbumHtmlView::OnUpdateFilePrintSetup(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}
