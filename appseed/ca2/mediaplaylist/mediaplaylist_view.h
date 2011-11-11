#pragma once


namespace mediaplaylist
{

   
   class document;


   class CLASS_DECL_ca view :
      virtual public ::userbase::split_view
   {
   public:


      view(::ca::application * papp);
      virtual ~view();


      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      document * get_document();

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace mediaplaylist