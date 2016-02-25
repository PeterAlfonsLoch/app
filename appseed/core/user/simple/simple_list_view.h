#pragma once


class CLASS_DECL_CORE simple_list_view :
   virtual public ::user::show < ::user::scroll < ::user::form_list > >
{
public:

   using BASE_TYPE = ::user::show < ::user::scroll < ::user::form_list > >;

   
   simple_list_view(::aura::application * papp);   
   virtual ~simple_list_view();

   virtual void install_message_handling(::message::dispatch * pinterface);

   oswindow GetHandle();
   sp(::user::interaction) OnDrawInterfaceGetWnd();

   virtual void OnDraw(::draw2d::dib * pdib);     
   virtual bool pre_create_window(::user::create_struct& cs);
   
   
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

};




