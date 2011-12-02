#include "StdAfx.h"

file_manager_operation_view::file_manager_operation_view(::ax::application * papp) :
   ax(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

file_manager_operation_view::~file_manager_operation_view()
{
}


void file_manager_operation_view::_001OnCreate(gen::signal_object * pobj)
{
   pobj->previous();

   get_document()->m_thread.m_pview = this;

   m_pviewcreator = new ::user::view_creator();

   SetPaneCount(2);

   SetSplitOrientation(orientation_horizontal);
  
   set_position_rate(0, 0.3);

   m_plistview = create_view < file_manager_operation_list_view > ();
   if(m_plistview == NULL)
   {
      System.simple_message_box(NULL, "Could not create transfer list ::view");
   }
   SetPane(0, m_plistview, false);


   m_pinfoview = create_view < file_manager_operation_info_view > ();
   if(m_pinfoview == NULL)
   {
      System.simple_message_box(NULL, "Could not create transfer information ::view");
   }
   SetPane(1, m_pinfoview, false);

}

void file_manager_operation_view::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::split_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &file_manager_operation_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(MessageMainPost, pinterface, this, &file_manager_operation_view::_001OnMainPostMessage);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &file_manager_operation_view::_001OnDestroy);
}

file_manager_operation_document * file_manager_operation_view::get_document()
{
   return dynamic_cast < file_manager_operation_document * > (::view::get_document());
}

void file_manager_operation_view::_001OnMainPostMessage(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::base, pbase, pobj)
   if(pbase->m_wparam == MessageMainPostFileOperation)
   {
      m_pinfoview->OnFileOperationStep(pbase->m_lparam, false);
      m_plistview->OnFileOperationStep(pbase->m_lparam, false);
   }
   else if(pbase->m_wparam == MessageMainPostFileOperationFinal)
   {
      m_pinfoview->OnFileOperationStep(pbase->m_lparam, true);
      m_plistview->OnFileOperationStep(pbase->m_lparam, true);
   }
}

void file_manager_operation_view::_001OnDestroy(gen::signal_object *pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}