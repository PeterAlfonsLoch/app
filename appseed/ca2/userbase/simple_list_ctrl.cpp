#include "framework.h"

simple_list_control::simple_list_control(::ca::application * papp) :
   ca(papp),
   m_headerctrl(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   m_listctrldata(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);
   SetDataInterface(&m_listctrldata);
}

simple_list_control::~simple_list_control()
{
}

::user::interaction* simple_list_control::OnDrawInterfaceGetWnd()
{
   return this;
}

bool simple_list_control::pre_create_window(CREATESTRUCT& cs)
{

   cs.style |= WS_CLIPCHILDREN;

   return ::user::interaction::pre_create_window(cs);
}

void simple_list_control::set_data(stringa &stra)
{
   m_listctrldata.set_data(this, stra);
}

void simple_list_control::get_data(stringa &stra)
{
   m_listctrldata.get_data(stra);
}

void simple_list_control::pre_subclass_window()
{
   PreSubClassWindow();

   if(!CreateHeaderCtrl())
   {
      return;
   }


   ::user::interaction::pre_subclass_window();


}


bool simple_list_control::RemoveItem(int32_t iItem)
{
   if(!m_listctrldata.RemoveItem(iItem))
      return false;
   _001OnUpdateItemCount();
   return true;
}

bool simple_list_control::RemoveItem(ItemRange & range)
{
   bool bOk = true;
   for(::index iItem = range.GetUBound(); iItem >= range.GetLBound(); iItem++)
   {
      if(!m_listctrldata.RemoveItem(iItem))
         bOk = false;
   }
   _001OnUpdateItemCount();
   return true;
}

bool simple_list_control::RemoveItem(Range & range)
{
   bool bOk = true;
   index_array iaRemove;
   for(::index iRange = 0; iRange < range.get_item_count(); iRange++)
   {
      ItemRange & itemrange = range.ItemAt(iRange);
      for(::index iItem = itemrange.GetLBound(); iItem <= itemrange.GetUBound(); iItem++)
      {
         iaRemove.add_unique(iItem);
      }
   }
   iaRemove.QuickSort(false);
   for(index i = 0; i < iaRemove.get_size(); i++)
   {
      if(!m_listctrldata.RemoveItem(iaRemove[i]))
         bOk = false;
   }
   _001OnUpdateItemCount();
   return bOk;
}


void simple_list_control::install_message_handling(::ca::message::dispatch * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
}
