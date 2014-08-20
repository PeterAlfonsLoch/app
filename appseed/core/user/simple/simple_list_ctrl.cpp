#include "framework.h"

simple_list_control::simple_list_control(sp(::axis::application) papp) :
   element(papp),
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

sp(::user::interaction) simple_list_control::OnDrawInterfaceGetWnd()
{
   return this;
}

bool simple_list_control::pre_create_window(::user::create_struct& cs)
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


bool simple_list_control::remove_item(int32_t iItem)
{
   if(!m_listctrldata.remove_item(iItem))
      return false;
   _001OnUpdateItemCount();
   return true;
}

bool simple_list_control::remove_item(item_range & range)
{
   bool bOk = true;
   for(::index iItem = range.get_upper_bound(); iItem >= range.get_lower_bound(); iItem++)
   {
      if(!m_listctrldata.remove_item(iItem))
         bOk = false;
   }
   _001OnUpdateItemCount();
   return true;
}

bool simple_list_control::remove_item(range & range)
{
   bool bOk = true;
   index_array iaRemove;
   for(::index iRange = 0; iRange < range.get_item_count(); iRange++)
   {
      item_range & itemrange = range.ItemAt(iRange);
      for(::index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
      {
         iaRemove.add_unique(iItem);
      }
   }
   iaRemove.quick_sort(false);
   for(index i = 0; i < iaRemove.get_size(); i++)
   {
      if(!m_listctrldata.remove_item(iaRemove[i]))
         bOk = false;
   }
   _001OnUpdateItemCount();
   return bOk;
}


void simple_list_control::install_message_handling(::message::dispatch * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
}
