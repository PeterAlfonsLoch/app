#pragma once

class CLASS_DECL_ca simple_list_control :
   virtual public ::user::interaction,
   virtual public ::user::list
{
public:
   simple_list_control(::ca::application * papp);

   simple_list_header_control       m_headerctrl;
   ::user::simple_list_data         m_listctrldata;

   virtual ::user::interaction* OnDrawInterfaceGetWnd();

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void pre_subclass_window();

   bool RemoveItem(int iItem);
   bool RemoveItem(Range & range);
   bool RemoveItem(ItemRange & range);
   void get_data(stringa & stra);
   void set_data(stringa & stra);
   virtual ~simple_list_control();

   virtual void install_message_handling(::gen::message::dispatch * pinterface);
};
