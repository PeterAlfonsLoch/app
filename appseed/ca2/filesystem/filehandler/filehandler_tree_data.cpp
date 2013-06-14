#include "framework.h"


namespace filehandler
{


   tree_data::tree_data(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::tree_data(papp)
   {

   }


   sp(::ca2::tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::filehandler::tree_item_data());

   }

   void tree_data::on_delete_item(sp(::ca2::tree_item_data) pitem)
   {

   }
   
   
} // namespace filehandler




