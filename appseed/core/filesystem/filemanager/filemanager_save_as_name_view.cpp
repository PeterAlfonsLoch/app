//#include "framework.h"


namespace filemanager
{


   save_as_view::save_as_view(::aura::application * papp):
      object(papp),
      ::user::edit_plain_text(papp),
      ::user::edit_plain_text_view(papp),
      ::user::interaction(papp)
   {

         m_bVoidSync = false;

      }

   void save_as_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {
      ::aura::impact::on_update(pSender,lHint,phint);
      if(phint != NULL)
      {
         if(base_class < ::filemanager::update_hint >::bases(phint))
         {
            ::filemanager::update_hint * puh = (::filemanager::update_hint *) phint;
            if(puh->m_pview == this &&
               puh->is_type_of(::filemanager::update_hint::TypeInitialize))
            {
               //            get_filemanager_manager() = puh->get_filemanager_manager();
               /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                           AddClient(this);
                           SetDataInterface(&m_datainterface);
                           AddClient(&m_datainterface);
                           string str;
                           str.Format("file_list(%d,%d)", get_filemanager_data()->m_iTemplate, get_filemanager_data()->m_iDocument);
                           if(get_filemanager_data()->m_bTransparentBackground)
                           {
                           ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
                           }
                           DISetSection(str);
                           _001UpdateColumns();*/
            }
            else if(puh->is_type_of(::filemanager::update_hint::TypeFilter))
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
            else if(base_class < ::user::form_update_hint >::bases(phint))
            {
            }
         }
      }
   }


   void save_as_view::browse_sync(::action::context actioncontext)
   {
      if(m_bVoidSync)
         return;
      string strText;
      _001GetText(strText);
      if(strText != get_filemanager_data()->m_pmanager->m_strTopic.title())
      {
         _001SetText(get_filemanager_data()->m_pmanager->m_strTopic.title(),actioncontext);
      }
   }

   void save_as_view::_001OnAfterChangeText(::action::context actioncontext)
   {

      string str;

      _001GetText(str);

      if(Application.dir().is(str))
      {
         get_filemanager_manager()->FileManagerBrowse(str,::action::source::sync(actioncontext));
      }
      else if(str.find("/") >= 0 || str.find("\\") >= 0)
      {

         ::file::path strName = str;

         while(true)
         {

            strName = strName.folder();

            if(Application.dir().is(strName))
            {

               if(get_filemanager_item().m_strPath != strName)
               {

                  get_filemanager_manager()->FileManagerBrowse(strName,::action::source::sync(actioncontext));

               }

               break;

            }

            if(strName.is_empty())
            {

               break;

            }

         }

      }

      if(get_filemanager_manager().is_set())
      {

         get_filemanager_manager()->m_strTopic = str;

      }

   }


} // namespace filemanager

















