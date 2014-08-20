#pragma once

class CLASS_DECL_CORE simple_list_control :
   virtual public ::user::interaction,
   virtual public ::user::list
{
public:
   simple_list_control(sp(::axis::application) papp);

   simple_list_header_control       m_headerctrl;
   ::user::simple_list_data         m_listctrldata;

   virtual sp(::user::interaction) OnDrawInterfaceGetWnd();

   virtual bool pre_create_window(::user::create_struct& cs);
   virtual void pre_subclass_window();

   bool remove_item(int32_t iItem);
   bool remove_item(range & range);
   bool remove_item(item_range & range);
   void get_data(stringa & stra);
   void set_data(stringa & stra);
   virtual ~simple_list_control();

   virtual void install_message_handling(::message::dispatch * pinterface);
};
