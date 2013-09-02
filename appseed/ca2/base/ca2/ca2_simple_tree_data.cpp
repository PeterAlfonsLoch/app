#include "framework.h"


namespace ca2
{


   simple_tree_data::simple_tree_data(sp(::application) papp) :
      element(papp),
      ::ca2::tree_data(papp)
   {
   }

   sp(::ca2::tree_item_data) simple_tree_data::on_allocate_item()
   {
      return canew(simple_tree_item_data);
   }

   void simple_tree_data::on_delete_item(sp(::ca2::tree_item_data) pitem)
   {

   }


} // namespace ca2


