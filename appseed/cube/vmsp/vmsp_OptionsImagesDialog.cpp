#include "StdAfx.h"
#include "OptionsImagesDialog.h"


OptionsSongsImagesDialog::OptionsSongsImagesDialog(::ca::application * papp) :
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
}


/*
void OptionsSongsImagesDialog::DoDataExchange(CDataExchange* pDX)
{
   //dialog::DoDataExchange(pDX);
/*   DDX::DDXRadio(pDX, IDC_RADIO_SEQUENTIAL, 1, &m_lChangeType);
   DDX::DDXRadio(pDX, IDC_RADIO_RANDOM, 2, &m_lChangeType);
   DDX::DDVEditIntegerRange(pDX, IDC_EDIT_CHANGE_TIME, BACKGROUND_IMAGE_CHANGE_MIN_SECONDS, BACKGROUND_IMAGE_CHANGE_MAX_SECONDS);
   DDX::DDXEdit(pDX, IDC_EDIT_CHANGE_TIME, &m_iChangeTime);*/
   //{{AFX_DATA_MAP(OptionsSongsImagesDialog)
      // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
//}



BOOL OptionsSongsImagesDialog::Update(BOOL bSaveAndValidate)
{
   if(bSaveAndValidate)
   {
//      if(!UpdateData())
//         return FALSE;
      if(!UpdateDatabase())
         return FALSE;
   }
   else
   {
      if(!UpdateDatabase(FALSE))
         return FALSE;
//      if(!UpdateData(FALSE))
//         return FALSE;
   }
   return TRUE;
}

BOOL OptionsSongsImagesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
/*   if(bSaveAndValidate)
   {
      data_set("OptionsSongsImagesDialog", "set", m_set);
   }
   else
   {
      data_get("OptionsSongsImagesDialog", "set", m_set);
      if(m_set["change_type"].get_value().get_type() != var::type_ulong)
         m_set["change_type"] = 1;
      if(m_set["change_time"].get_value().get_type() != var::type_ulong)
         m_set["change_time"] = 30;
   }*/
   return TRUE;
   
/*   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
   }
   return FALSE;*/
}


BOOL OptionsSongsImagesDialog::OnInitDialog() 
{
//   dialog::OnInitDialog();
   
   // TODO: add extra initialization here
   //vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   //db_server *pDataCentral = (db_server *) &System.db();
   //db_long_set *pSet = pDataCentral->get_db_long_set();
   

/*   CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_CHANGE_TIME);
   simple_edit *pEdit = (simple_edit *) GetDlgItem(IDC_EDIT_CHANGE_TIME);
   if(pSpin && pEdit)
   {
      pSpin->SetBuddy(pEdit);
      pSpin->SetRange(
         BACKGROUND_IMAGE_CHANGE_MIN_SECONDS,
         BACKGROUND_IMAGE_CHANGE_MAX_SECONDS);
   }*/

   // TODO: add extra initialization here
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE

}

BOOL OptionsSongsImagesDialog::DestroyWindow() 
{
   // TODO: add your specialized code here and/or call the base class
   
//   if(dialog::DestroyWindow())
    {
        delete this;
       return TRUE;
    }
  //  else
    {
        return FALSE;
    }
}
