#pragma once

namespace querydb
{

   class CLASS_DECL_CA2_QUERYDB menu_right_view :
      public simple_list_view
   {
   public:


      menu_right_view(::ca::application * papp);

      index _001GetItemCount();

      virtual void _001GetItemImage(::user::list_item * plistitem);
      virtual void _001GetItemText(::user::list_item * plistitem);

      void _001OnClick(UINT nFlags, point point) ;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _001InsertColumns();

      void install_message_handling(::user::win::message::dispatch * pinterface);

   };

} // namespace querydb