#include "StdAfx.h"


// IMPLEMENT_DYNCREATE(file_manager_operation_list_view, ::userbase::view)

file_manager_operation_list_view::file_manager_operation_list_view(::ca::application * papp) :
   ca(papp),
   m_headerctrl(papp),
   m_scrollbarVert(papp),
   m_scrollbarHorz(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp)
{
   m_dwLast123Update = ::GetTickCount();
   m_pcache = &m_cache;
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);
   m_pscrollbarVert  = &m_scrollbarVert;
   m_pscrollbarHorz  = &m_scrollbarHorz;
}

void file_manager_operation_list_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::_001InstallMessageHandling(pinterface);
   ::user::list::_001InstallMessageHandling(pinterface);
   InstallBuffering(pinterface);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &file_manager_operation_list_view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &file_manager_operation_list_view::_001OnCreate);
}

void file_manager_operation_list_view::OnDraw(::ca::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
}

count file_manager_operation_list_view::_001GetItemCount()
{
   if(get_document() == NULL)
      return 0;
   return get_document()->m_thread.get_item_count();
}

file_manager_operation_document * file_manager_operation_list_view::get_document()
{
   return dynamic_cast < file_manager_operation_document * > (::userbase::view::get_document());
}

bool file_manager_operation_list_view::_001GetItemText(
      string  &str,
      INT_PTR iItem,
      INT_PTR iSubItem, 
      INT_PTR iListItem)
{
   UNREFERENCED_PARAMETER(iListItem);
   if(iSubItem == 0)
   {
      str = get_document()->m_thread.get_item_message(iItem);
      return true;
   }
   else
   {
      double d;
      d = get_document()->m_thread.get_item_progress(iItem);
      str.Format("%0.1f%%", d * 100.0);
      return true;
   }
}

void file_manager_operation_list_view::_001InsertColumns()
{
   Column column;
   column.m_iWidth               = 500;
   column.m_iSubItem             = 0;
   column.m_sizeIcon.cx          = 16;
   column.m_sizeIcon.cy          = 16;
   _001AddColumn(column);
   column.m_iWidth               = 500;
   column.m_iSubItem             = 1;
   column.m_sizeIcon.cx          = 16;
   column.m_sizeIcon.cy          = 16;
   _001AddColumn(column);

}
void file_manager_operation_list_view::_001OnInitialUpdate(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   m_dataid = "file_manager_operation_list_view";
   _001UpdateColumns();
}


void file_manager_operation_list_view::on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint)
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(pHint);
   if(lHint == 123)
   {
      /*if(::GetTickCount() - m_dwLast123Update > 500)
      {
         m_dwLast123Update = ::GetTickCount();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
      }*/

   }
}

void file_manager_operation_list_view::_001OnCreate(gen::signal_object * pobj)
{
   pobj->previous();
   SetTimer(123, 500, NULL);
}
void file_manager_operation_list_view::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 123)
   {
       /*if(::GetTickCount() - m_dwLast123Update > 500)
      {
         m_dwLast123Update = ::GetTickCount();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
      }*/
  }
}

void file_manager_operation_list_view::OnFileOperationStep(int iOperation, bool bFinal)
{
   UNREFERENCED_PARAMETER(iOperation);
   if(bFinal || ::GetTickCount() - m_dwLast123Update > 184)
   {
      m_dwLast123Update = ::GetTickCount();
      _001OnUpdateItemCount();
      m_cache._001Invalidate();
      int iItem = 0;
      for(int i = 0; i < get_document()->m_thread.m_iOperation; i++)
      {
         iItem += get_document()->m_thread.m_fileoperationa.get_size();
      }
      if(get_document()->m_thread.m_iOperation < get_document()->m_thread.m_fileoperationa.get_size())
      {
         iItem += get_document()->m_thread.m_fileoperationa[get_document()->m_thread.m_iOperation].m_iFile;
      }
      _001ItemScroll(iItem);
   }
}