#pragma once

class CLASS_DECL_ca simple_form_list_view :
   public ::userbase::view,
   public ::userbase::form_list
{
public:
   simple_form_list_view(::ax::application * papp);

   simple_list_header_control   m_headerctrl;


   
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~simple_form_list_view();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual void install_message_handling(::gen::message::dispatch * pinterface);
   
};
