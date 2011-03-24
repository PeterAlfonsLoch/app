#include "StdAfx.h"
#include "AlbumOptionsDialog.h"


AlbumOptionsDialog::AlbumOptionsDialog(::ca::application * papp) :
   ca(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
   form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   dialog(papp)
{
   m_pSongsDirsDlg = NULL;
}


AlbumOptionsDialog::~AlbumOptionsDialog()
{
}

/*
void AlbumOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
//   dialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AlbumOptionsDialog)
   //DDX_Control(pDX, IDC_TAB, m_tab);
   //}}AFX_DATA_MAP
}
*/

void AlbumOptionsDialog::OnSelchangingTab(NMHDR* , LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
   
   *pResult = 0;

//   int index = m_tab._001GetSel();
   int index = -1;
   switch(index)
   {
   case 0:
/*      if(!m_pSongsDirsDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pSongsDirsDlg->ShowWindow(SW_HIDE);
      break;*/
   case 1:
/*      if(!m_pdlgGeneral->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pdlgGeneral->ShowWindow(SW_HIDE);
      break;
   case 2:
      if(!m_pImagesDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pImagesDlg->ShowWindow(SW_HIDE);
      break;
   case 3:
      if(!m_pImagesDirsDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pImagesDirsDlg->ShowWindow(SW_HIDE);
      break;
   case 4:
      if(!m_pAudioDevsDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pAudioDevsDlg->ShowWindow(SW_HIDE);
      break;*/
   default:
      break;
   }

}

//void AlbumOptionsDialog::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
void AlbumOptionsDialog::OnSelchangeTab(NMHDR* , LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
   //int index = m_tab._001GetSel();
   int index = -1;
   switch(index)
   {
   case 0:
      
/*      m_pSongsDirsDlg->UpdateData(FALSE);
      m_pSongsDirsDlg->ShowWindow(SW_SHOW);*/
      break;
   case 1:
/*      m_pdlgGeneral->UpdateData(FALSE);
      m_pdlgGeneral->ShowWindow(SW_SHOW);
      break;
   case 2:
      m_pImagesDlg->UpdateData(FALSE);
      m_pImagesDlg->ShowWindow(SW_SHOW);
      break;
   case 3:
      m_pImagesDirsDlg->UpdateData(FALSE);
      m_pImagesDirsDlg->ShowWindow(SW_SHOW);
      break;
   case 4:
      m_pAudioDevsDlg->UpdateData(FALSE);
      m_pAudioDevsDlg->ShowWindow(SW_SHOW);*/
      break;
   default:
      break;
   }
   
   *pResult = 0;
}

bool AlbumOptionsDialog::_001Initialize() 
{
   // linux dialog::OnInitDialog();
   
    string str;

    throw not_implemented_exception();
   // TODO: add extra initialization here
//    str.load_string(IDS_OPTIONS_SONGSFOLDER);
   // linux m_tab.add_tab(0, str);

//    str.load_string(IDS_OPTIONS_GENERAL);
 //   m_tab.InsertItem(1, str);

   // str.load_string(IDS_OPTIONS_IMAGES);
   //m_tab.InsertItem(2, str);

    //str.load_string(IDS_OPTIONS_IMAGESFOLDERS);
   //m_tab.InsertItem(3, str);

    //str.load_string(IDS_OPTIONS_AUDIODEVICES);
    //m_tab.InsertItem(4, str);


//   m_pImagesDlg = new COptionsImagesDialog();
//   m_pSongsDirsDlg = new COptionsSongsDirectoriesDialog();
  //  m_pdlgGeneral = new COptionsGeneralDialog();
   //m_pImagesDirsDlg = new COptionsImagesDirectoriesDialog();
    //m_pAudioDevsDlg = new COptionsAudioDevicesDialog();
   //m_pSongsDirsPlg->m_pSet = m_pSet;
//   BOOL b = IsWindow(m_pPrincipalView->m_hWnd);
//   b = IsWindow(m_pContatosView->m_hWnd);
    
//   HMODULE hmoduleOld = AfxGetResourceHandle();
  //  AfxSetResourceHandle(GetModuleHandle("vmsgui"));
//   m_pSongsDirsDlg->create(&m_tab);
    //AfxSetResourceHandle(hmoduleOld);

    //m_pImagesDlg->create(IDD_OPTIONS_IMAGES, &m_tab);
    //m_pdlgGeneral->create(IDD_OPTIONS_GENERAL, &m_tab);

   //m_pImagesDirsDlg->create(IDD_OPTIONS_IMAGES_DIRECTORIES, &m_tab);
    //m_pAudioDevsDlg->create(&m_tab);
//   b = IsWindow(m_pPrincipalView->m_hWnd);
//   b = IsWindow(m_pContatosView->m_hWnd);
   //RECT tabRect;
   //RECT parentRect;
   //RECT parentClientRect;
   RECT rect;
   //m_tab.GetWindowRect(&tabRect);
   //GetWindowRect(&parentRect);
   //GetClientRect(&parentClientRect);
   //::ca::graphics * pgraphics = GetDC();
   //point clientOrg = pgraphics->GetWindowOrg();
   //ReleaseDC(pgraphics);
   rect.left = 1;
   rect.top = 1;
   rect.right = 2; // not used
   rect.bottom = 2; // not used
   
//   bool bIsWindow = ::IsWindow(m_pSongsDirsDlg->m_hWnd);
//   if(bIsWindow)
//   {
//   m_pSongsDirsDlg->MapDialogRect(&rect);
//   }
//   rect.left = rect.left + tabRect.left + parentClientRect.right - parentRect.right;
//   rect.top = rect.top + tabRect.top + parentClientRect.bottom - parentRect.bottom;
   // linux m_tab.AdjustRect(FALSE, &rect);
/*   m_pSongsDirsDlg->SetWindowPos
      (&wndTop,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);*/
   /*m_pdlgGeneral->SetWindowPos
      (&wndTop,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pImagesDlg->SetWindowPos
      (&wndTop,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pImagesDirsDlg->SetWindowPos
      (&wndTop,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pAudioDevsDlg->SetWindowPos
      (&wndTop,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);*/
   //m_pImagesDirsDlg->Update(FALSE);
//   m_pSongsDirsDlg->Update(FALSE);
    //m_pdlgGeneral->Update(FALSE);
   //m_pImagesDlg->Update(FALSE);
    //m_pAudioDevsDlg->Update(FALSE);
   // m_tab._001SetSel(0);
   NMHDR NMHDR;
//   NMHDR.hwndFrom = m_tab._get_handle();
   //NMHDR.idFrom = IDC_TAB;
   NMHDR.code = TCN_SELCHANGE;
   //b = IsWindow(m_hWnd);
//   this->SendMessage(WM_NOTIFY, IDC_TAB , (LPARAM) &NMHDR);
//   Update(FALSE);
/* linux    CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);*/
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}


void AlbumOptionsDialog::OnOK() 
{
   // TODO: add extra validation here
    if(!Apply())
      return;
// linux   dialog::OnOK();
}

BOOL AlbumOptionsDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   
//   return dialog::PreCreateWindow(cs);
   return FALSE;
}

