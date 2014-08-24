#pragma once

class CLASS_DECL_CORE simple_list_view :
   virtual public ::user::impact,
   virtual public ::user::form_list
{
public:

   simple_list_header_control    m_headerctrl;
   
   simple_list_view(sp(::aura::application) papp);   
   virtual ~simple_list_view();

   virtual void install_message_handling(::message::dispatch * pinterface);

   oswindow GetHandle();
   sp(::user::interaction) OnDrawInterfaceGetWnd();

   virtual void OnDraw(::draw2d::graphics * pgraphics);     
   virtual bool pre_create_window(::user::create_struct& cs);
   
   
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
