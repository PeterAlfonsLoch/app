#pragma once

class CLASS_DECL_ca2 simple_list_view :
   virtual public ::userbase::view,
   virtual public ::userbase::form_list
{
public:

   simple_list_header_control    m_headerctrl;
   
   simple_list_view(::ca::application * papp);   
   virtual ~simple_list_view();

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   HWND GetHandle();
   ::user::interaction* OnDrawInterfaceGetWnd();
   virtual ::user::interaction* _GetWnd();

   virtual void OnDraw(::ca::graphics * pgraphics);     
   virtual bool pre_create_window(CREATESTRUCT& cs);
   
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
