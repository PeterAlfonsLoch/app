#pragma once

namespace usermail
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ::ca::tree_data
   {
   public:

      
      tree_data(sp(::ca::application) papp);

      
      virtual sp(::ca::tree_item_data) on_allocate_item();
      

   };


} // namespace usermail