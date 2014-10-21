#include "framework.h"


namespace filemanager
{


   operation_list_view::operation_list_view(sp(::aura::application) papp):
      element(papp),
      m_headerctrl(papp),

      ::user::scroll_view(papp),
      ::user::list(papp)
   {
         m_dwLast123Update = ::get_tick_count();
         m_pcache = &m_listcache;
         m_pheaderctrl     = &m_headerctrl;
         m_pheaderctrl->SetBaseListCtrlInterface(this);
      }

   void operation_list_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::impact::install_message_handling(pinterface);
      ::user::list::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_TIMER,pinterface,this,&operation_list_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&operation_list_view::_001OnCreate);
   }

   void operation_list_view::OnDraw(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   ::count operation_list_view::_001GetItemCount()
   {
      if(get_document() == NULL)
         return 0;
      return get_document()->m_thread.get_item_count();
   }

   sp(operation_document) operation_list_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_list_view::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 0)
      {
         pitem->m_strText = get_document()->m_thread.get_item_message((int32_t)pitem->m_iItem);
         pitem->m_bOk = true;
      }
      else
      {
         double d;
         d = get_document()->m_thread.get_item_progress((int32_t)pitem->m_iItem);
         pitem->m_strText.Format("%0.1f%%",d * 100.0);
         pitem->m_bOk = true;
      }
   }

   void operation_list_view::_001InsertColumns()
   {
      ::user::list_column column;
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
   void operation_list_view::_001OnInitialUpdate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_dataid = "operation_list_view";
      _001UpdateColumns();
   }


   void operation_list_view::on_update(::user::impact * pSender,LPARAM lHint,object * pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(pHint);
      if(lHint == 123)
      {
         /*if(::get_tick_count() - m_dwLast123Update > 500)
         {
         m_dwLast123Update = ::get_tick_count();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
         }*/

      }
   }

   void operation_list_view::_001OnCreate(signal_details * pobj)
   {
      pobj->previous();
      SetTimer(123,500,NULL);
   }
   void operation_list_view::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer,ptimer,pobj);
      if(ptimer->m_nIDEvent == 123)
      {
         /*if(::get_tick_count() - m_dwLast123Update > 500)
        {
        m_dwLast123Update = ::get_tick_count();
        _001OnUpdateItemCount();
        m_cache._001Invalidate();
        }*/
      }
   }

   void operation_list_view::OnFileOperationStep(int32_t iOperation,bool bFinal)
   {
      UNREFERENCED_PARAMETER(iOperation);
      if(bFinal || ::get_tick_count() - m_dwLast123Update > 184)
      {
         m_dwLast123Update = ::get_tick_count();
         _001OnUpdateItemCount();
         m_listcache._001Invalidate();
         ::count iItem = 0;
         for(int32_t i = 0; i < get_document()->m_thread.m_iOperation; i++)
         {
            iItem += get_document()->m_thread.m_fileoperationa.get_size();
         }
         if(get_document()->m_thread.m_iOperation < get_document()->m_thread.m_fileoperationa.get_size())
         {
            iItem += get_document()->m_thread.m_fileoperationa[get_document()->m_thread.m_iOperation]->m_iFile;
         }
         _001ItemScroll(iItem);
      }
   }


} // namespace filemanager
























