#include "StdAfx.h"


namespace ex1
{


   simple_tree_data::simple_tree_data(::ca::application * papp) :
      ca(papp),
      ex1::tree_data(papp),
      data(papp)
   {
   }

   ex1::tree_item_data * simple_tree_data::on_allocate_item()
   {
      return new simple_tree_item_data;
   }

   void simple_tree_data::on_delete_item(ex1::tree_item_data * pitem)
   {
      delete (simple_tree_item_data *) pitem;
   }

   bool simple_tree_data::initialize_data()
   {
      
      if(!ex1::tree_data::initialize_data())
         return false;

      return true;

   }

   bool simple_tree_data::finalize_data()
   {
      
      bool bOk = true;

      if(!ex1::tree_data::finalize_data())
         bOk = false;

      return bOk;

   }


} // namespace ex1


