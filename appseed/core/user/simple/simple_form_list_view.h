#pragma once


class CLASS_DECL_CORE simple_form_list_view :
   virtual public ::user::form_list_view
{
public:


   simple_list_header_control   m_headerctrl;


   simple_form_list_view(::aura::application * papp);
   virtual ~simple_form_list_view();


   virtual bool pre_create_window(::user::create_struct& cs);


   virtual void install_message_handling(::message::dispatch * pinterface);


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   virtual void _001OnInitialUpdate(signal_details * pobj);

};


