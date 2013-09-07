#include "framework.h"


namespace filehandler
{


   tree_data::tree_data(sp(base_application) papp) :
      element(papp),
      ::data::tree_data(papp)
   {

   }


   sp(::data::tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::filehandler::tree_item_data());

   }

   void tree_data::on_delete_item(sp(::data::tree_item_data) pitem)
   {

   }
   
   
} // namespace filehandler




