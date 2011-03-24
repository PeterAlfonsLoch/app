#include "StdAfx.h"
#include "ToolsOptionsDoc.h"


CToolsOptionsDoc::CToolsOptionsDoc(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp)
{
   m_bSongDirectoriedModified = false;
}

BOOL CToolsOptionsDoc::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;
   update_all_views(NULL);
   return TRUE;
}

CToolsOptionsDoc::~CToolsOptionsDoc()
{
}


#ifdef _DEBUG
void CToolsOptionsDoc::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void CToolsOptionsDoc::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDoc serialization

/*
void CToolsOptionsDoc::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
      // TODO: add storing code here
   }
   else
   {
      // TODO: add loading code here
   }
}
*/

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDoc commands

bool CToolsOptionsDoc::UpdateSongDirectories(bool bSave)
{
   UNREFERENCED_PARAMETER(bSave);
   db_server * pdb = (db_server *) &System.db();
   /*DBSongDirectorySet *pset = pdb->GetSongsDirsSet();
   if(bSave)
   {
      if(SUCCEEDED(pset->SetStringArray(m_wstraSongDirectories)))
      {
         SetSongDirectoriesModified(false);
         db()->OnSongsDirsModified(&System);

      }
   }
   else
   {
      if(m_wstraSongDirectories.get_size())
         m_wstraSongDirectories.remove_all();
      pset->GetStringArray(m_wstraSongDirectories);
   }*/
   return true;
   return false;

}

bool CToolsOptionsDoc::IsSongDirectoriesModified()
{
   return m_bSongDirectoriedModified;
}

void CToolsOptionsDoc::SetSongDirectoriesModified(bool bModified)
{
   m_bSongDirectoriedModified = bModified;
}

BOOL CToolsOptionsDoc::is_modified()
{
   return ::userbase::document::is_modified()
      || IsSongDirectoriesModified();
}

BOOL CToolsOptionsDoc::on_save_document(const char * lpszPathName) 
{
   if(IsSongDirectoriesModified())
   {
      if(!UpdateSongDirectories(true))
         return FALSE;
   }
   return TRUE;
}


bool CToolsOptionsDoc::do_save(const char * lpszPathName, bool bReplace)
{
   UNREFERENCED_PARAMETER(lpszPathName);
   UNREFERENCED_PARAMETER(bReplace);
/*   string newName = lpszPathName;
   if (newName.is_empty())
   {
      ::userbase::document_template* ptemplate = get_document_template();
      ASSERT(ptemplate != NULL);

      newName = m_strPathName;
      if (bReplace && newName.is_empty())
      {
         newName = m_strTitle;
         // check for dubious filename
         int iBad = newName.FindOneOf(" #%;/\\");
         if (iBad != -1)
            newName.ReleaseBuffer(iBad);

         // append the default suffix if there is one
         string strExt;
         if (ptemplate->GetDocString(strExt, ::userbase::document_template::filterExt) &&
           !strExt.is_empty())
         {
            ASSERT(strExt[0] == '.');
            newName += strExt;
         }
      }

      if (!System.do_prompt_file_name(newName,
        bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
        OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, ptemplate))
         return FALSE;       // don't even attempt to save
   }*/

   wait_cursor wait(get_app());

//   if (!on_save_document(newName))
   if (!on_save_document(NULL))
   {
/*      if (lpszPathName == NULL)
      {
         // be sure to delete the file
         try
         {
            ex1::filesp::remove(newName);
         }
         catch(base_exception * pe)
         {
            TRACE0("Warning: failed to delete file after failed SaveAs.\n");
            pe->Delete();
         }
         
      }*/
      return FALSE;
   }

   // reset the title and change the document name
//   if (bReplace)
//      set_path_name(newName);

   return TRUE;        // success

}

void CToolsOptionsDoc::OnUpdateFileSave(cmd_ui * pcmdui) 
{
   pcmdui->Enable(is_modified());   
}

void CToolsOptionsDoc::OnFileSaveAndClose() 
{
   if(do_file_save())
   {
      on_close_document();
   }
}

void CToolsOptionsDoc::OnUpdateFileSaveAndClose(cmd_ui * pcmdui) 
{
   pcmdui->Enable(is_modified());   
}
