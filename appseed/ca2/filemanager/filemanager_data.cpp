#include "framework.h"


namespace filemanager
{


   data::data(sp(::ca::application) papp) :
      ca(papp),
      ::fs::tree_data(papp),
      ::fs::list_data(papp)
   {
      m_iIconSize                = 16;
      m_bListText                = true;
      m_bListSelection           = true;
      m_bFileSize                = false;
      m_bPassBk                  = false;
      m_bIconView                = false;
      m_pholderFileList          = ::null();
      m_ptreeFileTreeMerge       = ::null();
      m_pdocumentSave            = ::null();
      m_ptemplate                = ::null();
      m_bSetBergedgeTopicFile    = false;
   }

   data::~data()
   {

   }

   void data::OnFileManagerOpenContextMenuFolder(sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle)
   {

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerOpenContextMenuFolder(this, item, straCommand, straCommandTitle);

      }

   }


   void data::OnFileManagerOpenContextMenuFile(const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerOpenContextMenuFile(this, itema);

      }

   }


   void data::OnFileManagerOpenContextMenu()
   {

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerOpenContextMenu(this);

      }

   }


   void data::OnFileManagerOpenFile(const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != ::null());

      if(is_saving() && itema.get_count() == 1)
      {

         sp(::filemanager::document) pdoc =  (m_pmanager);
         FileManagerViewUpdateHint uh;
         uh.m_pmanager = m_pmanager;
         uh.m_strPath = itema[0].m_strPath;
         uh.set_type(FileManagerViewUpdateHint::TypeSaveAsOK);
         pdoc->update_all_views(::null(), 0, &uh);
         m_pdocumentSave = ::null();

      }
      else if(m_pcallback != ::null())
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

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerOpenFolder(this, item);

      }

   }


   void data::OnFileManagerItemUpdate(cmd_ui * pcmdui, const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerItemUpdate(this, pcmdui, itema);

      }

   }


   void data::OnFileManagerItemCommand(const char * pszId, const ::fs::item_array & itema)
   {

      ASSERT(m_pcallback != ::null());

      if(m_pcallback != ::null())
      {

         m_pcallback->OnFileManagerItemCommand(this, pszId, itema);

      }

   }


   void data::FileManagerBrowse(sp(::fs::item)  item)
   {

      ASSERT(m_pmanager != ::null());

      if(m_pmanager != ::null())
      {

         m_pmanager->FileManagerBrowse(item);

      }

   }

   void data::FileManagerBrowse(const char * lpcsz)
   {
      
      ASSERT(m_pmanager != ::null());
      
      if(m_pmanager != ::null())
      {

         m_pmanager->FileManagerBrowse(lpcsz);

      }

   }


   bool data::is_saving()
   {

      return m_pdocumentSave != ::null();

   }


} // namespace filemanager


