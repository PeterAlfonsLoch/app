#include "framework.h"


namespace mail
{


   tree_data::tree_data(sp(::ca::application) papp) :
      ca(papp),
      ::ca::tree_data(papp)
   {



   }


   sp(::ca::tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::mail::tree_item_data());

   }



} // namespace mail


