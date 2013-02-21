#include "framework.h"

file_manager_form_view::file_manager_form_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp),
   html_form(papp), 
   html_form_view(papp), 
   form_view(papp)
{
}

void file_manager_form_view::on_update(::view * pSender, LPARAM lHint, ::gen::object* phint) 
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (GetFileManager());
   if(pdoc != NULL)
   {
      pdoc->update_all_views(pSender, lHint, phint);
   }
   form_view::on_update(pSender, lHint, phint);
}


bool file_manager_form_view::BaseOnControlEvent(::user::control_event * pevent)
{
   if(pevent->m_eevent == ::user::event_button_clicked)
   {
      if(pevent->m_puie->m_id == "lfs")
      {
         file_manager_form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager_add_location_lfs.xhtml";
         get_document()->update_all_views(NULL, 0, &uh);
         ::user::interaction* pguie = get_child_by_name("lfs");
         text_interface * ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001SetText(GetFileManagerItem().m_strPath);
      }
      else if(pevent->m_puie->m_id == "ftp")
      {
         file_manager_form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager_add_location_ftp.xhtml";
         get_document()->update_all_views(NULL, 0, &uh);
      }
      else if(pevent->m_puie->m_id == "submit")
      {
         if(m_strPath == "filemanager_add_location_lfs.xhtml")
         {
            stringa stra;
            GetFileManager()->data_get(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::gen::system::idEmpty, stra);
            ::user::interaction* pguie = get_child_by_name("lfs");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            string str;
            ptext->_001GetText(str);
            stra.add_unique(str);
            GetFileManager()->data_set(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::gen::system::idEmpty, stra);

         }
         else if(m_strPath == "filemanager_add_location_ftp.xhtml")
         {
         }
         else if(m_strPath == "filemanager\\replace_name_in_file_system.xhtml")
         {
            file_manager_form_update_hint uh;
            ::user::interaction* pguie = get_child_by_name("encontrar");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            ptext->_001GetText(uh.m_strFind);
            pguie = get_child_by_name("substituir");
            ptext = dynamic_cast < text_interface * > (pguie);
            ptext->_001GetText(uh.m_strReplace);
            ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (GetFileManager());
            pdoc->update_all_views(NULL, 0, &uh);
         }
      }
   }
   return false;
}

