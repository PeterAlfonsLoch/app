#include "framework.h"


FileManagerSaveAsView::FileManagerSaveAsView(sp(::base::application) papp) :
   element(papp),
   ::filemanager::data_interface(papp),
   data::data_listener(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text_view(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp)
{

   m_bVoidSync = false;

}

void FileManagerSaveAsView::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
{
   ::filemanager::data_interface::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base_class < filemanager::update_hint >::bases(phint))
      {
         filemanager::update_hint * puh = (filemanager::update_hint *) phint;
         if(puh->m_pview == this &&
            puh->is_type_of(filemanager::update_hint::TypeInitialize))
         {
//            GetFileManager() = puh->GetFileManager();
/*            m_pserverNext = simpledb::AppGet()->GetDataServer();
            AddClient(this);
            SetDataInterface(&m_datainterface);
            AddClient(&m_datainterface);
            string str;
            str.Format("::filemanager::file_list(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
            if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
            {
               ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
            }
            DISetSection(str);
            _001UpdateColumns();*/
         }
         else if(puh->is_type_of(filemanager::update_hint::TypeSynchronizePath))
         {
            _017Synchronize(puh->m_actioncontext + ::action::source_sync);
         }
         else if(puh->is_type_of(filemanager::update_hint::TypeFilter))
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
         else if(base_class < form_update_hint >::bases(phint))
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
}


void FileManagerSaveAsView::_017Synchronize(::action::context actioncontext)
{
   if(m_bVoidSync)
      return;
   string strText;
   _001GetText(strText);
   if(strText != System.file().title_(GetFileManager()->get_filemanager_data()->m_pmanager->m_strTopic))
   {
      _001SetText(System.file().title_(GetFileManager()->get_filemanager_data()->m_pmanager->m_strTopic), actioncontext);
   }
}

void FileManagerSaveAsView::_001OnAfterChangeText(::action::context actioncontext)
{

   string str;

   _001GetText(str);

   if(session().dir().is(str))
   {
      GetFileManager()->FileManagerBrowse(str, ::action::source::sync(actioncontext));
   }
   else if(str.find("/") >= 0 || str.find("\\") >= 0)
   {
      string strName = str;
      while(true)
      {
         strName = System.dir().name(strName);
         if(session().dir().is(strName))
         {
            if(!System.file().path().is_equal(GetFileManager()->get_item().m_strPath, strName))
            {
               GetFileManager()->FileManagerBrowse(strName, ::action::source::sync(actioncontext));
            }
            break;
         }
         if(strName.is_empty())
            break;
      }
   }

   if(GetFileManager().is_set())
   {

      GetFileManager()->m_strTopic = str;

   }

}


