#pragma once


class CLASS_DECL_CORE simple_form_list_view :
   virtual public ::user::form_list
{
public:


   simple_list_header_control   m_headerctrl;


   simple_form_list_view(sp(::base::application) papp);
   virtual ~simple_form_list_view();


   virtual bool pre_create_window(::user::create_struct& cs);


   virtual void install_message_handling(::message::dispatch * pinterface);


#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


};


