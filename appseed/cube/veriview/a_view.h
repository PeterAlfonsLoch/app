#pragma once

namespace veriview 
{

class CLASS_DECL_CA2_CUBE a_view :
   virtual public ::userbase::split_view
{
public:
   a_view(::ca::application * papp);



   main_document * get_document();
   html::data * m_pdata;

   void CreateViews();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual ~a_view();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   DECL_GEN_SIGNAL(_001OnCreate)
};


} // namespace veriview