#include "framework.h"


namespace filemanager
{



   path_view::path_view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::data::data_listener(papp),
      ::colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp),
      ::user::edit_plain_text_view(papp)
   {

         m_bVoidSync = false;

   }


   void path_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {

      ::filemanager::impact::on_update(pSender, lHint, phint);

      if (phint != NULL)
      {
         if (base_class < update_hint >::bases(phint))
         {
            update_hint * puh = (update_hint *) phint;
            if (puh->m_pview == this &&
               puh->is_type_of(update_hint::TypeInitialize))
            {
               //            get_filemanager_manager() = puh->get_filemanager_manager();
               /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                           AddClient(this);
                           SetDataInterface(&m_datainterface);
                           AddClient(&m_datainterface);
                           string str;
                           str.Format("::filemanager::file_list(%d,%d)", get_filemanager_data()->m_iTemplate, get_filemanager_data()->m_iDocument);
                           if(get_filemanager_data()->m_bTransparentBackground)
                           {
                           ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
                           }
                           DISetSection(str);
                           _001UpdateColumns();*/
            }
            else if (puh->is_type_of(update_hint::TypeSynchronizePath))
            {
               _017Synchronize(puh->m_actioncontext + ::action::source_sync);
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
         else if (base_class < form_update_hint >::bases(phint))
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
            form_update_hint * pmanageruh = dynamic_cast<form_update_hint * > (phint);
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


   void path_view::_017Synchronize(::action::context actioncontext)
   {

      if (m_bVoidSync)
         return;

      if (get_filemanager_manager() == NULL)
         return;

      string strOld;

      _001GetText(strOld);

      if (strOld == get_filemanager_item().m_strPath)
         return;

      _001SetText(get_filemanager_item().m_strPath, actioncontext);

   }

   void path_view::_001OnAfterChangeText(::action::context actioncontext)
   {

      if (actioncontext.is_source(::action::source_sync))
         return;

      string str;
      _001GetText(str);

      sp(manager) pmanager = get_filemanager_manager();

      if (pmanager == NULL)
         return;

      ::fs::data * pfsdata = pmanager->get_fs_data();

      if (pfsdata->is_dir(str))
      {

         string strPreviousPath = get_filemanager_manager()->m_item->m_strPath;
         if (strPreviousPath != str)
         {

            get_filemanager_manager()->FileManagerBrowse(str, ::action::source::sync(actioncontext));

         }

      }
      else
      {
         string strName = str;
         while (true)
         {
            strName = System.dir().name(strName);
            if (get_filemanager_manager()->get_fs_data()->is_dir(strName))
            {
               if (!System.file().path().is_equal(get_filemanager_item().m_strPath, strName))
               {
                  keep < bool > keepVoidSync(&m_bVoidSync, true, false, true);
                  get_filemanager_manager()->FileManagerBrowse(strName, ::action::source::sync(actioncontext));
               }
               break;
            }
            if (strName.is_empty())
               break;
         }
      }

      get_filemanager_data()->m_pmanager->m_strTopic = str;
      get_filemanager_data()->m_pmanagerMain->m_strTopic = str;


   }


   void path_view::_001OnDraw(::draw2d::graphics * pdc)
   {

      ::user::edit_plain_text_view::_001OnDraw(pdc);

   }


} // namespace filemanager



