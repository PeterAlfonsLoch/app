#include "StdAfx.h"
#include "ErrorDialog.h"


CErrorDialog::CErrorDialog(::ca::application * papp) :
   ca(papp),
   scroll_view(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   form(papp),
   html_form_view(papp),
   form_view(papp),
   dialog(papp)
{
}


void CErrorDialog::Initialize(midi_exception * pMidiException)
{
   m_pMidiException = pMidiException;
}

BOOL CErrorDialog::OnInitDialog() 
{
   //dialog::OnInitDialog();

/*   linux CStatic * pImage = (CStatic *) GetDlgItem(IDC_STATIC_IMAGE);
   ::ca::window * pWndText = GetDlgItem(IDC_STATIC_TEXT);
   user::edit_plain_text * pEditAdvanced = (user::edit_plain_text *) GetDlgItem(IDC_EDIT_ADVANCED);
   
   if(m_pMidiException != NULL)
   {
      HICON hIcon = ::LoadIcon(NULL, IDI_EXCLAMATION);
      pImage->SetIcon(hIcon);
      pWndText->SetWindowText(m_pMidiException->GetUserText());
      pEditAdvanced->SetWindowText(m_pMidiException->GetDetailsText());
   }
   // TODO: add extra initialization here*/
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}
