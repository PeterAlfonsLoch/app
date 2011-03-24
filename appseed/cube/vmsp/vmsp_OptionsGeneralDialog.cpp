#include "StdAfx.h"
#include "OptionsGeneralDialog.h"


OptionsSongsGeneralDialog::OptionsSongsGeneralDialog(::ca::application * papp) :
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
   m_bMRUEnable = FALSE;
   m_iMRUCount = 0;
}


/*void OptionsSongsGeneralDialog::DoDataExchange(CDataExchange* pDX)
{
//   dialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(OptionsSongsGeneralDialog)
   /*DDX_Control(pDX, IDC_SPIN_MRU, m_spinMRUCount);
   DDX_Check(pDX, IDC_CHECK_MRU, m_bMRUEnable);
   DDX_Text(pDX, IDC_EDIT_MRU_COUNT, m_iMRUCount);*/
   /*DDV_MinMaxInt(pDX, m_iMRUCount, 1, 10);*/
   //}}AFX_DATA_MAP
//}


/* // BEGIN_MESSAGE_MAP(OptionsSongsGeneralDialog, dialog)
   //{{AFX_MSG_MAP(OptionsSongsGeneralDialog)
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// OptionsSongsGeneralDialog message handlers

BOOL OptionsSongsGeneralDialog::Update(BOOL bSaveAndValidate)
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

BOOL OptionsSongsGeneralDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
//   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
//   db_server *pDataCentral = (db_server *) &System.db();
//db_long_set *pSet = pDataCentral->get_db_long_set();
   /*if(bSaveAndValidate)
   {
      data_set("MRU", "Count", m_iMRUCount);
      data_set("MRU", "Enable", m_bMRUEnable);
   }
   else
   {
      if(data_get("MRU", "Count", (int &) m_iMRUCount))
         m_iMRUCount = _AFX_MRU_COUNT;
      if(data_get("MRU", "Enable", (int &) m_bMRUEnable))
         m_bMRUEnable = TRUE;
   }
   return TRUE;
   */
   return FALSE;
}

BOOL OptionsSongsGeneralDialog::OnInitDialog() 
{
//   dialog::OnInitDialog();
   
  //  m_spinMRUCount.SetBuddy(GetDlgItem(IDC_EDIT_MRU_COUNT));
//    m_spinMRUCount.SetRange(1, 10);
   // TODO: add extra initialization here
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}
