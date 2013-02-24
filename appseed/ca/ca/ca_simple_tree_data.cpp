#include "framework.h"


namespace ca
{


   simple_tree_data::simple_tree_data(::ca::application * papp) :
      ca(papp),
      ca::tree_data(papp)
   {
   }

   ca::tree_item_data * simple_tree_data::on_allocate_item()
   {
      return new simple_tree_item_data;
   }

   void simple_tree_data::on_delete_item(ca::tree_item_data * pitem)
   {
      delete (simple_tree_item_data *) pitem;
   }

   bool simple_tree_data::initialize_data()
   {
      
      if(!ca::tree_data::initialize_data())
         return false;

      return true;

   }

   bool simple_tree_data::finalize_data()
   {
      
      bool bOk = true;

      if(!ca::tree_data::finalize_data())
         bOk = false;

      return bOk;

   }


} // namespace ca


