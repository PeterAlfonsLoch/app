#include "framework.h"


namespace gen
{


   simple_tree_data::simple_tree_data(::ca::application * papp) :
      ca(papp),
      gen::tree_data(papp)
   {
   }

   gen::tree_item_data * simple_tree_data::on_allocate_item()
   {
      return new simple_tree_item_data;
   }

   void simple_tree_data::on_delete_item(gen::tree_item_data * pitem)
   {
      delete (simple_tree_item_data *) pitem;
   }

   bool simple_tree_data::initialize_data()
   {
      
      if(!gen::tree_data::initialize_data())
         return false;

      return true;

   }

   bool simple_tree_data::finalize_data()
   {
      
      bool bOk = true;

      if(!gen::tree_data::finalize_data())
         bOk = false;

      return bOk;

   }


} // namespace gen


