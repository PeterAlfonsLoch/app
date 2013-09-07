#pragma once

namespace usermail
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ::data::tree_data
   {
   public:

      
      tree_data(sp(base_application) papp);

      
      virtual sp(::data::tree_item_data) on_allocate_item();
      

   };


} // namespace usermail