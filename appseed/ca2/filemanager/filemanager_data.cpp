#include "StdAfx.h"

namespace filemanager
{


   data::data(::ax::application * papp) :
      ax(papp),
      ::ax::data(papp),
      ex1::tree_data(papp),
      ::fs::tree_data(papp),
      ::fs::list_data(papp)
   {
      m_iIconSize                = 16;
      m_bListText                = true;
      m_bListSelection           = true;
      m_bFileSize                = false;
      m_bPassBk                  = false;
      m_bIconView                = false;
      m_pholderFileList          = NULL;
      m_ptreeFileTreeMerge       = NULL;
      m_pdocumentSave            = NULL;
      m_ptemplate                = NULL;
      m_bSetBergedgeTopicFile    = false;
   }

   data::~data()
   {

   }

   void data::OnFileManagerOpenContextMenuFolder(const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle)
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerOpenContextMenuFolder(this, item, straCommand, straCommandTitle);
      }
   }

   void data::OnFileManagerOpenContextMenuFile(const ::fs::item_array & itema)
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerOpenContextMenuFile(this, itema);
      }
   }

   void data::OnFileManagerOpenContextMenu()
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerOpenContextMenu(this);
      }
   }

   void data::OnFileManagerOpenFile(const ::fs::item_array & itema)
   {
      ASSERT(m_pcallback != NULL);
      if(is_saving() && itema.get_count() == 1)
      {
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pmanager);
         FileManagerViewUpdateHint uh;
         uh.m_pmanager = m_pmanager;
         uh.m_strPath = itema[0].m_strPath;
         uh.set_type(FileManagerViewUpdateHint::TypeSaveAsOK);
         pdoc->update_all_views(NULL, 0, &uh);
         m_pdocumentSave = NULL;
      }
      else if(m_pcallback != NULL)
      {
         var varFile(itema.get_var_file());
         var varQuery(itema.get_var_query());
         m_pcallback->request(varFile, varQuery);
      }
   }

   void data::OnFileManagerOpenFolder(const ::fs::item & item)
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerOpenFolder(this, item);
      }
   }

   void data::OnFileManagerItemUpdate(cmd_ui * pcmdui, const ::fs::item_array & itema)
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerItemUpdate(this, pcmdui, itema);
      }
   }
   void data::OnFileManagerItemCommand(const char * pszId, const ::fs::item_array & itema)
   {
      ASSERT(m_pcallback != NULL);
      if(m_pcallback != NULL)
      {
         m_pcallback->OnFileManagerItemCommand(this, pszId, itema);
      }
   }


   void data::FileManagerBrowse(const ::fs::item & item)
   {
      ASSERT(m_pmanager != NULL);
      if(m_pmanager != NULL)
      {
         m_pmanager->FileManagerBrowse(item);
      }

   }

   void data::FileManagerBrowse(const char * lpcsz)
   {
      ASSERT(m_pmanager != NULL);
      if(m_pmanager != NULL)
      {
         m_pmanager->FileManagerBrowse(lpcsz);
      }

   }

   bool data::is_saving()
   {
      return m_pdocumentSave != NULL;
   }

} // namespace filemanager
