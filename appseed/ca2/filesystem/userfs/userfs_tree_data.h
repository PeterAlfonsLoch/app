#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 tree_data :
      public ::ca2::tree_data
   {
   public:


      tree_data(sp(base_application) papp);


      virtual sp(::ca2::tree_item_data) on_allocate_item();


   };


} // namespace userfs




