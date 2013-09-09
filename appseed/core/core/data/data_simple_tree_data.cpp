#include "framework.h"


namespace data
{


   simple_tree_data::simple_tree_data(sp(base_application) papp) :
      element(papp),
      ::data::tree_data(papp)
   {
   }

   sp(::data::tree_item_data) simple_tree_data::on_allocate_item()
   {
      return canew(simple_tree_item_data);
   }

   void simple_tree_data::on_delete_item(sp(::data::tree_item_data) pitem)
   {

   }


} // namespace data


