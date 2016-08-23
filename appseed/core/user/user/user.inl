#pragma once


namespace user
{


   template < class VIEW >
   inline VIEW * split_view::create_pane_view(index iPane, id id, ::user::interaction * pviewLast)
   {

      return dynamic_cast <VIEW *> (create_view < VIEW >(get_pane_rect(iPane), get_pane_holder(iPane), id, pviewLast));

   }


} // namespace user



