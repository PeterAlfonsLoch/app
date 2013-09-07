#include "framework.h"


namespace usermail
{


   tree_data::tree_data(sp(base_application) papp) :
      element(papp),
      ::data::tree_data(papp)
   {



   }


   sp(::data::tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::usermail::tree_item_data());

   }



} // namespace mail


