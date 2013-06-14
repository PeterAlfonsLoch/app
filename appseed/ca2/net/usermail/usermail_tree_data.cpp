#include "framework.h"


namespace usermail
{


   tree_data::tree_data(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::tree_data(papp)
   {



   }


   sp(::ca2::tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::usermail::tree_item_data());

   }



} // namespace mail


