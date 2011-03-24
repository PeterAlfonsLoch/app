#include "StdAfx.h"


namespace fs
{


   tree_data::tree_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ex1::tree_data(papp)
   {
   }


   ::ex1::tree_item_data * tree_data::on_allocate_item()
   {
      return new fs::tree_item();
   }

   void tree_data::on_delete_item(::ex1::tree_item_data * pitem)
   {
      delete (fs::tree_item *) pitem;
   }


} // namespace fs


