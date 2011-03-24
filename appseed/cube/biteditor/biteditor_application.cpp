#include "StdAfx.h"
#include "biteditor_application.h"
#include "biteditor_document.h"
#include "biteditor_frame.h"
#include "biteditor_view.h"
#include "main_document.h"
#include "biteditor_child_frame.h"
#include "front_child_frame.h"
#include "front_document.h"
#include "front_view.h"

biteditor_application::biteditor_application()
{
}

void biteditor_application::construct()
{
   m_strAppName         = "biteditor";
   m_strBaseSupportId   = "votagus_ca2_biteditor";
   m_strInstallToken    = "biteditor";
}

biteditor_application::~biteditor_application()
{
}

bool biteditor_application::initialize_instance()
{
   System.factory().creatable_small < main_document > ();
   System.factory().creatable_small < biteditor_frame > ();
   System.factory().creatable_small < biteditor::tab_view > ();
   System.factory().creatable_small < biteditor_document > ();
   System.factory().creatable_small < biteditor_child_frame > ();
   System.factory().creatable_small < biteditor_view > ();

   if(!ca84::application::initialize_instance())
      return false;

   ::CoInitialize(NULL);
//   window_frame::FrameSchema::ButtonIdSpace idspace;
/*   SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
   SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

   //ToolBarIdSpace idspace2;
/*   SetResourceId(idspace2, "start", 999);
   SetResourceId(idspace2, "levelup", 1000);
   SetResourceId(idspace2, "savefile", 1001);
   SetResourceId(idspace2, "undo", 1002);
   SetResourceId(idspace2, "redo", 1003);*/

//   BaseWndMenuIdSpace idspace3;
/*   SetResourceId(idspace3, "ID_EDIT_CUT", ID_EDIT_CUT);
   SetResourceId(idspace3, "ID_EDIT_COPY", ID_EDIT_COPY);
   SetResourceId(idspace3, "ID_EDIT_PASTE", ID_EDIT_PASTE);*/

   m_ptemplateEdge = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      &typeid(main_document), 
      &typeid(biteditor_frame), 
      &typeid(biteditor::tab_view));

   m_ptemplate_devedge = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      &typeid(biteditor_document), 
      &typeid(biteditor_child_frame), 
      &typeid(biteditor_view));

   m_ptemplateFront = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      &typeid(front_document), 
      &typeid(front_child_frame), 
      &typeid(front_view));

   GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


   


   return true;
}


bool biteditor_application::bergedge_start()
{
   document * pdoc = m_ptemplateEdge->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
   ::view * pview = pdoc->get_view();
   SetMainWnd(pview->GetParentFrame());
   return true;
}

BOOL biteditor_application::exit_instance()
{
   return TRUE;
}


void biteditor_application::OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(pdata);
   m_ptemplate_devedge->open_document_file(itema[0].m_strPath);
}


void biteditor_application::pre_translate_message(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_KEYDOWN)
   {
      int i = 1;
      i = i + 1;
   }
   else if(pbase->m_uiMessage == WM_KEYUP)
   {
      int i = 1;
      i = i + 1;
   }
   ::winservice_filesystemsize::application::pre_translate_message(pobj);
}

bool biteditor_application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{
   return gen::application::_001OnCmdMsg(pcmdmsg);
}
