#include "StdAfx.h"
#include "OptionsDialog.h"
#include "OptionsImagesDirectoriesDialog.h"
#include "OptionsGeneralDialog.h"
#include "OptionsImagesDialog.h"
#include "OptionsAudioDevicesDialog.h"



OptionsDialog::OptionsDialog(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   dialog(papp)
{

   m_pImagesDlg = NULL;
   m_pdlgGeneral = NULL;
   m_pImagesDirsDlg = NULL;
   m_pAudioDevsDlg = NULL;

}

OptionsDialog::~OptionsDialog()
{
      if(m_pImagesDlg != NULL)
   {
      delete m_pImagesDlg;
      m_pImagesDlg = NULL;
   }
   if(m_pdlgGeneral != NULL)
   {
      delete m_pdlgGeneral;
      m_pdlgGeneral = NULL;
   }
   if(m_pImagesDirsDlg != NULL)
   {
      delete m_pImagesDirsDlg;
      m_pImagesDirsDlg = NULL;
   }
   if(m_pAudioDevsDlg != NULL)
   {
      delete m_pAudioDevsDlg;
      m_pAudioDevsDlg = NULL;
   }

}

/*
void OptionsDialog::DoDataExchange(CDataExchange* pDX)
{
//   dialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(OptionsDialog)
   //DDX_Control(pDX, IDC_TAB, m_Tab);
   //}}AFX_DATA_MAP
}
*/

void OptionsDialog::OnSelchangingTab(NMHDR* , LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
   
   *pResult = 0;

/*   int index = m_Tab.get_cur_sel();
   switch(index)
   {
   case 0:
      if(!m_pdlgGeneral->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pdlgGeneral->ShowWindow(SW_HIDE);
      break;
   case 1:
      if(!m_pImagesDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pImagesDlg->ShowWindow(SW_HIDE);
      break;
   case 2:
      if(!m_pImagesDirsDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pImagesDirsDlg->ShowWindow(SW_HIDE);
      break;
   case 3:
      if(!m_pAudioDevsDlg->UpdateData())
         *pResult = TRUE;
      if(!*pResult)
         m_pAudioDevsDlg->ShowWindow(SW_HIDE);
      break;
   default:
      break;
   }
*/
}

//void OptionsDialog::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
void OptionsDialog::OnSelchangeTab(NMHDR* , LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
/*   int index = m_Tab.get_cur_sel();
   switch(index)
   {
   case 0:
      m_pdlgGeneral->UpdateData(FALSE);
      m_pdlgGeneral->ShowWindow(SW_SHOW);
      break;
   case 1:
      m_pImagesDlg->UpdateData(FALSE);
      m_pImagesDlg->ShowWindow(SW_SHOW);
      break;
   case 2:
      m_pImagesDirsDlg->UpdateData(FALSE);
      m_pImagesDirsDlg->ShowWindow(SW_SHOW);
      break;
   case 3:
      m_pAudioDevsDlg->UpdateData(FALSE);
      m_pAudioDevsDlg->ShowWindow(SW_SHOW);
      break;
   default:
      break;
   }
*/   
   *pResult = 0;
}

BOOL OptionsDialog::OnInitDialog() 
{
//   dialog::OnInitDialog();
   
    string str;

    throw not_implemented_exception();
   /*// TODO: add extra initialization here
    str.load_string(IDS_OPTIONS_SONGSFOLDER);
//   m_Tab.InsertItem(0, str);

    str.load_string(IDS_OPTIONS_GENERAL);
//    m_Tab.InsertItem(1, str);
   // linux
    str.load_string(IDS_OPTIONS_IMAGES);
   //m_Tab.InsertItem(2, str);

    str.load_string(IDS_OPTIONS_IMAGESFOLDERS);
   //m_Tab.InsertItem(3, str);

    str.load_string(IDS_OPTIONS_AUDIODEVICES);
    //m_Tab.InsertItem(4, str);
*/

   m_pImagesDlg = new OptionsSongsImagesDialog(get_app());
   m_pdlgGeneral = new OptionsSongsGeneralDialog(get_app());
   m_pImagesDirsDlg = new OptionsSongsImagesDirectoriesDialog(get_app());
   m_pAudioDevsDlg = new OptionsSongsAudioDevicesDialog(get_app());
    
//   HMODULE hmoduleOld = AfxGetResourceHandle();

/*   m_pImagesDlg->create(IDD_OPTIONS_IMAGES, &m_Tab);
   m_pdlgGeneral->create(IDD_OPTIONS_GENERAL, &m_Tab);

   m_pImagesDirsDlg->create(IDD_OPTIONS_IMAGES_DIRECTORIES, &m_Tab);
   m_pAudioDevsDlg->create(&m_Tab);*/
//   b = IsWindow(m_pPrincipalView->m_hWnd);
//   b = IsWindow(m_pContatosView->m_hWnd);
   //RECT tabRect;
   //RECT parentRect;
   //RECT parentClientRect;
   RECT rect;
   //m_Tab.GetWindowRect(&tabRect);
   //GetWindowRect(&parentRect);
   //GetClientRect(&parentClientRect);
   //::ca::graphics * pgraphics = GetDC();
   //point clientOrg = pgraphics->GetWindowOrg();
   //ReleaseDC(pgraphics);
   rect.left = 1;
   rect.top = 1;
   rect.right = 2; // not used
   rect.bottom = 2; // not used
   
//   m_Tab.AdjustRect(FALSE, &rect);
/*   m_pdlgGeneral->SetWindowPos
      (ZORDER_TOP,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pImagesDlg->SetWindowPos
      (ZORDER_TOP,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pImagesDirsDlg->SetWindowPos
      (ZORDER_TOP,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);
   m_pAudioDevsDlg->SetWindowPos
      (ZORDER_TOP,
       rect.left,
       rect.top,
       0,
       0,
       SWP_NOSIZE);*/
   /*m_pImagesDirsDlg->Update(FALSE);
   m_pdlgGeneral->Update(FALSE);
   m_pImagesDlg->Update(FALSE);
   m_pAudioDevsDlg->Update(FALSE);*/
   //m_Tab._001SetSel(0);
   NMHDR NMHDR;
//   NMHDR.hwndFrom = m_Tab._get_handle();
//   NMHDR.idFrom = IDC_TAB;
   NMHDR.code = TCN_SELCHANGE;
   //b = IsWindow(m_hWnd);
//   this->SendMessage(WM_NOTIFY, IDC_TAB , (LPARAM) &NMHDR);
//   Update(FALSE);
/*   CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);*/
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}


void OptionsDialog::OnOK() 
{
   // TODO: add extra validation here
    if(Apply())
   {
//      dialog::OnOK();
   }
}

BOOL OptionsDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   
   //return dialog::PreCreateWindow(cs);
   return TRUE;
}

