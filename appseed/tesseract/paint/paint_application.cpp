#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace paint
{

   application::application()
   {
      m_strAppName         = "paint";
      m_strBaseSupportId   = "votagus_ca2_paint";
      m_strInstallToken    = "paint";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {

      if(!base_support())
         return false;

   //   window_frame::FrameSchema::ButtonIdSpace idspace;
   /*   SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < html_document > (),
         ::ca::get_type_info < html_frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      return m_ptemplate_html->open_document_file(NULL) != NULL;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   ::ca::application * application::get_app() const
   {
      return m_papp;
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

} // namespace paint


CLASS_DECL_CA2_TESSERACT ::ca::application * paint_get_new_app()
{
   return new ::paint::application;
}
