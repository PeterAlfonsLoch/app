#include "framework.h"
#include "FileManagerViewUpdateHint.h"


namespace filemanager
{

   SimplePreview::SimplePreview(sp(::ca::application) papp) :
      ca(papp),
      ::userbase::view(papp),
      SimplePreviewInterface(papp)
   {

   }

   SimplePreview::~SimplePreview()
   {
   }

   void SimplePreview::install_message_handling(::ca::message::dispatch * pdispatch)
   {
      ::userbase::view::install_message_handling(pdispatch);
      SimplePreviewInterface::install_message_handling(pdispatch);
   }


   void SimplePreview::on_update(::view * pSender, LPARAM lHint, ::ca::object* phint) 
   {
      FileManagerViewInterface::on_update(pSender, lHint, phint);
      if(phint != ::null())
      {
         if(base < FileManagerViewUpdateHint > :: bases (phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
            
   /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
               AddClient(this);
               SetDataInterface(&m_datainterface);
               AddClient(&m_datainterface);
               string str;
               str.Format("SimpleFileListView(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
               if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               {
                  ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
               }
               DISetSection(str);
               _001UpdateColumns();*/
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypePreSynchronize))
            {
               //_017PreSynchronize();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronize))
            {
               //_017Synchronize();
               m_strPath = GetFileManagerItem().m_strPath;
               m_straPath.remove_all();
               m_straTitle.remove_all();
               m_iCurFile = 0;
               GetFileManager()->get_fs_data()->ls(GetFileManagerItem().m_strPath, &m_straPath, &m_straTitle);
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeFilter))
            {
               /*if(puh->m_wstrFilter.is_empty())
               {
                  FilterClose();
               }
               else
               {
                  FilterBegin();
                  Filter1(puh->m_wstrFilter);
                  FilterApply();
               }*/
            }
         }
         else if(base < form_update_hint > :: bases(phint))
         {
            /*form_update_hint * puh = dynamic_cast<form_update_hint * > (phint);
            if(puh->m_etype == form_update_hint::type_after_browse)
            {
               if(puh->m_strForm == "filemanager\\replace_name_in_file_system.xhtml")
               {
                  html::elemental * pelemental = dynamic_cast < html::elemental * > (puh->m_pformview->get_document()->m_document.get_element_by_name("encontrar"));
                  html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);
                  sp(text_interface) ptext =  (pinput->m_pedit);
                  range range;
                  _001GetSelection(range);
                  if(range.get_item_count() > 0)
                  {
                     ptext->_001SetText(m_itema.get_item(range.ItemAt(0).get_lower_bound()).m_strName);
                  }
               }  
            }
            file_manager_form_update_hint * pmanageruh = dynamic_cast<file_manager_form_update_hint * > (phint);
            if(pmanageruh != ::null())
            {
               if(!pmanageruh->m_strFind.is_empty())
               {
                  System.file().replace(m_strPath, pmanageruh->m_strFind, pmanageruh->m_strReplace);
                  _017UpdateList();
               }
            }*/
         }

      }
   }



} // namespace filemanager