#pragma once


class CLASS_DECL_ca simple_tree_view :
   virtual public ::userbase::view,
   virtual public ::user::tree
{
public:

   simple_scroll_bar             m_scrollbarVert;
   simple_scroll_bar             m_scrollbarHorz;
   
   simple_tree_view(::ca::application * papp);   
   virtual ~simple_tree_view();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


   DECL_GEN_SIGNAL(_001OnCreate)

   
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
