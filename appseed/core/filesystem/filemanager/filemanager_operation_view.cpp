#include "framework.h"


file_manager_operation_view::file_manager_operation_view(sp(::base::application) papp) :
   element(papp),
   ::user::split_layout(papp),
   
   ::user::split_view(papp),
   place_holder_container(papp)
{
}

file_manager_operation_view::~file_manager_operation_view()
{
}


void file_manager_operation_view::_001OnCreate(signal_details * pobj)
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
      System.simple_message_box(NULL, "Could not create transfer list ::user::impact");
   }
   SetPane(0, m_plistview, false);


   m_pinfoview = create_view < file_manager_operation_info_view > ();
   if(m_pinfoview == NULL)
   {
      System.simple_message_box(NULL, "Could not create transfer information ::user::impact");
   }
   SetPane(1, m_pinfoview, false);

}

void file_manager_operation_view::install_message_handling(::message::dispatch * pinterface)
{
   ::user::split_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &file_manager_operation_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(MessageMainPost, pinterface, this, &file_manager_operation_view::_001OnMainPostMessage);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &file_manager_operation_view::_001OnDestroy);
}

sp(file_manager_operation_document) file_manager_operation_view::get_document()
{
   return  (::user::impact::get_document());
}

void file_manager_operation_view::_001OnMainPostMessage(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj)
   if(pbase->m_wparam == MessageMainPostFileOperation)
   {
      m_pinfoview->OnFileOperationStep((int32_t) pbase->m_lparam, false);
      m_plistview->OnFileOperationStep((int32_t) pbase->m_lparam, false);
   }
   else if(pbase->m_wparam == MessageMainPostFileOperationFinal)
   {
      m_pinfoview->OnFileOperationStep((int32_t) pbase->m_lparam, true);
      m_plistview->OnFileOperationStep((int32_t) pbase->m_lparam, true);
   }
}

void file_manager_operation_view::_001OnDestroy(signal_details *pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}