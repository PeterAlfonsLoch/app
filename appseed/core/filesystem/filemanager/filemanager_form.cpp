//#include "framework.h"
//#include "framework.h"




namespace filemanager
{


   form::form(::aura::application * papp):
      object(papp),
      html_form(papp),
      html_form_view(papp)
   {

   }

   void form::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {
      ::filemanager::impact::on_update(pSender,lHint,phint);
      if (m_pmanager == NULL)
      {

         m_pmanager = dynamic_cast <::filemanager::manager *> (get_document());

      }
      /*sp(::filemanager::manager) pdoc =  (get_filemanager_manager());
      if(pdoc != NULL)
      {
         pdoc->update_all_views(pSender,lHint,phint);
      }*/
      ::user::form_view::on_update(pSender,lHint,phint);
   }


   bool form::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "lfs")
         {
            form_update_hint uh;
            uh.m_etype = form_update_hint::type_browse;
            uh.m_strForm = "filemanager_add_location_lfs.xhtml";
            get_document()->update_all_views(NULL,0,&uh);
            sp(::user::interaction) pui = get_child_by_name("lfs");
            sp(::user::elemental) ptext =  (pui.m_p);
            ptext->_001SetText(get_filemanager_item().m_filepath,::action::source_user);
         }
         else if(pevent->m_puie->m_id == "ftp")
         {
            form_update_hint uh;
            uh.m_etype = form_update_hint::type_browse;
            uh.m_strForm = "filemanager_add_location_ftp.xhtml";
            get_document()->update_all_views(NULL,0,&uh);
         }
         else if(pevent->m_puie->m_id == "submit")
         {
            if(m_strPath == "filemanager_add_location_lfs.xhtml")
            {
               stringa stra;
               get_filemanager_manager()->data_get(get_filemanager_template()->m_dataidStatic,stra);
               sp(::user::interaction) pui = get_child_by_name("lfs");
               sp(::user::elemental) ptext =  (pui.m_p);
               string str;
               ptext->_001GetText(str);
               stra.add_unique(str);
               get_filemanager_manager()->data_set(get_filemanager_template()->m_dataidStatic,stra);

            }
            else if(m_strPath == "filemanager_add_location_ftp.xhtml")
            {
            }
            else if(m_idCreator == "replace_name")
            {
               form_update_hint uh(manager::hint_replace_name);
               sp(::user::interaction) pui = get_child_by_name("find");
               sp(::user::elemental) ptext =  (pui.m_p);
               ptext->_001GetText(uh.m_strFind);
               pui = get_child_by_name("replace");
               ptext =  (pui.m_p);
               ptext->_001GetText(uh.m_strReplace);
               sp(::filemanager::manager) pdoc =  get_filemanager_manager();
               pdoc->update_all_views(NULL,0,&uh);
            }
            else if (m_idCreator == "new_folder")
            {
               form_update_hint uh(manager::hint_new_folder);
               sp(::user::interaction) pui = get_child_by_name("name");
               sp(::user::elemental) ptext = (pui.m_p);
               ptext->_001GetText(uh.m_str);
               sp(::filemanager::manager) pdoc = get_filemanager_manager();
               pdoc->update_all_views(NULL, 0, &uh);
            }
         }
      }
      return false;
   }




} // namespace filemanager




