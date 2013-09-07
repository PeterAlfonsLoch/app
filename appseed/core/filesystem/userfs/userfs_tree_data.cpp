#include "framework.h"


namespace userfs
{


   tree_data::tree_data(sp(base_application) papp) :
      element(papp),
      ::data::tree_data(papp)
   {
   }


   sp(::core::tree_item_data) tree_data::on_allocate_item()
   {
      return canew(::userfs::tree_item_data());
   }


} // namespace userfs


