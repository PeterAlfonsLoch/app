#pragma once


namespace tesseract
{

namespace mail
{

   class document;

   class CLASS_DECL_CA2_TESSERACT tree :
      virtual public ::userbase::view,
      virtual public ::mail::tree_interface
   {
   public:


      tree(::ca::application * papp);
      virtual ~tree();

      void create_list(::ex1::tree_item * pitemParent = NULL);
      
      virtual void OnDraw(::ca::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      void _001OnOpenItem(::ex1::tree_item *pdataitem);

      virtual void _001OnItemExpand(::ex1::tree_item * pitem);

      document * get_document();

   };

   } // namespace mail


} // namespace tesseract


