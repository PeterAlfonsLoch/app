#include "framework.h"


namespace filemanager
{


   child_frame::child_frame(sp(::base::application) papp) :
      element(papp),
      simple_child_frame(papp),
      m_toolbar(papp)
   {
   }

   child_frame::~child_frame()
   {
   }

   void child_frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_child_frame::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(::core::application::APPM_LANGUAGE, pinterface, this, &child_frame::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &child_frame::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &child_frame::_001OnCreate);
   }

   bool child_frame::CreateBars()
   {
      sp(manager) pdoc = (GetActiveDocument());
      if (pdoc == NULL)
         return false;

      ASSERT(pdoc != NULL);
      ASSERT(base_class < manager >::bases(pdoc));

      DestroyBars();

      string strToolBar;

      if (pdoc->get_filemanager_data()->is_saving())
      {
         strToolBar = pdoc->get_filemanager_template()->m_strToolBarSave;
      }
      else
      {
         strToolBar = pdoc->get_filemanager_template()->m_strToolBar;
      }

      string str = session().file().as_string(session().dir().matter(strToolBar));

      if (!m_toolbar.CreateEx(this) || !m_toolbar.LoadXmlToolBar(str))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      layout();

      return true;

   }

   bool child_frame::DestroyBars()
   {
      m_toolbar.DestroyWindow();
      m_toolbar.RemoveAllTools();
      return true;
   }

   bool child_frame::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {

      //file_list_callback * pcallback = get_filemanager_template()->m_pfilelistcallback;
      return simple_child_frame::_001OnCmdMsg(pcmdmsg);
   }

   void child_frame::OnChangeEditSearch()
   {

      sp(::user::document) pdoc = GetActiveDocument();

      if (pdoc != NULL)
      {
         update_hint uh;
         uh.set_type(update_hint::TypeFilter);
         string str;

      }

   }

   sp(manager) child_frame::get_filemanager_template()
   {
      return  GetActiveDocument();
   }


   void child_frame::_001OnCreate(signal_details * pobj)
   {
      if (pobj->m_bRet)
         return;


      m_hMenuDefault = NULL;


   }


   void child_frame::_001OnAppLanguage(signal_details * pobj)
   {
      CreateBars();
      pobj->m_bRet = false;
   }

   void child_frame::GetSelected(::fs::item_array &itema)
   {
      sp(file_list) plistinterface = GetActiveView();
      if (plistinterface != NULL)
      {
         plistinterface->GetSelected(itema);
      }
   }

   void child_frame::_001OnShowWindow(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }




} // namespace filemanager




