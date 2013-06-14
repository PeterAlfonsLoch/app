#include "framework.h"


namespace filemanager
{


   data::data(sp(::ca2::application) papp) :
      ca2(papp),
      ::userfs::tree_data(papp),
      ::userfs::list_data(papp)
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

   void data::OnFileManagerOpenContextMenuFolder(sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle)
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

         sp(::filemanager::document) pdoc =  (m_pmanager);
         FileManagerViewUpdateHint uh;
         uh.m_pmanager = m_pmanager;
         uh.m_strPath = itema[0].m_strPath;
         uh.set_type(FileManagerViewUpdateHint::TypeSaveAsOK);
         pdoc->update_all_views(NULL, 0, &uh);
         m_pdocumentSave = NULL;

      }
      else if(m_pcallback != NULL)
      {
         
         var varFile;

         var varQuery;

         if(itema.get_count() == 2 && m_id == "left_file")
         {
            {
               varFile = itema[0].m_strPath;
               varQuery["file_manager_id"] = "left_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }

            {
               varFile = itema[1].m_strPath;
               varQuery["file_manager_id"] = "right_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }
         }
         else if(itema.get_count() == 2 && m_id == "right_file")
         {
            {
               varFile = itema[0].m_strPath;
               varQuery["file_manager_id"] = "right_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }

            {
               varFile = itema[1].m_strPath;
               varQuery["file_manager_id"] = "left_file";
               m_pcallback->request_file_query(varFile, varQuery);
            }
         }
         else
         {

            varFile = itema.get_var_file();

            varQuery = itema.get_var_query();

            varQuery["file_manager_id"] = m_id;

            m_pcallback->request_file_query(varFile, varQuery);

         }

      }

   }


   void data::OnFileManagerOpenFolder(sp(::fs::item)  item)
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


   void data::FileManagerBrowse(sp(::fs::item)  item)
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


