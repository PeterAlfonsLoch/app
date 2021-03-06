#pragma once


class CLASS_DECL_CORE simple_tree_view :
   virtual public ::user::impact,
   virtual public ::user::tree
{
public:

   
   simple_tree_view(::aura::application * papp);   
   virtual ~simple_tree_view();

   virtual void install_message_handling(::message::dispatch * pinterface);


   DECL_GEN_SIGNAL(_001OnCreate);

   virtual void on_update(::user::impact * pSender,LPARAM lHint,::object* pHint) override;
   
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
