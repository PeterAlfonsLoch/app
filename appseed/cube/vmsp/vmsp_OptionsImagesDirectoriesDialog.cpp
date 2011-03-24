#include "StdAfx.h"
#include "OptionsImagesDirectoriesDialog.h"


OptionsSongsImagesDirectoriesDialog::OptionsSongsImagesDirectoriesDialog(::ca::application * papp) :
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
   set_modified_flag(false);
}


/*
void OptionsSongsImagesDirectoriesDialog::DoDataExchange(CDataExchange* pDX)
{
//   dialog::DoDataExchange(pDX);
//   DDX::DDXListBox(pDX, IDC_LIST, m_ImagesDirs);
   //{{AFX_DATA_MAP(OptionsSongsImagesDirectoriesDialog)
   //}}AFX_DATA_MAP
}
*/


BOOL OptionsSongsImagesDirectoriesDialog::Update(BOOL bSaveAndValidate)
{
   if(bSaveAndValidate)
   {
      if(is_modified())
      {
//         if(!UpdateData())
//            return FALSE;
         if(!UpdateDatabase())
            return FALSE;
      }
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

BOOL OptionsSongsImagesDirectoriesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   db_server *pDataCentral = (db_server *) &System.db();
/*   CDBImageDirectorySet *pSet = pDataCentral->GetImageDirSet();
   if(bSaveAndValidate)
   {
      pSet->SetImagesDirectories(m_ImagesDirs);
       set_modified_flag(false);
   }
   else
   {
      if(m_ImagesDirs.get_size())
         m_ImagesDirs.remove_all();
      pSet->GetImagesDirectories(m_ImagesDirs);
   }*/
   return TRUE;
   
}

BOOL OptionsSongsImagesDirectoriesDialog::OnInitDialog() 
{
// linux   dialog::OnInitDialog();
   vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   db_server *pDataCentral = (db_server *) &System.db();
/*   CDBImageDirectorySet *pSet = pDataCentral->GetImageDirSet();
   
   if(pSet->m_spCommand == NULL)
      if(pDataCentral->OpenImagesDirsSet() != S_OK)
         System.simple_message_box("Record set failed to open.", MB_OK);
*/
   // TODO: add extra initialization here
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void OptionsSongsImagesDirectoriesDialog::OnAdd() 
{
   // TODO: add your control notification handler code here
   BROWSEINFO bi;
   
   string str;

//   bi.hwndOwner = GetTopLevelParent()->_get_handle();
   bi.pidlRoot = NULL;
   bi.pszDisplayName = NULL;
   throw not_implemented_exception();
   //str.load_string(IDS_CHOOSE_IMAGE_DIRECTORY);
   bi.lpszTitle = str;
   bi.ulFlags = 0;
   bi.lpfn = NULL;
   bi.lParam = 1;
   bi.iImage = 0;

   LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
   if(pidl)
   {
      char pszPath[MAX_PATH];
      if(SHGetPathFromIDList(pidl, pszPath))
      {
         str  = pszPath;
         m_ImagesDirs.add(str);
         //UpdateData(FALSE);
         set_modified_flag();
      }

   }




}


void OptionsSongsImagesDirectoriesDialog::OnRemove() 
{
   // TODO: add your control notification handler code here
/*   CListBox *pList =  (CListBox *) GetDlgItem(IDC_LIST);
   int iSelCount = pList->GetSelCount();
   if(iSelCount)
   {
      LPINT lpInt = (LPINT) malloc(iSelCount * sizeof(INT));
      pList->GetSelItems(iSelCount, lpInt);
        sort::BubbleSort(lpInt, iSelCount);
      for(int i = 0; i < iSelCount; i++)
      {
         pList->DeleteString(*lpInt - i);
         lpInt++;
      }
      UpdateData();
      set_modified_flag();
   }
   else
   {
      System.simple_message_box(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
   }*/
}

bool OptionsSongsImagesDirectoriesDialog::is_modified()
{
   return m_bModified;
}

BOOL OptionsSongsImagesDirectoriesDialog::DestroyWindow() 
{
   // TODO: add your specialized code here and/or call the base class
   
//   if(dialog::DestroyWindow())
    {
       delete this;
       return TRUE;
    }
//    else
    {
        return FALSE;
    }
}

void OptionsSongsImagesDirectoriesDialog::set_modified_flag(bool bModified)
{
    if(bModified)
    {
        m_bModified = true;
//        GetParent()->PostMessage(WM_USER, 1000);
    }
    else
    {
        m_bModified = false;
    }
}
