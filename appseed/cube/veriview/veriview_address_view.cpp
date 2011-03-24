#include "StdAfx.h"

namespace veriview
{

   address_view::address_view(::ca::application * papp) : 
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::edit_plain_text(papp),
      ::userbase::view(papp),
      ::userbase::edit_plain_text_view(papp),
      ::userex::autocomplete::interaction(papp),
      ::user::interaction(papp), 
      ::user::scroll_view(papp), 
      colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {

      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Arial");
      lf.lfHeight = 16;

      m_font->CreateFontIndirect(&lf);

      m_bVoidSync = false;
      m_bMultiLine = false;
   }

   void address_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::edit_plain_text_view::_001InstallMessageHandling(pinterface);
      ::userex::autocomplete::interaction::_001InstallMessageHandling(pinterface);
   }

   void address_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      if(phint != NULL)
      {
         if(base < FileManagerViewUpdateHint >::bases(phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->m_pview == this &&
               puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
   //            GetFileManager() = puh->GetFileManager();
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
               _017Synchronize();
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
         else if(base < form_update_hint >::bases(phint))
         {
            /*form_update_hint * puh = dynamic_cast<form_update_hint * > (phint);
            if(puh->m_etype == form_update_hint::type_after_browse)
            {
               if(puh->m_strForm == "filemanager\\replace_name_in_file_system.xhtml")
               {
                  html::elemental * pelemental = dynamic_cast < html::elemental * > (puh->m_pformview->get_document()->m_document.get_element_by_name("encontrar"));
                  html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);
                  text_interface * ptext = dynamic_cast < text_interface * > (pinput->m_pedit);
                  Range range;
                  _001GetSelection(range);
                  if(range.get_item_count() > 0)
                  {
                     ptext->_001SetText(m_itema.get_item(range.ItemAt(0).GetLBound()).m_strName);
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


   void address_view::_017Synchronize()
   {
      if(m_bVoidSync)
         return;
      _001SetText(get_document()->get_url());
   }

   main_document * address_view::get_document()
   {
      return dynamic_cast < main_document * > (::view::get_document());
   }

   bool address_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_puie == this
         && pevent->m_eevent == ::user::event_enter_key)
      {
         string strText;
         _001GetText(strText);
         main_document * pmaindocument = get_document();
         pane_view * ppaneview = pmaindocument->m_ppaneview;
         html_document * phtmldocument = ppaneview->get_view_html_document();
         phtmldocument->open_document(strText);
         return true;
      }
      return false;
   }

   void address_view::autocomplete_set_text(const char * pszText)
   {
      keeper < bool > keepVoidSync(&m_bVoidSync, true, false, true);
      _001SetText(pszText);
      keepVoidSync.KeepAway();
      main_document * pmaindocument = get_document();
      pane_view * ppaneview = pmaindocument->m_ppaneview;
      html_document * phtmldocument = ppaneview->get_view_html_document();
      phtmldocument->open_document(pszText);
   }

   void address_view::_001OnUpdate()
   {
      if(!m_bVoidSync)
      {
         string str;
         _001GetText(str);
         ::userex::autocomplete::interaction::m_phandler->set_text(str);
         SetFocus();
      }
      ::userbase::edit_plain_text_view::_001OnUpdate();
   }


} // namespace veriview