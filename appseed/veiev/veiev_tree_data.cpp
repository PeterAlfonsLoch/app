#include "StdAfx.h"


namespace veiev
{


   tree_data::tree_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ex1::tree_data(papp)
   {
   }


   ::ex1::tree_item_data * tree_data::on_allocate_item()
   {
      return new veiev::tree_item();
   }

   void tree_data::on_delete_item(::ex1::tree_item_data * pitem)
   {
      delete (veiev::tree_item *) pitem;
   }


} // namespace veiev