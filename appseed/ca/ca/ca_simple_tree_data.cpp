#include "framework.h"


namespace ca
{


   simple_tree_data::simple_tree_data(sp(::ca::application) papp) :
      ca(papp),
      ::ca::tree_data(papp)
   {
   }

   sp(::ca::tree_item_data) simple_tree_data::on_allocate_item()
   {
      return canew(simple_tree_item_data);
   }

   void simple_tree_data::on_delete_item(sp(::ca::tree_item_data) pitem)
   {

   }


} // namespace ca


