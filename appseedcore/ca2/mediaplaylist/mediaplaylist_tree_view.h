#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_ca tree_view   :
      virtual public ::userbase::view,
      virtual public ::mediaplaylist::tree_base
   {
   public:




      tree_view(::ca::application * papp);
      virtual ~tree_view();

      
      
      virtual void OnDraw(::ca::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      void _001OnOpenItem(::ex1::tree_item *pdataitem);

      virtual void _001OnItemExpand(::ex1::tree_item * pitem);

      document * get_document();

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   };



} // namespace mediaplaylist