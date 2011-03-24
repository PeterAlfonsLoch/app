#include "StdAfx.h"
#include "SongDirectoriesFormView.h"
#include "ToolsOptionsDoc.h"


CSongDirectoriesFormView::CSongDirectoriesFormView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   ::user::form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
}

CSongDirectoriesFormView::~CSongDirectoriesFormView()
{
}

/*
void CSongDirectoriesFormView::DoDataExchange(CDataExchange* pDX)
{
//   form_view::DoDataExchange(pDX);
//   DDX::DDXListBox(pDX, IDC_LIST, get_document()->m_wstraSongDirectories);
   //{{AFX_DATA_MAP(CSongDirectoriesFormView)
      // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}
*/

 // BEGIN_MESSAGE_MAP(CSongDirectoriesFormView, form_view)
   //{{AFX_MSG_MAP(CSongDirectoriesFormView)
/* xxx   ON_BN_CLICKED(IDC_ADD, OnAdd)
   ON_BN_CLICKED(IDC_REMOVE, OnRemove)
   ON_COMMAND(ID_ADD_SONG_DIRECTORY, OnAddSongDirectory)
   ON_UPDATE_COMMAND_UI(ID_ADD_SONG_DIRECTORY, OnUpdateAddSongDirectory)
   ON_COMMAND(ID_REMOVE_SONG_DIRECTORY, OnRemoveSongDirectory)
   ON_UPDATE_COMMAND_UI(ID_REMOVE_SONG_DIRECTORY, OnUpdateRemoveSongDirectory) */
//   ON_COMMAND(ID_FILE_SAVE, on_file_save)
//   ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSongDirectoriesFormView diagnostics

#ifdef _DEBUG
void CSongDirectoriesFormView::assert_valid() const
{
   form_view::assert_valid();
}

void CSongDirectoriesFormView::dump(dump_context & dumpcontext) const
{
   form_view::dump(dumpcontext);
}

CToolsOptionsDoc* CSongDirectoriesFormView::get_document() // non-debug version is inline
{
   ASSERT(base < CToolsOptionsDoc >::bases(::view::get_document()));
   return dynamic_cast < CToolsOptionsDoc * > (::view::get_document());
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSongDirectoriesFormView message handlers

void CSongDirectoriesFormView::OnAdd() 
{
   BROWSEINFO bi;
   
   string str;

   bi.hwndOwner = GetTopLevelParent()->_get_handle();
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
         str = pszPath;
         get_document()->m_wstraSongDirectories.add(str);
//         UpdateData(FALSE);
         get_document()->SetSongDirectoriesModified(true);
      }
   }
   
}

void CSongDirectoriesFormView::OnRemove() 
{
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
      get_document()->SetSongDirectoriesModified(true);
   }
   else
   {
      System.simple_message_box(IDS_NO_DIRECTORY_SELECTED,MB_ICONINFORMATION | MB_OK, 0);
   }   */
}

bool CSongDirectoriesFormView::UpdateForm(bool bSave)
{
   if(bSave)
   {
      if(get_document()->IsSongDirectoriesModified())
      {
//         if(!UpdateData())
//            return FALSE;
         if(!get_document()->UpdateSongDirectories(true))
            return FALSE;
      }
   }
   else
   {
      if(!get_document()->UpdateSongDirectories(FALSE))
         return FALSE;
//      if(!UpdateData(false))
//         return FALSE;
   }
   return TRUE;

}

void CSongDirectoriesFormView::OnAddSongDirectory() 
{
   OnAdd();   
}

void CSongDirectoriesFormView::OnUpdateAddSongDirectory(cmd_ui * pcmdui) 
{
   pcmdui->Enable(TRUE);
   
}

void CSongDirectoriesFormView::OnRemoveSongDirectory() 
{
   OnRemove();
}

void CSongDirectoriesFormView::OnUpdateRemoveSongDirectory(cmd_ui * pcmdui) 
{
   pcmdui->Enable(get_document()->m_wstraSongDirectories.get_size   () > 0);
}

/*void CSongDirectoriesFormView::on_file_save() 
{
   bool bModified = get_document()->IsSongDirectoriesModified();
   if(bModified)
   {
      if(!UpdateForm(true))
         return;
      get_document()->SetSongDirectoriesModified(false);
   }

   
}*/

/*void CSongDirectoriesFormView::OnUpdateFileSave(cmd_ui * pcmdui) 
{
   pcmdui->Enable(get_document()->IsSongDirectoriesModified());
}*/

void CSongDirectoriesFormView::OnInitialUpdate() 
{
//   form_view::OnInitialUpdate();
   
   if(!get_document()->IsSongDirectoriesModified())
   {
      UpdateForm(false);
   }
   
}