bool OptionsDialog::Apply()
{
   bool bImagesDirsModified = m_pImagesDirsDlg->is_modified();
    bool bAudioDevsModified = m_pAudioDevsDlg->is_modified();
   if(!m_pdlgGeneral->Update())
      return false;

   if(!m_pImagesDlg->Update())
      return false;
   if(bImagesDirsModified)
   {
      if(!m_pImagesDirsDlg->Update())
         return false;
   }
    if(bAudioDevsModified)
    {
        m_pAudioDevsDlg->Update();

    }

   vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);
   stringa strArray;

/*   pApp->m_iBackgroundUpdateMillis = m_pImagesDlg->m_iChangeTime * 1000;
    CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);
    pApp->UpdateMRU(m_pdlgGeneral->m_bMRUEnable, m_pdlgGeneral->m_iMRUCount);*/
   return true;
}

void OptionsDialog::OnApply() 
{
   // TODO: add your control notification handler code here
   Apply();
}

void OptionsDialog::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   // TODO: add your specialized code here and/or call the base class
   if(pbase->m_uiMessage == WM_USER)
    {
//        if(pMsg->hwnd = _get_handle())
        {
            if(pbase->m_wparam == 1000)
            {
/*                CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
                pApply->EnableWindow(TRUE);*/
            }
        }
    }
   //return dialog::pre_translate_message(pMsg);
   //return FALSE;
}

void OptionsDialog::OnDestroy() 
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
