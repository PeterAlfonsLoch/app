#include "framework.h"


namespace filemanager
{

   preview::preview(sp(base_application) papp) :
      element(papp),
      ::filemanager::data_interface(papp)
   {

      }

   preview::~preview()
   {
   }

   void preview::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::impact::install_message_handling(pdispatch);
   }


   void preview::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      data_interface::on_update(pSender, lHint, phint);
      if (phint != NULL)
      {
         if (base_class < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (puh->is_type_of(update_hint::TypeInitialize))
            {

               /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                           AddClient(this);
                           SetDataInterface(&m_datainterface);
                           AddClient(&m_datainterface);
                           string str;
                           str.Format("file_list(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
                           if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
                           {
                           ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
                           }
                           DISetSection(str);
                           _001UpdateColumns();*/
            }
            else if (puh->is_type_of(update_hint::TypeSynchronizePath))
            {
               //_017Synchronize(::action::context actioncontext);
               m_strPath = GetFileManagerItem().m_strPath;
               m_straPath.remove_all();
               m_straTitle.remove_all();
               m_iCurFile = 0;
               GetFileManager()->get_fs_data()->ls(GetFileManagerItem().m_strPath, &m_straPath, &m_straTitle, &m_iaSize);
            }
            else if (puh->is_type_of(update_hint::TypeFilter))
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
         else if (base_class < form_update_hint > ::bases(phint))
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
            ptext->_001SetText(m_itema.get_item(range.ItemAt(0).get_lower_bound()).m_strName, false);
            }
            }
            }
            file_manager_form_update_hint * pmanageruh = dynamic_cast<file_manager_form_update_hint * > (phint);
            if(pmanageruh != NULL)
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



   void preview::_001OnDraw(::draw2d::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(200, 200, 190));


      if (m_iCurFile < 0)
      {
      }
      else if (m_iCurFile == 0 && m_straPath.get_size() == 0)
      {
         pdc->TextOut(10, 10, "No files in this directory");
      }
      else if (m_iCurFile < m_straPath.get_size())
      {
         pdc->TextOut(10, 10, m_straTitle[m_iCurFile]);
      }

   }



} // namespace filemanager




