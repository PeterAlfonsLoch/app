#pragma once

class CLASS_DECL_ca2 simple_list_view :
   virtual public ::user::view,
   virtual public ::user::form_list
{
public:

   simple_list_header_control    m_headerctrl;
   
   simple_list_view(sp(::ca2::application) papp);   
   virtual ~simple_list_view();

   virtual void install_message_handling(::ca2::message::dispatch * pinterface);

   oswindow GetHandle();
   sp(::user::interaction) OnDrawInterfaceGetWnd();
   virtual sp(::user::interaction) _GetWnd();

   virtual void OnDraw(::draw2d::graphics * pgraphics);     
   virtual bool pre_create_window(CREATESTRUCT& cs);
   
   
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
