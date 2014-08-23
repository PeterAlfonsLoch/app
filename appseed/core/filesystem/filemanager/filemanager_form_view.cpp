#include "framework.h"


namespace filemanager
{


   form_view::form_view(sp(::aura::application) papp):
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::form_interface(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      ::form_view(papp)
   {
      }

   void form_view::on_update(sp(::user::impact) pSender,LPARAM lHint,object* phint)
   {
      ::filemanager::impact::on_update(pSender,lHint,phint);
      sp(::filemanager::manager) pdoc =  (get_filemanager_template());
      if(pdoc != NULL)
      {
         pdoc->update_all_views(pSender,lHint,phint);
      }
      ::form_view::on_update(pSender,lHint,phint);
   }


   bool form_view::BaseOnControlEvent(::user::control_event * pevent)
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
            sp(text_interface) ptext =  (pui.m_p);
            ptext->_001SetText(get_filemanager_item().m_strPath,::action::source_user);
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
               get_filemanager_manager()->data_get(get_filemanager_template()->m_dataidStatic,::base::system::idEmpty,stra);
               sp(::user::interaction) pui = get_child_by_name("lfs");
               sp(text_interface) ptext =  (pui.m_p);
               string str;
               ptext->_001GetText(str);
               stra.add_unique(str);
               get_filemanager_manager()->data_set(get_filemanager_template()->m_dataidStatic,::base::system::idEmpty,stra);

            }
            else if(m_strPath == "filemanager_add_location_ftp.xhtml")
            {
            }
            else if(m_strPath == "filemanager\\replace_name_in_file_system.xhtml")
            {
               form_update_hint uh;
               sp(::user::interaction) pui = get_child_by_name("encontrar");
               sp(text_interface) ptext =  (pui.m_p);
               ptext->_001GetText(uh.m_strFind);
               pui = get_child_by_name("substituir");
               ptext =  (pui.m_p);
               ptext->_001GetText(uh.m_strReplace);
               sp(::filemanager::manager) pdoc =  (get_filemanager_template());
               pdoc->update_all_views(NULL,0,&uh);
            }
         }
      }
      return false;
   }




} // namespace filemanager




