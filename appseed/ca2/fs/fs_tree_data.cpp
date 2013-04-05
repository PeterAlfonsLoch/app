#include "framework.h"


namespace fs
{


   tree_data::tree_data(::ca::applicationsp papp) :
      ca(papp),
      ::ca::tree_data(papp)
   {
   }


   ::ca::tree_item_data * tree_data::on_allocate_item()
   {
      return new ::fs::tree_item();
   }

   void tree_data::on_delete_item(::ca::tree_item_data * pitem)
   {
      delete (::fs::tree_item *) pitem;
   }


} // namespace fs