bool AlbumOptionsDialog::Apply()
{
/*   if(!m_pSongsDirsDlg->Apply())
      return false;*/
   return true;
}

void AlbumOptionsDialog::OnApply() 
{
   // TODO: add your control notification handler code here
   Apply();
}

void AlbumOptionsDialog::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   // TODO: add your specialized code here and/or call the base class
   if(pbase->m_uiMessage == WM_USER)
    {
//        if(pMsg->hwnd = _get_handle())
        {
            if(pbase->m_wparam == 1000)
            {
/* linux                CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
                pApply->EnableWindow(TRUE); */
            }
        }
    }
//   return dialog::pre_translate_message(pMsg);
   //return FALSE;
}

void AlbumOptionsDialog::OnDestroy() 
{
//   dialog::OnDestroy();
   
//      if(m_pSongsDirsDlg != NULL)
//      m_pSongsDirsDlg->DestroyWindow();
//   if(m_pImagesDirsDlg != NULL)
//      m_pImagesDirsDlg->DestroyWindow();
//   if(m_pImagesDlg != NULL)
//      m_pImagesDlg->DestroyWindow();

   // TODO: add your message handler code here
}

BOOL AlbumOptionsDialog::create(AlbumOptionsDialog ** pp)

{
   m_pp = pp;
// linux   return dialog::create(IDD);

   return FALSE;
}

void AlbumOptionsDialog::OnClose() 
{

//    dialog::OnClose();

//    DestroyWindow();

}

void AlbumOptionsDialog::PostNcDestroy() 
{
   // TODO: add your specialized code here and/or call the base class
   
//   dialog::PostNcDestroy();
   *m_pp = NULL;

    delete this;
}
